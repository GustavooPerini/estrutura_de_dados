#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "forward_list.h"


Node *node_construct(void *key, void *value, Node *left, Node *right){

    Node *n = (Node*)malloc(sizeof(Node));

    n->key = key;
    n->value = value;
    n->left = left;
    n->right = right;

    return n;
}

void node_destroy(Node *node){

    if(node == NULL){
        return;
    }
    free(node->key);
    free(node->value);
    node_destroy(node->left);
    node_destroy(node->right);
    free(node);
}

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn){

    BinaryTree *bt = (BinaryTree*)malloc(sizeof(BinaryTree));

    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    bt->root = NULL;

    return bt;
}


void binary_tree_add(BinaryTree *bt, void *key, void *value){

    if(binary_tree_get(bt, key) == NULL){

        Node *newNode = node_construct(key, value, NULL, NULL);

        if(bt->root == NULL){

            bt->root = newNode;
        }
        else{

            Node *n = bt->root;
            while(1){
                
                if(bt->cmp_fn(key, n->key) < 0){

                    if(n->left == NULL){
                        n->left = newNode;
                        break;
                    }
                    n = n->left;
                }
                else{

                    if(n->right == NULL){
                        n->right = newNode;
                        break;
                    }
                    n = n->right;
                }
            }
        }
    }
    else{
        bt->key_destroy_fn(key);
        bt->val_destroy_fn(value);
    }
}

int binary_tree_empty(BinaryTree *bt){
    if(bt->root == NULL)
        return 1;
    return 0;
}


void *binary_tree_get(BinaryTree *bt, void *key){

    if(bt->root == NULL){
        return NULL;
    }
    else{

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
        else{
            return n->value;
        }
    }
}


void remove_no(BinaryTree *bt, Node *n){

    if(n->value != NULL){
        bt->key_destroy_fn(n->key);
        bt->val_destroy_fn(n->value);
        free(n);
    }
    else{
        free(n);
    }
}


Node *encontrar_sucessor(Node *n){

    Node *sucessor = n->right;
    while(sucessor->left != NULL){
        sucessor = sucessor->left;
    }
    
    return sucessor;
}


void binary_tree_remove(BinaryTree *bt, void *key){

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

        //CASO 1 (NÓ FOLHA)
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
            remove_no(bt, n);
        }
        //CASO 2 (NÓ COM UM FILHO)
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
            remove_no(bt, n);
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
            remove_no(bt, n);
        }
        //CASO 3 (NÓ COM DOIS FILHOS)
        else{

            Node *sucessor = encontrar_sucessor(n);
            void *key = sucessor->key;
            void *val = sucessor->value;
            sucessor->value = NULL;

            binary_tree_remove(bt, sucessor->key);

            bt->key_destroy_fn(n->key);
            bt->val_destroy_fn(n->value);

            n->key = key;
            n->value = val;
        }
    }
}


void printa_no(Node *n){

    if(n == NULL){
        printf("NULL");
        return;
    }
    printf("(%d, ", *((int*)n->value));
    printa_no(n->left);
    printf(", ");
    printa_no(n->right);
    printf(")");

}


void binary_tree_print(BinaryTree *bt){
    

    Node *n = bt->root;
    printa_no(n);
    printf("\n");
}


void binary_tree_destroy(BinaryTree *bt){

    node_destroy(bt->root);
    free(bt);
}


KeyValPair *key_val_pair_construct(void *key, void *val){

    KeyValPair *kvp = malloc(sizeof(KeyValPair));
    kvp->key = key;
    kvp->value = val;

    return kvp;
}


void key_val_pair_destroy(KeyValPair *kvp){

    //free(kvp->key);
    //free(kvp->value);
    free(kvp);
}


KeyValPair *binary_tree_min(BinaryTree *bt){

    Node *n = bt->root;

    if(n == NULL){
        return NULL;
    }

    while(n->left != NULL){
        n = n->left;
    }
    
    KeyValPair *kvp = key_val_pair_construct(n->key, n->value);
    return kvp;
}


KeyValPair *binary_tree_max(BinaryTree *bt){

    Node *n = bt->root;

    if(n == NULL){
        return NULL;
    }

    while(n->right != NULL){
        n = n->right;
    }
    
    return key_val_pair_construct(n->key, n->value);
}


KeyValPair *binary_tree_pop_min(BinaryTree *bt){

    Node *n = bt->root;

    if(n == NULL){
        return NULL;
    }

    while(n->left != NULL){
        n = n->left;
    }

    KeyValPair *min = key_val_pair_construct(n->key, n->value);

    n->value = NULL;
    binary_tree_remove(bt, n->key);
    
    return min;
}


