#if !defined(MSTD_H)
#define MSTD_H

#include <stdint.h>

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

#if defined(_M_AMD64) || defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__) || defined(__amd64__)
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

#if COMPILER_MSVC
    #include <intrin.h>
#endif

////////////////////////////////
// Macros: Memory

#if defined(COMPILER_MSVC)
#include <intrin.h>
    void* memmove(void* dest, const void* src, size_t count);
    int memcmp(const void* buffer1, const void* buffer2, size_t count);
    #pragma intrinsic(memcmp, memmove)
    #define trap()                    __debugbreak()
    #define mem_set(p, byte, size)    __stosb((unsigned char*)(p), (unsigned char)(byte), (size))
    #define mem_copy(dest, src, size) __movsb((unsigned char*)(dest), (const unsigned char*)(src), (size))
    #define mem_move(dest, src, size) memmove((dest), (src), (size))
    #define mem_match(a, b, size)     (memcmp((a), (b), (size)) == 0)
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
    #define trap()                    __builtin_trap()
    #define mem_set(p, byte, size)    __builtin_memset((p), (byte), (size))
    #define mem_copy(dest, src, size) __builtin_memcpy((dest), (src), (size))
    #define mem_move(dest, src, size) __builtin_memmove((dest), (src), (size))
    #define mem_match(a, b, size)     (__builtin_memcmp((a), (b), (size)) == 0)
#else
#error "mem_" functions not defined for this compiler.
#endif

#define mem_zero(p, size)                mem_set((p), 0, (size))
#define mem_zero_struct(p)               mem_zero((p), sizeof(*(p)))
#define mem_zero_array(p, count)         mem_zero((p), sizeof(*(p)) * (count))

#define mem_copy_struct(dest, src)       mem_copy((dest), (src), sizeof(*(dest)))
#define mem_copy_array(dest, src, count) mem_copy((dest), (src), sizeof(*(dest)) * (count))

#define mem_move_struct(dest, src)       mem_move((dest), (src), sizeof(*(dest)))
#define mem_move_array(dest, src, count) mem_move((dest), (src), sizeof(*(dest)) * (count))

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
#define align_to(x) __declspec(align(x))
#elif COMPILER_CLANG || COMPILER_GCC
#define align_to(x) __attribute__((aligned(x)))
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

#if MSTD_DEBUG
    #define debug_trap_code_if(code, op, check) while((code) op (check)) { trap(); }
    #define debug_trap_if(condition) while(condition) { trap(); }
#else
    #define debug_trap_code_if(code, op, check) ((void)(code))
    #define debug_trap_if(condition)
#endif

#define debug_validate_code(code, check) debug_trap_code_if(code, !=, check)
#define debug_validate(condition) debug_trap_if(!(condition))

#define _stringify(S) #S
#define stringify(S) _stringify(S)

#define _concat(a, b) a##b
#define concat(a,b) _concat(a,b)

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

#define clamp_top(val, high)    (((val) < (high)) ? (val) : (high))
#define clamp_bottom(val, low)  (((val) > (low)) ? (val) : (low))
#define clamp(val, low, high) (clamp_bottom(low, clamp_top(val, high)))

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

////////////////////////////////
// Types: Vecs

#define VEC2_GEN(T) \
    typedef union T##vec2 { \
        struct { T x, y; }; \
        struct { T u, v; }; \
        T elements[2]; \
    } T##vec2

#define VEC3_GEN(T) \
    typedef union T##vec3 { \
        struct { T x, y, z; }; \
        struct { T r, g, b; }; \
        T elements[3]; \
    } T##vec3

#define VEC4_GEN(T) \
    typedef union T##vec4 { \
        struct { T x, y, z, w; }; \
        struct { T r, g, b, a; }; \
        T elements[4]; \
    } T##vec4

#define VEC_GEN(T) VEC2_GEN(T); VEC3_GEN(T); VEC4_GEN(T);

