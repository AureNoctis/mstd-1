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

#if defined(_M_AMD64) || defined(__x86_64__) || defined(__amd64__)
#undef  ARCH_X64
#define ARCH_X64   1

#elif defined(__aarch64__) || defined(_M_ARM64)
#undef  ARCH_ARM64
#define ARCH_ARM64 1

#elif defined(_M_IX86) || defined(__i386__)
#undef  ARCH_X86
#define ARCH_X86   1

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
    void* memmove(void* dest, const void* src, size_t count);
    int memcmp(const void* buffer1, const void* buffer2, size_t count);
    #pragma intrinsic(memcmp, memmove)
    #define trap()                    __debugbreak()
    #define mem_set(p, byte, size)    __stosb((u8*)(p), (u8)(byte), (size))
    #define mem_copy(dest, src, size) __movsb((u8*)(dest), (const u8*)(src), (size))
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
    #define DEBUG_TRUE 1
#else
    #define debug_trap_code_if(code, op, check) ((void)(code))
    #define debug_trap_if(condition)
    #define DEBUG_TRUE 0
#endif

#define debug_validate_code(code, check) debug_trap_code_if(code, !=, check)
#define debug_validate(condition) debug_trap_if(!(condition))

#define _stringify(S) #S
#define stringify(S) _stringify(S)

#define _concat(a, b) a##b
#define concat(a,b) _concat(a,b)

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

#ifndef MSTD_BASE_TYPES
    #define MSTD_BASE_TYPES 1
#endif

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef intptr_t  iptr;
typedef uintptr_t uptr;

#define enum_t(enum, storage_data_type) storage_data_type

#if COMPILER_MSVC

static i8 u32_msb(u32 mask) { unsigned long where; return _BitScanReverse(&where, mask) ? (i8)where : -1; }
static i8 u64_msb(u64 mask) { unsigned long where; return _BitScanReverse64(&where, mask) ? (i8)where : -1; }
static i8 u32_lsb(u32 mask) { unsigned long where; return _BitScanForward(&where, mask) ? (i8)where : -1; }
static i8 u64_lsb(u64 mask) { unsigned long where; return _BitScanForward64(&where, mask) ? (i8)where : -1; }
#define u32_count_set_bits __popcnt
#define u64_count_set_bits __popcnt64

#elif COMPILER_CLANG || COMPILER_GCC

#define u32_msb(x) ((x) == 0 ? -1 : 31 - __builtin_clz(x))
#define u64_msb(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))
#define u32_lsb(x) ((x) == 0 ? -1 : __builtin_ctz(x))
#define u64_lsb(x) ((x) == 0 ? -1 : __builtin_ctzll(x))
#define u32_count_set_bits __builtin_popcount
#define u64_count_set_bits __builtin_popcountll
#endif

////////////////////////////////
// Types: Constants

