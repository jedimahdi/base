#include "arena.h"
#include "ds/stack.h"
#include "str.h"
#include <criterion/criterion.h>

typedef struct {
  char *items;
  usize count;
  usize capacity;
} CharStack;

b32 is_parens_valid(CharStack *stack, s8 s, Arena *arena) {
  for (usize i = 0; i < s.len; ++i) {
    if (s.data[i] == '(') {
      stack_push(stack, '(', arena);
    }
    if (s.data[i] == ')') {
      if (stack->count == 0) {
        return 0;
      } else {
        stack_pop(stack);
      }
    }
  }
  return stack->count == 0;
}

Test(stack, pushpop) {
  CharStack s = {0};
  Arena arena = arena_make();

  stack_push(&s, 'a', &arena);
  stack_push(&s, 'b', &arena);
  stack_push(&s, 'c', &arena);
  cr_expect(stack_peek(&s) == 'c');
  cr_expect(stack_pop(&s) == 'c');
  cr_expect(stack_pop(&s) == 'b');
  cr_expect(stack_pop(&s) == 'a');
}

Test(stack, pransexample) {
  CharStack s = {0};
  Arena arena = arena_make();

  cr_expect(is_parens_valid(&s, s8("((()))()"), &arena));
  cr_expect(!is_parens_valid(&s, s8(")()"), &arena));
}
