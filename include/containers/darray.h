#ifndef DARRAY_H_
#define DARRAY_H_

#define ARENA_DA_INIT_CAP 256

#define da_init_arena(da, cap, arena)                                                    \
  do {                                                                                   \
    (da)->capacity = cap;                                                                \
    (da)->items = arena_alloc_zero(arena, sizeof(*(da)->items), DEFAULT_ALIGNMENT, cap); \
  } while (0)

#define da_append_arena(da, item, arena)                                                                     \
  do {                                                                                                       \
    if ((da)->count >= (da)->capacity) {                                                                     \
      size_t new_capacity = (da)->capacity == 0 ? ARENA_DA_INIT_CAP : (da)->capacity * 2;                    \
      (da)->items = arena_realloc((arena), (da)->items, sizeof(*(da)->items), (da)->capacity, new_capacity); \
      (da)->capacity = new_capacity;                                                                         \
    }                                                                                                        \
    (da)->items[(da)->count++] = (item);                                                                     \
  } while (0)

#endif // DARRAY_H_
