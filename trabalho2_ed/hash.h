#ifndef _HASH_H_
#define _HASH_H_

typedef struct HashTable HashTable;

typedef struct HashTableItem HashTableItem;

typedef int(*HashFunction)(HashTable *h, void *data);
typedef int(*CmpFunction)(void *k1, void*k2);


HashTable *hash_table_construct(int size, HashFunction hash_func, CmpFunction cmp_func);

void *hash_table_set(HashTable *h, void *key, void *val);

void *hash_table_get(HashTable *h, void *key);

int hash_table_size(HashTable *h);

void hash_table_destroy(HashTable *h);

#endif