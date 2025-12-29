#if !defined(MSTD_H)
#define MSTD_H

#include <stdint.h>
#include <string.h>


////////////////////////////////
// Macros: Compilers

#define COMPILER_MSVC    0
#define COMPILER_CLANG   0
#define COMPILER_GCC     0

#if defined(_MSC_VER)
#undef  COMPILER_MSVC
#define COMPILER_MSVC  1
#elif defined(__clang__)
#undef  COMPILER_CLANG
#define COMPILER_CLANG 1
#elif defined(__GNUC__)
#undef  COMPILER_GCC
#define COMPILER_GCC   1
#else
#error "Unknown Compiler"
#endif

////////////////////////////////
// Macros: Operating Systems

#define OS_WINDOWS 0
#define OS_LINUX   0
#define OS_MAC     0

#if defined(_WIN32)
#undef  OS_WINDOWS
#define OS_WINDOWS 1
#elif defined(__linux__)
#undef  OS_LINUX
#define OS_LINUX   1
#elif defined(__APPLE__) && defined(__MACH__)
#undef  OS_MAC
#define OS_MAC     1
#else
#error "Unknown Operating System"
#endif

////////////////////////////////
// Macros: Architectures

#define ARCH_X64   0
#define ARCH_X86   0
#define ARCH_ARM   0
#define ARCH_ARM64 0

#if defined(_M_AMD64) || defined(__amd64__) || defined(__x86_64__)
#undef  ARCH_X64
#define ARCH_X64   1
#elif defined(_M_IX86) || defined(__i386__)
#undef  ARCH_X86
#define ARCH_X86   1
#elif defined(__aarch64__) || defined(_M_ARM64)
#undef  ARCH_ARM64
#define ARCH_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#undef  ARCH_ARM
#define ARCH_ARM   1
#else
#error "Unknown Architecture"
#endif

////////////////////////////////
// Macros: Language

#define LANG_CXX 0
#define LANG_C 0

#if defined(__cplusplus)
#undef LANG_CXX
#define LANG_CXX 1
#else
#undef LANG_C
#define LANG_C 1
#endif

////////////////////////////////
// Macros: Memory

#define mem_zero(p, size) memset((p), 0, (size))
#define mem_zero_struct(p) mem_zero((p), sizeof(*(p)))
#define mem_zero_array(p) mem_zero((p), sizeof(p))

#define mem_copy(dest, src, size) memcpy((dest), (src), (size))
#define mem_copy_struct(dest, src) mem_copy((dest), (src), sizeof(*(dest)))
#define mem_copy_array(dest, src, size) mem_copy((dest), (src), sizeof(dest))

#define mem_move(dest, src, size) memmove((dest), (src), (size))
#define mem_match(a, b, size) (memcmp((a), (b), (size)) == 0)

////////////////////////////////
// Macros: Misc

#if COMPILER_MSVC
#define align_of(T) __alignof(T)
#elif COMPILER_CLANG
#define align_of(T) __alignof(T)
#elif COMPILER_GCC
#define align_of(T) __alignof__(T)
#else
#error AlignOf not defined for this compiler.
#endif

#if COMPILER_MSVC
#define align_type(x) __declspec(align(x))
#elif COMPILER_CLANG || COMPILER_GCC
#define align_type(x) __attribute__((aligned(x)))
#else
#error AlignType not defined for this compiler.
#endif

#if COMPILER_MSVC
#define force_inline __forceinline
#elif COMPILER_CLANG || COMPILER_GCC
#define force_inline __attribute__((always_inline))
#else
#error force_inline not defined for this compiler.
#endif

#if COMPILER_MSVC
#define no_inline __declspec(noinline)
#elif COMPILER_CLANG || COMPILER_GCC
#define no_inline __attribute__((noinline))
#else
#error no_inline not defined for this compiler.
#endif

#if COMPILER_MSVC
#define thread_var __declspec(thread)
#elif COMPILER_CLANG || COMPILER_GCC
#define thread_var __thread
#else
#error thread_var not defined for this compiler
#endif

#define _stringify(S) #S
#define stringify(S) _stringify(S)

#define _concat(a, b) a##b
#define concat(a,b) _concat(a,b)

#define function
#define internal static
#define global static

#define is_pow2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
#define is_pow2_or_zero(x) (((x) & ((x) - 1)) == 0)

#define align_up_pow2(x, p) (((x) + ((p) - 1)) & ~((p) - 1))
#define align_down_pow2(x, p) ((x) & ~((p) - 1))

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((x) << 40)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define clamp(val, low, high) (max(low, min(val, high)))

#define clamp_top(val, high)    min(val, high)
#define clamp_bottom(val, low)  max(val, low)


////////////////////////////////
// Types: Basic

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef u8  b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;
typedef float  f32;
typedef double f64;

typedef intptr_t  isize;
typedef uintptr_t usize;
typedef intptr_t  iptr;
typedef uintptr_t uptr;

#define enum_t(enum, storage_data_type) storage_data_type

#if COMPILER_MSVC
#include <intrin.h>
#endif

