#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"
#include "hash.h"


struct HashTableItem{

    void *key;
    void *value;
};


struct HashTable{

    HashFunction hash_func;
    CmpFunction cmp_func;
    void **buckets;
    int table_size;
    int elements;
};


HashTable *hash_table_construct(int size, HashFunction hash_func, CmpFunction cmp_func){

    HashTable *h = (HashTable*)malloc(sizeof(HashTable));

    h->hash_func = hash_func;
    h->cmp_func = cmp_func;
    h->table_size = size;
    h->buckets = (void**)malloc(sizeof(void*) * size);

    for(int i = 0; i < size; i++){
        h->buckets[i] = NULL;
    }

    h->elements = 0;

    return h;
}


void *hash_table_set(HashTable *h, void *key, void *val){
     
    int b_idx = h->hash_func(h, key); //indice do bucket

    HashTableItem *item = (HashTableItem*)malloc(sizeof(HashTableItem));
    item->key = key;
    item->value = val;

    if(h->buckets[b_idx] != NULL){

        int fl_size = forward_list_size(h->buckets[b_idx]);

        for(int i = 0; i < fl_size; i++){ //busca para ver se a chave ja existe na lista

            HashTableItem *table_item = (HashTableItem*)forward_list_get(h->buckets[b_idx], i);

            if(h->cmp_func(key, table_item->key) == 0){ //caso exista, atualiza o valor

                void *val_to_remove = table_item->value; //pego o valor a ser removido do par
                table_item->value = item->value; //atualizo o valor do par
                free(item); //libero a estrutura que tinha o novo item a ser inserido na tabela
                return val_to_remove;
            }
        }

        //caso nao ache a chava na lista, basta apenas adicionar mais um elemento nela
        forward_list_push_front(h->buckets[b_idx], item);
        h->elements++;
        return NULL;
    }

    h->buckets[b_idx] = forward_list_contruct();
    forward_list_push_front(h->buckets[b_idx], item);
    h->elements++;
    return NULL;
}


void *hash_table_get(HashTable *h, void *key){

    int b_idx = h->hash_func(h, key); //indice do bucket

    if(h->buckets[b_idx] != NULL){

        int fl_size = forward_list_size(h->buckets[b_idx]);

        for(int i = 0; i < fl_size; i++){

            HashTableItem *table_item = (HashTableItem*)forward_list_get(h->buckets[b_idx], i);
            
            if(h->cmp_func(key, table_item->key) == 0){

                return table_item->value;
            }
        }

        return NULL;
    }

    return NULL;
}


int hash_table_size(HashTable *h){
    return h->table_size;
}


void hash_table_destroy(HashTable *h){

    for(int i = 0; i < h->table_size; i++){

        if(h->buckets[i] != NULL){
            
            int fl_size = forward_list_size(h->buckets[i]);
            for(int j = 0; j < fl_size; j++){

                HashTableItem *table_item = (HashTableItem*)forward_list_get(h->buckets[i], j);
                free(table_item->key);
                free(table_item->value);
            }
            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}