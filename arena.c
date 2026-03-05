function Arena* arena_alloc(u64 reserve_size, ArenaFlag flags) {
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

function void arena_release(Arena* arena) {
    os_release(arena, arena->reserved);
}

function void* arena_push(Arena* arena, u64 size, u64 align) {
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
            *slot = arena_alloc(ARENA_DEFAULT_RESERVE_SIZE, ARENA_FLAG_NONE);
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