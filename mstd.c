#include "mstd.h"
#include <math.h>

#if OS_WINDOWS
#include "mstd_win32.c"
#endif

////////////////////////////////
 //Types: Arena

#define ARENA_DEFAULT_COMMIT_SIZE MB(4)
#define ARENA_DEFAULT_RESERVE_SIZE MB(64)
#define ARENA_HEADER_SIZE align_up_pow2(sizeof(Arena), 64)

Arena* arena_alloc(u64 reserve_size, ArenaFlag flags) {
    u64 page_size = (flags & ARENA_FLAG_COMMIT_LARGE_PAGES)
        ? os_get_system_info()->large_page_size
        : os_get_system_info()->page_size;

    u64 actual_reserve = align_up_pow2(reserve_size, page_size);
    u64 initial_commit = align_up_pow2(ARENA_DEFAULT_COMMIT_SIZE, page_size);

    void* memory = os_reserve(actual_reserve, flags & ARENA_FLAG_COMMIT_LARGE_PAGES);
    os_commit(memory, initial_commit, flags & ARENA_FLAG_COMMIT_LARGE_PAGES);

    Arena* arena = (Arena*)memory;
    arena->cursor = ARENA_HEADER_SIZE;
    arena->committed = initial_commit;
    arena->reserved = actual_reserve;
    arena->flags = flags;
    arena->page_size = (u32)page_size;

    debug_trap_if(arena == 0);

    return arena;
}

void arena_release(Arena* arena) {
    os_release(arena, arena->reserved);
}

void* arena_push(Arena* arena, u64 size, u64 align) {
    u64 begin_pos = align_up_pow2(arena->cursor, align);
    u64 end_pos = begin_pos + size;

    debug_trap_if(end_pos > arena->reserved);

    if (end_pos > arena->committed) {
        u64 commit_target = align_up_pow2(end_pos, (u64)arena->page_size);
        u64 commit_size = clamp_top(commit_target, arena->reserved) - arena->committed;
        os_commit((u8*)arena + arena->committed, commit_size, arena->flags & ARENA_FLAG_COMMIT_LARGE_PAGES);
        arena->committed = commit_target;
    }

    void* user_ptr = (u8*)arena + begin_pos;
    arena->cursor = end_pos;

    debug_trap_if(((uptr)user_ptr & (align - 1)) != 0);

    return user_ptr;
}

ArenaTemp arena_temp_begin(Arena* arena) {
    ArenaTemp temp;
    temp.arena = arena;
    temp.cursor = arena->cursor;
    return temp;
}

void arena_temp_end(ArenaTemp temp) {
    temp.arena->cursor = temp.cursor;
    temp.arena = NULL;
}

void arena_reset(Arena* arena) {
    arena->cursor = ARENA_HEADER_SIZE;
}

#define ARENA_SCRATCH_POOL_COUNT 8

global thread_var Arena* __arena_scratch[ARENA_SCRATCH_POOL_COUNT] = { 0 };
global thread_var u8     __arena_scratch_available_mask = (1u << ARENA_SCRATCH_POOL_COUNT) - 1;

ArenaScratch arena_scratch_begin(void) {
    ArenaScratch scratch = { 0 };
    i32 index = u32_lsb((u32)__arena_scratch_available_mask);

    if (index >= 0 && index < ARENA_SCRATCH_POOL_COUNT) {
        Arena** slot = &__arena_scratch[index];
        if (*slot == 0)
            *slot = arena_alloc(ARENA_DEFAULT_RESERVE_SIZE, ARENA_FLAG_NONE);
        (*slot)->cursor = 0;
        __arena_scratch_available_mask &= ~(1u << index);
        scratch.arena = *slot;
        scratch.index = (u32)index;
    }
    return scratch;
}

void arena_scratch_end(ArenaScratch scratch) {
    if (scratch.arena != 0)
        __arena_scratch_available_mask |= (u8)(1u << scratch.index);
}

////////////////////////////////
// Types: Str8, Str16, Str32

Str8 str8_from_cstr(u8* str) {
    Str8 text;
    text.data = str;
    text.size = strlen((char*)str);
    return text;
}

Str8 str8_of_size(Arena* arena, u64 size) {
    Str8 text;
    text.data = arena_push_array(arena, u8, size + 1);
    text.size = size;
    text.data[text.size] = 0;
    return text;
}

