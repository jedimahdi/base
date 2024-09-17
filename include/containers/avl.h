#ifndef AVL_H_
#define AVL_H_

#include "base/defines.h"

typedef struct AVLNode AVLNode;

struct AVLNode {
  AVLNode *left;
  AVLNode *right;
  AVLNode *parent;
  u32 depth;
  u32 cnt;
};

void avlnode_init(AVLNode *node);
AVLNode *avl_fix(AVLNode *node);
AVLNode *avl_del(AVLNode *node);
u32 avl_depth(AVLNode *node);
u32 avl_cnt(AVLNode *node);

#endif // AVL_H_
