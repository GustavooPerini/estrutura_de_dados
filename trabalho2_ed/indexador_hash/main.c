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

    char file_name[300];

    scanf("%s%*c", file_name);

    FILE *file = fopen(file_name, "r");

    int n;
    fscanf(file, "%d", &n);

    HashTable *h = hash_table_construct(11, hash_str, cmp_str);

    for(int i = 0; i < n; i++){

        char name[100];
        int num_words = 0;

        fscanf(file, "%s ", name);
        fscanf(file, "%d: ", &num_words);
        name[strlen(name) - 1] = '\0';

        for(int j = 0; j < num_words; j++){

            ForwardList *l = forward_list_contruct();

            char *word = (char*)malloc(sizeof(char)*100);
            char *document = (char*)malloc(sizeof(char)*100);
            strcpy(document, name);
            fscanf(file, "%s", word);
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
                    free(document);
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

    fclose(file);

    HashTableIterator *it1 = hash_table_iterator_construct(h);

    printf("%d\n", hash_table_elements(h));
    while(!hash_table_iterator_is_over(it1)){

        HashTableItem *item = hash_table_iterator_next(it1);
        char *key = (char*)get_table_item_key(item);
        void *value = get_table_item_value(item);
        
        ForwardListIterator *it2 = forward_list_iterator_construct(value);

        int fl_size = forward_list_size(value);
        printf("%s %d ", key, fl_size);

        while(!forward_list_iterator_is_over(it2)){

            HashTableItem *item = forward_list_iterator_next(it2);
            char *doc = (char*)get_table_item_key(item);
            int *frequencia = (int*)get_table_item_value(item);

            printf("%s %d ", doc, *frequencia);
        }
        printf("\n");
        forward_list_iterator_destroy(it2);

        for(int i = 0; i < fl_size; i++){
            hash_table_item_destroy_elements(forward_list_get(value, i));
        }

        forward_list_destroy_itens(value);
    }
    
    hash_table_iterator_destroy(it1);

    hash_table_destroy(h);
    
    return 0;
}