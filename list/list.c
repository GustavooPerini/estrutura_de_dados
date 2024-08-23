#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct List{
    Node *head;
    Node *last;
    int size;
};

struct ListIterator{
    Node *current;
};


List *list_construct(){

    List *l = (List*)malloc(sizeof(List));

    l->head = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}


int list_size(List *l){
    return l->size;
}


void list_push_front(List *l, data_type data){

    Node *n = node_construct(data, NULL, l->head);

    if(l->head != NULL){
        set_node_prev(l->head, n);
    }
    l->head = n;
    l->size++;

    if(l->size == 1){
        l->last = l->head;
    }
}


void list_push_back(List *l, data_type data){

    Node *n = node_construct(data, l->last, NULL);

    if(l->last != NULL){
        set_node_next(l->last, n);
    }
    l->last = n;
    l->size++;

    if(l->size == 1){
        l->head = l->last;
    }
}


void list_print(List *l, void (*print_fn)(data_type)){

    Node *n = l->head;

    printf("[");
    while(n != NULL){
        
        node_print(n, print_fn);
        n = node_next(n);

        if(n != NULL){
            printf(", ");
        }
    }
    printf("]\n");
}


void list_print_reverse(List *l, void (*print_fn)(data_type)){

    Node *n = l->last;

    printf("[");
    while(n != NULL){

        node_print(n, print_fn);
        n = node_prev(n);

        if(n != NULL){
            printf(", ");
        }
    }
    printf("]\n");
}


data_type list_pop_front(List *l){

    if(l->size == 0){
        printf("list empty\n");
        exit(0);
    }

    Node *n = l->head;
    data_type data = node_val(n);

    if(node_next(n) != NULL){
        set_node_prev(node_next(n), NULL);
    }
    l->head = node_next(n);

    node_destroy(n);
    l->size--;

    if(l->size <= 1){
        l->last = l->head;
    }
    return data;
}


data_type list_pop_back(List *l){

    if(l->size == 0){
        printf("list empty\n");
        exit(0);
    }

    Node *n = l->last;
    data_type data = node_val(n);

    if(node_prev(n) != NULL){
        set_node_next(node_prev(n), NULL);
    }
    l->last = node_prev(n);

    node_destroy(n);
    l->size--;

    if(l->size <= 1){
        l->head = l->last;
    }
    return data;
}


void list_clear(List *l){

    if(l->head != NULL){
        int size = l->size;

        for(int i = 0; i < size; i++){
            list_pop_front(l);
        }
    }
}


void list_destroy(List *l){

    list_clear(l);
    free(l);
}


ListIterator *list_front_iterator(List *l){

    ListIterator *it = (ListIterator*)malloc(sizeof(ListIterator));
    it->current = l->head;

    return it;
}


ListIterator *list_back_iterator(List *l){

    ListIterator *it = (ListIterator*)malloc(sizeof(ListIterator));
    it->current = l->last;

    return it;
}


data_type *list_iterator_next(ListIterator *it){

    if(list_iterator_is_over(it)){
        return NULL;
    }

    data_type *data = node_val_address(it->current);
    it->current = node_next(it->current);
    return data;
}


data_type *list_iterator_previous(ListIterator *it){

    if(list_iterator_is_over(it)){
        return NULL;
    }

    data_type *data = node_val_address(it->current);
    it->current = node_prev(it->current);
    return data;
}


bool list_iterator_is_over(ListIterator *it){

    if(it->current == NULL){
        return 1;
    }
    return 0;
}


void list_iterator_destroy(ListIterator *it){
    free(it);
}