#define bit_0  (1ULL << 0)
#define bit_1  (1ULL << 1)
#define bit_2  (1ULL << 2)
#define bit_3  (1ULL << 3)
#define bit_4  (1ULL << 4)
#define bit_5  (1ULL << 5)
#define bit_6  (1ULL << 6)
#define bit_7  (1ULL << 7)
#define bit_8  (1ULL << 8)
#define bit_9  (1ULL << 9)
#define bit_10 (1ULL << 10)
#define bit_11 (1ULL << 11)
#define bit_12 (1ULL << 12)
#define bit_13 (1ULL << 13)
#define bit_14 (1ULL << 14)
#define bit_15 (1ULL << 15)
#define bit_16 (1ULL << 16)
#define bit_17 (1ULL << 17)
#define bit_18 (1ULL << 18)
#define bit_19 (1ULL << 19)
#define bit_20 (1ULL << 20)
#define bit_21 (1ULL << 21)
#define bit_22 (1ULL << 22)
#define bit_23 (1ULL << 23)
#define bit_24 (1ULL << 24)
#define bit_25 (1ULL << 25)
#define bit_26 (1ULL << 26)
#define bit_27 (1ULL << 27)
#define bit_28 (1ULL << 28)
#define bit_29 (1ULL << 29)
#define bit_30 (1ULL << 30)
#define bit_31 (1ULL << 31)
#define bit_32 (1ULL << 32)
#define bit_33 (1ULL << 33)
#define bit_34 (1ULL << 34)
#define bit_35 (1ULL << 35)
#define bit_36 (1ULL << 36)
#define bit_37 (1ULL << 37)
#define bit_38 (1ULL << 38)
#define bit_39 (1ULL << 39)
#define bit_40 (1ULL << 40)
#define bit_41 (1ULL << 41)
#define bit_42 (1ULL << 42)
#define bit_43 (1ULL << 43)
#define bit_44 (1ULL << 44)
#define bit_45 (1ULL << 45)
#define bit_46 (1ULL << 46)
#define bit_47 (1ULL << 47)
#define bit_48 (1ULL << 48)
#define bit_49 (1ULL << 49)
#define bit_50 (1ULL << 50)
#define bit_51 (1ULL << 51)
#define bit_52 (1ULL << 52)
#define bit_53 (1ULL << 53)
#define bit_54 (1ULL << 54)
#define bit_55 (1ULL << 55)
#define bit_56 (1ULL << 56)
#define bit_57 (1ULL << 57)
#define bit_58 (1ULL << 58)
#define bit_59 (1ULL << 59)
#define bit_60 (1ULL << 60)
#define bit_61 (1ULL << 61)
#define bit_62 (1ULL << 62)
#define bit_63 (1ULL << 63)

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
    enum_t(ArenaFlag, u32) flags;
    u32 page_size;
};

#define ARENA_HEADER_SIZE align_up_pow2(sizeof(Arena), 64)

typedef struct ArenaTemp ArenaTemp;
struct ArenaTemp {
    Arena* arena;
    union {
        u64 cursor;
        u64 index;
    };
};

typedef ArenaTemp ArenaScratch;

Arena* arena_alloc(u64 reserve_size, ArenaFlag flags);

void* arena_push(Arena* arena, u64 size, u64 align);
#define arena_push_struct(arena, T) (T*)arena_push(arena, sizeof(T), align_of(T))
#define arena_push_array(arena, T, count) (T*)arena_push(arena, sizeof(T) * (count), align_of(T))

void arena_reset(Arena* arena);
void arena_release(Arena *arena);

/// @brief This function can have 0 passed as param which causes it to create a TLS scratch arena.
ArenaTemp arena_temp_begin(Arena* arena);
void arena_temp_end(ArenaTemp temp);

/// @brief defines a loop which will run once. use { //code  } just after it.
#define arena_temp_scope(temp_arena) for (ArenaTemp _temp = arena_temp_begin(temp_arena); _temp.arena != NULL; arena_temp_end(_temp), _temp.arena = NULL)

ArenaScratch arena_scratch_begin();
void arena_scratch_end(ArenaScratch scratch);

/// @brief defines a loop which will run once. use { //code  } just after it.
/// @param scratch - name you pass should be used in the scope
#define arena_scratch_scope(scratch) for (ArenaScratch scratch = arena_scratch_begin(); scratch.arena != NULL; arena_scratch_end(scratch), scratch.arena.arena = NULL)

////////////////////////////////
// Types: Str8, Str16, Str32

typedef struct Str8 Str8;
struct Str8 {
    u8* data;
    u64 size;
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

#define str8(literal) _Generic((literal) + 0,                \
    char*:              str8_from_cstr((u8*)literal),        \
    const char*:        str8_from_cstr((u8*)literal),        \
    u8*:                str8_from_cstr((u8*)literal),        \
    const u8*:          str8_from_cstr((u8*)literal)         \
)

Str8 _str8_from_fmt(Arena* arena, u8* fmt, ...);
#define str8_from_fmt(arena, fmt, ...) _str8_from_fmt(arena, (u8*)fmt, ##__VA_ARGS__)

Str8 str8_of_size(Arena* arena, u64 size);
Str16 str16_of_size(Arena* arena, u64 size);

