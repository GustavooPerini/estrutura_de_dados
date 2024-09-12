#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef void* data_type;

typedef struct Vector Vector;

// Cria um vetor vazio
Vector *vector_construct();

// Adiciona um elemento no final do vetor
void vector_push_back(Vector *v, data_type val);

int vector_size(Vector *v);

void *vector_remove(Vector *v, int i);

void *vector_pop_back(Vector *v);

void *vector_pop_front(Vector *v);

void vector_destroy(Vector *v);

#endif