#include <Windows.h>
#include <direct.h>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "advapi32")

typedef struct OS_Win32_State OS_Win32_State;
struct OS_Win32_State {
    Arena* arena;
    OS_SystemInfo system_info;
    OS_ProcessInfo process_info;
    u64 resolution_us;
    f64 inverse_ticks_per_us;
};

global OS_Win32_State os_win32_state;

 void os_init_state() {

    u32 large_pages_allowed = 0;

    {
        HANDLE token;
        if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token))
        {
            LUID luid;
            if (LookupPrivilegeValue(0, SE_LOCK_MEMORY_NAME, &luid))
            {
                TOKEN_PRIVILEGES priv;
                priv.PrivilegeCount = 1;
                priv.Privileges[0].Luid = luid;
                priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                large_pages_allowed = !!AdjustTokenPrivileges(token, 0, &priv, sizeof(priv), 0, 0);
            }
            CloseHandle(token);
        }
    }

    os_win32_state.resolution_us = 1;
    LARGE_INTEGER resolution;
    if (QueryPerformanceFrequency(&resolution))
        os_win32_state.resolution_us = resolution.QuadPart;

    os_win32_state.inverse_ticks_per_us = 1000000.0 / (f64)resolution.QuadPart;

    os_win32_state.process_info.large_pages_allowed = large_pages_allowed;
    os_win32_state.process_info.id = GetCurrentProcessId();

    SYSTEM_INFO sysinfo = { 0 };
    GetSystemInfo(&sysinfo);
    os_win32_state.system_info.page_size = sysinfo.dwPageSize;
    os_win32_state.system_info.large_page_size = GetLargePageMinimum();
    os_win32_state.system_info.logical_processor_count = sysinfo.dwNumberOfProcessors;
    os_win32_state.system_info.allocation_granularity = sysinfo.dwAllocationGranularity;

    os_win32_state.arena = arena_alloc(ARENA_DEFAULT_RESERVE_SIZE, 0);
    u8 cwd[1024];
    debug_validate(_getcwd((char*)cwd, sizeof(cwd)));
    os_win32_state.process_info.current_working_directory = str8_copy(os_win32_state.arena, str8(cwd));

}

OS_SystemInfo* os_get_system_info() {
    return &os_win32_state.system_info;
}

OS_ProcessInfo* os_get_process_info() {
    return &os_win32_state.process_info;
}

u64 os_get_resolution_us() {
    return os_win32_state.resolution_us;
}

f64 os_get_inverse_ticks_per_us() {
    return os_win32_state.inverse_ticks_per_us;
}

OS_Handle os_load_lib(char* name) {
    OS_Handle handle;
    handle.val[0] = (u64)LoadLibraryA(name);
    return handle;
}

void* os_load_symbol(OS_Handle lib, char* name) {
    return (void*)GetProcAddress((HMODULE)lib.val[0], name);
}

void os_attach_console_if_exists() {
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        FILE* dummy;
        freopen_s(&dummy, "CONOUT$", "w", stdout);
        freopen_s(&dummy, "CONOUT$", "w", stderr);
        freopen_s(&dummy, "CONIN$", "r", stdin);

        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
    }
}

void* os_reserve(u64 size, u32 large_pages) {
    void* result = (large_pages) ? VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE)
        : VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
    return result;
}

u8 os_commit(void* ptr, u64 size, u32 large_pages) {
    u8 result = (large_pages) ? 1 : (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != NULL);
    return result;
}

void os_decommit(void* ptr, u64 size) {
    VirtualFree(ptr, size, MEM_DECOMMIT);
}

void os_release(void* ptr, u64 size) {
    (void)size;
    VirtualFree(ptr, 0, MEM_RELEASE);
}

