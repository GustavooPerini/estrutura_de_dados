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


data_type vector_get(Vector *v, int i){

    if(i < 0 || i >= v->size){
        return NULL;
    }
    return v->data[i];
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
        return NULL;
    }

}


void *vector_pop_back(Vector *v){
    return vector_remove(v, v->size - 1);
}


void *vector_pop_front(Vector *v){
    return vector_remove(v, 0);
}


int vector_binary_search(Vector *v, data_type val , int(*cmp_func)(void *a, void *b)){

    int left = 0;
    int right = v->size - 1;

    while (left <= right){
        
        int mid = left + (right - left) / 2;
        int search = cmp_func(val, v->data[mid]);

        if(search == 0){
            return mid;
        }
        else if(search > 0){
            left = mid + 1;
        }
        else if(search < 0){
            right = mid - 1;
        }
    }
    
    return -1;
}


data_type vector_linear_search(Vector *v, data_type val, int(*cmp_func)(void *a, void *b)){

    for(int i = 0; i < v->size; i++){

        if(cmp_func(val, v->data[i]) == 0){
            return v->data[i];
        }
    }
    return NULL;
}


void vector_destroy(Vector *v){

    for(int i = 0; i < v->size; i++){
        
        free(v->data[i]);
    }
    free(v->data);
    free(v);
}