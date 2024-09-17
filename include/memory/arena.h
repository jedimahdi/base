#ifndef ARENA_H_
#define ARENA_H_

#include <stdlib.h>

#define ARENA_MAX_CAPACITY GB(1)
#define ARENA_COMMIT_SIZE KB(64)
#define PAGE_SIZE KB(4)

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

#define make(arena, t, n) (t *)arena_alloc((arena), sizeof(t) * n)

typedef struct {
  unsigned char *memory;
  size_t capacity;
  size_t curr_offset;
  size_t prev_offset;
  size_t commit_offset;
} Arena;

typedef struct {
  Arena *arena;
  size_t curr_offset;
  size_t prev_offset;
} ArenaTemp;

void arena_init(Arena *arena);
void *arena_alloc_align(Arena *arena, size_t size, size_t align);
void *arena_alloc(Arena *arena, size_t size);
void *arena_resize_align(Arena *arena, void *oldptr, size_t old_size, size_t new_size, size_t align);
void *arena_resize(Arena *arena, void *oldptr, size_t old_size, size_t new_size);
void arena_clear(Arena *arena);
void arena_release(Arena *arena);

ArenaTemp arena_temp_begin(Arena *arena);
void arena_temp_end(ArenaTemp tmp);

ArenaTemp get_scratch(void);

#endif // ARENA_H_
