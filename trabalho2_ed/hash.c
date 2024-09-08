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


struct HashTableIterator{

    void **buckets;
    int table_size;
    int current;
    ForwardListIterator *fl_it;
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


void *hash_table_pop(HashTable *h, void *key){

    int b_idx = h->hash_func(h, key); // indice do bucket

    if(h->buckets[b_idx] != NULL){

        int fl_size = forward_list_size(h->buckets[b_idx]);

        for(int i = 0; i < fl_size; i++){

            HashTableItem *table_item = (HashTableItem*)forward_list_get(h->buckets[b_idx], i);

            if(h->cmp_func(key, table_item->key) == 0){

                void *val = table_item->value;
                free(table_item->key);
                forward_list_pop_index(h->buckets[b_idx], i);

                return val;
            }
        }
    }

    return NULL;
}


int hash_table_size(HashTable *h){
    return h->table_size;
}


int hash_table_elements(HashTable *h){
    return h->elements;
}


void hash_table_destroy_itens(HashTable *h){

    if(h != NULL){

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
    }
}


void hash_table_destroy(HashTable *h){

    hash_table_destroy_itens(h);
    free(h);
}


//HASH TABLE ITERATOR FUNCTIONS

int search_node(HashTableIterator *it){

    while(it->buckets[it->current] == NULL){
            
        if(it->current == it->table_size - 1){
            return 1;
        }
        it->current++;
    }

    return 0;
}


HashTableIterator *hash_table_iterator_construct(HashTable *h){

    HashTableIterator *it = (HashTableIterator*)malloc(sizeof(HashTableIterator));

    it->buckets = h->buckets;
    it->table_size = h->table_size;
    it->current = 0;

    int search = search_node(it);
    if(search == 1){
        free(it);
        return NULL;
    }

    it->fl_it = forward_list_iterator_construct(it->buckets[it->current]);

    return it;
}


HashTableItem *hash_table_iterator_next(HashTableIterator *it){

    if(it->fl_it == NULL){
        
        it->fl_it = forward_list_iterator_construct(it->buckets[it->current]);
    }

    HashTableItem *item = (HashTableItem*)forward_list_iterator_next(it->fl_it);
    
    return item;
}


int hash_table_iterator_is_over(HashTableIterator *it){

    if(it->current == it->table_size - 1){
    
        if(forward_list_iterator_is_over(it->fl_it) == 1){
            forward_list_iterator_destroy(it->fl_it);
            return 1;
        }
        return 0;
    }
    else if(forward_list_iterator_is_over(it->fl_it) == 1){
        
        forward_list_iterator_destroy(it->fl_it);
        it->fl_it = NULL;
        it->current++;

        return search_node(it);
    }

    return 0;
}


void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}


//HASH TABLE ITEM FUNCTIONS

HashTableItem *hash_table_item_construct(void *key, void *value){

    HashTableItem *item = (HashTableItem*)malloc(sizeof(HashTableItem));

    item->key = key;
    item->value = value;
    return item;
}


void *get_table_item_key(HashTableItem *item){
    return item->key;
}


void *get_table_item_value(HashTableItem *item){
    return item->value;
}