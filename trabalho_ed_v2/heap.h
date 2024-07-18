#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_construct();

void heap_push(Heap *heap, void *data, double priority);

int heap_empty(Heap *heap);

void *heap_max(Heap *heap);

double heap_max_priority(Heap *heap);

void *heap_pop(Heap *heap);

void heap_destroy(Heap *heap);

void heap_sort(void *array, int array_size, int item_size, double (*key_fn)(void *));

#endif