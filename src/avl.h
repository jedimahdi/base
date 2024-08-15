#ifndef AVL_H_
#define AVL_H_

#include "defines.h"

typedef struct avlnode avlnode;

struct avlnode {
  avlnode *left;
  avlnode *right;
  avlnode *parent;
  u32 depth;
  u32 cnt;
};

void avlnode_init(avlnode *node);
avlnode *avl_fix(avlnode *node);
avlnode *avl_del(avlnode *node);
u32 avl_depth(avlnode *node);
u32 avl_cnt(avlnode *node);

#endif // AVL_H_
