#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_construct();

void heap_push(Heap *heap, void *data, float priority);

int heap_empty(Heap *heap);

int heap_size(Heap *heap);

void *heap_max(Heap *heap);

float heap_max_priority(Heap *heap);

void *heap_pop(Heap *heap);

void *heap_get(Heap *heap, int idx);

void heap_destroy(Heap *heap);

#endif