#if COMPILER_MSVC
force_inline static i32 u32_msb(u32 mask) { unsigned long where; return _BitScanReverse(&where, mask) ? where : -1; }
force_inline static i32 u32_lsb(u32 mask) { unsigned long where; return _BitScanForward(&where, mask) ? where : -1; }
force_inline static i32 u64_msb(u64 mask) { unsigned long where; return _BitScanReverse64(&where, mask) ? where : -1; }
force_inline static i32 u64_lsb(u64 mask) { unsigned long where; return _BitScanForward64(&where, mask) ? where : -1; }
#elif COMPILER_CLANG || COMPILER_GCC
#define u32_msb(x) ((x) == 0 ? -1 : 31 - __builtin_clz(x))
#define u32_lsb(x) ((x) == 0 ? -1 : __builtin_ctz(x))
#define u64_msb(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))
#define u64_lsb(x) ((x) == 0 ? -1 : __builtin_ctzll(x))
#endif

////////////////////////////////
// Types: Arena

typedef enum ArenaFlag ArenaFlag;
enum ArenaFlag {
    arena_flag_none = 0,
    arena_flag_commit_large_pages = 1 << 0,
};

typedef struct Arena Arena;
struct Arena {
    enum_t(ArenaFlag, b64) flags;
    usize reserved;
    usize cursor;
    usize commited;
};

typedef struct ArenaTemp ArenaTemp;
struct ArenaTemp {
    Arena* arena;
    usize cursor;
};

typedef struct ArenaScratch ArenaScratch;
struct ArenaScratch {
    Arena* arena;
    usize index;
};

function Arena* arena_alloc(usize reserve_size, ArenaFlag flag);

function void* arena_push(Arena* arena, usize size, usize align);
#define arena_push_struct(arena, T) (T*)arena_push(arena, sizeof(T), align_of(T))
#define arena_push_array(arena, T, count) (T*)arena_push(arena, sizeof(T) * count, align_of(T))

function void arena_reset(Arena* arena);
function void arena_release(Arena *arena);

function ArenaTemp* arena_temp_begin(Arena* arena);
function void arena_temp_end(ArenaTemp* temp);
#define arena_temp(arena) for (ArenaTemp* _temp = arena_temp_begin(arena); _temp != NULL; arena_temp_end(_temp), _temp = NULL)

function ArenaScratch arena_scratch_begin(void);
function void arena_scratch_end(ArenaScratch scratch);

////////////////////////////////
// Types: str8, str16, str32

typedef struct str8 str8;
struct str8 {
    u8* c_str;
    usize size;
};

typedef struct str16 str16;
struct str16 {
    u16* c_str;
    usize size;
};

typedef struct str32 str32;
struct str32 {
    u32* c_str;
    usize size;
};

typedef struct UnicodeDecode UnicodeDecode;
struct UnicodeDecode {
    u32 inc;
    u32 codepoint;
};

#define str8_char_is_space(c) isspace(c)
#define str8_char_is_upper(c) isupper(c)
#define str8_char_is_lower(c) islower(c)
#define str8_char_is_alpha(c) isalpha(c)
#define str8_char_is_alphanumeric(c) isalnum(c)
#define str8_char_is_numeric(c) isdigit(c)
#define str8_char_is_numeric_hex(c) isxdigit(c)

#define str8_char_to_upper(c) (u8)toupper(c)
#define str8_char_to_lower(c) (u8)tolower(c)

function str8 str8_from_cstr(u8* str);
#define str8_literal(literal) str8_from_cstr((u8*)literal)

function void str8_to_lower(str8 string);
function void str8_to_upper(str8 string);
function b8 str8_equal(str8 a, str8 b);

function str16 str16_from_cstr(u16* str);
#define str16_literal(literal) str16_from_cstr((u16*)literal)
function b8 str16_equal(str16 a, str16 b);

function str8 str8_from_16(Arena* arena, str16 string);
function str16 str16_from_8(Arena* arena, str8 string);
function str8 str8_from_32(Arena* arena, str32 string);
function str32 str32_from_8(Arena* arena, str8 string);

////////////////////////////////
// OS: Core

typedef struct OS_SystemInfo OS_SystemInfo;
struct OS_SystemInfo {
    u32 logical_processor_count;
    usize page_size;
    usize large_page_size;
    usize allocation_granularity;
};

typedef struct OS_ProcessInfo OS_ProcessInfo;
struct OS_ProcessInfo {
    u32 id;
    b32 large_pages_allowed;
};

function OS_SystemInfo* os_get_system_info(void);
function OS_ProcessInfo* os_get_process_info(void);

////////////////////////////////
// OS: Memory Helpers

function void* os_reserve(usize size);
function void* os_reserve_large(usize size);
function b8 os_commit(void* ptr, usize size);
function b8 os_commit_large(void* ptr, usize size);
function void os_decommit(void* ptr, usize size);
function void os_release(void* ptr, usize size);

////////////////////////////////
// OS: FileSystem Helpers

// function void os_file_read(Arena* arena, str8 file_name);

#endif // MSTD_H