OS_Handle os_file_open(OS_AccessFlag flags, Str8 path) {
    OS_Handle result = { 0 };
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DWORD access_flags = 0;
    DWORD share_mode = 0;
    DWORD creation_disposition = OPEN_EXISTING;

    if (flags & OS_ACCESS_FLAG_READ)        { access_flags |= GENERIC_READ; }
    if (flags & OS_ACCESS_FLAG_WRITE)       { access_flags |= GENERIC_WRITE; creation_disposition = CREATE_ALWAYS; }
    if (flags & OS_ACCESS_FLAG_EXECUTE)     { access_flags |= GENERIC_EXECUTE; }
    if (flags & OS_ACCESS_FLAG_SHARE_READ)  { share_mode |= FILE_SHARE_READ; }
    if (flags & OS_ACCESS_FLAG_SHARE_WRITE) { share_mode |= FILE_SHARE_WRITE | FILE_SHARE_DELETE; }
    if (flags & OS_ACCESS_FLAG_APPEND)      { access_flags &= ~GENERIC_WRITE; access_flags |= FILE_APPEND_DATA; creation_disposition = OPEN_ALWAYS;}

    HANDLE file = CreateFile((WCHAR*)path_w32.data, access_flags, share_mode, 0, creation_disposition, FILE_ATTRIBUTE_NORMAL, 0);
    if (file != INVALID_HANDLE_VALUE)
        result.val[0] = (u64)file;
    arena_scratch_end(scratch);
    return result;
}

void os_file_close(OS_Handle handle) {
    if (handle.val[0])
        CloseHandle((HANDLE)handle.val[0]);
}

u64 os_file_read(OS_Handle handle, u64 begin, u64 end, void* out_data) {
    u64 total_read_size = 0;

    if (handle.val[0]) {
        HANDLE file = (HANDLE)handle.val[0];
        u64 size = 0;
        GetFileSizeEx(file, (LARGE_INTEGER*)&size);

        u64 begin_clamped = clamp_top(begin, size);
        u64 end_clamped = clamp_top(end, size);
        u64 total_to_read = (end_clamped > begin_clamped) ? end_clamped - begin_clamped : 0;

        for (u64 offset = begin_clamped; total_read_size < total_to_read; ) {
            u64 remaining = total_to_read - total_read_size;
            DWORD to_read = (DWORD)clamp_top(remaining, UINT32_MAX);
            DWORD actual_read = 0;

            OVERLAPPED overlapped = { 0 };
            overlapped.Offset = (DWORD)(offset & UINT32_MAX);
            overlapped.OffsetHigh = (DWORD)(offset >> 32);

            ReadFile(file, (u8*)out_data + total_read_size, to_read, &actual_read, &overlapped);
            offset += actual_read;
            total_read_size += actual_read;

            if (actual_read != to_read)
                break;
        }
    }

    return total_read_size;
}

u64 os_file_write(OS_Handle handle, u64 begin, u64 end, void* data) {
    u64 total_written = 0;

    if (handle.val[0] && end > begin) {
        HANDLE file = (HANDLE)handle.val[0];
        u64 total_to_write = (end > begin) ? end - begin : 0;
        u64 dest_offset = begin;
        for (;;) {
            u64 remaining = total_to_write - total_written;
            if (remaining == 0) break;
            DWORD to_write = (DWORD)clamp_top(remaining, MB(1));
            DWORD actual_write = 0;

            OVERLAPPED overlapped = { 0 };
            overlapped.Offset = (DWORD)(dest_offset & 0xFFFFFFFF);
            overlapped.OffsetHigh = (DWORD)(dest_offset >> 32);

            if (!WriteFile(file, (u8*)data + total_written, to_write, &actual_write, &overlapped))
                break;
            total_written += actual_write;
            dest_offset += actual_write;

            if (remaining == 0)
                break;
        }
    }

    return total_written;
}

u64 os_file_get_size(OS_Handle handle) {
    u64 size = 0;
    GetFileSizeEx((HANDLE)handle.val[0], (LARGE_INTEGER*)&size);
    return size;
}

void os_file_delete(Str8 path) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DeleteFileW((WCHAR*)path_w32.data);
    arena_scratch_end(scratch);
}

void os_file_copy(Str8 src, Str8 dest) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 src_w32 = str16_from_8(scratch.arena, dest);
    Str16 dest_w32 = str16_from_8(scratch.arena, src);
    CopyFileW((WCHAR*)src_w32.data, (WCHAR*)dest_w32.data, 0);
    arena_scratch_end(scratch);
}

void os_file_move(Str8 src, Str8 dest) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 src_w32 = str16_from_8(scratch.arena, dest);
    Str16 dest_w32 = str16_from_8(scratch.arena, src);
    MoveFileW((WCHAR*)src_w32.data, (WCHAR*)dest_w32.data);
    arena_scratch_end(scratch);
}

