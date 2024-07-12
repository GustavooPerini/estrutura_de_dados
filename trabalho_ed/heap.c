#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


struct heap{

    Vector *v;
    int (*cmp_fn)(const void *, const void *);

};


Heap *heap_constructor(int (*cmp_fn)(const void *, const void *)){

    Heap *heap = (Heap*)malloc(sizeof(Heap));

    heap->v = vector_construct();
    heap->cmp_fn = cmp_fn;

    return heap;
}


void heap_push(Heap *heap, void *data){

    vector_push_back(heap->v, data);

    if(heap_size(heap) > 1){
        vector_heapify(heap->v, heap->cmp_fn);
    }
}


int heap_size(Heap *heap){

    return vector_size(heap->v);
}


void *heap_pop(Heap *heap){
    
    void *data = vector_heapify_down(heap->v, heap->cmp_fn);
    return data;
}


void heap_destroy(Heap *heap){

    if(heap != NULL){

        vector_destroy(heap->v);
        free(heap);
    }
}


data_type heap_get(Heap *heap, int i){

    return vector_get(heap->v, i);
}


void heap_remove(Heap *heap, int i){
    vector_remove(heap->v, i);
}