Str16 str16_of_size(Arena* arena, u64 size) {
    Str16 text;
    text.data = arena_push_array(arena, u16, size + 1);
    text.size = size;
    text.data[text.size] = 0;
    return text;
}

void str8_to_lower(Str8 text) {
    for (u64 i = 0; i < text.size; i++) {
        text.data[i] = str8_char_to_lower(text.data[i]);
    }
}

void str8_to_upper(Str8 text) {
    for (u64 i = 0; i < text.size; i++) {
        text.data[i] = str8_char_to_upper(text.data[i]);
    }
}

b8 str8_equal(Str8 a, Str8 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size) : 0;
}

Str16 str16_from_cstr(u16* str) {
    Str16 text;
    text.data = str;
    text.size = 0;
    while (text.data[text.size] != 0) text.size++;
    return text;
}

b8 str16_equal(Str16 a, Str16 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size * sizeof(u16)) : 0;
}


// ---  Decode Helpers ---

const global u8 utf8_class[32] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,2,2,2,3,3,4,5,
};

internal  UnicodeDecode utf8_decode(u8* str, u64 max) {
    UnicodeDecode result = { 1, UINT32_MAX };
    u8 byte = str[0];
    u8 byte_class = utf8_class[byte >> 3];
    switch (byte_class) {
    case 1: {
        result.codepoint = byte;
    }break;
    case 2: {
        if (1 < max) {
            u8 cont_byte = str[1];
            if (utf8_class[cont_byte >> 3] == 0) {
                result.codepoint = (byte & 0x1f) << 6;
                result.codepoint |= (cont_byte & 0x3f);
                result.inc = 2;
            }
        }
    }break;
    case 3: {
        if (2 < max) {
            u8 cont_byte[2] = { str[1], str[2] };
            if (utf8_class[cont_byte[0] >> 3] == 0 && utf8_class[cont_byte[1] >> 3] == 0) {
                result.codepoint = (byte & 0xf) << 12;
                result.codepoint |= ((cont_byte[0] & 0x3f) << 6);
                result.codepoint |= (cont_byte[1] & 0x3f);
                result.inc = 3;
            }
        }
    }break;
    case 4: {
        if (3 < max) {
            u8 cont_byte[3] = { str[1], str[2], str[3] };
            if (utf8_class[cont_byte[0] >> 3] == 0 && utf8_class[cont_byte[1] >> 3] == 0 && utf8_class[cont_byte[2] >> 3] == 0) {
                result.codepoint = (byte & 0x7) << 18;
                result.codepoint |= ((cont_byte[0] & 0x3f) << 12);
                result.codepoint |= ((cont_byte[1] & 0x3f) << 6);
                result.codepoint |= (cont_byte[2] & 0x3f);
                result.inc = 4;
            }
        }
    }
    }
    return result;
}

internal  UnicodeDecode utf16_decode(u16* str, u64 max) {
    UnicodeDecode result = { 1, UINT32_MAX };
    result.codepoint = str[0];
    result.inc = 1;
    if (max > 1 && 0xD800 <= str[0] && str[0] < 0xDC00 && 0xDC00 <= str[1] && str[1] < 0xE000) {
        result.codepoint = ((str[0] - 0xD800) << 10) | ((str[1] - 0xDC00) + 0x10000);
        result.inc = 2;
    }
    return result;
}

internal  u32 utf8_encode(u8* str, u32 codepoint) {
    u32 inc = 0;
    if (codepoint <= 0x7F) {
        str[0] = (u8)codepoint;
        inc = 1;
    }
    else if (codepoint <= 0x7FF) {
        str[0] = (0x3 << 6) | ((codepoint >> 6) & 0x1f);
        str[1] = (1 << 7) | (codepoint & 0x3f);
        inc = 2;
    }
    else if (codepoint <= 0xFFFF) {
        str[0] = (0x7 << 5) | ((codepoint >> 12) & 0xf);
        str[1] = (1 << 7) | ((codepoint >> 6) & 0x3f);
        str[2] = (1 << 7) | (codepoint & 0x3f);
        inc = 3;
    }
    else if (codepoint <= 0x10FFFF) {
        str[0] = (0xf << 4) | ((codepoint >> 18) & 0x7);
        str[1] = (1 << 7) | ((codepoint >> 12) & 0x3f);
        str[2] = (1 << 7) | ((codepoint >> 6) & 0x3f);
        str[3] = (1 << 7) | (codepoint & 0x3f);
        inc = 4;
    }
    else {
        str[0] = '?';
        inc = 1;
    }
    return inc;
}

