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
};


struct ForwardListIterator{
    Node *current;
};


//Node functions header//

Node *node_construct(data_type value, Node *next);

void node_destroy(Node *node);

//forward list functions

ForwardList *forward_list_contruct(){

    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));

    l->head = NULL;
    l->size = 0;
    return l;
}


void forward_list_push_front(ForwardList *l, data_type value){

    l->head = node_construct(value, l->head);
    l->size++;
}


int forward_list_size(ForwardList *l){

    return l->size;
}


data_type forward_list_get(ForwardList *l, int idx){

    if(idx < 0 || idx >= forward_list_size(l)){
        
        printf("indice invalido\n");
        return NULL;
    }
    
    Node *n = l->head;
    for(int i = 0; i < idx; i++){

        n = n->next;
    }
    
    return n->value;
}


Node *search_prev(ForwardList *l ,int index){
    
    Node *n = l->head;
    Node *prev = NULL;

    for(int i = 0; i < index; i++){
       prev = n;
       n = n->next; 
    }
    
    return prev;
}


data_type forward_list_pop_index(ForwardList *l, int index){

    if(index < 0 || index >= l->size){
        printf("Invalid index\n");
        exit(0);
    }

    Node *prev = search_prev(l, index);
    Node *to_remove;

    if(prev == NULL){
        to_remove = l->head;
        l->head = l->head->next;
    }
    else{
        to_remove = prev->next;
        prev->next = to_remove->next;
    }

    data_type val = to_remove->value;
    node_destroy(to_remove);
    l->size--;
    return val;
}


void forward_list_destroy_itens(ForwardList *l){

    if(l->head != NULL){
        
        Node *n = l->head;
        while(n != NULL){
            
            Node *to_remove = n;
            n = n->next;
            node_destroy(to_remove);
        }
    }
}


void forward_list_destroy(ForwardList *l){

    forward_list_destroy_itens(l);
    free(l);
}

//Node functions

Node *node_construct(data_type value, Node *next){

    Node *n = (Node*)malloc(sizeof(Node));
    
    n->value = value;
    n->next = next;

    return n;
}


void node_destroy(Node *node){

    free(node->value);
    free(node);
}


//Iterator functions

ForwardListIterator *forward_list_iterator_construct(ForwardList *l){

    ForwardListIterator *it = (ForwardListIterator*)malloc(sizeof(ForwardListIterator));
    it->current = l->head;
    return it;
}


data_type forward_list_iterator_next(ForwardListIterator *it){

    data_type data = it->current->value;
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