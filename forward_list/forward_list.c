#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"


ForwardList *forward_list_construct(){

    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));

    l->head = NULL;
    l->size = 0;

    return l;
}


int forward_list_size(ForwardList *l){

    return l->size;
}


void forward_list_push_front(ForwardList *l, data_type data){

    l->head = node_construct(data, l->head);
    l->size++;
}


void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){

    Node *node = l->head;
    int cont = 0;
    printf("[");
    while(node != NULL){
    
        print_fn(node_val(node));
        node = node_next(node);
        cont++;

        if(cont < l->size){
            printf(", ");
        }

    }
    printf("]\n");
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

    return val;
}


void forward_list_clear(ForwardList *l){

    Node *node = l->head;
    while(node != NULL){

        Node *to_destroy = node;
        node = node_next(node);
        node_destroy(to_destroy);
    }
}


void forward_list_remove(ForwardList *l, data_type val){

    for(int i = 0; i < forward_list_size(l); i++){

        if(forward_list_get(l, i) == val){

            Node *node_aux = l->head;
            for(int j = 0; j < i; j++){
                node_aux = node_next(node_aux);
            }
            Node *next_node = node_next(node_aux);
            node_destroy(node_aux);

            if(i == 0){
                l->head = next_node;
            }
            else{
                node_aux = l->head;
                for(int k = 0; k < i - 1; k++){
                    node_aux = node_next(node_aux);
                }
                set_node_next(node_aux, next_node);
            }
            
            l->size--;
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


void forward_list_destroy(ForwardList *l){

    if(l->head != NULL){
        forward_list_clear(l);
    }

    free(l);
}