VEC_GEN(u8);
VEC_GEN(u16);
VEC_GEN(u32);
VEC_GEN(u64);

VEC_GEN(i8);
VEC_GEN(i16);
VEC_GEN(i32);
VEC_GEN(i64);

VEC_GEN(f32);
VEC_GEN(f64);

#if COMPILER_MSVC
static i32 u32_msb(u32 mask) { unsigned long where; return _BitScanReverse(&where, mask) ? where : -1; }
static i32 u32_lsb(u32 mask) { unsigned long where; return _BitScanForward(&where, mask) ? where : -1; }
static i32 u64_msb(u64 mask) { unsigned long where; return _BitScanReverse64(&where, mask) ? where : -1; }
static i32 u64_lsb(u64 mask) { unsigned long where; return _BitScanForward64(&where, mask) ? where : -1; }
#elif COMPILER_CLANG || COMPILER_GCC
#define u32_msb(x) ((x) == 0 ? -1 : 31 - __builtin_clz(x))
#define u32_lsb(x) ((x) == 0 ? -1 : __builtin_ctz(x))
#define u64_msb(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))
#define u64_lsb(x) ((x) == 0 ? -1 : __builtin_ctzll(x))
#endif

////////////////////////////////
// Types: Arena

#define ARENA_DEFAULT_COMMIT_SIZE MB(4)
#define ARENA_DEFAULT_RESERVE_SIZE MB(64)

typedef enum ArenaFlag ArenaFlag;
enum ArenaFlag {
    ARENA_FLAG_NONE = 0,
    ARENA_FLAG_COMMIT_LARGE_PAGES = 1 << 0,
};

typedef struct Arena Arena;
struct Arena {
    u64 cursor;
    u64 committed;
    u64 reserved;
    enum_t(ArenaFlag, b32) flags;
    u32 page_size;
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