internal  u32 utf16_encode(u16* str, u32 codepoint) {
    u32 inc = 1;
    if (codepoint == UINT32_MAX)
        str[0] = (u16)'?';
    else if (codepoint < 0x10000)
        str[0] = (u16)codepoint;
    else {
        u32 v = codepoint - 0x10000;
        str[0] = (u16)(0xD800 + (v >> 10));
        str[1] = (u16)(0xDC00 + (v & 0x3ff));
        inc = 2;
    }
    return inc;
}

internal  u32 utf8_size(u32 cp) {
    if (cp <= 0x7F)       return 1;
    if (cp <= 0x7FF)      return 2;
    if (cp <= 0xFFFF)     return 3;
    return 4;
}

internal  u32 utf16_size(u32 cp) {
    if (cp > 0x10FFFF) return 0;
    if (cp >= 0xD800 && cp <= 0xDFFF) return 0;
    if (cp <= 0xFFFF) return 1;
    return 2;
}


Str8 str8_from_16(Arena* arena, Str16 text) {
    Str8 result = { 0 };

    u16* ptr = text.data;
    u16* opl = ptr + text.size;
    u64 size = 0;

    for (; ptr < opl; ) {
        UnicodeDecode d = utf16_decode(ptr, opl - ptr);
        ptr += d.inc;
        size += utf8_size(d.codepoint);
    }

    u8* out = arena_push_array(arena, u8, size + 1);

    ptr = text.data;
    u64 at = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf16_decode(ptr, opl - ptr);
        ptr += d.inc;
        at += utf8_encode(out + at, d.codepoint);
    }

    out[size] = 0;
    result.data = out;
    result.size = size;
    return result;
}

Str16 str16_from_8(Arena* arena, Str8 text) {
    Str16 result = { 0 };
    if (!text.size) return result;

    u8* ptr = text.data;
    u8* opl = ptr + text.size;

    u64 size = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf8_decode(ptr, opl - ptr);
        ptr += d.inc;
        size += utf16_size(d.codepoint);
    }

    u16* out = arena_push_array(arena, u16, size + 1);

    ptr = text.data;
    u64 at = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf8_decode(ptr, opl - ptr);
        ptr += d.inc;
        at += utf16_encode(out + at, d.codepoint);
    }

    out[size] = 0;

    result.data = out;
    result.size = size;
    return result;
}

Str8 str8_from_32(Arena* arena, Str32 text) {
    Str8 result = { 0 };
    if (!text.size) return result;

    u32* ptr = text.data;
    u32* opl = ptr + text.size;

    u64 size = 0;
    for (; ptr < opl; ptr++) {
        size += utf8_size(*ptr);
    }

    u8* out = arena_push_array(arena, u8, size + 1);

    u64 at = 0;
    for (ptr = text.data; ptr < opl; ptr++) {
        at += utf8_encode(out + at, *ptr);
    }

    out[size] = 0;
    result.data = out;
    result.size = size;
    return result;
}

Str32 str32_from_8(Arena* arena, Str8 text) {
    Str32 result = { 0 };
    if (!text.size) return result;

    u8* ptr = text.data;
    u8* opl = ptr + text.size;

    u64 size = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf8_decode(ptr, opl - ptr);
        ptr += d.inc;
        size += 1;
    }

    u32* out = arena_push_array(arena, u32, size + 1);

    ptr = text.data;
    u64 at = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf8_decode(ptr, opl - ptr);
        ptr += d.inc;
        out[at++] = d.codepoint;
    }

    out[size] = 0;
    result.data = out;
    result.size = size;
    return result;
}

Str8 str8_copy(Arena* arena, Str8 text) {
    Str8 string = str8_of_size(arena, text.size);
    mem_copy_array(string.data, text.data, text.size);
    string.data[string.size] = 0;
    return string;
}

Str16 str16_copy(Arena* arena, Str16 text) {
    Str16 string = str16_of_size(arena, text.size);
    mem_copy_array(string.data, text.data, text.size);
    string.data[string.size] = 0;
    return string;
}