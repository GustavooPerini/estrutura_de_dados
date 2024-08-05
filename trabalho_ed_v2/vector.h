
#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef void* data_type;

typedef void (*delete_func)(void*);

typedef struct Vector Vector;

// Cria um vetor vazio
Vector *vector_construct(delete_func func);

// Adiciona um elemento no final do vetor
void vector_push_back(Vector *v, data_type val);

// Retorna o i-ésimo elemento do vetor
data_type vector_get(Vector *v, int i);

// Retorna o tamanho do vetor
int vector_size(Vector *v);

// Libera a memoria alocada para o vetor
void vector_destroy(Vector *v);

#endif