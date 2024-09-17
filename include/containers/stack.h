#ifndef STACK_H_
#define STACK_H_

#define ARENA_STACK_INIT_CAP 64

#define stack_push(stack, item, arena)                                                                                   \
  do {                                                                                                                   \
    if ((stack)->count >= (stack)->capacity) {                                                                           \
      size_t new_capacity = (stack)->capacity == 0 ? ARENA_STACK_INIT_CAP : (stack)->capacity * 2;                       \
      (stack)->items = arena_realloc((arena), (stack)->items, sizeof(*(stack)->items), (stack)->capacity, new_capacity); \
      (stack)->capacity = new_capacity;                                                                                  \
    }                                                                                                                    \
    (stack)->items[(stack)->count++] = (item);                                                                           \
  } while (0)

#define stack_pop(stack) ({ (stack)->count--; (stack)->items[(stack)->count]; })

#define stack_peek(stack) (stack)->items[(stack)->count - 1]

#endif // STACK_H_
