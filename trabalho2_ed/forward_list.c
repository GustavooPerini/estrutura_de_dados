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


void forward_list_destroy(ForwardList *l){

    if(l->head != NULL){
        
        Node *n = l->head;
        while(n != NULL){
            
            Node *to_remove = n;
            n = n->next;
            node_destroy(to_remove);
        }
    }

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