#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forward_list.h"
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

            ForwardList *l = forward_list_contruct();

            char *word = (char*)malloc(sizeof(char)*100);
            char *document = (char*)malloc(sizeof(char)*100);
            strcpy(document, name);
            scanf("%s", word);
            int *frq = malloc(sizeof(int));
            *frq = 1;

            ForwardList *search = (ForwardList*)hash_table_get(h, word);

            if(search != NULL){
                
                ForwardListIterator *it = forward_list_iterator_construct(search);
                int documento_novo = 0;

                while(!forward_list_iterator_is_over(it)){
                    
                    HashTableItem *pair = forward_list_iterator_next(it);
                    void *key = get_table_item_key(pair);

                    if(cmp_str(key, document) == 0){
                        int *value = (int*)get_table_item_value(pair);
                        *(value) = *(value) + 1;
                        break;
                    }
                    else if(cmp_str(key, document) != 0){
                        HashTableItem *item = hash_table_item_construct(document, frq);
                        forward_list_push_front(search, item);
                        documento_novo = 1;
                        break;
                    }
                }
                forward_list_iterator_destroy(it);
                
                if(documento_novo == 0){
                    free(frq);
                }

                free(word);
                forward_list_destroy(l);
            }
            else{

                HashTableItem *item = hash_table_item_construct(document, frq);
                forward_list_push_front(l, item);
            
                hash_table_set(h, word, l);
            }
        }
    }

    //VER A DESALOCAÇÃO

    HashTableIterator *it1 = hash_table_iterator_construct(h);

    printf("%d\n", hash_table_elements(h));
    while(!hash_table_iterator_is_over(it1)){

        HashTableItem *item = hash_table_iterator_next(it1);
        char *key = (char*)get_table_item_key(item);
        void *value = get_table_item_value(item);
        
        ForwardListIterator *it2 = forward_list_iterator_construct(value);

        printf("%s %d ", key, forward_list_size(value));

        while(!forward_list_iterator_is_over(it2)){

            HashTableItem *item = forward_list_iterator_next(it2);
            char *doc = (char*)get_table_item_key(item);
            int *frequencia = (int*)get_table_item_value(item);

            printf("%s %d ", doc, *frequencia);
        }
        printf("\n");
        forward_list_iterator_destroy(it2);
        forward_list_destroy(value);
    }
    
    hash_table_iterator_destroy(it1);

    hash_table_destroy(h);
    
    return 0;
}