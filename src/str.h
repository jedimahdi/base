#ifndef STR_H_
#define STR_H_

#include "defines.h"

#define s8(s) \
  (s8) { (u8 *)s, lengthof(s) }

typedef struct {
  u8 *data;
  usize len;
} s8;

#define s16(s) \
  (s16) { u##s, lengthof(u##s) }

typedef struct {
  c16 *data;
  usize len;
} s16;

b32 s8equal(s8 a, s8 b);
u64 s8hash(s8 s);

#endif // STR_H_