Str8 str8_concat(Arena* arena, Str8 a, Str8 b);
Str16 str16_concat(Arena* arena, Str16 a, Str16 b);

UnicodeDecode utf8_decode(u8* str, u64 max);
UnicodeDecode utf16_decode(u16* str, u64 max);
u32 utf8_encode(u8* str, u32 codepoint);
u32 utf16_encode(u16* str, u32 codepoint);
u32 utf8_size(u32 cp);
u32 utf16_size(u32 cp);

void str8_to_lower(Str8 text);
void str8_to_upper(Str8 text);
u8 str8_equal(Str8 a, Str8 b);
Str16 str16_from_cstr(u16* str);
#define str16(literal) str16_from_cstr((u16*)literal)
u8 str16_equal(Str16 a, Str16 b);
Str8 str8_from_16(Arena* arena, Str16 text);
Str16 str16_from_8(Arena* arena, Str8 text);
Str8 str8_from_32(Arena* arena, Str32 text);
Str32 str32_from_8(Arena* arena, Str8 text);
Str8 str8_copy(Arena* arena, Str8 text);
Str16 str16_copy(Arena* arena, Str16 text);

////////////////////////////////
// Linked List
#define SLL_STACK_GEN(ListType, NodeType) \
typedef struct NodeType NodeType; \
struct NodeType { \
    Str8 data; \
    NodeType* next; \
}; \
 \
typedef struct ListType ListType; \
struct ListType { \
    NodeType* head; \
};

#define SLL_QUEUE_GEN(ListType, NodeType) \
typedef struct NodeType NodeType; \
struct NodeType { \
    Str8 data; \
    NodeType* next; \
}; \
 \
typedef struct ListType ListType; \
struct ListType { \
    NodeType* head; \
    NodeType* tail; \
};

#define DLL_GEN(ListType, NodeType) \
typedef struct NodeType NodeType; \
struct NodeType { \
    Str8 data; \
    NodeType* next; \
    NodeType* prev; \
}; \
 \
typedef struct ListType ListType; \
struct ListType { \
    NodeType* head; \
    NodeType* tail; \
};

#define dll_push_back_np(head, tail, node, next, prev) ((head) == 0 ? \
        ((head) = (tail) = (node), (node)->next = (node)->prev = 0) \
        : \
        ((node)->prev = (tail), (tail)->next = (node), (tail) = (node), (node)->next = 0))

#define dll_push_front_np(head, tail, node, next, prev) dll_push_back_np(tail, head, node, prev, next)
#define dll_remove_np(head, tail, node, next, prev) (((head) == (node)) ? \
    (((head) == (tail)) ? ((head) = (tail) = 0) : ((head) = (head)->next, (head)->prev = 0)) \
    : \
    ((tail) == (node)) ? ((tail) = (tail)->prev, (tail)->next = 0) : ((node)->next->prev = (node)->prev, (node)->prev->next = (node)->next))

#define dll_push_back(head, tail, node)  dll_push_back_np(head, tail, node, next, prev)
#define dll_push_front(head, tail, node) dll_push_front_np(head, tail, node, next, prev)
#define dll_remove(head, tail, node)     dll_remove_np(head, tail, node, next, prev)

#define sll_stack_push_n(head, node, next) ((node)->next = (head), (head) = (node))
#define sll_stack_pop_n(head, next) ((head) == 0 ? 0 : ((head) = (head)->next))

#define sll_stack_push(head, node) sll_stack_push_n(head, node, next)
#define sll_stack_pop(head)        sll_stack_pop_n(head, next)

#define sll_queue_push_n(head, tail, node, next) (((head) == 0 ? \
    (head) = (tail) = (node) \
    : \
    ((tail)->next = (node), (tail) = (node))), (node)->next = 0)

#define sll_queue_push_front_n(head, tail, node, next) ((head) == 0 ? \
    ((head) = (tail) = (node), (node)->next = 0) \
    : \
    ((node)->next = (head), (head) = (node)))

