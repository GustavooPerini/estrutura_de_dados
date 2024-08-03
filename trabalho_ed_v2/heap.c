#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

const int HEAP_INITIAL_CAPACITY = 10;
const int HEAP_GROW_RATE = 2;


typedef struct {

    void *data;
    float priority;
}HeapNode;


struct Heap{

    HeapNode *nodes;
    int size;
    int capacity;
};

void _swap_nodes(Heap *heap, int idx, int parent){

    HeapNode swapNode = heap->nodes[idx];
    heap->nodes[idx] = heap->nodes[parent];
    heap->nodes[parent] = swapNode;
}

void _heapify_up(Heap *heap, int idx){

    if(idx < 0 || idx >= heap->size){
        printf("Error: indice invalido\n");
        exit(0);
    }

    while (idx > 0){
       
        int parent = (idx - 1) / 2;

        if(heap->nodes[idx].priority < heap->nodes[parent].priority){
            _swap_nodes(heap, idx, parent);
            idx = parent;
        }
        else{
            break;
        }
    }
}


void _heapify_down(Heap *heap, int idx){

    while (1){

        int max = idx;
        int left_child = idx * 2 + 1;
        int right_child = idx * 2 + 2;

        if((left_child < heap->size) &&
           (heap->nodes[left_child].priority < heap->nodes[max].priority)){

            max = left_child;
        }

        if((right_child < heap->size) &&
           (heap->nodes[right_child].priority < heap->nodes[max].priority)){
            
            max = right_child;
        }
        
        if(max != idx){
            _swap_nodes(heap, idx, max);
            idx = max;
        }
        else{
            break;
        }
    }
}


Heap *heap_construct(){

    Heap *h = (Heap*)malloc(sizeof(Heap));

    h->nodes = (HeapNode*)malloc(sizeof(HeapNode) * HEAP_INITIAL_CAPACITY);
    h->size = 0;
    h->capacity = HEAP_INITIAL_CAPACITY;

    return h;
}


void heap_push(Heap *heap, void *data, float priority){

    if(heap->size == heap->capacity){

        heap->capacity *= HEAP_GROW_RATE;
        heap->nodes = (HeapNode*)realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    if(heap->size > 1){
        _heapify_up(heap, heap->size - 1);
    }
}


int heap_empty(Heap *heap){
    
    if(heap->size == 0)
        return 1;
    return 0;
}


int heap_size(Heap *heap){

    return heap->size;
}


void *heap_max(Heap *heap){
    return heap->nodes[0].data;
}


float heap_max_priority(Heap *heap){
    return heap->nodes[0].priority;
}


void *heap_pop(Heap *heap){

    if(heap_empty(heap)){
        printf("Error: a heap esta vazia.\n");
        exit(0);
    }

    void *data = heap_max(heap);

    if(heap->size >= 2){
        _swap_nodes(heap, heap->size - 1, 0);
    }

    heap->size--;
    _heapify_down(heap, 0);

    return data;
}


void heap_destroy(Heap *heap){

    free(heap->nodes);
    free(heap);
}