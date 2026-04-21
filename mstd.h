#if !defined(MSTD_H)
#define MSTD_H

// Compiler
#if defined(_MSC_VER)
#define COMPILER_MSVC  1
#else
#define COMPILER_MSVC  0
#endif

#if defined(__clang__)
#define COMPILER_CLANG 1
#else
#define COMPILER_CLANG 0
#endif

#if defined(__GNUC__)
#define COMPILER_GCC   1
#else
#define COMPILER_GCC   0
#endif

// OS
#if defined(_WIN32)
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

#if defined(__linux__)
#define OS_LINUX   1
#else
#define OS_LINUX   0
#endif

#if defined(__APPLE__) && defined(__MACH__)
#define OS_MAC     1
#else
#define OS_MAC     0
#endif

// Architecture
#if defined(_M_AMD64) || defined(__x86_64__) || defined(__amd64__)
#define ARCH_X64   1
#else
#define ARCH_X64   0
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
#define ARCH_ARM64 1
#else
#define ARCH_ARM64 0
#endif

#if defined(_M_IX86) || defined(__i386__)
#define ARCH_X86   1
#else
#define ARCH_X86   0
#endif

#if defined(__arm__) || defined(_M_ARM)
#define ARCH_ARM   1
#else
#define ARCH_ARM   0
#endif

// Language
#if defined(__cplusplus)
#define LANG_CXX 1
#else
#define LANG_C 1
#endif

