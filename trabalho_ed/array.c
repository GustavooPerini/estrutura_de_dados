#include <stdio.h>
#include <stdlib.h>
#include "array.h"

struct carray{

    data_type *data;
    int size;
    int allocated;
    int start;
    int end;
};


C_array *array_construct(){

    C_array *c = (C_array*)calloc(1, sizeof(C_array));

    c->allocated = 10;
    c->data = (data_type*)calloc(c->allocated, sizeof(data_type));

    return c;
}


void array_destroy(C_array *c){

    if(c != NULL){
        free(c->data);
        free(c);
    }

}


void array_push_back(C_array *c, data_type val){ // ok

    if(c->size == c->allocated){ //MEXIDO

        int j = c->size;

        c->allocated *= 2;
        data_type *new_data = (data_type*)calloc(c->allocated, sizeof(data_type));

        for(int i = 0; i < j; i++){
            new_data[i] = array_pop_front(c);
        }

        free(c->data);
        c->data = new_data;

        c->start = 0;
        c->end = j;
        c->size = j;

    }

    c->data[c->end] = val;
    c->end = (c->end + 1) % c->allocated;
    c->size++;
}


int array_size(C_array *c){ //ok

    return c->size;
}


data_type array_get(C_array *c, int i){ //MEXIDA

    int position = (c->start + i) % c->allocated;

    if(position >= 0 && position < c->allocated){
        return c->data[position];
    }
    else{
        printf("ERRO: indice invalido\n");
        exit(1);
    }
}


data_type array_pop_front(C_array *c){ //ok

    data_type num = c->data[c->start];
    c->start = (c->start + 1) % c->allocated;
    c->size--;
    return num;
}


data_type array_pop_back(C_array *c){ //ok

    int a = c->end - 1;

    if(a < 0){
        c->end = c->allocated - 1;
    }
    else if(a >= 0){
        c->end = (c->end - 1) % c->allocated;
    }

    data_type num = c->data[c->end];
    c->size--;

    return num;
}