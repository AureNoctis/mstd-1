#ifndef MSTD_H
#define MSTD_H

// ----------------------------------------------------------------------------
// INTERFACE
// ----------------------------------------------------------------------------

#include "base/mstd_base.h"
#include "base/mstd_memory.h"
#include "os/mstd_os.h"

// ----------------------------------------------------------------------------
// IMPLEMENTATION
// ----------------------------------------------------------------------------

#if defined(MSTD_IMPLEMENTATION)

#include "base/mstd_memory.c"

#if defined(OS_WINDOWS)
    #include "os/core/mstd_os_win32.c"
#endif

#endif // MSTD_IMPLEMENTATION
#endif // MSTD_H