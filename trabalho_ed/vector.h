#ifndef _ED_VECTOR_H_
#define _ED_VECTOR_H_

typedef void* data_type;

typedef int (*func_point_compare)(const void *a, const void *b); //adicionado

typedef struct vector Vector;

// Aloca espaço para um elemento do tipo vector e inicializa os seus atributos.
Vector *vector_construct();

// Libera o espaço reservado para o vector.
void vector_destroy(Vector *v);

// Adiciona o item dado ao final do vector e aumenta o tamanho. Aumenta a capacidade alocada se necessário.
void vector_push_back(Vector *v, data_type val);

// Retorna o número de elementos atualmente no vector.
int vector_size(Vector *v);

// Retorna o i-ésimo elemento do vector.
data_type vector_get(Vector *v, int i);

// Retorna o índice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v, int cmp_fn(const void *, const void *));

// Retorna o índice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v, int cmp_fn(const void *, const void *));

// Remove o i-ésimo elemento do vetor.
data_type vector_remove(Vector *v, int i);

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v);

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v);

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j);

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v, func_point_compare func);

Vector *vector_copy(Vector *v);

void printa_dado(Vector *v, void print_func(void *data)); //teste

void vector_heapify(Vector *v, func_point_compare func);

data_type vector_heapify_down(Vector *v, func_point_compare func);

#endif