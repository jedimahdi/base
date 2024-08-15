#include "defines.h"
#include <criterion/criterion.h>

Test(defines, max) {
  cr_assert(max(5, 7) == 7);
}

Test(defines, min) {
  cr_assert(min(5, 7) == 5);
}

Test(kdjasl, clamp) {
  cr_assert(clamp(2, 4, 7) == 4);
  cr_assert(clamp(6, 4, 7) == 6);
  cr_assert(clamp(9, 4, 7) == 7);
}