u32 os_file_path_exists(Str8 path) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DWORD attributes = GetFileAttributesW((WCHAR*)path_w32.data);
    u32 exists = (attributes != INVALID_FILE_ATTRIBUTES) && !!(~attributes & FILE_ATTRIBUTE_DIRECTORY);
    arena_scratch_end(scratch);
    return exists;
}

u32 os_file_directory_exists(Str8 path) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DWORD attributes = GetFileAttributesW((WCHAR*)path_w32.data);
    u32 exists = (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_DIRECTORY);
    arena_scratch_end(scratch);
    return exists;
}

typedef struct OS_Win32_FileWatcher OS_Win32_FileWatcher;
struct OS_Win32_FileWatcher {
    Arena* arena;
    HANDLE dir_handle;
    HANDLE iocp;
    u8 notification_buffer[KB(4)];
    u32 scan_sub_tree;
    OVERLAPPED overlapped;
};

OS_FileWatcher* os_file_watcher_create(Arena* arena, Str8 path, u32 watch_sub_directory) {
    Str16 u16_path = str16_from_8(arena, path);

    HANDLE dir = CreateFileW(u16_path.data, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                             NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

    if (dir == INVALID_HANDLE_VALUE)
        return NULL;

    OS_Win32_FileWatcher* watcher = arena_push_struct(arena, OS_Win32_FileWatcher);
    mem_zero_struct(watcher);
    watcher->arena = arena;
    watcher->scan_sub_tree = watch_sub_directory;
    watcher->dir_handle = dir;
    watcher->iocp = CreateIoCompletionPort(watcher->dir_handle, NULL, 0, 1);

    mem_zero_struct(&watcher->overlapped);
    debug_trap_code_if(ReadDirectoryChangesW(watcher->dir_handle,
                                         watcher->notification_buffer,
                                         sizeof(watcher->notification_buffer),
                                         watcher->scan_sub_tree,
                                         FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME,
                                         NULL, &watcher->overlapped, NULL), ==, 0);
    return(watcher);
}

u32 os_file_watcher_poll_event(OS_FileWatcher* watcher, u32 timeout_ms, OS_FileEventType* type, Str8* file) {
    OS_Win32_FileWatcher* win32_watcher = (OS_Win32_FileWatcher*)watcher;
    DWORD bytes = 0;
    ULONG_PTR key = 0;
    LPOVERLAPPED p_overlapped = NULL;

    if (GetQueuedCompletionStatus(win32_watcher->iocp, &bytes, &key, &p_overlapped, (DWORD)timeout_ms)) {

        if (p_overlapped == &win32_watcher->overlapped && bytes > 0) {
            FILE_NOTIFY_INFORMATION* notify = (FILE_NOTIFY_INFORMATION*)win32_watcher->notification_buffer;

            for (;;) {
                u32 name_len_chars = notify->FileNameLength / sizeof(WCHAR);
                Str16 u16_file = {0};
                u16_file.data = notify->FileName;
                u16_file.size = name_len_chars;

                if (name_len_chars > 0) {
                     WCHAR last_char = u16_file.data[name_len_chars - 1];
                     if (last_char == L'c' || last_char == L'h') {
                        Str8 u8_file = str8_from_16(win32_watcher->arena, u16_file);

                        if (file)
                             file->data = u8_file.data;
                             file->size = u8_file.size;

                        if (type)
                            *type = OS_FILE_EVENT_TYPE_MODIFIED;

                        goto reissue_watch;
                     }
                }

                if (notify->NextEntryOffset == 0) break;
                notify = (FILE_NOTIFY_INFORMATION*)((u8*)notify + notify->NextEntryOffset);
            }
        }

reissue_watch:
        mem_zero_struct(&win32_watcher->overlapped);
        ReadDirectoryChangesW(win32_watcher->dir_handle, win32_watcher->notification_buffer, sizeof(win32_watcher->notification_buffer),
                              win32_watcher->scan_sub_tree, FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME, NULL,
                              &win32_watcher->overlapped, NULL);

        if (file->data != 0)
            return 1;
    }

    return 0;
}

void os_file_watcher_destroy(OS_FileWatcher* watcher) {
    OS_Win32_FileWatcher* win32_watcher = (OS_Win32_FileWatcher*)watcher;
    debug_validate(win32_watcher);
    CloseHandle(win32_watcher->iocp);
    CloseHandle(win32_watcher->dir_handle);
    win32_watcher = 0;
}

u64 os_get_ticks() {
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (u64)(counter.QuadPart);
}