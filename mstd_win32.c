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

function Str8 os_file_read(Arena* arena, Str8 file_name) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 file_name_w32 = str16_from_8(scratch.arena, file_name);
    HANDLE file = CreateFileW((WCHAR*)file_name_w32.c_str, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    Str8 result = { 0 };
    if (file != INVALID_HANDLE_VALUE) {
        DWORD hi_size = 0;
        DWORD lo_size = GetFileSize(file, &hi_size);
        u64 size = ((u64)hi_size << 32) | (u64)lo_size;

        arena_temp(arena) {
            Str8 buffer = str8_of_size(arena, size);
            u8* ptr = buffer.c_str;
            u8* opl = buffer.c_str + size;
            b32 success = 1;
            for (;ptr < opl;) {
                u64 total_to_read = (u64)(opl - ptr);
                DWORD to_read = (DWORD)clamp_top(total_to_read, UINT32_MAX);
                DWORD actual_read = 0;
                if (!ReadFile(file, ptr, to_read, &actual_read, 0)) {
                    success = 0;
                    break;
                }
                ptr += actual_read;
            }
            if (success) {
                result = buffer;
            }
        }
        CloseHandle(file);
    }
    arena_scratch_end(scratch);
    return result;
}

function b32 os_file_write(Str8List* first_node, Str8 file_name) {
    ArenaScratch scratch = arena_scratch_begin();
    Str16 file_name_w32 = str16_from_8(scratch.arena, file_name);
    HANDLE file = CreateFileW((WCHAR*)file_name_w32.c_str, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    b32 result = 0;

    if (file != INVALID_HANDLE_VALUE) {
        result = 1;
        for (Str8List* node = first_node; node != NULL; node = node->next) {
            u8* ptr = node->str8_node.c_str;
            u8* opl = ptr + node->str8_node.size;

            for (;ptr < opl;) {
                u64 total_to_write = (u64)(opl - ptr);
                DWORD to_write = (DWORD)clamp_top(total_to_write, UINT32_MAX);
                DWORD actual_write = 0;
                if (!WriteFile(file, ptr, to_write, &actual_write, 0)) {
                    result = 0;
                    goto dblbreak;
                }
                ptr += actual_write;
            }
        }
    dblbreak:
        CloseHandle(file);
    }

    arena_scratch_end(scratch);
    return result;
}
