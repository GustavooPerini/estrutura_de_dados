
#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef void* data_type;

typedef void (*delete_func)(void*);
typedef int (*compare_func)(const void *, const void *);

typedef struct Vector Vector;

// Cria um vetor vazio
Vector *vector_construct(delete_func func);

// Adiciona um elemento no final do vetor
void vector_push_back(Vector *v, data_type val);

// Retorna o i-ésimo elemento do vetor
data_type vector_get(Vector *v, int i);

// Atribui o valor val ao i-ésimo elemento do vetor
void vector_set(Vector *v, int i, data_type val);

// Retorna o tamanho do vetor
int vector_size(Vector *v);

// Retorna o indice do primeiro elemento com valor val. Retorna -1 se nao encontrado.
int vector_find(Vector *v, data_type val, compare_func cmp);

// Remove o i-ésimo elemento do vetor.
void vector_remove(Vector *v, int i); //houve alteração no retorno

// Remove o primeiro elemento
void vector_pop_front(Vector *v); //houve alteração no retorno

// Remove o ultimo elemento
void vector_pop_back(Vector *v); //houve alteração no retorno

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val);

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j);

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v, compare_func cmp);

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val, compare_func cmp);

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v);

// Cria uma cópia do vector e dos valores de seus atributos.
Vector *vector_copy(Vector *v);

// Remove todos os elementos de v
void vector_clear(Vector *v);

// Libera parte da memoria alocada para o vetor. Desaloca apenas a estrutura, ainda falta desalocar os itens.
void vector_pacial_destroy(Vector *v);

// Libera a memoria alocada para o vetor
void vector_destroy(Vector *v);

#endif
