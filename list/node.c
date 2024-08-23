
#include <stdio.h>
#include <stdlib.h>
#include "node.h"


struct Node{

    data_type value;
    Node *prev;
    Node *next;
};


Node *node_construct(data_type value, Node *prev, Node *next){
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    n->prev = prev;
    return n;
}

Node *node_next(Node *n){
    return n->next;
}


Node *node_prev(Node *n){
    return n->prev;
}


void set_node_next(Node *n, Node *next){
    n->next = next;
}


void set_node_prev(Node *n, Node *prev){
    n->prev = prev;
}


data_type node_val(Node *n){
    return n->value;
}


data_type *node_val_address(Node *n){
    return &n->value;
}


void node_print(Node *n, void (*print_fn)(data_type)){
    print_fn(n->value);
}


void node_destroy(Node *n){
    free(n);
}