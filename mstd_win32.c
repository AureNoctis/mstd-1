#include "mstd.h"

#include <Windows.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "Advapi32")

typedef struct Win32_State Win32_State;
struct Win32_State {
    Arena* arena;
    OS_SystemInfo system_info;
    OS_ProcessInfo process_info;
    u64 micro_second_resolution;
};

global Win32_State win32_state;
global b8 win32_state_is_initialized;

function void win32_state_init() {

    b32 large_pages_allowed = 0;

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

    win32_state.micro_second_resolution = 1;
    LARGE_INTEGER resolution;
    if (QueryPerformanceCounter(&resolution))
        win32_state.micro_second_resolution = resolution.QuadPart;

    win32_state.process_info.large_pages_allowed = large_pages_allowed;
    win32_state.process_info.id = GetCurrentProcessId();

    SYSTEM_INFO sysinfo = { 0 };
    GetSystemInfo(&sysinfo);
    win32_state.system_info.page_size = sysinfo.dwPageSize;
    win32_state.system_info.large_page_size = GetLargePageMinimum();
    win32_state.system_info.logical_processor_count = sysinfo.dwNumberOfProcessors;
    win32_state.system_info.allocation_granularity = sysinfo.dwAllocationGranularity;

    win32_state_is_initialized = 1;
}

function OS_SystemInfo* os_get_system_info() {
    if (!win32_state_is_initialized)
        win32_state_init();

    return &win32_state.system_info;
}

function OS_ProcessInfo* os_get_process_info() {
    if (!win32_state_is_initialized)
        win32_state_init();

    return &win32_state.process_info;
}

function u64 os_get_micro_second_resolution(void) {
    if (!win32_state_is_initialized)
        win32_state_init();
    return win32_state.micro_second_resolution;
}

function void* os_reserve(u64 size) {
    void* result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
    return result;
}

function void* os_reserve_large(u64 size) {
    void* result = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
    return result;
}

function b8 os_commit(void* ptr, u64 size) {
    b8 result = (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != NULL);
    return result;
}

function b8 os_commit_large(void* ptr, u64 size) {
    return 1;
}

function void os_decommit(void* ptr, u64 size) {
    VirtualFree(ptr, size, MEM_DECOMMIT);
}

function void os_release(void* ptr, u64 size) {
    VirtualFree(ptr, 0, MEM_RELEASE);
}

function OS_Handle os_file_open(OS_AccessFlag flags, Str8 path) {
    OS_Handle result = {0};
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DWORD access_flags = 0;
    DWORD share_mode = 0;
    DWORD creation_disposition = OPEN_EXISTING;

    if (flags & os_access_flag_read)        { access_flags |= GENERIC_READ; }
    if (flags & os_access_flag_write)       { access_flags |= GENERIC_WRITE; creation_disposition = CREATE_ALWAYS; }
    if (flags & os_access_flag_execute)     { access_flags |= GENERIC_EXECUTE; }
    if (flags & os_access_flag_share_read)  { share_mode |= FILE_SHARE_READ; }
    if (flags & os_access_flag_share_write) { share_mode |= FILE_SHARE_WRITE | FILE_SHARE_DELETE; }
    if (flags & os_access_flag_share_write) { creation_disposition |= OPEN_ALWAYS; access_flags |= FILE_APPEND_DATA; }

    HANDLE file = CreateFileW((WCHAR*)path_w32.data, access_flags, share_mode, 0, creation_disposition, FILE_ATTRIBUTE_NORMAL, 0);
    if (file != INVALID_HANDLE_VALUE)
        result.val[0] = (u64)file;
    arena_scratch_end(scratch);
    return result;
}

function void os_file_close(OS_Handle handle) {
    if(handle.val[0])
        CloseHandle((HANDLE)handle.val[0]);
}

function u64 os_file_read(OS_Handle handle, u64 begin, u64 end, void* out_data) {
    u64 total_read_size = 0;

    if (handle.val[0]) {
        HANDLE file = (HANDLE)handle.val[0];
        u64 size = 0;
        GetFileSizeEx(file, (LARGE_INTEGER*)&size);

        u64 begin_clamped = clamp_top(begin, size);
        u64 end_clamped   = clamp_top(end, size);
        u64 total_to_read = (end_clamped > begin_clamped) ? end_clamped - begin_clamped : 0;

        for (u64 offset = begin_clamped; total_read_size < total_to_read; ) {
            u64 remaining = total_to_read - total_read_size;
            DWORD to_read = (DWORD)clamp_top(remaining, UINT32_MAX);
            DWORD actual_read = 0;

            OVERLAPPED overlapped = {0};
            overlapped.Offset     = (DWORD)(offset & UINT32_MAX);
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

function u64 os_file_write(OS_Handle handle, u64 begin, u64 end, void* data) {
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

            OVERLAPPED overlapped = {0};
            overlapped.Offset     = (DWORD)(dest_offset & 0xFFFFFFFF);
            overlapped.OffsetHigh = (DWORD)(dest_offset >> 32);

            if(!WriteFile(file, (u8*)data + total_written, to_write, &actual_write, &overlapped))
                break;
            total_written += actual_write;
            dest_offset   += actual_write;

            if(remaining == 0)
                break;
        }
    }

    return total_written;
}

function u64 os_file_get_size(OS_Handle handle) {
    u64 size = 0;
    GetFileSizeEx(handle.val[0], (LARGE_INTEGER*)&size);
    return size;
}

function void os_file_delete(Str8 path) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DeleteFileW((WCHAR*)path_w32.data);
    arena_scratch_end(scratch);
}

