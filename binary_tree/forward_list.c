#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"



typedef struct Node{
    
    data_type value;
    struct Node *next;
}Node;


struct ForwardList{

    int size;
    Node *head;
    Node *last;
};

//node functions

Node *fl_node_construct(data_type val, Node *next){

    Node *n = (Node*)malloc(sizeof(Node));

    n->value = val;
    n->next = next;

    return n;
}

void fl_node_destroy(Node *node){
    free(node);
}

//forward_list functions
ForwardList *forward_list_construct(){

    ForwardList *fl = (ForwardList*)malloc(sizeof(ForwardList));

    fl->size = 0;
    fl->head = NULL;
    fl->last = NULL;

    return fl;
}


int forward_list_size(ForwardList *fl){
    return fl->size;
}


void forward_list_push_front(ForwardList *fl, data_type data){

    fl->head = fl_node_construct(data, fl->head);
    fl->size++;

    if(fl->size == 1){
        fl->last = fl->head;
    }
}


void forward_list_push_back(ForwardList *fl, data_type data){

    Node *node = fl_node_construct(data, NULL);

    if(fl->head == NULL){
        fl->head = fl->last = node;
    }
    else{
        fl->last->next = node;
        fl->last = node;
    }

    fl->size++;
}


data_type forward_list_pop_front(ForwardList *fl){

    data_type val = fl->head->value;
    Node *to_destroy = fl->head;

    fl->head = fl->head->next;
    fl_node_destroy(to_destroy);
    fl->size--;

    if(fl->size <= 1){
        fl->last = fl->head;
    }

    return val;
}


void forward_list_destroy(ForwardList *fl){

    Node *n = fl->head;
    while(n != NULL){

        Node *to_destroy = n;
        n = n->next;
        fl_node_destroy(to_destroy);
    }
    
    free(fl);
}