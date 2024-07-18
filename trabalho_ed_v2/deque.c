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


void deque_push_back(Deque *f, void *item){

    //verificar se ta cheio

    if(f->size == f->allocated){

        int initial_size = f->size;
        void **newData = (void**)malloc((sizeof(void*) * f->allocated) * DEQUE_GROWTH);

        for(int i = 0; i < initial_size; i++){
            newData[i] = deque_pop_front(f);
        }

        free(f->data);

        f->allocated *= DEQUE_GROWTH;
        f->size = initial_size;
        f->data = newData;
        f->start = 0;
        f->end = f->size; 
    }

    f->data[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}


void deque_push_front(Deque *f, void *item){

    //verificar se ta cheio
    if(f->size == f->allocated){

        int initial_size = f->size;
        void **newData = (void**)malloc((sizeof(void*) * f->allocated) * DEQUE_GROWTH);

        for(int i = 0; i < initial_size; i++){
            newData[i] = deque_pop_front(f);
        }

        free(f->data);

        f->allocated *= DEQUE_GROWTH;
        f->size = initial_size;
        f->data = newData;
        f->start = 0;
        f->end = f->size;    
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
    else{
        f->end = (f->end - 1);
        if(f->end < 0){
            f->end = f->allocated - 1;
        }

        f->size--;
        return f->data[f->end];
    }

}


void *deque_pop_front(Deque *f){

    if(f->size == 0){
        printf("Error: o vetor esta vazio\n");
        return NULL;
    }
    else{

        void *data = f->data[f->start];
        f->start = (f->start + 1) % f->allocated;
        f->size--;
        return data;
    }
}


int deque_size(Deque *f){
    return f->size;
}


void deque_destroy(Deque *f){

    free(f->data);
    free(f);
}