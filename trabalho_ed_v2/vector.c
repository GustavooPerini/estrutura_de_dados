#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define VECTOR_GROWTH 2
#define VECTOR_INITIAL_ALLOCATION 10

struct Vector{

    data_type *data;
    int size;
    int allocated;
    delete_func delete;
};


Vector *vector_construct(delete_func func){

    Vector *v = (Vector*)malloc(sizeof(Vector));

    v->size = 0;
    v->allocated = VECTOR_INITIAL_ALLOCATION;
    v->data = (data_type*)malloc(VECTOR_INITIAL_ALLOCATION * sizeof(data_type));
    v->delete = func;

    return v;
}


void vector_push_back(Vector *v, data_type val){

    if(v->size == v->allocated){
        v->allocated *= VECTOR_GROWTH;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;

}


data_type vector_get(Vector *v, int i){

    if(i >= 0 && i < v->size){
        return v->data[i];
    }
    printf("Indice invalido\n");
    return NULL;
}


int vector_size(Vector *v){
    return v->size;
}


void vector_destroy(Vector *v){

    for(int i = 0; i < v->size; i++){

        v->delete(v->data[i]);  
    }
    free(v->data);
    free(v);
}