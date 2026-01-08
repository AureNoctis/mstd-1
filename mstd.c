#include "mstd.h"
#include <math.h>

#ifdef OS_WINDOWS
    #include "mstd_win32.c"
#endif

////////////////////////////////
 //Types: Arena

#define ARENA_DEFAULT_COMMIT_SIZE MB(4)
#define ARENA_DEFAULT_RESERVE_SIZE GB(1)
#define ARENA_INITIAL_MEM_ALIGNMENT 64
#define ARENA_HEADER_SIZE align_up_pow2(sizeof(Arena), ARENA_INITIAL_MEM_ALIGNMENT)

function Arena* arena_alloc(u64 reserve_size, ArenaFlag flag) {
    u64 page_size = 0;

    void* memory;
    if ((flag & arena_flag_commit_large_pages) && os_get_process_info()->large_pages_allowed) {
        page_size = os_get_system_info()->large_page_size;
        reserve_size = align_up_pow2(reserve_size, page_size);
        memory = os_reserve_large(reserve_size);
        os_commit_large(memory, clamp_bottom(ARENA_DEFAULT_COMMIT_SIZE, os_get_system_info()->large_page_size));
    }
    else {
        flag &= ~arena_flag_commit_large_pages;
        page_size = os_get_system_info()->page_size;
        reserve_size = align_up_pow2(reserve_size, page_size);
        memory = os_reserve(reserve_size);
        os_commit(memory, clamp_bottom(ARENA_DEFAULT_COMMIT_SIZE, os_get_system_info()->page_size));
    }

    Arena* result = (Arena*)memory;
    result->flags = flag;
    result->reserved = reserve_size;
    result->cursor = ARENA_HEADER_SIZE;
    result->commited = page_size;

    return result;
}

function void arena_release(Arena *arena) {
    os_release(arena, arena->reserved);
}

function void* arena_push(Arena* arena, u64 size, u64 align) {
    void* result = 0;
    u64 begin_pos = align_up_pow2(arena->cursor, align);
    u64 end_pos = begin_pos + size;

    if(end_pos > arena->commited && end_pos <= arena->reserved) {
        u64 commit_size = clamp_top(align_up_pow2(end_pos, ARENA_DEFAULT_COMMIT_SIZE), arena->reserved) - arena->commited;
        void* commit_pointer = (u8*)arena + arena->commited;
        b8 commit_success = (arena->flags & arena_flag_commit_large_pages) ?
                                os_commit_large(commit_pointer, commit_size) :
                                os_commit(commit_pointer, commit_size);
        if(commit_success)
            arena->commited += commit_size;
    }

    if (end_pos <= arena->commited){
        result = (u8*)arena + begin_pos;
        arena->cursor = end_pos;
    }

    return result;
}

function ArenaTemp arena_temp_begin(Arena* arena) {
    ArenaTemp temp;
    temp.arena = arena;
    temp.cursor = arena->cursor;
    return temp;
}

function void arena_temp_end(ArenaTemp temp) {
    temp.arena->cursor = temp.cursor;
    temp.arena = NULL;
}

function void arena_reset(Arena* arena) {
    arena->cursor = ARENA_HEADER_SIZE;
}

#define ARENA_SCRATCH_POOL_COUNT 8

global thread_var Arena *__arena_scratch[ARENA_SCRATCH_POOL_COUNT] = {0};
global thread_var u8     __arena_scratch_available_mask = (1u << ARENA_SCRATCH_POOL_COUNT) - 1;

function ArenaScratch arena_scratch_begin(void) {
    ArenaScratch scratch = {0};
    i32 index = u32_lsb((u32)__arena_scratch_available_mask);

    if(index >= 0 && index < ARENA_SCRATCH_POOL_COUNT) {
        Arena **slot = &__arena_scratch[index];
        if (*slot == 0)
            *slot = arena_alloc(ARENA_DEFAULT_RESERVE_SIZE, arena_flag_none);
        (*slot)->cursor = 0;
        __arena_scratch_available_mask &= ~(1u << index);
        scratch.arena = *slot;
        scratch.index = (u32)index;
    }
    return scratch;
}

