#include "base/str.h"

b32 s8_equals(s8 a, s8 b) {
  if (a.len != b.len) {
    return 0;
  }
  usize mismatch = 0;
  for (usize i = 0; i < a.len; i++) {
    mismatch += a.data[i] != b.data[i];
  }
  return !mismatch;
}

u64 s8_hash(s8 s) {
  u64 h = 0x100;
  for (usize i = 0; i < s.len; i++) {
    h ^= s.data[i];
    h *= 1111111111111111111;
  }
  return h ^ h >> 32;
}

s8 s8_takehead(s8 s, usize len) {
  assert(len <= s.len);
  s.len = len;
  return s;
}

s8 s8_cuthead(s8 s, usize off) {
  assert(off <= s.len);
  s.len -= off;
  s.data += off;
  return s;
}

s8 s8_taketail(s8 s, usize len) {
  assert(len <= s.len);
  return s8_cuthead(s, s.len - len);
}

s8 s8_cuttail(s8 s, usize off) {
  assert(off <= s.len);
  s.len -= off;
  return s;
}

b32 s8_starts_with(s8 s, s8 prefix) {
  return s.len >= prefix.len && s8_equals(prefix, s8_takehead(s, prefix.len));
}

s8pair s8_cut(s8 s, char delim) {
  s8pair result;
  usize len = 0;
  for (; len < s.len; len++) {
    if (s.data[len] == delim) {
      break;
    }
  }
  if (len == s.len) {
    result.head = s;
    result.tail = s8_cuthead(s, s.len);
    return result;
  }
  result.head = s8_takehead(s, len);
  result.tail = s8_cuthead(s, len + 1);
  return result;
}
