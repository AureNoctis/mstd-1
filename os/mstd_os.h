#if !defined(MSTD_OS_H)
#define MSTD_OS_H
#include "base/mstd_base.h"

////////////////////////////////
// Memory

u64 os_get_page_size();
u64 os_get_large_page_size();
void* os_reserve(u64 size);
void* os_reserve_large(u64 size);
b8 os_commit(void* ptr, u64 size);
b8 os_commit_large(void* ptr, u64 size);
void os_decommit(void* ptr, u64 size);
void os_release(void* ptr, u64 size);

////////////////////////////////
// File system



////////////////////////////////
// Time

#endif // MSTD_OS_H