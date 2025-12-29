#include "mstd.h"

#include <Windows.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "Advapi32")

typedef struct Win32_State Win32_State;
struct Win32_State {
    Arena* arena;
    OS_SystemInfo system_info;
    OS_ProcessInfo process_info;
    usize micro_second_resolution;
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
    if(QueryPerformanceCounter(&resolution))
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
    if(!win32_state_is_initialized)
        win32_state_init();

    return &win32_state.system_info;
}

function OS_ProcessInfo* os_get_process_info() {
    if(!win32_state_is_initialized)
        win32_state_init();

    return &win32_state.process_info;
}

function void* os_reserve(usize size) {
    void* result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
    return result;
}

function void* os_reserve_large(usize size) {
    void* result = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
    return result;
}

function b8 os_commit(void* ptr, usize size) {
    b8 result = (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != NULL);
    return result;
}

function b8 os_commit_large(void* ptr, usize size) {
    return 1;
}

function void os_decommit(void* ptr, usize size) {
    VirtualFree(ptr, size, MEM_DECOMMIT);
}

function void os_release(void* ptr, usize size) {
    VirtualFree(ptr, 0, MEM_RELEASE);
}