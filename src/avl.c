#include "containers/avl.h"

#include <stddef.h>
#include <stdint.h>

void avlnode_init(AVLNode *node) {
  node->depth = 1;
  node->cnt = 1;
  node->left = node->right = node->parent = NULL;
}

u32 avl_depth(AVLNode *node) {
  return node ? node->depth : 0;
}

u32 avl_cnt(AVLNode *node) {
  return node ? node->cnt : 0;
}

// maintaining the depth and cnt field
static void avl_update(AVLNode *node) {
  node->depth = 1 + max(avl_depth(node->left), avl_depth(node->right));
  node->cnt = 1 + avl_cnt(node->left) + avl_cnt(node->right);
}

static AVLNode *rot_left(AVLNode *node) {
  AVLNode *new_node = node->right;
  if (new_node->left) {
    new_node->left->parent = node;
  }
  node->right = new_node->left;
  new_node->left = node;
  new_node->parent = node->parent;
  node->parent = new_node;
  avl_update(node);
  avl_update(new_node);
  return new_node;
}

static AVLNode *rot_right(AVLNode *node) {
  AVLNode *new_node = node->left;
  if (new_node->right) {
    new_node->right->parent = node;
  }
  node->left = new_node->right;
  new_node->right = node;
  new_node->parent = node->parent;
  node->parent = new_node;
  avl_update(node);
  avl_update(new_node);
  return new_node;
}

// the left subtree is too deep
static AVLNode *avl_fix_left(AVLNode *root) {
  if (avl_depth(root->left->left) < avl_depth(root->left->right)) {
    root->left = rot_left(root->left);
  }
  return rot_right(root);
}

// the right subtree is too deep
static AVLNode *avl_fix_right(AVLNode *root) {
  if (avl_depth(root->right->right) < avl_depth(root->right->left)) {
    root->right = rot_right(root->right);
  }
  return rot_left(root);
}

// fix imbalanced nodes and maintain invariants until the root is reached
AVLNode *avl_fix(AVLNode *node) {
  while (true) {
    avl_update(node);
    uint32_t l = avl_depth(node->left);
    uint32_t r = avl_depth(node->right);
    AVLNode **from = NULL;
    if (node->parent) {
      from = (node->parent->left == node)
                 ? &node->parent->left
                 : &node->parent->right;
    }
    if (l == r + 2) {
      node = avl_fix_left(node);
    } else if (l + 2 == r) {
      node = avl_fix_right(node);
    }
    if (!from) {
      return node;
    }
    *from = node;
    node = node->parent;
  }
}

// detach a node and returns the new root of the tree
AVLNode *avl_del(AVLNode *node) {
  if (node->right == NULL) {
    // no right subtree, replace the node with the left subtree
    // link the left subtree to the parent
    AVLNode *parent = node->parent;
    if (node->left) {
      node->left->parent = parent;
    }
    if (parent) {
      // attach the left subtree to the parent
      if (parent->left == node) {
        parent->left = node->left;
      } else {
        parent->right = node->left;
      }
      return avl_fix(parent);
    } else {
      // removing root?
      return node->left;
    }
  } else {
    // swap the node with its next sibling
    AVLNode *victim = node->right;
    while (victim->left) {
      victim = victim->left;
    }
    AVLNode *root = avl_del(victim);

    *victim = *node;
    if (victim->left) {
      victim->left->parent = victim;
    }
    if (victim->right) {
      victim->right->parent = victim;
    }
    AVLNode *parent = node->parent;
    if (parent) {
      if (parent->left == node) {
        parent->left = victim;
      } else {
        parent->right = victim;
      }
      return root;
    } else {
      // removing root?
      return victim;
    }
  }
}
