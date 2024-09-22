#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"


typedef struct Node{

    void *key;
    void *value;
    struct Node *left;
    struct Node *right;

}Node;


struct KeyValPair{

    void *key;
    void *value;
};


struct BinaryTree{

    int size;
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};


//node functions
Node *bt_node_construct(void *key, void *value, Node *left, Node *right){

    Node *n = (Node*)malloc(sizeof(Node));

    n->key = key;
    n->value = value;
    n->left = left;
    n->right = right;

    return n;
}


void bt_node_destroy(Node *node){

    if(node == NULL){
        return;
    }
    free(node->key);
    free(node->value);
    bt_node_destroy(node->left);
    bt_node_destroy(node->right);
    free(node);
}


//KeyValPair functions
KeyValPair *key_val_pair_construct(void *key, void *val){

    KeyValPair *kvp = (KeyValPair*)malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}


void *get_key_val_pair_val(KeyValPair *kvp){
    return kvp->value;
}


void *get_key_val_pair_key(KeyValPair *kvp){
    return kvp->key;
}


void key_val_pair_destroy(KeyValPair *kvp){

    free(kvp);
}


int cmp_kvp_keys(void *a, void *b){

    KeyValPair *kvp1 = (KeyValPair*)a;
    KeyValPair *kvp2 = (KeyValPair*)b;

    char *key1 = (char*)kvp1->key;
    char *key2 = (char*)kvp2->key;

    return strcmp(key1, key2);
}


//Binary Tree functions
BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn){

    BinaryTree *bt = (BinaryTree*)malloc(sizeof(BinaryTree));

    bt->size = 0;
    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}


void binary_tree_add(BinaryTree *bt, void *key, void *value){

    Node *n = bt_node_construct(key, value, NULL, NULL);

    if(bt->root == NULL){
        bt->root = n;
    }
    else{

        Node *current = bt->root;
        while(1){
            
            int compare = bt->cmp_fn(key, current->key);
            if(compare < 0){

                if(current->left == NULL){
                    current->left = n;
                    break;
                }
                current = current->left;
            }
            else if(compare > 0){
                
                if(current->right == NULL){
                    current->right = n;
                    break;
                }
                current = current->right;
            }
            else{
                bt_node_destroy(n);
                break;
            }
        }
    }
    bt->size++;
}


int binary_tree_empty(BinaryTree *bt){

    if(bt->root == NULL){
        return 1;
    }
    return 0;
}


int binary_tree_size(BinaryTree *bt){
    return bt->size;
}


void remove_no(Node *node){

    if(node->value == NULL){
        free(node);
    }
    else{
        free(node->key);
        free(node->value);
        free(node);
    }

}


Node *encontra_sucessor(Node *node){

    Node *n = node;
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}


void binary_tree_remove(BinaryTree *bt, void *key){

    if(bt->root != NULL){

        Node *pai = NULL;
        Node *n = bt->root;

        while(n != NULL && bt->cmp_fn(key, n->key) != 0){
            
            pai = n;
            if(bt->cmp_fn(key, n->key) < 0){
                n = n->left;
            }
            else{
                n = n->right;
            }
        }

        if(n != NULL){
            //Caso 1(sem filhos)
            if(n->left == NULL && n->right == NULL){

                if(pai == NULL){
                    bt->root = NULL;
                }
                else if(pai->left == n){
                    pai->left = NULL;
                }
                else{
                    pai->right = NULL;
                }
                remove_no(n);
            }
            //Caso 2(apenas um filho)
            else if(n->left == NULL){
                
                if(pai == NULL){
                    bt->root = n->right;
                }
                else if(pai->left == n){
                    pai->left = n->right;
                }
                else{
                    pai->right = n->right;
                }
                remove_no(n);
            }
            else if(n->right == NULL){

                if(pai == NULL){
                    bt->root = n->left;
                }
                else if(pai->left == n){
                    pai->left = n->left;
                }
                else{
                    pai->right = n->left;
                }
                remove_no(n);
            }
            //Caso 3(dois filhos)
            else{
                
                Node *sucessor = encontra_sucessor(n->right);
                void *key = sucessor->key;
                void *val = sucessor->value;

                sucessor->value = NULL;
                binary_tree_remove(bt, sucessor->key);

                free(n->key);
                free(n->value);

                n->key = key;
                n->value = val;
            }
        }
    }
}


void *binary_tree_get(BinaryTree *bt, void *key){

    Node *n = bt->root;
    while(n != NULL && bt->cmp_fn(key, n->key) != 0){
        
        if(bt->cmp_fn(key, n->key) < 0){
            n = n->left;
        }
        else{
            n = n->right;
        }
    }
    
    if(n == NULL){
        return NULL;
    }

    return n->value;
}


void binary_tree_destroy(BinaryTree *bt){

    bt_node_destroy(bt->root);
    free(bt);
}


//Tree Traversal
void inorder_traversal_recursive(Node *node, Vector *v){

    if(node == NULL){
        return;
    }

    inorder_traversal_recursive(node->left, v);
    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
    vector_push_back(v, kvp);
    inorder_traversal_recursive(node->right, v);
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){

    Vector *v = vector_construct();
    inorder_traversal_recursive(bt->root, v);
    return v;
}