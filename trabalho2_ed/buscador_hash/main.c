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


int compara_documentos(const void *a, const void *b){

    HashTableItem *p1 = *((HashTableItem**)a);
    HashTableItem *p2 = *((HashTableItem**)b);

    char *key1 = (char*)get_table_item_key(p1);
    int *val1 = (int*)get_table_item_value(p1);

    char *key2 = (char*)get_table_item_key(p2);
    int *val2 = (int*)get_table_item_value(p2);
    

    if(*val1 > *val2) {
        return -1;
    }
    else if(*val1 < *val2) {
        return 1;
    }
    else{
        // Se as frequencias forem iguais, comparar os nomes dos documentos em ordem alfabética
        return strcmp(key1, key2);
    }
}



int main(){

    char indice_path[100];
    char stop_words_path[100];
    char search_word[50];

    scanf("%s %s", indice_path, stop_words_path);

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
    while(scanf("%s", search_word) > 0){

        if(vector_binary_search(stop_words_vector, search_word, cmp_str) == -1){

            char *data_word = (char*)malloc(sizeof(char)*50);
            strcpy(data_word, search_word);
            forward_list_push_front(list_of_words, data_word);
        }
    }

    //CRIANDO A HASH TABLE COM AS INFORMAÇÕES DO INDICE
    int indice_size = 0;
    fscanf(indice_file, "%d", &indice_size);

    HashTable *h = hash_table_construct(919, hash_str, cmp_str);

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

    Vector *documents_frequency = vector_construct();

    while(!hash_table_iterator_is_over(it1)){

        HashTableItem *item = hash_table_iterator_next(it1);
        char *key = (char*)get_table_item_key(item);
        void *value = get_table_item_value(item);
        

        for(int i = 0; i < forward_list_size(list_of_words); i++){
            
            if(cmp_str(key, forward_list_get(list_of_words, i)) == 0){

                ForwardListIterator *it2 = forward_list_iterator_construct(value);

                while(!forward_list_iterator_is_over(it2)){

                    HashTableItem *item = forward_list_iterator_next(it2);
    
                    int *frequencia = (int*)get_table_item_value(item);

                    void *retorno = vector_linear_search(documents_frequency, item, cmp_hash_item_keys);

                    if(retorno != NULL){
                        
                        HashTableItem *item_vetor = (HashTableItem*)retorno;
                        int *frequencia_atual = (int*)get_table_item_value(item_vetor);
                        *frequencia_atual += *frequencia;
                    }
                    else if(retorno == NULL){

                        char *documento_vetor = (char*)malloc(sizeof(char)*50);
                        int *frequencia_documento = (int*)malloc(sizeof(int));

                        char *doc = (char*)get_table_item_key(item);

                        strcpy(documento_vetor, doc);
                        *frequencia_documento = *frequencia;

                        HashTableItem *item_para_vetor = hash_table_item_construct(documento_vetor, frequencia_documento);
                        vector_push_back(documents_frequency, item_para_vetor);
                    }
                }
                forward_list_iterator_destroy(it2);
            }
        }

        for(int i = 0; i < forward_list_size(value); i++){
            hash_table_item_destroy_elements(forward_list_get(value, i));
        }

        forward_list_destroy_itens(value);
    }
    hash_table_iterator_destroy(it1);
    
    //TRATAMENTO DO VETOR DE DOCUMENTOS
    vector_sort(documents_frequency, compara_documentos);

    int cont = 0;
    for(int i = 0; i < vector_size(documents_frequency); i++){

        cont++;
        HashTableItem *item = vector_get(documents_frequency, i);
        if(cont <= 10){

            char *key = get_table_item_key(item);
            int *val = get_table_item_value(item);
            printf("%s %d\n", key, *val);
        }

        hash_table_item_destroy_elements(item);
    }

    fclose(indice_file);
    fclose(stop_words_file);

    hash_table_destroy(h);

    vector_destroy(stop_words_vector);

    forward_list_destroy(list_of_words);
    vector_destroy(documents_frequency);

    return 0;
}