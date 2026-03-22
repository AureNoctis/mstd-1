#include "mstd.h"

#if OS_WINDOWS
#include "mstd_win32.c"
#endif

#include <math.h>

function Timer timer_init() {
    Timer timer = {0};
    timer.ticks = os_get_ticks();
    timer.delta = 16666.6f;
    timer.smooth_delta = 16666.6f;
    timer.very_smooth_delta = 16666.6f;

    return timer;
}

function void timer_update(Timer* timer) {
    u64 current_ticks = os_get_ticks();

    u64 elapsed_ticks = (current_ticks > timer->ticks) ? (current_ticks - timer->ticks) : 0;
    double us = (double)elapsed_ticks * os_get_inverse_ticks_per_us();
    if (us > 200000.0) us = 200000.0;

    timer->delta = (float)us;
    timer->ticks = current_ticks;

    float diff = timer->delta - timer->smooth_delta;
    float rel_diff = fabsf(diff) / (timer->smooth_delta + 1.0f);
    float f = rel_diff / (1.0f + rel_diff);

    timer->smooth_delta += diff * clamp_bottom(f, 1.0f / 32.0f);
    timer->very_smooth_delta += (timer->delta - timer->very_smooth_delta) * clamp_bottom(f, 1.0f / 128.0f);
}

function force_inline u64 u64_rotl(u64 x, i8 s) {
    const u64 mask = 63;
    u64 n = (u64)s & mask;
    if (n == 0) return x;
    return (x << n) | (x >> ((-(i64)n) & mask));
}

force_inline u64 u64_rotr(u64 x, i8 s) {
    const u64 mask = 63;
    u64 n = (u64)s & mask;
    if (n == 0) return x;
    return (x >> n) | (x << ((-(i64)n) & mask));
}

function Arena* arena_alloc(u64 reserve_size, u32 commit_large_pages) {
    u64 page_size = (commit_large_pages) ? os_get_system_info()->large_page_size : os_get_system_info()->page_size;
    u64 actual_reserve = align_up_pow2(reserve_size, page_size);
    u64 initial_commit = align_up_pow2(ARENA_DEFAULT_COMMIT_SIZE, page_size);

    void* memory = os_mem_reserve(actual_reserve, commit_large_pages);
    os_mem_commit(memory, initial_commit, commit_large_pages);

    Arena* arena = (Arena*)memory;
    arena->cursor = ARENA_HEADER_SIZE;
    arena->committed = initial_commit;
    arena->reserved = actual_reserve;
    arena->commit_large_pages = commit_large_pages;
    arena->page_size = (u32)page_size;

    debug_trap_if(arena == 0);

    return arena;
}

function void arena_release(Arena* arena) {
    os_mem_release(arena, arena->reserved);
}

