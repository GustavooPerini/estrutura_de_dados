#ifndef _HEAP_H_
#define _HEAP_H_

#include "vector.h"

typedef struct heap Heap;

Heap *heap_constructor(int (*cmp_fn)(const void *, const void *));

void heap_push(Heap *heap, void *data);

int heap_size(Heap *heap);

void *heap_pop(Heap *heap);

void heap_destroy(Heap *heap);

data_type heap_get(Heap *heap, int i);

void heap_remove(Heap *heap, int i);

#endif