
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "vector.h"

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);

typedef struct KeyValPair KeyValPair;

typedef struct BinaryTree BinaryTree;

//KeyValPair headers
KeyValPair *key_val_pair_construct(void *key, void *val);

void *get_key_val_pair_val(KeyValPair *kvp);

void *get_key_val_pair_key(KeyValPair *kvp);

void key_val_pair_destroy(KeyValPair *kvp);

int cmp_kvp_keys(void *a, void *b);

//Binary tree headers
BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn);

void binary_tree_add(BinaryTree *bt, void *key, void *value);

int binary_tree_empty(BinaryTree *bt);

int binary_tree_size(BinaryTree *bt);

void binary_tree_remove(BinaryTree *bt, void *key);

void *binary_tree_get(BinaryTree *bt, void *key);

void binary_tree_destroy(BinaryTree *bt);

//Tree Traversal header
Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);

#endif