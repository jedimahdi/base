#ifndef ARENA_H_
#define ARENA_H_

#include "defines.h"

#define ARENA_MAX_CAPACITY Gigabytes(1)
#define ARENA_COMMIT_SIZE Kilobytes(64)
#define DEFAULT_ALIGNMENT sizeof(void *)

#define make(a, t, n) (t *)arena_alloc_zero((a), sizeof(t), _Alignof(t), n)

typedef struct {
  u8 *memory;
  u64 capacity;
  u64 alloc_pos;
  u64 commit_pos;
} Arena;

typedef struct {
  Arena *arena;
  u64 pos;
} ArenaTemp;

Arena arena_make(void);
Arena arena_make_with_capacity(u64 capacity);
void arena_clear(Arena *arena);
void arena_free(Arena *arena);

void *arena_alloc(Arena *arena, u64 elem_size, u64 align, u64 count);
void *arena_alloc_zero(Arena *arena, u64 elem_size, u64 align, u64 count);
void *arena_realloc(Arena *arena, void *oldptr, u64 elem_size, u64 old_count, u64 new_count);

void *arena_push(Arena *arena, u64 size);
void *arena_push_zero(Arena *arena, u64 size);
void arena_pop(Arena *arena, u64 size);
void arena_pop_to(Arena *arena, u64 pos);
#define arena_push_array(arena, T, count) (T *)arena_push((arena), sizeof(T) * (count))
#define arena_push_array_zero(arena, T, count) (T *)arena_push_zero((arena), sizeof(T) * (count))

ArenaTemp arena_temp_begin(Arena *arena);
void arena_temp_end(ArenaTemp tmp);

ArenaTemp get_scratch(void);

#endif // ARENA_H_