KeyValPair *binary_tree_pop_max(BinaryTree *bt){

    Node *n = bt->root;

    if(n == NULL){
        return NULL;
    }

    while(n->right != NULL){
        n = n->right;
    }

    KeyValPair *max = key_val_pair_construct(n->key, n->value);

    n->value = NULL;
    binary_tree_remove(bt, n->key);

    return max;
}


Vector *binary_tree_inorder_traversal(BinaryTree *bt){

    if(bt->root == NULL){
        return NULL;
    }

    Vector *pilha = vector_construct();
    Vector *v = vector_construct();

    Node *n = bt->root;

    while(1){

        while(n != NULL){
        
            vector_push_back(pilha, n);
            n = n->left;
        }

        if(vector_size(pilha) == 0){
            break;
        }
        else{

            Node *node = (Node*)vector_pop_back(pilha);

            KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
            vector_push_back(v, kvp);

            n = node->right;
        }
    }

    vector_destroy(pilha);
    return v;
}


Vector *binary_tree_preorder_traversal(BinaryTree *bt){

    if(bt->root == NULL){
        return NULL;
    }

    Vector *pilha = vector_construct();
    Vector *v = vector_construct();

    vector_push_back(pilha, bt->root);
    while(vector_size(pilha) != 0){
        
        Node *node = (Node*)vector_pop_back(pilha);

        KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
        vector_push_back(v, kvp);

        if(node->right != NULL){
            vector_push_back(pilha, node->right);
        }

        if(node->left != NULL){
            vector_push_back(pilha, node->left);
        }
    }
    
    vector_destroy(pilha);
    return v;
}


Vector *binary_tree_postorder_traversal(BinaryTree *bt){

    if(bt->root == NULL){
        return NULL;
    }

    Vector *pilha1 = vector_construct();
    Vector *pilha2 = vector_construct();
    Vector *v = vector_construct();

    vector_push_back(pilha1, bt->root);
    while(vector_size(pilha1) != 0){
        
        Node *node = (Node*)vector_pop_back(pilha1);

        if(node->left != NULL){
            vector_push_back(pilha1, node->left);
        }

        if(node->right != NULL){
            vector_push_back(pilha1, node->right);
        }

        vector_push_back(pilha2, node);
    }

    int size = vector_size(pilha2);
    for(int i = 0; i < size; i++){

        Node *saida = (Node*)vector_pop_back(pilha2);
        KeyValPair *kvp = key_val_pair_construct(saida->key, saida->value);
        vector_push_back(v, kvp);
    }
    
    vector_destroy(pilha1);
    vector_destroy(pilha2);
    return v;
}


Vector *binary_tree_levelorder_traversal(BinaryTree *bt){

    Vector *v = vector_construct();
    ForwardList *fila = forward_list_construct();

    forward_list_push_back(fila, bt->root);
    while(forward_list_size(fila) != 0){

        Node *n = (Node*)forward_list_pop_front(fila);
        KeyValPair *kvp = key_val_pair_construct(n->key, n->value);
        vector_push_back(v, kvp);

        if(n->left != NULL){
            forward_list_push_back(fila, n->left);
        }

        if(n->right != NULL){
            forward_list_push_back(fila, n->right);
        }
    }

    forward_list_destroy(fila);
    return v;
}


void inorder_transversal_recursive(Node *n, Vector *v){
    
    if(n == NULL){
        return;
    }
    inorder_transversal_recursive(n->left, v);
    KeyValPair *kvp = key_val_pair_construct(n->key, n->value);
    vector_push_back(v, kvp);
    inorder_transversal_recursive(n->right, v);
}


Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){

    Vector *v = vector_construct();
    inorder_transversal_recursive(bt->root, v);
    return v;
}


void preorder_traversal_recursive(Node *n, Vector *v){

    if(n == NULL){
        return;
    }
    KeyValPair *kvp = key_val_pair_construct(n->key, n->value);
    vector_push_back(v, kvp);
    preorder_traversal_recursive(n->left, v);
    preorder_traversal_recursive(n->right, v);

}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt){

    Vector *v = vector_construct();
    preorder_traversal_recursive(bt->root, v);
    return v;
}


void postorder_traversal_recursive(Node *n, Vector *v){

    if(n == NULL){
        return;
    }
    postorder_traversal_recursive(n->left, v);
    postorder_traversal_recursive(n->right, v);
    KeyValPair *kvp = key_val_pair_construct(n->key, n->value);
    vector_push_back(v, kvp);
}


Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt){

    Vector *v = vector_construct();
    postorder_traversal_recursive(bt->root, v);
    return v;
}