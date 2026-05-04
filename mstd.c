#if OS_WINDOWS
#include "mstd_win32.c"
#endif

////////////////////////////////
// Arena

function Arena* arena_alloc_opt(u64 reserve_size, ArenaOpt opt) {
    u64 page_size = (opt.large_pages) ? mem_large_page_size() : mem_page_size();
    debug_validate(page_size);

    u64 actual_reserve = align_up_pow2(reserve_size, page_size);
    u64 initial_commit = align_up_pow2(ARENA_HEADER_SIZE, page_size);

    void* memory = mem_reserve(actual_reserve, opt.large_pages);
    debug_validate(memory);
    mem_commit(memory, initial_commit, opt.large_pages);

    Arena* arena = (Arena*)memory;
    arena->committed                = initial_commit;
    arena->reserved                 = reserve_size;
    arena->page_size                = page_size;
    arena->cursor                   = ARENA_HEADER_SIZE;
    arena->can_commit_large_pages   = opt.large_pages;
    arena->temp_stack_head          = 0;
    arena->temp_stack_tail          = 0;

    return arena;
}

function void arena_release(Arena* arena) {
    debug_validate(arena);
    mem_release(arena, arena->reserved);
}

function void* arena_push(Arena* arena, u64 size, u64 align) {
    debug_validate(arena);
    u64 begin_pos = align_up_pow2(arena->cursor, align);
    u64 end_pos = begin_pos + size;

    debug_validate(end_pos <= arena->reserved);

    if (end_pos > arena->committed) {
        u64 commit_target = align_up_pow2(end_pos, (u64)arena->page_size);
        u64 commit_size = clamp_top(commit_target, arena->reserved) - arena->committed;
        mem_commit((u8*)arena + arena->committed, commit_size, arena->can_commit_large_pages);
        arena->committed = commit_target;
    }

    void* user_ptr = (u8*)arena + begin_pos;
    arena->cursor = end_pos;

    return user_ptr;
}

function void arena_reset(Arena* arena) {
    debug_validate(arena);

    if (arena->temp_stack_head)
        arena->cursor = (u8*)arena->temp_stack_head - (u8*)arena + sizeof(ArenaTempNode);
    else
        arena->cursor = ARENA_HEADER_SIZE;
}

function void arena_reset_forced(Arena* arena) {
    debug_validate(arena);

    arena->temp_stack_head = 0;
    arena->temp_stack_tail = 0;
    arena->cursor = ARENA_HEADER_SIZE;
}

function void arena_temp_push(Arena* arena) {
    debug_validate(arena);
    ArenaTempNode* node = arena_push_struct(arena, ArenaTempNode);
    sll_stack_push(arena->temp_stack_head, arena->temp_stack_tail, node);
}

function void arena_temp_pop(Arena* arena) {
    debug_validate(arena);

    if (arena->temp_stack_head) {
        u64 cursor = (u8*)arena->temp_stack_head - (u8*)arena;
        sll_stack_pop(arena->temp_stack_head, arena->temp_stack_tail);
        arena->cursor = cursor;
    }
}

function void arena_temp_pop_all(Arena* arena) {
    debug_validate(arena);

    if (arena->temp_stack_tail) {
        arena->cursor = (u8*)arena->temp_stack_tail - (u8*)arena;
        arena->temp_stack_head = 0;
        arena->temp_stack_tail = 0;
    }
}

#define ARENA_SCRATCH_POOL_COUNT 8

global thread_var Arena* arena_scratch_pool[ARENA_SCRATCH_POOL_COUNT] = { 0 };
global thread_var u8     arena_scratch_pool_available_mask = (1u << ARENA_SCRATCH_POOL_COUNT) - 1;