function void arena_scratch_end(ArenaScratch scratch) {
    if (scratch.arena != 0)
        __arena_scratch_available_mask |= (u8)(1u << scratch.index);
}

////////////////////////////////
// Types: Str8, Str16, Str32

function Str8 str8_from_cstr(u8* str) {
    Str8 text;
    text.data = str;
    text.size = strlen((char*)str);
    return text;
}

function Str8 str8_of_size(Arena* arena, u64 size) {
    Str8 text;
    text.data = arena_push_array(arena, u8, size + 1);
    text.size = size;
    text.data[text.size] = 0;
    return text;
}

function Str16 str16_of_size(Arena* arena, u64 size) {
    Str16 text;
    text.data = arena_push_array(arena, u16, size + 1);
    text.size = size;
    text.data[text.size] = 0;
    return text;
}

function void str8_to_lower(Str8 text) {
    for (u64 i = 0; i < text.size; i++) {
        text.data[i] = str8_char_to_lower(text.data[i]);
    }
}

function void str8_to_upper(Str8 text) {
    for (u64 i = 0; i < text.size; i++) {
        text.data[i] = str8_char_to_upper(text.data[i]);
    }
}

function b8 str8_equal(Str8 a, Str8 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size) : 0;
}

function Str16 str16_from_cstr(u16* str) {
    Str16 text;
    text.data = str;
    text.size = 0;
    while (text.data[text.size] != 0) text.size++;
    return text;
}

function b8 str16_equal(Str16 a, Str16 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size * sizeof(u16)) : 0;
}


// --- function Decode Helpers ---

const global u8 utf8_class[32] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,2,2,2,3,3,4,5,
};

internal function UnicodeDecode utf8_decode(u8* str, u64 max) {
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

internal function UnicodeDecode utf16_decode(u16* str, u64 max) {
    UnicodeDecode result = { 1, UINT32_MAX };
    result.codepoint = str[0];
    result.inc = 1;
    if (max > 1 && 0xD800 <= str[0] && str[0] < 0xDC00 && 0xDC00 <= str[1] && str[1] < 0xE000) {
        result.codepoint = ((str[0] - 0xD800) << 10) | ((str[1] - 0xDC00) + 0x10000);
        result.inc = 2;
    }
    return result;
}

internal function u32 utf8_encode(u8* str, u32 codepoint) {
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

internal function u32 utf16_encode(u16* str, u32 codepoint) {
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

internal function u32 utf8_size(u32 cp) {
    if (cp <= 0x7F)       return 1;
    if (cp <= 0x7FF)      return 2;
    if (cp <= 0xFFFF)     return 3;
    return 4;
}

internal function u32 utf16_size(u32 cp) {
    if (cp > 0x10FFFF) return 0;
    if (cp >= 0xD800 && cp <= 0xDFFF) return 0;
    if (cp <= 0xFFFF) return 1;
    return 2;
}


function Str8 str8_from_16(Arena* arena, Str16 text) {
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

function Str16 str16_from_8(Arena* arena, Str8 text) {
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

function Str8 str8_from_32(Arena* arena, Str32 text) {
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

function Str32 str32_from_8(Arena* arena, Str8 text) {
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

function Str8 str8_copy(Arena* arena, Str8 text) {
    Str8 string = str8_of_size(arena, text.size);
    mem_copy_array(string.data, text.data, text.size);
    string.data[string.size] = 0;
    return string;
}

function Str16 str16_copy(Arena* arena, Str16 text) {
    Str16 string = str16_of_size(arena, text.size);
    mem_copy_array(string.data, text.data, text.size);
    string.data[string.size] = 0;
    return string;
}