#define sll_queue_pop_n(head, tail, next) ((head) == (tail) ? ((head) = (tail) = 0) : ((head) = (head)->next))

#define sll_queue_push(head, tail, node)       sll_queue_push_n(head, tail, node, next)
#define sll_queue_push_front(head, tail, node) sll_queue_push_front_n(head, tail, node, next)
#define sll_queue_pop(head, tail)              sll_queue_pop_n(head, tail, next)

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
    u32 large_pages_allowed;
    Str8 current_working_directory;
};

typedef struct OS_Handle OS_Handle;
struct OS_Handle {
    u64 val[1];
};

void os_init_state();
OS_SystemInfo* os_get_system_info();
OS_ProcessInfo* os_get_process_info();
u64 os_get_resolution_us();
f64 os_get_inverse_ticks_per_us();
u64 os_get_ticks();
#define os_get_timestamp_us() (u64)(os_get_ticks() * os_get_inverse_ticks_per_us())

OS_Handle os_load_lib(u8* name);
void* os_load_symbol(OS_Handle lib, u8* name);

void os_attach_console_if_exists();

////////////////////////////////
// OS: Memory Helpers

void* os_reserve(u64 size, u32 large_pages);
u8 os_commit(void* ptr, u64 size, u32 large_pages);
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
    OS_ACCESS_FLAG_EXECUTE        = 1 << 5,
    OS_ACCESS_FLAG_READ           = 1 << 6,
    OS_ACCESS_FLAG_WRITE          = 1 << 7,
    OS_ACCESS_FLAG_APPEND         = 1 << 8
};

typedef enum OS_FileEventType OS_FileEventType;
enum OS_FileEventType {
    OS_FILE_EVENT_TYPE_NULL,
    OS_FILE_EVENT_TYPE_MODIFIED,
    OS_FILE_EVENT_TYPE_ADDED,
    OS_FILE_EVENT_TYPE_DELETED,
    OS_FILE_EVENT_TYPE_RENAMED,
};

typedef void OS_FileWatcher;

OS_Handle os_file_open(OS_AccessFlag flags, Str8 path);
void os_file_close(OS_Handle handle);
u64 os_file_read(OS_Handle handle, u64 begin, u64 end, void* out_data);
#define os_file_read_struct(handle, offset, struct_ptr) os_file_read((handle), (offset), (offset) + sizeof(*(struct_ptr)), (struct_ptr))
u64 os_file_write(OS_Handle handle, u64 begin, u64 end, void* data);
#define os_file_write_struct(handle, offset, struct_ptr) os_file_write((handle), (offset), (offset) + sizeof(*(struct_ptr)), (struct_ptr))
#define os_file_write_string(handle, str) os_file_write((handle), 0, str.size, str.data)


void os_file_delete(Str8 path);
u64 os_file_get_size(OS_Handle handle);
void os_file_copy(Str8 src, Str8 dest);
void os_file_move(Str8 src, Str8 dest);
u32 os_file_path_exists(Str8 path);
u32 os_file_directory_exists(Str8 path);

OS_FileWatcher* os_file_watcher_create(Arena* arena, Str8 path, u32 watch_sub_directory);
u32 os_file_watcher_poll_event(OS_FileWatcher* watcher, u32 timeout_ms, OS_FileEventType* type, Str8* file);
void os_file_watcher_destroy(OS_FileWatcher* watcher);

////////////////////////////////
// OS: Timer

typedef struct Timer Timer;
struct Timer {
    u64 ticks;
    float delta;
    float smooth_delta;
    float very_smooth_delta;
};

Timer timer_init();
void timer_update(Timer* timer);

//////////////////////////////
// Types: DArray

typedef struct DArrayHeader DArrayHeader;
struct DArrayHeader {
    u64 size;
};

typedef struct DarrayMetaData DarrayMetaData;
struct DarrayMetaData {
    u8 shift;
    u8 chunks_n;
    u64 el_size;
};

force_inline static void* darray_handle(Arena* arena, DArrayHeader* header, DarrayMetaData meta, u64 index);
#endif // MSTD_H