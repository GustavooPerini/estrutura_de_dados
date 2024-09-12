#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define VECTOR_GROWTH 2
#define VECTOR_INITIAL_ALLOCATION 10

struct Vector{

    data_type *data;
    int size;
    int allocated;
};


Vector *vector_construct(){

    Vector *v = (Vector*)malloc(sizeof(Vector));

    v->size = 0;
    v->allocated = VECTOR_INITIAL_ALLOCATION;
    v->data = (data_type*)malloc(VECTOR_INITIAL_ALLOCATION * sizeof(data_type));

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


int vector_size(Vector *v){
    return v->size;
}


void *vector_remove(Vector *v, int i){

    if(i >= 0 && i < v->size){

        void *data = v->data[i];

        for(int j = i; j < v->size - 1; j++){
            v->data[j] = v->data[j+1];
        }
        v->size--;
        return data;
    }
    else{
        printf("Indice invalido\n");
        return NULL;
    }

}


void *vector_pop_back(Vector *v){
    return vector_remove(v, v->size - 1);
}


void *vector_pop_front(Vector *v){
    return vector_remove(v, 0);
}


void vector_destroy(Vector *v){

    for(int i = 0; i < v->size; i++){
        free(v->data[i]);
    }
    free(v->data);
    free(v);
}