function Arena* arena_scratch_alloc() {
    i32 index = u32_lsb((u32)arena_scratch_pool_available_mask);

    if (index >= 0 && index < ARENA_SCRATCH_POOL_COUNT) {
        Arena* arena = arena_scratch_pool[index];
        if (arena == 0) {
            arena = arena_alloc(MB(100));
            arena_scratch_pool[index] = arena;
        }
        arena_reset(arena);
        arena_scratch_pool_available_mask &= ~(1u << index);
        return arena;
    }
    return 0;
}

function void arena_scratch_release(Arena* arena) {
    debug_validate(arena);

    for (i32 i = 0; i < ARENA_SCRATCH_POOL_COUNT; ++i) {
        if (arena_scratch_pool[i] == arena) {
            arena_scratch_pool_available_mask |= (1u << i);
            return;
        }
    }
    trap();
}

////////////////////////////////
// Strings

function Str8 str8_from_cstr(u8* str) {
    u64 size = 0;
    for (;str[size] != 0; size++);

    Str8 result = { 0 };
    result.data = str;
    result.size = size;

    return result;
}

function Str8 str8_of_size(Arena* arena, u64 size) {
    debug_validate(arena);

    Str8 result = { 0 };

    result.data = arena_push_array(arena, u8, size + 1);
    result.data[size] = 0;
    result.size = size;

    return result;
}

function Str8 str8_from_fmt(Arena *arena, const char *fmt, ...) {
    Str8 result = {0};

    va_list args;
    va_start(args, fmt);

    va_list args_copy;
    va_copy(args_copy, args);
    int length = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    if (length) {
        result = str8_of_size(arena, length);
        vsnprintf((char *)result.data, result.size + 1, fmt, args);
    }

    va_end(args);
    return result;
}

function Str8 __str8_concat_n(Arena* arena, ...) {
    debug_validate(arena);
    va_list args;
    u64 size = 0;

    va_start(args, arena);
    for(;;) {
        Str8 s = va_arg(args, Str8);
        if (s.data == 0) break;
        size += s.size;
    }
    va_end(args);

    u8* buffer = arena_push_array(arena, u8, size);
    u64 offset = 0;

    va_start(args, arena);
    for(;;) {
        Str8 s = va_arg(args, Str8);
        if (s.data == 0 && s.size == str_npos) break;
        mem_copy(buffer + offset, s.data, s.size);
        offset += s.size;
    }
    va_end(args);

    return (Str8){.size = size, .data = buffer};
}

function Str8 str8_concat(Arena* arena, Str8 a, Str8 b) {
    debug_validate(arena);
    Str8 result = str8_of_size(arena, a.size + b.size);

    mem_copy(result.data, a.data, a.size);
    mem_copy(result.data + a.size, b.data, b.size);
    result.data[result.size] = 0;

    return result;
}

function void str8_to_lower(Str8 str) {
    for (u64 i = 0; i < str.size; i++) {
        str.data[i] = str8_char_to_lower(str.data[i]);
    }
}

function void str8_to_upper(Str8 str) {
    for (u64 i = 0; i < str.size; i++) {
        str.data[i] = str8_char_to_upper(str.data[i]);
    }
}

function u8 str8_match(Str8 a, Str8 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size) : 0;
}


function Str8 str8_copy(Arena* arena, Str8 str) {
    debug_validate(arena);
    Str8 string = str8_of_size(arena, str.size);

    mem_copy_array(string.data, str.data, str.size);
    string.data[string.size] = 0;

    return string;
}

function Str16 str16_from_cstr(u16* str) {
    u64 size = 0;
    for (;str[size] != 0; size++);

    Str16 result = { 0 };
    result.data = str;
    result.size = size;

    return result;
}

function Str16 str16_of_size(Arena* arena, u64 size) {
    debug_validate(arena);
    Str16 result = { 0 };

    result.data = arena_push_array(arena, u16, size + 1);
    result.data[size] = 0;
    result.size = size;

    return result;
}

function Str16 str16_concat(Arena* arena, Str16 a, Str16 b) {
    debug_validate(arena);
    Str16 result = str16_of_size(arena, a.size + b.size);

    mem_copy(result.data, a.data, a.size);
    mem_copy(result.data + a.size, b.data, b.size);
    result.data[result.size] = 0;

    return result;
}

