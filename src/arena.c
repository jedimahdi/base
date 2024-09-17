#include "memory/arena.h"
#include "os/os.h"
#include <stdint.h>
#include <string.h>

static bool is_power_of_two(uintptr_t x) {
  return (x & (x - 1)) == 0;
}

static uintptr_t align_forward(uintptr_t ptr, size_t align) {
  uintptr_t p, a, modulo;

  assert(is_power_of_two(align));

  p = ptr;
  a = (uintptr_t)align;
  // Same as (p % a) but faster as 'a' is a power of two
  modulo = p & (a - 1);

  if (modulo != 0) {
    // If 'p' address is not aligned, push the address to the
    // next value which is aligned
    p += a - modulo;
  }
  return p;
}

void arena_init(Arena *arena) {
  arena->capacity = ARENA_MAX_CAPACITY;
  arena->memory = os_memory_reserve(arena->capacity);
  arena->curr_offset = 0;
  arena->prev_offset = 0;
  arena->commit_offset = 0;
}

void *arena_alloc_align(Arena *arena, size_t size, size_t align) {
  uintptr_t curr_ptr = (uintptr_t)arena->memory + (uintptr_t)arena->curr_offset;
  uintptr_t offset = align_forward(curr_ptr, align);
  offset -= (uintptr_t)arena->memory;
  uintptr_t new_offset = offset + size;

  if (new_offset < arena->capacity) {
    if (new_offset >= arena->commit_offset) {
      uintptr_t new_commit_offset_unclamped = align_forward(new_offset, PAGE_SIZE);
      uintptr_t new_commit_offset = clamp_top(new_commit_offset_unclamped, arena->capacity);
      uintptr_t commit_size = new_commit_offset - arena->commit_offset;
      os_memory_commit(arena->memory + arena->commit_offset, commit_size);
      arena->commit_offset += commit_size;
    }

    void *ptr = arena->memory + offset;
    arena->prev_offset = offset;
    arena->curr_offset = new_offset;
    memset(ptr, 0, size);
    return ptr;
  }

  assert(0 && "Arena out of memory!");
  return NULL;
}

void *arena_alloc(Arena *arena, size_t size) {
  return arena_alloc_align(arena, size, DEFAULT_ALIGNMENT);
}

void *arena_resize_align(Arena *arena, void *oldptr, size_t old_size, size_t new_size, size_t align) {
  unsigned char *old_mem = (unsigned char *)oldptr;

  assert(is_power_of_two(align));

  if (old_mem == NULL || old_size == 0) {
    return arena_alloc_align(arena, new_size, align);
  } else if (arena->memory <= old_mem && old_mem < arena->memory + arena->capacity) {
    if (arena->memory + arena->prev_offset == old_mem) {
      arena->curr_offset = arena->prev_offset + new_size;
      if (new_size > old_size) {
        memset(&arena->memory[arena->curr_offset], 0, new_size - old_size);
      }
      return oldptr;
    } else {
      void *new_memory = arena_alloc_align(arena, new_size, align);
      size_t copy_size = old_size < new_size ? old_size : new_size;
      memmove(new_memory, oldptr, copy_size);
      return new_memory;
    }
  } else {
    assert(0 && "Memory is out of bounds of the buffer in this arena");
    return NULL;
  }
}

void *arena_resize(Arena *arena, void *oldptr, size_t old_size, size_t new_size) {
  return arena_resize_align(arena, oldptr, old_size, new_size, DEFAULT_ALIGNMENT);
}

void arena_clear(Arena *arena) {
  arena->curr_offset = 0;
  arena->prev_offset = 0;
}

void arena_release(Arena *arena) {
  os_memory_release(arena->memory, arena->capacity);
}

ArenaTemp arena_temp_begin(Arena *arena) {
  ArenaTemp temp;
  temp.arena = arena;
  temp.curr_offset = arena->curr_offset;
  temp.prev_offset = arena->prev_offset;
  return temp;
}

void arena_temp_end(ArenaTemp temp) {
  temp.arena->curr_offset = temp.curr_offset;
  temp.arena->prev_offset = temp.prev_offset;
}

Arena scratch_arena = {0};

ArenaTemp get_scratch(void) {
  if (scratch_arena.capacity == 0) {
    arena_init(&scratch_arena);
  }
  return arena_temp_begin(&scratch_arena);
}
