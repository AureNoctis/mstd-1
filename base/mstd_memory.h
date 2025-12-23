#if !defined(MSTD_MEMORY_H)
#define MSTD_MEMORY_H

#include "mstd_base.h"

////////////////////////////////
// Memory Helpers

#include <string.h>
#include <stdalign.h>

#define mem_zero(p, size) memset((p), 0, (size))
#define mem_zero_struct(p) mem_zero((p), sizeof(*(p)))
#define mem_zero_array(p) mem_zero((p), sizeof(p))

#define mem_copy(dest, src, size) memcpy((dest), (src), (size))
#define mem_copy_struct(dest, src) mem_copy((dest), (src), sizeof(*(dest)))
#define mem_copy_array(dest, src, size) mem_copy((dest), (src), sizeof(dest))

#define mem_move(dest, src, size) memmove((dest), (src), (size))
#define mem_match(a, b, size) (memcmp((a), (b), (size)) == 0)

////////////////////////////////
// Arena

typedef struct Arena Arena;
typedef struct ArenaScratch ArenaScratch;

Arena* arena_alloc(u64 to_reserve, u64 to_commit, b8 commit_large_pages);
void* arena_push(Arena* arena, u64 size, u64 align);
#define arena_push_struct(arena, T) (T*)arena_push(arena, sizeof(T), alignof(T))
#define arena_push_array(arena, T, count) (T*)arena_push(arena, sizeof(T) * count, alignof(T))

ArenaScratch* arena_begin_scratch(Arena* arena);
void arena_scratch_end(ArenaScratch* scratch);

#define arena_scratch(arena) \
    for (ArenaScratch* _scratch_ptr = arena_begin_scratch(arena); _scratch_ptr != NULL; \
         arena_scratch_end(_scratch_ptr), _scratch_ptr = NULL)

void arena_reset(Arena* arena);
void arena_release(Arena* arena);


#endif // MSTD_MEMORY_H