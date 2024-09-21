#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"


typedef struct Node{

    data_type val;
    struct Node *next;
}Node;


struct ForwardList{

    int size;
    Node *head;
};


struct ForwardListIterator{
    Node *current;
};


//Node functions
Node *node_construct(data_type data, Node *next){

    Node *n = (Node*)malloc(sizeof(Node));

    n->val = data;
    n->next = next;

    return n;
}


void node_destroy(Node *node){
    free(node);
}


//Forward list functions
ForwardList *forward_list_construct(){

    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));

    l->size = 0;
    l->head = NULL; 

    return l;
}


int forward_list_size(ForwardList *l){
    return l->size;
}


void forward_list_push_front(ForwardList *l, data_type data){

    l->head = node_construct(data, l->head);
    l->size++;
}

data_type forward_list_get(ForwardList *l, int idx){

    if(idx < 0 || idx >= l->size){
        return NULL;
    }

    Node *n = l->head;
    for(int i = 0; i < idx; i++){
        n = n->next;
    }

    return n->val;
}


data_type forward_list_pop_front(ForwardList *l){

    if(l->head == NULL){
        return NULL;
    }

    data_type val = l->head->val;
    Node *to_destroy = l->head;

    l->head = l->head->next;
    node_destroy(to_destroy);
    l->size--;

    return val;
}


void forward_list_destroy_itens(ForwardList *l){

    int size = l->size;
    for(int i = 0; i < size; i++){
        data_type data = forward_list_pop_front(l);
        free(data);
    }
}


void forward_list_destroy(ForwardList *l){

    if(l->size > 0){
        forward_list_destroy_itens(l);
    }
    free(l);
}


//Iterator functions
ForwardListIterator *forward_list_iterator_construct(ForwardList *l){

    ForwardListIterator *it = (ForwardListIterator*)malloc(sizeof(ForwardListIterator));
    it->current = l->head;
    return it;
}


data_type forward_list_iterator_next(ForwardListIterator *it){

    data_type data = it->current->val;
    it->current = it->current->next;
    return data;
}


int forward_list_iterator_is_over(ForwardListIterator *it){

    if(it->current == NULL){
        return 1;
    }
    return 0;
}

void forward_list_iterator_destroy(ForwardListIterator *it){
    free(it);
}