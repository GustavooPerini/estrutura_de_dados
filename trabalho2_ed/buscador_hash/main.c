#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forward_list.h"
#include "vector.h"
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

    char indice_path[100];
    char stop_words_path[100];
    char search_word[50];

    scanf("%s %s %[^\n]", indice_path, stop_words_path, search_word);

    FILE *indice_file = fopen(indice_path, "r");
    FILE *stop_words_file = fopen(stop_words_path, "r");

    //PREENCHENDO O VETOR DE STOP WORDS
    Vector *stop_words_vector = vector_construct();

    int stop_words_size_list;
    fscanf(stop_words_file, "%d", &stop_words_size_list);

    for(int i = 0; i < stop_words_size_list; i++){
        char *word = (char*)malloc(sizeof(char) * 50);
        fscanf(stop_words_file, "%s", word);
        vector_push_back(stop_words_vector, word);
    }

    //CRIANDO UMA LISTA QUE SEPARA AS PALAVRAS COMPOSTAS EM PALAVRAS UNICAS
    ForwardList *list_of_words = forward_list_contruct();
    char *pal;
    pal = strtok(search_word, " ");

    while(pal != NULL){
        char *data_word = (char*)malloc(sizeof(char)*50);
        strcpy(data_word, pal);
        forward_list_push_front(list_of_words, data_word);
        pal = strtok(NULL, " ");
    }

    //CRIANDO A HASH TABLE COM AS INFORMAÇÕES DO INDICE
    int indice_size = 0;
    fscanf(indice_file, "%d", &indice_size);

    HashTable *h = hash_table_construct(11, hash_str, cmp_str);

    for(int i = 0; i < indice_size; i++){

        char *name = (char*)malloc(sizeof(char) * 100);
        int num_docs = 0;

        fscanf(indice_file, "%s", name);
        fscanf(indice_file, "%d", &num_docs);

        for(int j = 0; j < num_docs; j++){

            ForwardList *l = forward_list_contruct();
            
            char *document = (char*)malloc(sizeof(char)*100);
            int *frq = (int*)malloc(sizeof(int));

            fscanf(indice_file, "%s", document);
            fscanf(indice_file, "%d", frq);

            ForwardList *search = (ForwardList*)hash_table_get(h, name);

            if(search != NULL){

                HashTableItem *item = hash_table_item_construct(document, frq);
                forward_list_push_front(search, item);
                forward_list_destroy(l);
            }
            else{

                HashTableItem *item = hash_table_item_construct(document, frq);
                forward_list_push_front(l, item);
                hash_table_set(h, name, l);
            }
        }
    }

    //ITERADORES
    HashTableIterator *it1 = hash_table_iterator_construct(h);

    printf("%d\n", hash_table_elements(h));
    while(!hash_table_iterator_is_over(it1)){

        HashTableItem *item = hash_table_iterator_next(it1);
        char *key = (char*)get_table_item_key(item);
        void *value = get_table_item_value(item);


        //CODAR AQUI




        
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

    vector_destroy(stop_words_vector);
    fclose(indice_file);
    fclose(stop_words_file);
    

    for(int i = 0; i < forward_list_size(list_of_words); i++){
        char *word = (char*)forward_list_get(list_of_words, i);
        printf("%s\n", word);
    }

    forward_list_destroy(list_of_words);

    return 0;
}