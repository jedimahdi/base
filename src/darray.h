#ifndef DARRAY_H_
#define DARRAY_H_

#define ARENA_DA_INIT_CAP 256

#include "arena.h"

#define arena_da_append(a, da, item)                                                                     \
  do {                                                                                                   \
    if ((da)->count >= (da)->capacity) {                                                                 \
      size_t new_capacity = (da)->capacity == 0 ? ARENA_DA_INIT_CAP : (da)->capacity * 2;                \
      (da)->items = arena_realloc((a), (da)->items, sizeof(*(da)->items), (da)->capacity, new_capacity); \
      (da)->capacity = new_capacity;                                                                     \
    }                                                                                                    \
    (da)->items[(da)->count++] = (item);                                                                 \
  } while (0)

#endif // DARRAY_H_
