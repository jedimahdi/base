#include "str.h"

b32 s8equal(s8 a, s8 b) {
  if (a.len != b.len) {
    return 0;
  }
  usize mismatch = 0;
  for (usize i = 0; i < a.len; i++) {
    mismatch += a.data[i] != b.data[i];
  }
  return !mismatch;
}

u64 s8hash(s8 s) {
  u64 h = 0x100;
  for (usize i = 0; i < s.len; i++) {
    h ^= s.data[i];
    h *= 1111111111111111111;
  }
  return h ^ h >> 32;
}