 Arena* arena_alloc(u64 reserve_size, ArenaFlag flags);

void* arena_push(Arena* arena, u64 size, u64 align);
#define arena_push_struct(arena, T) (T*)arena_push(arena, sizeof(T), align_of(T))
#define arena_push_array(arena, T, count) (T*)arena_push(arena, sizeof(T) * count, align_of(T))

void arena_reset(Arena* arena);
void arena_release(Arena *arena);

ArenaTemp arena_temp_begin(Arena* arena);
void arena_temp_end(ArenaTemp temp);
#define arena_temp_scope(temp_arena) for (ArenaTemp _temp = arena_temp_begin(temp_arena); _temp.arena != NULL; arena_temp_end(_temp), _temp.arena = NULL)

ArenaScratch arena_scratch_begin(void);
void arena_scratch_end(ArenaScratch scratch);

////////////////////////////////
// Types: Str8, Str16, Str32

typedef struct Str8 Str8;
struct Str8 {
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

typedef enum CharType CharType;
enum CharType {
    CHAR_TYPE_SPACE   = (1 << 0), // 0x01
    CHAR_TYPE_UPPER   = (1 << 1), // 0x02
    CHAR_TYPE_LOWER   = (1 << 2), // 0x04
    CHAR_TYPE_DIGIT10 = (1 << 3), // 0x08
    CHAR_TYPE_DIGIT16 = (1 << 4), // 0x10
};

align_to(64) global const u8 ASCII_LUT[256] = {
    // White-space: Tab, LF, VT, FF, CR, Space
    [0x09] = CHAR_TYPE_SPACE, [0x0A] = CHAR_TYPE_SPACE, [0x0B] = CHAR_TYPE_SPACE,
    [0x0C] = CHAR_TYPE_SPACE, [0x0D] = CHAR_TYPE_SPACE, [0x20] = CHAR_TYPE_SPACE,

    // Digits: 0-9 (Decimal + Hex)
    ['0'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16, ['1'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16,
    ['2'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16, ['3'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16,
    ['4'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16, ['5'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16,
    ['6'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16, ['7'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16,
    ['8'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16, ['9'] = CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16,

    // Uppercase Hex: A-F
    ['A'] = CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16, ['B'] = CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16,
    ['C'] = CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16, ['D'] = CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16,
    ['E'] = CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16, ['F'] = CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16,

    // Uppercase Non-Hex: G-Z
    ['G'] = CHAR_TYPE_UPPER, ['H'] = CHAR_TYPE_UPPER, ['I'] = CHAR_TYPE_UPPER, ['J'] = CHAR_TYPE_UPPER,
    ['K'] = CHAR_TYPE_UPPER, ['L'] = CHAR_TYPE_UPPER, ['M'] = CHAR_TYPE_UPPER, ['N'] = CHAR_TYPE_UPPER,
    ['O'] = CHAR_TYPE_UPPER, ['P'] = CHAR_TYPE_UPPER, ['Q'] = CHAR_TYPE_UPPER, ['R'] = CHAR_TYPE_UPPER,
    ['S'] = CHAR_TYPE_UPPER, ['T'] = CHAR_TYPE_UPPER, ['U'] = CHAR_TYPE_UPPER, ['V'] = CHAR_TYPE_UPPER,
    ['W'] = CHAR_TYPE_UPPER, ['X'] = CHAR_TYPE_UPPER, ['Y'] = CHAR_TYPE_UPPER, ['Z'] = CHAR_TYPE_UPPER,

    // Lowercase Hex: a-f
    ['a'] = CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16, ['b'] = CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16,
    ['c'] = CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16, ['d'] = CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16,
    ['e'] = CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16, ['f'] = CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16,

    // Lowercase Non-Hex: g-z
    ['g'] = CHAR_TYPE_LOWER, ['h'] = CHAR_TYPE_LOWER, ['i'] = CHAR_TYPE_LOWER, ['j'] = CHAR_TYPE_LOWER,
    ['k'] = CHAR_TYPE_LOWER, ['l'] = CHAR_TYPE_LOWER, ['m'] = CHAR_TYPE_LOWER, ['n'] = CHAR_TYPE_LOWER,
    ['o'] = CHAR_TYPE_LOWER, ['p'] = CHAR_TYPE_LOWER, ['q'] = CHAR_TYPE_LOWER, ['r'] = CHAR_TYPE_LOWER,
    ['s'] = CHAR_TYPE_LOWER, ['t'] = CHAR_TYPE_LOWER, ['u'] = CHAR_TYPE_LOWER, ['v'] = CHAR_TYPE_LOWER,
    ['w'] = CHAR_TYPE_LOWER, ['x'] = CHAR_TYPE_LOWER, ['y'] = CHAR_TYPE_LOWER, ['z'] = CHAR_TYPE_LOWER,
};

#define str8_char_is_space(c)        (ASCII_LUT[(u8)(c)] & CHAR_TYPE_SPACE)
#define str8_char_is_upper(c)        (ASCII_LUT[(u8)(c)] & CHAR_TYPE_UPPER)
#define str8_char_is_lower(c)        (ASCII_LUT[(u8)(c)] & CHAR_TYPE_LOWER)
#define str8_char_is_alpha(c)        (ASCII_LUT[(u8)(c)] & ( CHAR_TYPE_UPPER | CHAR_TYPE_LOWER ))
#define str8_char_is_alphanumeric(c) (ASCII_LUT[(u8)(c)] & ( CHAR_TYPE_UPPER | CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT10 ))
#define str8_char_is_numeric(c)      (ASCII_LUT[(u8)(c)] & CHAR_TYPE_DIGIT10)
#define str8_char_is_numeric_hex(c)  (ASCII_LUT[(u8)(c)] & CHAR_TYPE_DIGIT16)

#define str8_char_to_upper(c)        ((u8)((u8)(c) ^ (str8_char_is_lower(c) ? 0x20 : 0)))
#define str8_char_to_lower(c)        ((u8)((u8)(c) ^ (str8_char_is_upper(c) ? 0x20 : 0)))

Str8 str8_from_cstr(u8* str);
#define str8_literal(literal) str8_from_cstr((u8*)literal)

Str8 str8_of_size(Arena* arena, u64 size);
Str16 str16_of_size(Arena* arena, u64 size);

UnicodeDecode utf8_decode(u8* str, u64 max);
UnicodeDecode utf16_decode(u16* str, u64 max);
u32 utf8_encode(u8* str, u32 codepoint);
u32 utf16_encode(u16* str, u32 codepoint);
u32 utf8_size(u32 cp);
u32 utf16_size(u32 cp);

void str8_to_lower(Str8 text);
void str8_to_upper(Str8 text);
b8 str8_equal(Str8 a, Str8 b);
Str16 str16_from_cstr(u16* str);
#define str16_literal(literal) str16_from_cstr((u16*)literal)
b8 str16_equal(Str16 a, Str16 b);
Str8 str8_from_16(Arena* arena, Str16 text);
Str16 str16_from_8(Arena* arena, Str8 text);
Str8 str8_from_32(Arena* arena, Str32 text);
Str32 str32_from_8(Arena* arena, Str8 text);
Str8 str8_copy(Arena* arena, Str8 text);
Str16 str16_copy(Arena* arena, Str16 text);

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

typedef struct OS_Handle OS_Handle;
struct OS_Handle {
    u64 val[1];
};

void os_init_state();
OS_SystemInfo* os_get_system_info(void);
OS_ProcessInfo* os_get_process_info(void);
u64 os_get_micro_second_resolution(void);

OS_Handle os_load_lib(char* name);
void* os_load_symbol(OS_Handle lib, char* name);

void os_attach_console_if_exists();

////////////////////////////////
// OS: Memory Helpers

void* os_reserve(u64 size, b32 large_pages);
b8 os_commit(void* ptr, u64 size, b32 large_pages);
void os_decommit(void* ptr, u64 size);
void os_release(void* ptr, u64 size);

////////////////////////////////
// OS: FileSystem Helpers

typedef enum OS_AccessFlag OS_AccessFlag;
enum OS_AccessFlag {
    OS_ACCESS_FLAG_OPEN_EXISTING  = 1 << 0,
    OS_ACCESS_FLAG_OPEN_ALWAYS    = 1 << 1,
    OS_ACCESS_FLAG_SHARE_READ     = 1 << 2,
    OS_ACCESS_FLAG_SHARE_WRITE    = 1 << 3,
    OS_ACCESS_FLAG_EXECUTE        = 1 << 4,
    OS_ACCESS_FLAG_READ           = 1 << 5,
    OS_ACCESS_FLAG_WRITE          = 1 << 6,
    OS_ACCESS_FLAG_APPEND         = 1 << 7,
};

OS_Handle os_file_open(OS_AccessFlag flags, Str8 path);
void os_file_close(OS_Handle handle);
u64 os_file_read(OS_Handle handle, u64 begin, u64 end, void* out_data);
#define os_file_read_struct(handle, offset, struct_ptr) os_file_read((handle), (offset), (offset) + sizeof(*(struct_ptr)), (struct_ptr))
u64 os_file_write(OS_Handle handle, u64 begin, u64 end, void* data);
u64 os_file_get_size(OS_Handle handle);
void os_file_delete(Str8 path);
void os_file_copy(Str8 src, Str8 dest);
void os_file_move(Str8 src, Str8 dest);
b32 os_file_path_exists(Str8 path);
b32 os_file_directory_exists(Str8 path);


////////////////////////////////
// OS: Time

 u64 os_get_time_now_microseconds(void);

////////////////////////////////
// Entrypoint: i32 mstd_main() {}
// #define MSTD_USE_MAIN
// #define MSTD_USE_GUI_MAIN

#endif // MSTD_H