#include "arena.h"
#include "defines.h"
#include "os/os.h"
#include <string.h>

Arena arena_make(void) {
  Arena arena = {0};
  arena.capacity = ARENA_MAX_CAPACITY;
  arena.memory = os_memory_reserve(arena.capacity);
  arena.alloc_pos = 0;
  arena.commit_pos = 0;
  return arena;
}

Arena arena_make_with_capacity(u64 capacity) {
  Arena arena = {0};
  arena.capacity = capacity;
  arena.memory = os_memory_reserve(arena.capacity);
  arena.alloc_pos = 0;
  arena.commit_pos = 0;
  return arena;
}

void arena_clear(Arena *arena) {
  arena->alloc_pos = 0;
}

void arena_free(Arena *arena) {
  os_memory_release(arena->memory, arena->capacity);
}

void *arena_alloc(Arena *arena, u64 elem_size, u64 align, u64 count) {
  u64 size = elem_size * count;
  u64 pos = arena->alloc_pos;
  u64 pos_aligend = ALIGN_POW_2(pos, align);
  u64 new_pos = pos_aligend + size;
  void *result = arena->memory + pos_aligend;
  arena->alloc_pos = new_pos;

  if (new_pos > arena->commit_pos) {
    u64 new_commit_unclamped = ALIGN_POW_2(new_pos, ARENA_COMMIT_SIZE);
    u64 new_commit = clamp_top(new_commit_unclamped, arena->capacity);
    u64 commit_size = new_commit - arena->commit_pos;

    if (arena->commit_pos >= arena->capacity) {
      assert(0 && "Arena is out of memory!");
    } else {
      os_memory_commit(arena->memory + arena->commit_pos, commit_size);
      arena->commit_pos += commit_size;
    }
  }
  return result;
}

void *arena_alloc_zero(Arena *arena, u64 elem_size, u64 align, u64 count) {
  void *result = arena_alloc(arena, elem_size, align, count);
  memset(result, 0, elem_size * count);
  return result;
}

void *arena_realloc(Arena *arena, void *oldptr, u64 elem_size, u64 old_count, u64 new_count) {
  if (new_count <= old_count)
    return oldptr;
  void *newptr = arena_alloc(arena, elem_size, DEFAULT_ALIGNMENT, new_count);
  char *newptr_char = (char *)newptr;
  char *oldptr_char = (char *)oldptr;
  for (size_t i = 0; i < old_count * elem_size; ++i) {
    newptr_char[i] = oldptr_char[i];
  }
  return newptr;
}

void *arena_push(Arena *arena, u64 size) {
  return arena_alloc(arena, size, DEFAULT_ALIGNMENT, 1);
  // u64 pos = arena->alloc_pos;
  // u64 align = DEFAULT_ALIGNMENT;
  // u64 pos_aligend = ALIGN_POW_2(pos, align);
  // u64 new_pos = pos_aligend + size;
  // void *result = arena->memory + pos_aligend;
  // arena->alloc_pos = new_pos;
  //
  // if (new_pos > arena->commit_pos) {
  //   u64 new_commit_unclamped = ALIGN_POW_2(new_pos, ARENA_COMMIT_SIZE);
  //   u64 new_commit = CLAMP_TOP(new_commit_unclamped, arena->capacity);
  //   u64 commit_size = new_commit - arena->commit_pos;
  //
  //   if (arena->commit_pos >= arena->capacity) {
  //     assert(0 && "Arena is out of memory!");
  //   } else {
  //     os_memory_commit(arena->memory + arena->commit_pos, commit_size);
  //     arena->commit_pos += commit_size;
  //   }
  // }
  //
  // return result;
}

void *arena_push_zero(Arena *arena, u64 size) {
  void *result = arena_push(arena, size);
  memset(result, 0, size);
  return result;
}

void arena_pop(Arena *arena, u64 size) {
  if (size > arena->alloc_pos)
    size = arena->alloc_pos;
  arena->alloc_pos -= size;
}

void arena_pop_to(Arena *arena, u64 pos) {
  if (pos > arena->capacity)
    pos = arena->capacity;
  arena->alloc_pos = pos;
}

ArenaTemp arena_temp_begin(Arena *arena) {
  return (ArenaTemp){.arena = arena, .pos = arena->alloc_pos};
}

void arena_temp_end(ArenaTemp tmp) {
  arena_pop_to(tmp.arena, tmp.pos);
}

Arena scratch_arena = {0};

ArenaTemp get_scratch(void) {
  if (scratch_arena.capacity == 0) {
    scratch_arena = arena_make();
  }
  return arena_temp_begin(&scratch_arena);
}
