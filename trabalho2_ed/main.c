#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


int hash_str(HashTable *h, void *data){

    char *str = (char*)data;
    unsigned long int hash_val = 0, base = 27183;
    unsigned long int random_val = 31415;
    int size = strlen(str);

    for(int i = 0; i < size; i++){
        hash_val = (hash_val * random_val + str[i]) % hash_table_size(h);
        random_val = (random_val * base) % (hash_table_size(h) - 1);
    }

    return hash_val;
}


int cmp_str(void *a, void *b){
    
    return strcmp((char *)a, (char *)b);
}


int main(){

    int n;

    scanf("%d", &n);

    HashTable *h = hash_table_construct(11, hash_str, cmp_str);

    for(int i = 0; i < n; i++){

        char name[100];
        int words = 0;

        scanf("%s ", name);
        scanf("%d: ", &words);
        name[strlen(name) - 1] = '\0';

        for(int j = 0; j < words; j++){

            HashTable *h2 = hash_table_construct(11, hash_str, cmp_str);

            char *word = (char*)malloc(sizeof(char)*100);
            char *document = (char*)malloc(sizeof(char)*100);
            strcpy(document, name);
            scanf("%s", word);
            int *frq = malloc(sizeof(int));
            *frq = 1;
            
            void *search = hash_table_get(h, word);

            if(search != NULL){
        
                void *val = hash_table_get(search, document);
                
                if(val != NULL){
                    *frq += *(int *)val;
                }
                
                void *b = hash_table_set(search, document, frq);
                if(b != NULL){
                    
                    free(b);
                    free(document);
                }
                free(word);
                hash_table_destroy(h2);
            }
            else{
                
                hash_table_set(h2, document, frq);
            
                void *a = hash_table_set(h, word, h2);
                if(a != NULL){
                    hash_table_destroy(a);
                    free(word);
                }
            }
        }
    }

    HashTableIterator *it1 = hash_table_iterator_construct(h);

    printf("%d\n", hash_table_elements(h));
    while(!hash_table_iterator_is_over(it1)){

        HashTableItem *item = hash_table_iterator_next(it1);
        char *key = (char*)get_table_item_key(item);
        void *value = get_table_item_value(item);

        HashTableIterator *it2 = hash_table_iterator_construct(value);

        printf("%s %d ", key, hash_table_elements(value));

        while(!hash_table_iterator_is_over(it2)){

            HashTableItem *item = hash_table_iterator_next(it2);
            char *doc = (char*)get_table_item_key(item);
            int *frequencia = (int*)get_table_item_value(item);

            printf("%s %d ", doc, *frequencia);
        }
        printf("\n");
        hash_table_iterator_destroy(it2);
        hash_table_destroy_itens(value);
    }
    
    hash_table_iterator_destroy(it1);

    hash_table_destroy(h);
    
    return 0;
}