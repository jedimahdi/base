#ifndef STR_H_
#define STR_H_

#include "defines.h"

#define s8(s) \
  (s8) { (u8 *)s, lengthof(s) }

typedef struct {
  char *data;
  usize len;
} s8;

#define s16(s) \
  (s16) { u##s, lengthof(u##s) }

typedef struct {
  c16 *data;
  usize len;
} s16;

typedef struct {
  s8 head;
  s8 tail;
} s8pair;

b32 s8_equals(s8 a, s8 b);
u64 s8_hash(s8 s);
s8 s8_cuthead(s8 s, usize off);
s8 s8_takehead(s8 s, usize len);
s8 s8_cuttail(s8 s, usize off);
s8 s8_taketail(s8 s, usize len);
b32 s8_starts_with(s8 s, s8 prefix);
s8pair s8_cut(s8 s, char delim);

#endif // STR_H_
