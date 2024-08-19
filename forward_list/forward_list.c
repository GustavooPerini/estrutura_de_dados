#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"


ForwardList *forward_list_construct(){

    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));

    l->head = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}


int forward_list_size(ForwardList *l){

    return l->size;
}


void forward_list_push_front(ForwardList *l, data_type data){

    l->head = node_construct(data, l->head);
    l->size++;

    if(l->size == 1){
        l->last = l->head;
    }
}


void forward_list_push_back(ForwardList *l, data_type data){

    Node *n = node_construct(data, NULL);

    if(l->head == NULL){
        l->head = l->last = n;
    }
    else{
        set_node_next(l->last, n);
        l->last = n;
    }

    l->size++;
}


void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){

    Node *node = l->head;
    //printf("[");
    while(node != NULL){
    
        print_fn(node_val(node));
        node = node_next(node);

        /*if(node != NULL){
            printf(", ");
        }*/
    }
    //printf("]\n");
}


data_type forward_list_get(ForwardList *l, int i){

    if(i < 0 || i >= forward_list_size(l)){

        printf("Error: invalid index\n");
        exit(0);
    }
    
    Node *node = l->head;
    for(int j = 0; j < i; j++){
        node = node_next(node);
    }

    return node_val(node);
}


data_type forward_list_pop_front(ForwardList *l){

    if(l->head == NULL){
        printf("Erro: list without nodes\n");
        exit(0);
    }

    data_type val = node_val(l->head);
    Node *to_destroy = l->head;

    l->head = node_next(l->head);
    node_destroy(to_destroy);
    l->size--;

    if(l->size <= 1){
        l->last = l->head;
    }

    return val;
}


data_type forward_list_pop_index(ForwardList *l, int index){

    if(index < 0 || index >= l->size){
        printf("Invalid index\n");
        exit(0);
    }

    Node *node = l->head;
    Node *prev = NULL;

    for(int i = 0; i < index; i++){
        prev = node;
        node = node_next(node);
    }

    if(prev == NULL){
        l->head = node_next(node);
    }
    else{
        set_node_next(prev, node_next(node));
    }

    data_type val = node_val(node);
    node_destroy(node);
    l->size--;
    return val;

}


ForwardList *forward_list_reverse(ForwardList *l){

    ForwardList *new_list = forward_list_construct();

    Node *n = l->head;
    while(n != NULL){
        forward_list_push_front(new_list, node_val(n));
        n = node_next(n);
    }

    return new_list;
}


void forward_list_clear(ForwardList *l){

    int size = l->size;

    for(int i = 0; i < size; i++){
        forward_list_pop_front(l);
    }
}


void forward_list_remove(ForwardList *l, data_type val){
    
    Node *n = l->head;
    Node *prev = NULL;
    Node *new_n = NULL;

    while (n != NULL){
        
        if(node_val(n) == val){

            new_n = node_next(n);
            
            if(prev == NULL){
                l->head = new_n;
            }
            else{
                set_node_next(prev, new_n);
            }

            node_destroy(n);
            n = new_n;
            l->size--;
        }
        else{
            prev = n;
            n = node_next(n);
        }
    }
}


void forward_list_cat(ForwardList *l, ForwardList *m){

    Node *node = m->head;
    while(node != NULL){
        
        forward_list_push_front(l, node_val(node));
        node = node_next(node);
    }
}


void forward_list_sort(ForwardList *l){
    
    ListIterator *it = list_iterator_construct(l);

    for(int i = 0; i < l->size - 1; i++){
        int trocas = 0;
        for(int j = 0; j < l->size - i - 1; j++){

            data_type *value1 = list_iterator_next(it);
            data_type *value2 = node_val_address(it->current);

            if(*value1 > *value2){
                
                data_type swap = *value1;
                *value1 = *value2;
                *value2 = swap;
                trocas++;
            }

        }
        if(trocas == 0){
            break;
        }
        it->current = l->head;
    }

    list_iterator_destroy(it);
}


void forward_list_destroy(ForwardList *l){

    if(l->head != NULL){
        forward_list_clear(l);
    }

    free(l);
}


ListIterator *list_iterator_construct(ForwardList *l){

    ListIterator *it = (ListIterator*)malloc(sizeof(ListIterator));
    it->current = l->head;
    return it;
}


void list_iterator_destroy(ListIterator *it){
    free(it);
}


data_type* list_iterator_next(ListIterator *it){

    data_type *data = node_val_address(it->current);
    it->current = node_next(it->current);
    return data;
}


bool list_iterator_is_over(ListIterator *it){

    if(it->current == NULL){
        return true;
    }
    return false;
}