function void* arena_push(Arena* arena, u64 size, u64 align) {
    u64 begin_pos = align_up_pow2(arena->cursor, align);
    u64 end_pos = begin_pos + size;

    debug_trap_if(end_pos > arena->reserved);

    if (end_pos > arena->committed) {
        u64 commit_target = align_up_pow2(end_pos, (u64)arena->page_size);
        u64 commit_size = clamp_top(commit_target, arena->reserved) - arena->committed;
        os_mem_commit((u8*)arena + arena->committed, commit_size, arena->commit_large_pages);
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

function void arena_temp_end(ArenaTemp temp) {
    temp.arena->cursor = temp.cursor;
    temp.arena = NULL;
}

function void arena_reset(Arena* arena) {
    arena->cursor = ARENA_HEADER_SIZE;
}

#define ARENA_SCRATCH_POOL_COUNT 8

global thread_var Arena* __arena_scratch[ARENA_SCRATCH_POOL_COUNT] = { 0 };
global thread_var u8     __arena_scratch_available_mask = (1u << ARENA_SCRATCH_POOL_COUNT) - 1;

function ArenaScratch arena_scratch_begin() {
    ArenaScratch scratch = { 0 };
    i32 index = u32_lsb((u32)__arena_scratch_available_mask);

    if (index >= 0 && index < ARENA_SCRATCH_POOL_COUNT) {
        Arena** slot = &__arena_scratch[index];
        if (*slot == 0)
            *slot = arena_alloc(ARENA_DEFAULT_RESERVE_SIZE, 0);
        arena_reset((*slot));
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

internal force_inline u64 str8_get_length_from_cstr(u8* data) {
    u64 i = 0;
    for(i; data[i] != 0; i++) {}
    return(i);
}

function Str8 str8_from_cstr(u8* str) {
    Str8 text;
    text.data = str;
    text.size = str8_get_length_from_cstr(str);
    return text;
}

function Str8 _str8_from_fmt(Arena* arena, u8* fmt, ...) {
    Str8 result = { 0 };

    va_list args;
    va_start(args, (char*)fmt);

    va_list args_copy;
    va_copy(args_copy, args);
    int length = vsnprintf(NULL, 0, (char*)fmt, args_copy);
    va_end(args_copy);

    if(length > 0) {
        result = str8_of_size(arena, length);
        vsnprintf((char*)result.data, result.size + 1, (char*)fmt, args);
    }
    va_end(args);

    return result;
}

function Str8 str8_of_size(Arena* arena, u64 size) {
    Str8 text;
    u8* ptr = arena_push_array(arena, u8, size + 1);
    text.data = ptr;
    text.size = size;
    text.data[text.size] = 0;
    return text;
}

function Str16 str16_of_size(Arena* arena, u64 size) {
    Str16 text;
    u16* ptr = arena_push_array(arena, u16, size + 1);
    text.data = ptr;
    text.size = size;
    text.data[text.size] = 0;
    return text;
}

function Str8 str8_concat(Arena* arena, Str8 a, Str8 b) {
    Str8 result = str8_of_size(arena, a.size + b.size);
    mem_copy(result.data, a.data, a.size);
    mem_copy(result.data + a.size, b.data, b.size);
    result.data[result.size] = 0;
    return result;
}

function Str16 str16_concat(Arena* arena, Str16 a, Str16 b) {
    Str16 result = str16_of_size(arena, a.size + b.size);
    mem_copy(result.data, a.data, a.size);
    mem_copy(result.data + a.size, b.data, b.size);
    result.data[result.size] = 0;
    return result;
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

function u8 str8_equal(Str8 a, Str8 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size) : 0;
}

internal force_inline u64 str16_get_length_from_cstr(u16* data) {
    u64 i = 0;
    for(i; data[i] != 0; i++) {}
    return(i);
}

function Str16 str16_from_cstr(u16* str) {
    Str16 text;
    text.data = str;
    text.size = str16_get_length_from_cstr(str);
    return text;
}

function u8 str16_equal(Str16 a, Str16 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size * sizeof(u16)) : 0;
}


// ---  Decode Helpers ---

const global u8 utf8_class[32] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,2,2,2,3,3,4,5,
};

function UnicodeDecode utf8_decode(u8* str, u64 max) {
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

function UnicodeDecode utf16_decode(u16* str, u64 max) {
    UnicodeDecode result = { 1, UINT32_MAX };
    result.codepoint = str[0];
    result.inc = 1;
    if (max > 1 && 0xD800 <= str[0] && str[0] < 0xDC00 && 0xDC00 <= str[1] && str[1] < 0xE000) {
        result.codepoint = ((str[0] - 0xD800) << 10) | ((str[1] - 0xDC00) + 0x10000);
        result.inc = 2;
    }
    return result;
}

function u32 utf8_encode(u8* str, u32 codepoint) {
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

function u32 utf16_encode(u16* str, u32 codepoint) {
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

function u32 utf8_size(u32 cp) {
    if (cp <= 0x7F)       return 1;
    if (cp <= 0x7FF)      return 2;
    if (cp <= 0xFFFF)     return 3;
    return 4;
}

function u32 utf16_size(u32 cp) {
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

function force_inline void* darray_handle(Arena* arena, DArrayHeader* header, DArrayMetaData meta, u64 index) {
    u8** chunks = (u8**)(header + 1);

    u64 i_shift = index >> meta.shift;
    i8 msb = u64_msb(i_shift + 1);
    i8 chunks_i = msb;

    if (arena && chunks_i < meta.chunks_n) {
        for (i8 i = 0; i <= chunks_i; ++i) {
            if (chunks[i] == 0) {
                u64 tier_size = 1ULL << clamp_top((i + meta.shift), 63);
                chunks[i] = (u8*)arena_push(arena, tier_size * meta.el_size, 8);
            }
        }
    }

    u64 elem_i = index;

    if (chunks_i > 0) {
        u64 base = (1ULL << (chunks_i + meta.shift)) - (1ULL << meta.shift);
        elem_i -= base;
    }

    debug_validate(chunks[chunks_i]);
    return chunks[chunks_i] + (elem_i * meta.el_size);
}