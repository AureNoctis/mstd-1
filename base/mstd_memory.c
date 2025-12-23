#include "mstd_memory.h"
#include <os/mstd_os.h>

#define ARENA_HEADER_ALIGNMENT 128
#define ARENA_BASE_ALIGNMENT 16

typedef struct Arena {
    void* memory;
    u64 arena_base_offset;
    u64 offset;
    u64 reserved;
    u64 commited;
    u64 commit_size;
    b8 is_commiting_large_pages;
}Arena;

typedef struct ArenaScratch {
    Arena* arena;
    u64 original_offset;
}ArenaScratch;

Arena* arena_alloc(u64 to_reserve, u64 to_commit, b8 commit_large_pages) {
    u64 page_size = (commit_large_pages) ? os_get_large_page_size() : os_get_page_size();
    u64 reserve_size = align_up_pow2(to_reserve, page_size);
    u64 commit_size  = align_up_pow2(to_commit, page_size);

    if (commit_size < page_size)
        commit_size = page_size;

    if (commit_size > reserve_size)
        reserve_size = commit_size;

    void* mem;

    if (commit_large_pages) {
        mem = os_reserve_large(reserve_size);
        os_commit_large(mem, commit_size);
    }
    else {
        mem = os_reserve(reserve_size);
        os_commit(mem, commit_size);
    }

    Arena* arena = (Arena*)mem;
    arena->memory = mem;
    arena->arena_base_offset = align_up_pow2(sizeof(Arena), ARENA_HEADER_ALIGNMENT);
    arena->commit_size = page_size;
    arena->reserved = reserve_size;
    arena->commited = commit_size;
    arena->offset = 0;
    arena->is_commiting_large_pages = commit_large_pages;

    return arena;
}

void* arena_push(Arena* arena, u64 size, u64 align) {
    u64 begin_offset = align_up_pow2(arena->offset + arena->arena_base_offset, (is_pow2(align) ? align : ARENA_BASE_ALIGNMENT));
    u64 end_offset = begin_offset + size;

    if (arena->commited < end_offset) {
        u64 commit_size = clamp_top(align_up_pow2(end_offset, arena->commit_size), arena->reserved) - arena->commited;
        void* commit_pointer = (void*)((uaddress)arena->memory + arena->commited);

        b8 commit_success = (arena->is_commiting_large_pages) ?
                 os_commit_large(commit_pointer, commit_size) : os_commit(commit_pointer, commit_size);

        if (commit_success)
            arena->commited += commit_size;
    }

    void* result = 0;
    if(arena->commited >= end_offset) {
        result = (void*)((uaddress)arena->memory + begin_offset);
        arena->offset = end_offset - arena->arena_base_offset;
    }
    return result;
}

ArenaScratch* arena_begin_scratch(Arena* arena) {
    u64 offset = arena->offset;
    ArenaScratch* scratch = arena_push_struct(arena, ArenaScratch);
    scratch->arena = arena;
    scratch->original_offset = offset;
    return scratch;
}

void arena_scratch_end(ArenaScratch* scratch) {
    scratch->arena->offset = scratch->original_offset;
}

void arena_reset(Arena* arena) {
    arena->offset = 0;
}

void arena_release(Arena* arena) {
    os_release(arena->memory, arena->reserved);
}