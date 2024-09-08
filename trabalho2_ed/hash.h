#ifndef _HASH_H_
#define _HASH_H_


typedef struct HashTable HashTable;

typedef struct HashTableItem HashTableItem;

typedef struct HashTableIterator HashTableIterator;

typedef int(*HashFunction)(HashTable *h, void *data);
typedef int(*CmpFunction)(void *k1, void*k2);


HashTable *hash_table_construct(int size, HashFunction hash_func, CmpFunction cmp_func);

void *hash_table_set(HashTable *h, void *key, void *val);

void *hash_table_get(HashTable *h, void *key);

void *hash_table_pop(HashTable *h, void *key);

int hash_table_size(HashTable *h);

int hash_table_elements(HashTable *h);

void hash_table_destroy(HashTable *h);

void hash_table_destroy_itens(HashTable *h);

HashTableIterator *hash_table_iterator_construct(HashTable *h);

HashTableItem *hash_table_iterator_next(HashTableIterator *it);

int hash_table_iterator_is_over(HashTableIterator *it);

void hash_table_iterator_destroy(HashTableIterator *it);

//HASH TABLE ITEM FUNCTIOS

HashTableItem *hash_table_item_construct(void *key, void *value);

void *get_table_item_key(HashTableItem *item);

void *get_table_item_value(HashTableItem *item);

#endif