#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "memory/arena.h"
#include "base/defines.h"

typedef struct HNode HNode;
typedef struct HTab HTab;
typedef struct HMap HMap;

struct HNode {
  HNode *next;
  u64 hcode;
};

struct HTab {
  HNode **tab;
  usize mask;
  usize size;
};

struct HMap {
  HTab ht1; // newer
  HTab ht2; // older
  usize resizing_pos;
};

HNode *hm_lookup(HMap *hmap, HNode *key, bool (*eq)(HNode *, HNode *));
void hm_insert(HMap *hmap, HNode *node, Arena *arena);
HNode *hm_pop(HMap *hmap, HNode *key, bool (*eq)(HNode *, HNode *));
size_t hm_size(HMap *hmap);
void hm_destroy(HMap *hmap);

#endif // HASHTABLE_H_
