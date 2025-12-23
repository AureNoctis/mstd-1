#if !defined(MSTD_BASE_H)
#define MSTD_BASE_H

////////////////////////////////
// Compilers

#define COMPILER_MSVC    0
#define COMPILER_CLANG   0
#define COMPILER_GCC     0

#if defined(_MSC_VER)
#  undef  COMPILER_MSVC
#  define COMPILER_MSVC  1
#elif defined(__clang__)
#  undef  COMPILER_CLANG
#  define COMPILER_CLANG 1
#elif defined(__GNUC__)
#  undef  COMPILER_GCC
#  define COMPILER_GCC   1
#else
#  error "Unknown Compiler"
#endif

////////////////////////////////
// Operating Systems

#define OS_WINDOWS 0
#define OS_LINUX   0
#define OS_MAC     0

#if defined(_WIN32)
#  undef  OS_WINDOWS
#  define OS_WINDOWS 1
#elif defined(__linux__)
#  undef  OS_LINUX
#  define OS_LINUX   1
#elif defined(__APPLE__) && defined(__MACH__)
#  undef  OS_MAC
#  define OS_MAC     1
#else
#  error "Unknown Operating System"
#endif

////////////////////////////////
// Architectures

#define ARCH_X64   0
#define ARCH_X86   0
#define ARCH_ARM   0
#define ARCH_ARM64 0

#if defined(_M_AMD64) || defined(__amd64__) || defined(__x86_64__)
#  undef  ARCH_X64
#  define ARCH_X64   1
#elif defined(_M_IX86) || defined(__i386__)
#  undef  ARCH_X86
#  define ARCH_X86   1
#elif defined(__aarch64__) || defined(_M_ARM64)
#  undef  ARCH_ARM64
#  define ARCH_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#  undef  ARCH_ARM
#  define ARCH_ARM   1
#else
#  error "Unknown Architecture"
#endif

////////////////////////////////
// Misc

#if !defined(MSTD_DEBUG)
#define MSTD_DEBUG
#endif

#if !defined(ENABLE_ASSERTS)
#define ENABLE_ASSERTS
#endif

#define global_variable static
#define internal        static
#define local_persist   static

////////////////////////////////
// Basic Types

#include <stdint.h>
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;
typedef float f32;
typedef double f64;

typedef intptr_t iaddress;
typedef uintptr_t uaddress;

////////////////////////////////
// Helper Macros

#if !defined(mstd_assert_break)
    #define mstd_assert_break() (*(int*)0 = 0)
#endif

#ifdef ENABLE_ASSERTS
    #define mstd_assert(c) do { if(!(c)) mstd_assert_break(); } while(0);
#else
    #define mstd_assert(c)
#endif

#define mstd_static_assert(C, ID) global U8 Glue(ID, __LINE__)[(C)?1:-1]

#define _stringify(S) #S
#define stringify(S) _stringify(S)

#define _concat(a, b) a##b
#define concat(a,b) _concat(a,b)

// #define uaddress_from_ptr(p) (unsigned long long)((char*)p - (char*)0)
// #define ptr_from_uaddress(n) (void*)((char*)0 + n)

#define member(T, m) (((T*)0)->m)
#define offset_of_member(T, m) (uaddress)(&member(T,m))

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define clamp(val, low, high) (max(low, min(val, high)))

#define clamp_top(val, high)    min(val, high)
#define clamp_bottom(val, low)  max(val, low)

#define c_linkage_begin extern "C"{
#define c_linkage_end }
#define c_linkage extern "C"

////////////////////////////////
// Math

#include <math.h>

#define inf_f32     ((f32)INFINITY)
#define neg_inf_f32 (-(f32)INFINITY)
#define inf_f64     ((f64)INFINITY)
#define neg_inf_f64 (-(f64)INFINITY)

#define f32_sin(x)   sinf(x)
#define f32_cos(x)   cosf(x)
#define f32_tan(x)   tanf(x)
#define f32_sqrt(x)  sqrtf(x)
#define f32_abs(x)   fabsf(x)
#define f32_ln(x)    logf(x)
#define f32_log10(x) log10f(x)
#define f32_log2(x)  log2f(x)
#define f32_exp(x)   expf(x)
#define f32_exp2(x)  exp2f(x)
#define f32_pow(x,y) powf(x,y)

#define f64_sin(x)   sin(x)
#define f64_cos(x)   cos(x)
#define f64_tan(x)   tan(x)
#define f64_sqrt(x)  sqrt(x)
#define f64_abs(x)   fabs(x)
#define f64_ln(x)    log(x)
#define f64_log10(x) log(x)
#define f64_log2(x)  log2(x)
#define f64_exp(x)   exp(x)
#define f64_exp2(x)  exp2(x)
#define f64_pow(x,y) pow(x,y)

#define is_pow2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
#define is_pow2_or_zero(x) (((x) & ((x) - 1)) == 0)

#define align_up_pow2(x, p) (((x) + ((p) - 1)) & ~((p) - 1))
#define align_down_pow2(x, p) ((x) & ~((p) - 1))

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((x) << 40)

#endif // MSTD_BASE_H