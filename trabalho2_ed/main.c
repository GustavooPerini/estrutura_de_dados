#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


int hash_str(HashTable *h, void *data){

    char *str = (char*)data;
    unsigned long int hash_val = 0, base = 127;
    unsigned long int random_val = 31415;
    int size = strlen(str);

    for(int i = 0; i < size; i++){
        hash_val = (hash_val * base + str[i]) % hash_table_size(h);
        random_val = (random_val * base) % (hash_table_size(h) - 1);
    }

    return hash_val;
}


int cmp_str(void *a, void *b){
    
    return strcmp((char *)a, (char *)b);
}


int main(){

    int n;

    char palavras[4][100] = {"agua", "azul", "bola", "ceu"};
    char textos[3][100] = {"a1.txt", "a2.txt", "a3.txt"};

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

    int size = hash_table_elements(h);

    for(int j = 0; j < size; j++){

        void *a = hash_table_get(h, palavras[j]);
        
        for(int k = 0; k < 3; k++){
            
            
            void *c = hash_table_get(a, textos[k]);
            
            if(c != NULL){
                
                int *r = (int *)c;
                printf("%s: %s %d\n", palavras[j], textos[k], *r);
            }
        }
    }

    int sizet = hash_table_elements(h);
    for(int j = 0; j < sizet; j++){

        void *a = hash_table_get(h, palavras[j]);

        hash_table_destroy_itens(a);
    }

    hash_table_destroy(h);
    
    return 0;
}