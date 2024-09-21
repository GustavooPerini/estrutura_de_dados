#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef void* data_type;

typedef struct Vector Vector;

// Cria um vetor vazio
Vector *vector_construct();

// Adiciona um elemento no final do vetor
void vector_push_back(Vector *v, data_type val);

int vector_size(Vector *v);

data_type vector_get(Vector *v, int i);

void *vector_remove(Vector *v, int i);

void *vector_pop_back(Vector *v);

void *vector_pop_front(Vector *v);

int vector_binary_search(Vector *v, data_type val, int(*cmp_func)(void *a, void *b));

data_type vector_linear_search(Vector *v, data_type val, int(*cmp_func)(void *a, void *b));

void vector_sort(Vector *v, int(*cmp_func)(const void *a, const void *b));

void vector_destroy(Vector *v);

#endif