#if LANG_CXX
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstdarg>
extern "C" {
#elif LANG_C
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#endif

#if COMPILER_MSVC
    #include <intrin.h>
#endif

////////////////////////////////
// Keywords, Tags

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

#define global static
#define function
#define internal static

////////////////////////////////
// Utils

#define ___STRING___(S) #S
#define __STRING__(S) ___STRING___(S)

#define ___JOIN___(a, b) a##b
#define __JOIN__(a, b) ___JOIN___(a, b)

#define bit(x) (1ULL << x)

////////////////////////////////
// Base Types

typedef int8_t   i8;
#define i8_min INT8_MIN
#define i8_max INT8_MAX

typedef int16_t  i16;
#define i16_min INT16_MIN
#define i16_max INT16_MAX

typedef int32_t  i32;
#define i32_min INT32_MIN
#define i32_max INT32_MAX

typedef int64_t  i64;
#define i64_min INT64_MIN
#define i64_max INT64_MAX

typedef uint8_t  u8;
#define u8_min UINT8_MIN
#define u8_max UINT8_MAX

typedef uint16_t u16;
#define u16_min UINT16_MIN
#define u16_max UINT16_MAX

typedef uint32_t u32;
#define u32_min UINT32_MIN
#define u32_max UINT32_MAX

typedef uint64_t u64;
#define u64_min UINT64_MIN
#define u64_max UINT64_MAX

typedef float  f32;
typedef double f64;

typedef intptr_t  iptr;
typedef uintptr_t uptr;

#define enum_t(enum, T) T

#if COMPILER_MSVC

static function force_inline u8 u32_count_zerol(u32 x) { unsigned long zeros = 0; return _BitScanReverse(&zeros, x) ? (u8)(31 - zeros) : 32; }
static function force_inline u8 u64_count_zerol(u64 x) { unsigned long zeros = 0; return _BitScanReverse64(&zeros, x) ? (u8)(63 - zeros) : 64; }

static function force_inline u8 u32_count_zeror(u32 x) { unsigned long zeros = 0; _BitScanForward(&zeros, x); return (u8)zeros; }
static function force_inline u8 u64_count_zeror(u64 x) { unsigned long zeros = 0; _BitScanForward64(&zeros, x); return (u8)zeros; }

static function force_inline i8 u32_msb(u32 x) { unsigned long where; return _BitScanReverse(&where, x)   ? (i8)where : -1; }
static function force_inline i8 u64_msb(u64 x) { unsigned long where; return _BitScanReverse64(&where, x) ? (i8)where : -1; }

static function force_inline i8 u32_lsb(u32 x) { unsigned long where; return _BitScanForward(&where, x)   ? (i8)where : -1; }
static function force_inline i8 u64_lsb(u64 x) { unsigned long where; return _BitScanForward64(&where, x) ? (i8)where : -1; }

#define u32_count_set_bits __popcnt
#define u64_count_set_bits __popcnt64

#elif COMPILER_CLANG || COMPILER_GCC

#define u32_msb(x) ((x) == 0 ? -1 : 31 - __builtin_clz(x))
#define u64_msb(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))

#define u32_lsb(x) ((x) == 0 ? -1 : __builtin_ctz(x))
#define u64_lsb(x) ((x) == 0 ? -1 : __builtin_ctzll(x))

#define u32_count_set_bits __builtin_popcount
#define u64_count_set_bits __builtin_popcountll

#define u32_count_zerol    __builtin_clz
#define u64_count_zerol    __builtin_clzll

#define u32_count_zeror    __builtin_ctz
#define u64_count_zeror    __builtin_ctzll

#endif

typedef struct Handle {
    u64 val[1];
}Handle;

////////////////////////////////
// MATH

#define is_pow2(x)                  ((x) != 0 && (((x) & ((x) - 1)) == 0))
#define is_pow2_or_zero(x)          (((x) & ((x) - 1)) == 0)

#define align_up_pow2(x, p)         (((x) + ((p) - 1)) & ~((p) - 1))
#define align_down_pow2(x, p)       ((x) & ~((p) - 1))

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((x) << 40)

#define clamp_top(val, high)        (((val) < (high)) ? (val) : (high))
#define clamp_bottom(val, low)      (((val) > (low)) ? (val) : (low))
#define clamp(val, low, high)       (clamp_bottom(low, clamp_top(val, high)))

////////////////////////////////
// Module: Debug

// TODO: mem leak debugger

#if defined(COMPILER_MSVC)
    #define trap()                    __debugbreak()
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
    #define trap()                    __builtin_trap()
#endif

#if MSTD_DEBUG
    #define debug_trap_code_if(code, op, check) while((code) op (check)) { trap(); }
    #define debug_trap_if(condition)            while(condition) { trap(); }
    #define DEBUG_TRUE 1
#else
    #define debug_trap_code_if(code, op, check) ((void)(code))
    #define debug_trap_if(condition)
    #define DEBUG_TRUE 0
#endif

#define debug_validate_code(code, check)        debug_trap_code_if(code, !=, check)
#define debug_validate(condition)               debug_trap_if(!(condition))

////////////////////////////////
// Module: Memory

#if defined(COMPILER_MSVC)
    void* memmove(void* dest, const void* src, size_t count);
    int memcmp(const void* buffer1, const void* buffer2, size_t count);
    #pragma intrinsic(memcmp, memmove)
    #define trap()                    __debugbreak()
    #define mem_set(p, byte, size)    __stosb((u8*)(p), (u8)(byte), (size))
    #define mem_copy(dest, src, size) __movsb((u8*)(dest), (u8*)(src), (size))
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

#define mem_zero(mem, size)                 mem_set((mem), 0, (size))
#define mem_zero_struct(mem)                mem_zero((mem), sizeof(*(mem)))
#define mem_zero_array(mem, count)          mem_zero((mem), sizeof(*(mem)) * (count))
#define mem_copy_struct(dest, src)          mem_copy((dest), (src), sizeof(*(dest)))
#define mem_copy_array(dest, src, count)    mem_copy((dest), (src), sizeof(*(dest)) * (count))
#define mem_move_struct(dest, src)          mem_move((dest), (src), sizeof(*(dest)))
#define mem_move_array(dest, src, count)    mem_move((dest), (src), sizeof(*(dest)) * (count))

#if COMPILER_MSVC
#define mem_align_of(T) __alignof(T)
#elif COMPILER_CLANG
#define mem_align_of(T) __alignof(T)
#elif COMPILER_GCC
#define mem_align_of(T) __alignof__(T)
#else
#error AlignOf not defined for this compiler.
#endif

#if COMPILER_MSVC
#define mem_align_to(x) __declspec(align(x))
#elif COMPILER_CLANG || COMPILER_GCC
#define mem_align_to(x) __attribute__((aligned(x)))
#else
#error AlignType not defined for this compiler.
#endif


function void* mem_reserve(u64 size, u32 large_pages);
function u8 mem_commit(void* ptr, u64 size, u32 large_pages);
function void mem_decommit(void* ptr, u64 size);
function void mem_release(void* ptr, u64 size);

function u64 mem_page_size();
function u64 mem_large_page_size();

////////////////////////////////
// DS: LinkList

#define dll_push_back_np(head, tail, node, next, prev) (                \
    (head) == 0 ?                                                       \
    (                                                                   \
        (head) = (tail) = (node),                                       \
        (node)->next = (node)->prev = 0                                 \
    ) :                                                                 \
    (                                                                   \
        (node)->prev = (tail),                                          \
        (tail)->next = (node),                                          \
        (tail) = (node),                                                \
        (node)->next = 0                                                \
    )                                                                   \
)