function u8 str16_match(Str16 a, Str16 b) {
    return (a.size == b.size) ? mem_match(a.data, b.data, a.size * sizeof(u16)) : 0;
}

function Str16 str16_copy(Arena* arena, Str16 str) {
    debug_validate(arena);
    Str16 string = str16_of_size(arena, str.size);

    mem_copy_array(string.data, str.data, str.size);
    string.data[string.size] = 0;

    return string;
}

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

function Str8 str8_from_16(Arena* arena, Str16 str) {
    debug_validate(arena);
    Str8 result = { 0 };

    u16* ptr = str.data;
    u16* opl = ptr + str.size;
    u64 size = 0;

    for (; ptr < opl; ) {
        UnicodeDecode d = utf16_decode(ptr, opl - ptr);
        ptr += d.inc;
        size += utf8_size(d.codepoint);
    }

    u8* out = arena_push_array(arena, u8, size + 1);

    ptr = str.data;
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

function Str16 str16_from_8(Arena* arena, Str8 str) {
    debug_validate(arena);
    Str16 result = { 0 };
    if (!str.size) return result;

    u8* ptr = str.data;
    u8* opl = ptr + str.size;

    u64 size = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf8_decode(ptr, opl - ptr);
        ptr += d.inc;
        size += utf16_size(d.codepoint);
    }

    u16* out = arena_push_array(arena, u16, size + 1);

    ptr = str.data;
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

function Str8 str8_from_32(Arena* arena, Str32 str) {
    debug_validate(arena);
    Str8 result = { 0 };
    if (!str.size) return result;

    u32* ptr = str.data;
    u32* opl = ptr + str.size;

    u64 size = 0;
    for (; ptr < opl; ptr++) {
        size += utf8_size(*ptr);
    }

    u8* out = arena_push_array(arena, u8, size + 1);

    u64 at = 0;
    for (ptr = str.data; ptr < opl; ptr++) {
        at += utf8_encode(out + at, *ptr);
    }

    out[size] = 0;
    result.data = out;
    result.size = size;
    return result;
}

function Str32 str32_from_8(Arena* arena, Str8 str) {
    debug_validate(arena);
    Str32 result = { 0 };
    if (!str.size) return result;

    u8* ptr = str.data;
    u8* opl = ptr + str.size;

    u64 size = 0;
    for (; ptr < opl; ) {
        UnicodeDecode d = utf8_decode(ptr, opl - ptr);
        ptr += d.inc;
        size += 1;
    }

    u32* out = arena_push_array(arena, u32, size + 1);

    ptr = str.data;
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

////////////////////////////////
// Module: Timer

function Timer timer_start() {
    Timer timer = { 0 };
    timer.ticks = clock_ticks_now();
    timer.delta = 16666.6f;

    timer.resolution_us = clock_resolution_us();
    timer.inverse_ticks_per_us = 1000000.0 / (f64)timer.resolution_us;

    return timer;
}

function void timer_update(Timer* timer) {
    u64 current_ticks = clock_ticks_now();

    u64 elapsed_ticks = (current_ticks > timer->ticks) ? (current_ticks - timer->ticks) : 0;
    double us = (double)elapsed_ticks * timer->inverse_ticks_per_us;
    if (us > 200000.0) us = 200000.0;

    timer->delta = (float)us;
    timer->ticks = current_ticks;
}

function u64 timer_get_timestamp(Timer* timer) {
    return (u64)(timer->ticks * timer->inverse_ticks_per_us);
}

//////////////////////////////
// DS: DArray

function force_inline void* darray_handle(Arena* arena, DArrayHeader* header, DArrayMetaData meta, u64 index) {
    u8** chunks = (u8**)(header + 1);

    u64 i_shift = index >> meta.shift;
    i8 chunks_i = u64_msb(i_shift + 1);

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