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
#define mem_zero_array(p, count) mem_zero((p), sizeof(*(p)) * (count))

#define mem_copy(dest, src, size) memcpy((dest), (src), (size))
#define mem_copy_struct(dest, src) mem_copy((dest), (src), sizeof(*(dest)))
#define mem_copy_array(dest, src, count) mem_copy((dest), (src), sizeof(*(dest)) * (count))

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
    u64 reserved;
    u64 cursor;
    u64 commited;
};

typedef struct ArenaTemp ArenaTemp;
struct ArenaTemp {
    Arena* arena;
    u64 cursor;
};

typedef struct ArenaScratch ArenaScratch;
struct ArenaScratch {
    Arena* arena;
    u64 index;
};

function Arena* arena_alloc(u64 reserve_size, ArenaFlag flag);

function void* arena_push(Arena* arena, u64 size, u64 align);
#define arena_push_struct(arena, T) (T*)arena_push(arena, sizeof(T), align_of(T))
#define arena_push_array(arena, T, count) (T*)arena_push(arena, sizeof(T) * count, align_of(T))

function void arena_reset(Arena* arena);
function void arena_release(Arena *arena);

function ArenaTemp arena_temp_begin(Arena* arena);
function void arena_temp_end(ArenaTemp temp);
#define arena_temp(temp_arena) for (ArenaTemp _temp = arena_temp_begin(temp_arena); _temp.arena != NULL; arena_temp_end(_temp), _temp.arena = NULL)

function ArenaScratch arena_scratch_begin(void);
function void arena_scratch_end(ArenaScratch scratch);

////////////////////////////////
// Types: Str8, Str16, Str32

typedef struct Str8 Str8;
struct Str8 {
    u8* data;
    u64 size;
};

typedef struct Str8View Str8View;
struct Str8View {
    u8* data;
    u64 size;
};

typedef struct Str8List Str8List;
struct Str8List {
    Str8 str8_node;
    Str8List* next;
};

typedef struct Str16 Str16;
struct Str16 {
    u16* data;
    u64 size;
};

typedef struct Str32 Str32;
struct Str32 {
    u32* data;
    u64 size;
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

function Str8 str8_from_cstr(u8* str);
#define str8_literal(literal) str8_from_cstr((u8*)literal)

function Str8 str8_of_size(Arena* arena, u64 size);
function Str16 str16_of_size(Arena* arena, u64 size);

function void str8_to_lower(Str8 text);
function void str8_to_upper(Str8 text);
function b8 str8_equal(Str8 a, Str8 b);
function Str16 str16_from_cstr(u16* str);
#define str16_literal(literal) str16_from_cstr((u16*)literal)
function b8 str16_equal(Str16 a, Str16 b);

function Str8 str8_from_16(Arena* arena, Str16 text);
function Str16 str16_from_8(Arena* arena, Str8 text);
function Str8 str8_from_32(Arena* arena, Str32 text);
function Str32 str32_from_8(Arena* arena, Str8 text);

function Str8 str8_copy(Arena* arena, Str8 text);
function Str16 str16_copy(Arena* arena, Str16 text);

////////////////////////////////
// OS: Core

typedef struct OS_SystemInfo OS_SystemInfo;
struct OS_SystemInfo {
    u32 logical_processor_count;
    u64 page_size;
    u64 large_page_size;
    u64 allocation_granularity;
};

typedef struct OS_ProcessInfo OS_ProcessInfo;
struct OS_ProcessInfo {
    u32 id;
    b32 large_pages_allowed;
};

function OS_SystemInfo* os_get_system_info(void);
function OS_ProcessInfo* os_get_process_info(void);
function u64 os_get_micro_second_resolution(void);

////////////////////////////////
// OS: Memory Helpers

function void* os_reserve(u64 size);
function void* os_reserve_large(u64 size);
function b8 os_commit(void* ptr, u64 size);
function b8 os_commit_large(void* ptr, u64 size);
function void os_decommit(void* ptr, u64 size);
function void os_release(void* ptr, u64 size);

////////////////////////////////
// OS: FileSystem Helpers

typedef Str8 Buffer;
typedef struct BufferList BufferList;
struct BufferList {
    Buffer buffer;
    BufferList* next;
};

typedef enum OS_AccessFlag OS_AccessFlag;
enum OS_AccessFlag {
    os_access_flag_open_existing  = 1 << 0,
    os_access_flag_open_always    = 1 << 1,
    os_access_flag_share_read     = 1 << 2,
    os_access_flag_share_write    = 1 << 3,
    os_access_flag_execute        = 1 << 4,
    os_access_flag_read           = 1 << 5,
    os_access_flag_write          = 1 << 6,
    os_access_flag_append         = 1 << 7,
};

typedef struct OS_Handle OS_Handle;
struct OS_Handle {
    u64 val[1];
};

function OS_Handle os_file_open(OS_AccessFlag flags, Str8 path);
function void os_file_close(OS_Handle handle);
function u64 os_file_read(OS_Handle handle, u64 begin, u64 end, void* out_data);
#define os_file_read_struct(handle, offset, struct_ptr) os_file_read((handle), (offset), (offset) + sizeof(*(struct_ptr)), (struct_ptr))
function u64 os_file_write(OS_Handle handle, u64 begin, u64 end, void* data);
function u64 os_file_get_size(OS_Handle handle);
function void os_file_delete(Str8 path);
function void os_file_copy(Str8 src, Str8 dest);
function void os_file_move(Str8 src, Str8 dest);
function b32 os_file_path_exists(Str8 path);
function b32 os_file_directory_exists(Str8 path);

////////////////////////////////
// OS: Time

function u64 os_now_microseconds(void);

#endif // MSTD_H
