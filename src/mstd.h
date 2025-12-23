#ifndef MSTD_H
#define MSTD_H

// ----------------------------------------------------------------------------
// INTERFACE
// ----------------------------------------------------------------------------

#include "core/mstd_base.h"
#include "core/mstd_memory.h"
#include "core/mstd_os.h"

// ----------------------------------------------------------------------------
// IMPLEMENTATION
// ----------------------------------------------------------------------------

#if defined(MSTD_IMPLEMENTATION)

#include "core/mstd_memory.cpp"

#if defined(OS_WINDOWS)
    #include "core/mstd_os_win32.cpp"
#endif

#endif // MSTD_IMPLEMENTATION
#endif // MSTD_H