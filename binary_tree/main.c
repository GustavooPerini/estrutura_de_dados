#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

int cmp_fn(void *key1, void *key2)
{
    int *v = key1;
    int *w = key2;

    return *v - *w;
}

void key_destroy_fn(void *key)
{
    free(key);
}

void val_destroy_fn(void *val)
{
    free(val);
}

int *new_int(int value)
{
    int *ptr = malloc(sizeof(int));
    *ptr = value;
    return ptr;
}

int main()
{
    BinaryTree *bt = binary_tree_construct(cmp_fn, key_destroy_fn, val_destroy_fn);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        binary_tree_add(bt, new_int(val), new_int(val));
    }

    Vector *v_inorder = binary_tree_inorder_traversal_recursive(bt);
    Vector *v_preorder = binary_tree_preorder_traversal_recursive(bt);
    Vector *v_postorder = binary_tree_postorder_traversal_recursive(bt);

    printf("InOrder recursivo: ");
    for (int i = 0; i < vector_size(v_inorder); i++)
    {
        KeyValPair *kvp = vector_get(v_inorder, i);
        int *val = kvp->value;
        printf("%d ", *val);
        key_val_pair_destroy(kvp);
    }
    printf("\n");

    printf("PreOrder recursivo: ");
    for (int i = 0; i < vector_size(v_preorder); i++)
    {
        KeyValPair *kvp = vector_get(v_preorder, i);
        int *val = kvp->value;
        printf("%d ", *val);
        key_val_pair_destroy(kvp);
    }
    printf("\n");

    printf("PostOrder recursivo: ");
    for (int i = 0; i < vector_size(v_postorder); i++)
    {
        KeyValPair *kvp = vector_get(v_postorder, i);
        int *val = kvp->value;
        printf("%d ", *val);
        key_val_pair_destroy(kvp);
    }
    printf("\n");

    vector_destroy(v_inorder);
    vector_destroy(v_preorder);
    vector_destroy(v_postorder);

    binary_tree_destroy(bt);

    return 0;
}