#define dll_remove_np(head, tail, node, next, prev) (                   \
    (head) == (node) ?                                                  \
    (                                                                   \
        (head) == (tail) ?                                              \
        (                                                               \
            (head) = (tail) = 0                                         \
        ) :                                                             \
        (                                                               \
            (head) = (head)->next,                                      \
            (head)->prev = 0                                            \
        )                                                               \
    ) :                                                                 \
    (                                                                   \
        (tail) == (node) ?                                              \
        (                                                               \
            (tail) = (tail)->prev,                                      \
            (tail)->next = 0                                            \
        ) :                                                             \
        (                                                               \
            (node)->next->prev = (node)->prev,                          \
            (node)->prev->next = (node)->next                           \
        )                                                               \
    )                                                                   \
)

#define sll_push_front_n(head, tail, node, next) (                      \
    (node)->next = (head),                                              \
    ((head) == 0 ? (tail) = (node) : 0),                                \
    (head) = (node)                                                     \
)

#define sll_push_back_n(head, tail, node, next) (                       \
    (node)->next = 0,                                                   \
    ((head) == 0 ? ((head) = (node)) : ((tail)->next = (node))),        \
    (tail) = (node)                                                     \
)

#define sll_pop_front_n(head, tail, next) (                             \
    (head) == (tail) ? ((head) = (tail) = 0) : ((head) = (head)->next)  \
)

#define sll_pop_back_n(head, tail, next) (                              \
    (head) == (tail) ? ((head) = (tail) = 0) : ((head) = (head)->next)  \
)

#define dll_push_front_np(head, tail, node, next, prev) dll_push_back_np(tail, head, node, prev, next)

#define dll_push_back(head, tail, node)  dll_push_back_np(head, tail, node, next, prev)
#define dll_push_front(head, tail, node) dll_push_front_np(head, tail, node, next, prev)
#define dll_remove(head, tail, node)     dll_remove_np(head, tail, node, next, prev)

#define sll_push_front(head, tail, node) sll_push_front_n(head, tail, node, next)
#define sll_push_back(head, tail, node)  sll_push_back_n(head, tail, node, next)
#define sll_pop_front(head, tail)        sll_pop_front_n(head, tail, next)
#define sll_pop_back(head, tail)         sll_pop_back_n(head, tail, next)

#define sll_stack_push(head, tail, node) sll_push_front(head, tail, node)
#define sll_stack_pop(head, tail)        sll_pop_front(head, tail)

#define sll_queue_push(head, tail, node) sll_push_back(head, tail, node)
#define sll_queue_pop(head, tail)        sll_pop_front(head, tail)

////////////////////////////////
// Module: Arena

typedef struct ArenaTempNode {
    struct ArenaTempNode* next;
}ArenaTempNode;

typedef struct Arena {
    u64 cursor;
    u64 committed;
    u64 reserved;
    ArenaTempNode* temp_stack_tail;
    ArenaTempNode* temp_stack_head;
    u32 page_size;
    u8 can_commit_large_pages;
}Arena;


