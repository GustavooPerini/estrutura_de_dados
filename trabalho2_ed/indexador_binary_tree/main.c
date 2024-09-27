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



int main(){

    //Leitura do arquivo
    char file_name[300];

    scanf("%s%*c", file_name);

    FILE *file = fopen(file_name, "r");

    int n;
    fscanf(file, "%d", &n);

    //Montando a arvore binaria
    BinaryTree *bt = binary_tree_construct(cmp_str, key_destroy_fn, val_destroy_fn);
    
    for(int i = 0; i < n; i++){

        char doc_name[100];
        int num_words = 0;

        fscanf(file, "%s ", doc_name);
        fscanf(file, "%d: ", &num_words);
        doc_name[strlen(doc_name) - 1] = '\0';

        for(int j = 0; j < num_words; j++){

            ForwardList *l = forward_list_construct();

            char *word = (char*)malloc(sizeof(char)*100);
            char *document = (char*)malloc(sizeof(char)*100);
            strcpy(document, doc_name);
            fscanf(file, "%s", word);
            int *frq = (int*)malloc(sizeof(int));
            *frq = 1;

            ForwardList *search = (ForwardList*)binary_tree_get(bt, word);

            if(search != NULL){

                ForwardListIterator *it = forward_list_iterator_construct(search);
                int eh_documento_novo = 0;

                while(!forward_list_iterator_is_over(it)){
                    
                    KeyValPair *kvp = forward_list_iterator_next(it);
                    void *key = get_key_val_pair_key(kvp);
                
                    if(cmp_str(key, document) == 0){ //verifico se aquele documento ja esta na lista encadeada
                        //se ele estiver, basta aumentar a frequencia
                        int *value = (int*)get_key_val_pair_val(kvp);
                        *(value) = *(value) + 1;
                        break;
                    }
                    else{ //temos um documento novo sendo inserido na lista encadeada
                        KeyValPair *kvp = key_val_pair_construct(document, frq);
                        forward_list_push_front(search, kvp);
                        eh_documento_novo = 1;
                        break;
                    }
                }
                forward_list_iterator_destroy(it);

                if(eh_documento_novo == 0){
                    free(frq);
                    free(document);
                }

                free(word);
                forward_list_destroy(l);
            }
            else{

                KeyValPair *kvp = key_val_pair_construct(document, frq);
                forward_list_push_front(l, kvp);

                binary_tree_add(bt, word, l);
            }
        }
    }
    fclose(file);


    //Iteradores e saida
    Vector *inorder_traversal = binary_tree_inorder_traversal_recursive(bt);

    printf("%d\n", binary_tree_size(bt));
    for(int i = 0; i < vector_size(inorder_traversal); i++){

        KeyValPair *kvp = vector_get(inorder_traversal, i);
        char *key = (char*)get_key_val_pair_key(kvp);
        ForwardList *fl = (ForwardList*)get_key_val_pair_val(kvp);

        ForwardListIterator *it = forward_list_iterator_construct(fl);

        int fl_size = forward_list_size(fl);
        printf("%s %d ", key, fl_size);

        while(!forward_list_iterator_is_over(it)){

            KeyValPair *kvp = forward_list_iterator_next(it);
            char *doc = (char*)get_key_val_pair_key(kvp);
            int *frequencia = (int*)get_key_val_pair_val(kvp);

            printf("%s %d ", doc, *frequencia);
            free(doc);
            free(frequencia);
        }
        printf("\n");
        forward_list_iterator_destroy(it);

        forward_list_destroy_itens(fl);
        key_val_pair_destroy(kvp);
    }

    vector_destroy(inorder_traversal);

    binary_tree_destroy(bt);

    return 0;
}