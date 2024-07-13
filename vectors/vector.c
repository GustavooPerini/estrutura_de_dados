#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define VECTOR_GROWTH 2
#define VECTOR_INITIAL_ALLOCATION 10

struct Vector{

    data_type *data;
    int size;
    int allocated;
    delete_func delete;
};


Vector *vector_construct(delete_func func){

    Vector *v = (Vector*)malloc(sizeof(Vector));

    v->size = 0;
    v->allocated = VECTOR_INITIAL_ALLOCATION;
    v->data = (data_type*)malloc(VECTOR_INITIAL_ALLOCATION * sizeof(data_type));
    v->delete = func;

    return v;
}


void vector_push_back(Vector *v, data_type val){

    if(v->size == v->allocated){
        v->allocated *= VECTOR_GROWTH;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;

}


data_type vector_get(Vector *v, int i){

    if(i >= 0 && i < v->size){
        return v->data[i];
    }
    printf("Indice invalido\n");
    return NULL;
}


void vector_set(Vector *v, int i, data_type val){

    if(i >= 0 && i < v->size){
        v->delete(v->data[i]);
        v->data[i] = val;
    }
    else{
        printf("Indice invalido\n");
    }
}


int vector_size(Vector *v){
    return v->size;
}


int vector_find(Vector *v, data_type val, compare_func cmp){

    for(int i = 0; i < v->size; i++){

       if(!cmp(val, vector_get(v, i))){
            return i;
       }

    }

    return -1;
}


void vector_remove(Vector *v, int i){

    if(i >= 0 && i < v->size){
        
        v->delete(v->data[i]);

        for(int j = i; j < v->size - 1; j++){
            v->data[j] = v->data[j+1];
        }
        v->size--;
    }
    else{
        printf("Indice invalido\n");
    }

}


void vector_pop_front(Vector *v){
    vector_remove(v, 0);
}


void vector_pop_back(Vector *v){
    vector_remove(v, v->size - 1);
}


void vector_insert(Vector *v, int i, data_type val){

    if(i >= 0 && i < v->size){

        if(v->size == v->allocated){
            v->allocated *= VECTOR_GROWTH;
            v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
        }

        for(int j = v->size; j > i; j--){

            v->data[j] = v->data[j-1];
        }
        v->data[i] = val;
        v->size++;

    }
    else{
        printf("indide invalido\n");
    }

}


void vector_swap(Vector *v, int i, int j){


    if((i >= 0 && i < v->size) && (j >= 0 && j < v->size)){
        
        data_type data = v->data[i];
        v->data[i] = v->data[j];
        v->data[j] = data;
    }
    else{
        printf("indice invalido\n");
    }

}


void vector_sort(Vector *v, compare_func cmp){

    for(int i = 0; i < v->size - 1; i++){
        int trocas = 0;

        for(int j = 0; j < v->size - i - 1; j++){

            if(cmp(v->data[j], v->data[j+1]) > 0){
                vector_swap(v, j, j+1);
                trocas++;
            }
        }

        if(trocas == 0){
            break;
        }
    }

   //qsort(v->data, v->size, sizeof(data_type), cmp);

}


int vector_binary_search(Vector *v, data_type val, compare_func cmp){

    int left = 0;
    int right = v->size - 1;

    while(left <= right){

        int mid = left + (right - left) / 2;
        int search = cmp(val, vector_get(v, mid));

        if(search == 0){
            return mid;
        }
        else if(search > 0){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    
    return -1;
}


//deixar a função de comparação funcionar com o qsort e as outras funções (ver com o professor)


void vector_destroy(Vector *v){

    for(int i = 0; i < v->size; i++){
        v->delete(v->data[i]);
    }
    free(v->data);
    free(v);
}