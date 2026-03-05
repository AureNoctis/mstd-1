function force_inline void* darray_handle(Arena* arena, DArrayHeader* header, DarrayMetaData meta, u64 index) {
    u8** chunks = (u8**)(header + 1);

    u64 i_shift = index >> meta.shift;
    i8 msb = u64_msb(i_shift + 1);
    i8 chunks_i = msb;

    if (arena && chunks_i < meta.chunks_n) {
        for (i8 i = 0; i <= chunks_i; ++i) {
            if (chunks[i] == 0) {
                u64 tier_size = (u64)1 << (i + meta.shift);
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