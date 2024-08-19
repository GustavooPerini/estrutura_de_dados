#include <stdlib.h>
#include "node.h"


struct node{

    data_type val;
    Node *next;
};


Node *node_construct(data_type val, Node *node){

    Node *n = (Node*)malloc(sizeof(Node));

    n->val = val;
    n->next = node;

    return n;
}


data_type node_val(Node *node){

    return node->val;
}


data_type *node_val_address(Node *node){

    return &node->val;
}


Node *node_next(Node *node){

    return node->next;
}


void set_node_next(Node *node, Node *destiny){

    node->next = destiny;
}


void node_destroy(Node *node){

    free(node);
}