#define ARENA_HEADER_SIZE align_up_pow2(sizeof(Arena), 64)

function Arena* arena_alloc(u64 reserve_size, u32 can_commit_large_pages);
function void arena_release(Arena* arena);
function void arena_reset(Arena* arena);

function void* arena_push(Arena* arena, u64 size, u64 align);
#define arena_push_struct(arena, T) (T*)arena_push(arena, sizeof(T), mem_align_of(T))
#define arena_push_array(arena, T, count) (T*)arena_push(arena, sizeof(T) * (count), mem_align_of(T))

function void arena_temp_push(Arena* arena);
function void arena_temp_pop(Arena* arena);
function void arena_temp_pop_all(Arena* arena);

function Arena* arena_scratch_alloc();
function void arena_scratch_release(Arena* arena);

////////////////////////////////
// Strings

#define str_npos (u64)(-1)

typedef struct Str8 {
    u8* data;
    u64 size;
}Str8;

typedef struct Str16 {
    u16* data;
    u64 size;
}Str16;

typedef struct Str32 {
    u32* data;
    u64 size;
}Str32;

typedef struct UnicodeDecode {
    u32 inc;
    u32 codepoint;
}UnicodeDecode;

typedef enum CharType {
    CHAR_TYPE_SPACE     = (1 << 0),
    CHAR_TYPE_UPPER     = (1 << 1),
    CHAR_TYPE_LOWER     = (1 << 2),
    CHAR_TYPE_DIGIT10   = (1 << 3),
    CHAR_TYPE_DIGIT16   = (1 << 4)
}CharType;

mem_align_to(64) global u8 ASCII_LUT[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, CHAR_TYPE_SPACE, CHAR_TYPE_SPACE, CHAR_TYPE_SPACE, CHAR_TYPE_SPACE, CHAR_TYPE_SPACE, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    CHAR_TYPE_SPACE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), (CHAR_TYPE_DIGIT10 | CHAR_TYPE_DIGIT16), 0, 0, 0, 0, 0, 0,
    0, (CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_UPPER | CHAR_TYPE_DIGIT16), CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER,
    CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, CHAR_TYPE_UPPER, 0, 0, 0, 0, 0,
    0, (CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16), (CHAR_TYPE_LOWER | CHAR_TYPE_DIGIT16), CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER,
    CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, CHAR_TYPE_LOWER, 0, 0, 0, 0, 0,

    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
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

function Str8 str8_from_cstr(u8* str);
#define str8(str) str8_from_cstr((u8*)str)
function Str8 str8_of_size(Arena* arena, u64 size);
function Str8 str8_from_fmt(Arena *arena, const char *fmt, ...);
function Str8 str8_concat(Arena* arena, Str8 a, Str8 b);
function Str8 __str8_concat_n(Arena* arena, ...);
#define str8_concat_n(arena, ...) __str8_concat_n(arena, __VA_ARGS__, (Str8){.size = str_npos})
function void str8_to_lower(Str8 str);
function void str8_to_upper(Str8 str);
function u8 str8_match(Str8 a, Str8 b);
function Str8 str8_copy(Arena* arena, Str8 str);

function Str16 str16_from_cstr(u16* str);
#define str16 str16_from_cstr
function Str16 str16_of_size(Arena* arena, u64 size);
function Str16 str16_concat(Arena* arena, Str16 a, Str16 b);
function u8 str16_match(Str16 a, Str16 b);
function Str16 str16_copy(Arena* arena, Str16 str);

function UnicodeDecode utf8_decode(u8* str, u64 max);
function UnicodeDecode utf16_decode(u16* str, u64 max);
function u32 utf8_encode(u8* str, u32 codepoint);
function u32 utf16_encode(u16* str, u32 codepoint);
function u32 utf8_size(u32 cp);
function u32 utf16_size(u32 cp);

function Str8 str8_from_16(Arena* arena, Str16 str);
function Str8 str8_from_32(Arena* arena, Str32 str);

function Str16 str16_from_8(Arena* arena, Str8 str);

function Str32 str32_from_8(Arena* arena, Str8 str);

