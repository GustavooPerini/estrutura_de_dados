#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

#define DEQUE_GROWTH 2
#define DEQUE_INITIAL_SIZE 10

struct Deque{

    int start;
    int end;
    int size;
    int allocated;
    void **data;
};


Deque *deque_construct(){

    Deque *f = (Deque*)malloc(sizeof(Deque));

    f->start = 0;
    f->end = 0;
    f->size = 0;
    f->allocated = DEQUE_INITIAL_SIZE;
    f->data = (void**)malloc(sizeof(void*) * f->allocated);

    return f;
}


void deque_resize(Deque *f){

    void **newData = (void**)malloc(sizeof(void*) * (f->allocated * DEQUE_GROWTH));

    for(int i = 0; i < f->size; i++){
        newData[i] = deque_get(f, i);
    }
    
    free(f->data);

    f->data = newData;
    f->allocated *= DEQUE_GROWTH;
    f->start = 0;
    f->end = f->size;
}


void deque_push_back(Deque *f, void *item){

    if(f->size == f->allocated){
        deque_resize(f);
    }

    f->data[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}


void deque_push_front(Deque *f, void *item){

    if(f->size == f->allocated){
        deque_resize(f);   
    }

    f->start = (f->start - 1);
    if(f->start < 0){
        f->start = f->allocated - 1;
    }
    
    f->data[f->start] = item;
    f->size++;
}


void *deque_pop_back(Deque *f){

    if(f->size == 0){
        printf("Error: o vetor esta vazio\n");
        return NULL;
    }
    
    f->end = (f->end - 1);
    if(f->end < 0){
        f->end = f->allocated - 1;
    }

    f->size--;
    return f->data[f->end];
}


void *deque_pop_front(Deque *f){

    if(f->size == 0){
        printf("Error: o vetor esta vazio\n");
        return NULL;
    }
    
    void *data = f->data[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
    return data;
    
}


int deque_size(Deque *f){
    return f->size;
}


void *deque_get(Deque *f, int idx){

    if(idx < 0 || idx >= f->size){
        return NULL;
    }
    
    return f->data[(f->start + idx) % f->allocated];
}


void deque_destroy(Deque *f){

    free(f->data);
    free(f);
}