function void os_file_copy(Str8 src, Str8 dest) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 src_w32 = str16_from_8(scratch.arena, dest);
    Str16 dest_w32 = str16_from_8(scratch.arena, src);
    CopyFileW((WCHAR*)src_w32.data,(WCHAR*)dest_w32.data, 0);
    arena_scratch_end(scratch);
}

function void os_file_move(Str8 src, Str8 dest) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 src_w32 = str16_from_8(scratch.arena, dest);
    Str16 dest_w32 = str16_from_8(scratch.arena, src);
    MoveFileW((WCHAR*)src_w32.data,(WCHAR*)dest_w32.data);
    arena_scratch_end(scratch);
}

function b32 os_file_path_exists(Str8 path) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DWORD attributes = GetFileAttributesW((WCHAR *)path_w32.data);
    b32 exists = (attributes != INVALID_FILE_ATTRIBUTES) && !!(~attributes & FILE_ATTRIBUTE_DIRECTORY);
    arena_scratch_end(scratch);
    return exists;
}

function b32 os_file_directory_exists(Str8 path) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 path_w32 = str16_from_8(scratch.arena, path);
    DWORD attributes = GetFileAttributesW((WCHAR *)path_w32.data);
    b32 exists = (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_DIRECTORY);
    arena_scratch_end(scratch);
    return exists;
}

function u64 os_now_microseconds(void) {
    u64 result = 0;
    LARGE_INTEGER counter;
    if(QueryPerformanceCounter(&counter))
        result = (counter.QuadPart*Million(1))/os_get_micro_second_resolution();
    return result;
}

// function Buffer os_file_read(Arena* arena, Str8 file_name) {
//     ArenaScratch scratch = arena_scratch_begin();
//     Str16 file_name_w32 = str16_from_8(scratch.arena, file_name);
//     HANDLE file = CreateFileW((WCHAR*)file_name_w32.data, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//     Buffer result = { 0 };
//     if (file != INVALID_HANDLE_VALUE) {
//         DWORD hi_size = 0;
//         DWORD lo_size = GetFileSize(file, &hi_size);
//         u64 size = ((u64)hi_size << 32) | (u64)lo_size;

//         arena_temp(arena) {

//             Buffer buffer;
//             buffer.data = arena_push_array(arena, u8, size + 1);
//             buffer.size = size;
//             buffer.data[buffer.size] = 0;

//             u8* ptr = buffer.data;
//             u8* opl = buffer.data + size;
//             b32 success = 1;
//             for (;ptr < opl;) {
//                 u64 total_to_read = (u64)(opl - ptr);
//                 DWORD to_read = (DWORD)clamp_top(total_to_read, UINT32_MAX);
//                 DWORD actual_read = 0;
//                 if (!ReadFile(file, ptr, to_read, &actual_read, 0)) {
//                     success = 0;
//                     break;
//                 }
//                 ptr += actual_read;
//             }
//             if (success) {
//                 result = buffer;
//             }
//         }
//         CloseHandle(file);
//     }
//     arena_scratch_end(scratch);
//     return result;
// }

// function b32 os_file_write(BufferList* first_node, Str8 file_name) {
//     ArenaScratch scratch = arena_scratch_begin();
//     Str16 file_name_w32 = str16_from_8(scratch.arena, file_name);

//     HANDLE file = CreateFileW((WCHAR*)file_name_w32.data,
//                               GENERIC_WRITE,
//                               FILE_SHARE_READ,
//                               0,
//                               CREATE_ALWAYS,
//                               FILE_ATTRIBUTE_NORMAL,
//                               0);

//     b32 result = (file != INVALID_HANDLE_VALUE);
//     if (result) {
//         for (BufferList* node = first_node; node != NULL; node = node->next) {
//             u8* ptr = node->buffer.data;
//             u8* opl = ptr + node->buffer.size;

//             for (;ptr < opl;) {
//                 u64 total_to_write = (u64)(opl - ptr);
//                 DWORD to_write = (DWORD)clamp_top(total_to_write, UINT32_MAX);
//                 DWORD actual_write = 0;
//                 if (!WriteFile(file, ptr, to_write, &actual_write, 0)) {
//                     result = 0;
//                     goto dblbreak;
//                 }
//                 ptr += actual_write;
//             }
//         }
//     dblbreak:
//         CloseHandle(file);
//     }

//     arena_scratch_end(scratch);
//     return result;
// }
