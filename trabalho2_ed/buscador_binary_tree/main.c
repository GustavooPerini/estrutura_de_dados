#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "forward_list.h"

int cmp_str(void *a, void *b){
    
    return strcmp((char *)a, (char *)b);
}

void key_destroy_fn(void *key){
    free(key);
}

void val_destroy_fn(void *val){
    free(val);
}


int compara_documentos(const void *a, const void *b){

    KeyValPair *p1 = *((KeyValPair**)a);
    KeyValPair *p2 = *((KeyValPair**)b);

    char *key1 = (char*)get_key_val_pair_key(p1);
    int *val1 = (int*)get_key_val_pair_val(p1);

    char *key2 = (char*)get_key_val_pair_key(p2);
    int *val2 = (int*)get_key_val_pair_val(p2);
    

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

    //Leitura do arquivo
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
    ForwardList *list_of_words = forward_list_construct();
    while(scanf("%s", search_word) > 0){

        if(vector_binary_search(stop_words_vector, search_word, cmp_str) == -1){

            char *data_word = (char*)malloc(sizeof(char)*50);
            strcpy(data_word, search_word);
            forward_list_push_front(list_of_words, data_word);
        }
    }

    //CRIANDO A BINARY TREE COM AS INFORMAÇÕES DO INDICE
    int indice_size = 0;
    fscanf(indice_file, "%d", &indice_size);

    BinaryTree *bt = binary_tree_construct(cmp_str, key_destroy_fn, val_destroy_fn);
    
    for(int i = 0; i < indice_size; i++){

        char word_name[100];
        int num_docs = 0;

        fscanf(indice_file, "%s", word_name);
        fscanf(indice_file, "%d", &num_docs);

        for(int j = 0; j < num_docs; j++){

            ForwardList *l = forward_list_construct();

            char *document = (char*)malloc(sizeof(char)*100);
            char *word = (char*)malloc(sizeof(char)*100);
            strcpy(word, word_name);
            fscanf(indice_file, "%s", document);
            int *frq = (int*)malloc(sizeof(int));

            fscanf(indice_file, "%d", frq);

            ForwardList *search = (ForwardList*)binary_tree_get(bt, document);

            if(search != NULL){
                
                KeyValPair *kvp = key_val_pair_construct(word, frq);
                forward_list_push_front(search, kvp);
                forward_list_destroy(l);
                free(document);
            }
            else{

                KeyValPair *kvp = key_val_pair_construct(word, frq);
                forward_list_push_front(l, kvp);
                binary_tree_add(bt, document, l);
            }
        }
    }


    //Iteradores e saida
    Vector *inorder_traversal = binary_tree_inorder_traversal_recursive(bt);
    Vector *documents_frequency = vector_construct();

    for(int i = 0; i < vector_size(inorder_traversal); i++){

        KeyValPair *kvp = vector_get(inorder_traversal, i);
        char *key = (char*)get_key_val_pair_key(kvp);
        ForwardList *fl = (ForwardList*)get_key_val_pair_val(kvp);

        int *frequencia_busca = (int*)malloc(sizeof(int));
        *frequencia_busca = 0;
        int achou_alguma_palavra = 0;

        ForwardListIterator *it = forward_list_iterator_construct(fl);

        while(!forward_list_iterator_is_over(it)){

            KeyValPair *kvp = forward_list_iterator_next(it);
            char *word = (char*)get_key_val_pair_key(kvp);
            int *frequencia = (int*)get_key_val_pair_val(kvp);

            for(int i = 0; i < forward_list_size(list_of_words); i++){

                if(cmp_str(word, forward_list_get(list_of_words, i)) == 0){
                    achou_alguma_palavra = 1;
                    *frequencia_busca += *frequencia;
                }
            }

            free(word);
            free(frequencia);
        }
        forward_list_iterator_destroy(it);

        if(achou_alguma_palavra != 0){
            KeyValPair *pair = key_val_pair_construct(key, frequencia_busca);
            vector_push_back(documents_frequency, pair);
        }
        else{
            free(frequencia_busca);
        }

        forward_list_destroy_itens(fl);
        key_val_pair_destroy(kvp);
    }
    vector_destroy(inorder_traversal);

    //TRATAMENTO DO VETOR DE DOCUMENTOS
    vector_sort(documents_frequency, compara_documentos);

    int cont = 0;
    for(int i = 0; i < vector_size(documents_frequency); i++){

        cont++;
        KeyValPair *kvp = (KeyValPair*)vector_get(documents_frequency, i);
        char *key = get_key_val_pair_key(kvp);
        int *val = get_key_val_pair_val(kvp);
        if(cont <= 10){

            printf("%s %d\n", key, *val);
        }
        free(val);
        key_val_pair_destroy(kvp);
    }


    fclose(indice_file);
    fclose(stop_words_file);

    forward_list_destroy(list_of_words);

    for(int i = 0; i < stop_words_size_list; i++){
        free(vector_pop_front(stop_words_vector));
    }
    vector_destroy(stop_words_vector);
    vector_destroy(documents_frequency);

    binary_tree_destroy(bt);

    return 0;
}