////////////////////////////////
// Module: CLI

function void cli_attach_if_exists();

////////////////////////////////
// Module: Clock

function u64 clock_resolution_us();
function u64 clock_ticks_now();

////////////////////////////////
// Module Timer

typedef struct Timer {
    u64 ticks;
    float delta;
    u64 resolution_us;
    f64 inverse_ticks_per_us;
}Timer;

function Timer timer_start();
function void timer_update(Timer* timer);
function u64 timer_get_timestamp(Timer* timer);

////////////////////////////////
// Module: File

typedef Handle FileHandle;

typedef enum FileAccessFlag {
    FILE_ACCESS_FLAG_OPEN_EXISTING  = 1 << 0,
    FILE_ACCESS_FLAG_OPEN_ALWAYS    = 1 << 1,
    FILE_ACCESS_FLAG_SHARE_READ     = 1 << 2,
    FILE_ACCESS_FLAG_SHARE_WRITE    = 1 << 3,
    FILE_ACCESS_FLAG_EXECUTE        = 1 << 5,
    FILE_ACCESS_FLAG_READ           = 1 << 6,
    FILE_ACCESS_FLAG_WRITE          = 1 << 7,
    FILE_ACCESS_FLAG_APPEND         = 1 << 8
}FileAccessFlag;

function u32 file_delete(Str8 path);
function u32 file_copy(Str8 src, Str8 dest);
function u32 file_move(Str8 src, Str8 dest);
function u32 file_exists(Str8 path);
function u32 file_directory_exists(Str8 path);

function FileHandle file_open(Str8 name, FileAccessFlag flags);
function u64 file_size(FileHandle handle);
function void file_close(FileHandle handle);
function u8* file_read(Arena* arena, FileHandle handle, u64 begin, u64 end);
#define file_read_struct(arena, handle, offset) file_read((arena), (handle), (offset), (offset) + sizeof(*(struct_ptr)))
function void file_write(FileHandle handle, u64 begin, u64 end, void* data);
#define file_write_struct(handle, offset, struct_ptr) file_write((handle), (offset), (offset) + sizeof(*(struct_ptr)), (struct_ptr))
#define file_write_string(handle, str) file_write((handle), 0, str.size, str.data)

////////////////////////////////
// Module: File Watcher

typedef enum FileEventType {
    FILE_EVENT_TYPE_NULL,
    FILE_EVENT_TYPE_MODIFIED,
    FILE_EVENT_TYPE_ADDED,
    FILE_EVENT_TYPE_DELETED,
    FILE_EVENT_TYPE_RENAMED,
}FileEventType;

typedef struct FileEvent {
    Str8 file_name;
    FileEventType type;
}FileEvent;

typedef struct Win32FileWatcher FileWatcher;

function FileWatcher file_watcher_create(Str8 path, u32 watch_sub_directory);
function FileEvent* file_watcher_poll_events(FileWatcher* watcher, Arena* arena, u32 timeout_ms, u32* out_count);
function void file_watcher_destroy(FileWatcher* watcher);

////////////////////////////////
// Module: Lib

typedef Handle LibHandle;

function LibHandle lib_load(Str8 name);
function void lib_unload(LibHandle handle);
function void* __lib_get_symbol(LibHandle lib, char* name);
#define lib_get_symbol(lib, name) __lib_get_symbol(lib, __STRING__(name))

//////////////////////////////
// DS: DArray

typedef struct DArrayHeader DArrayHeader;
struct DArrayHeader { u64 size; };

#define __darray__ union { u64 size; DArrayHeader header; };

typedef struct DArrayMetaData DArrayMetaData;
struct DArrayMetaData {
    u8 shift;
    u8 chunks_n;
    u64 el_size;
};

function force_inline void* darray_handle(Arena* arena, DArrayHeader* header, DArrayMetaData meta, u64 index);


////////////////////////////////
// MX

#ifdef MSTD_USE_MATH
#include "mx/mstd_math.h"
#endif

#if LANG_CXX
}
#endif

#endif // MSTD_V1_H