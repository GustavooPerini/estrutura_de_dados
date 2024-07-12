#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


struct vector{

    data_type *data;
    int size; // quantos elementos estao preenchidos na array
    int allocated; // tamanho alocado
};


Vector *vector_construct(){ // ok

    Vector *v = (Vector*)calloc(1, sizeof(Vector));

    v->allocated = 10;
    v->size = 0;
    v->data = (data_type*)calloc(v->allocated, sizeof(data_type));

    return v;
}


void vector_destroy(Vector *v){ //ok

    if(v != NULL){

        if(v->data != NULL){
            free(v->data);
        }
        free(v);
    }
}


void vector_push_back(Vector *v, data_type val){ // ok

    if(v->size == v->allocated){ //MEXIDO

        v->allocated *= 2;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}


int vector_size(Vector *v){ //ok

    return v->size;
}


data_type vector_get(Vector *v, int i){ 

    if(i >= 0 && i < v->allocated){
        return v->data[i];
    }
    else{
        printf("ERRO: indice invalido\n");
        exit(1);
    }
}


int vector_argmax(Vector *v, int cmp_fn(const void *, const void *)){ //ok

    data_type max = v->data[0];
    int max_index = 0;

    for(int i = 0; i < v->size; i++){
        if(cmp_fn(v->data[i], max) > 0){
            max = v->data[i];
            max_index = i;
        }
    }

    return max_index;
}


int vector_argmin(Vector *v, int cmp_fn(const void *, const void *)){ //ok

    data_type min = v->data[0];
    int min_index = 0;

    for(int i = 0; i < v->size; i++){
        if(cmp_fn(v->data[i], min) < 0){
            min = v->data[i];
            min_index = i;
        }
    }

    return min_index;
}


data_type vector_remove(Vector *v, int i){ // ok
    
    if(i >= 0 && i < v->size){

        data_type num = v->data[i];
        
        for(int j = i+1; j < v->size; j++){

            v->data[i] = v->data[j];
            i++;
        }  
        v->size--;
        return num;
        
    }
    else{
        printf("ERRO: indice invalido\n");
        exit(1);
    }

}


data_type vector_pop_front(Vector *v){ //ok

    return vector_remove(v, 0);
}


data_type vector_pop_back(Vector *v){ //ok

    return vector_remove(v, v->size - 1);
}


void vector_swap(Vector *v, int i, int j){ //ok

    if(i >= 0 && i < v->allocated && j >= 0 && j < v->allocated){

        data_type swap = v->data[i];
        v->data[i] = v->data[j];
        v->data[j] = swap;
    }

}


void vector_sort(Vector *v, func_point_compare func){ //ok

    qsort(v->data, v->size, sizeof(data_type), func);
}


Vector *vector_copy(Vector *v){

    Vector *vClone = vector_construct();
    
    for(int i = 0; i < v->size; i++){
        vector_push_back(vClone, v->data[i]);
    }

    return vClone;
}


void printa_dado(Vector *v, void print_func(void *data)){ //teste

    for(int i = 0; i < v->size; i++){

        //int position = (v->start + i) % v->allocated;

        print_func(v->data[i]);
    }
    
}


void vector_heapify(Vector *v, func_point_compare func){

    int idx = vector_size(v) - 1;
    int root_idx = (idx - 1)/2;

    while(1){

        int result = func(v->data[idx], v->data[root_idx]);

        if(result > 0){
            vector_swap(v, idx, root_idx);
            idx = root_idx;
            if(idx == 0){
                break;
            }
            root_idx = (idx - 1)/2;
        }
        else if(result <= 0){
            break;
        }
    }
}


data_type vector_heapify_down(Vector *v, func_point_compare func){

    data_type num = v->data[0];

    vector_swap(v, 0, v->size - 1);
    v->size--;
    int max = 0;
    int left_child = 0;
    int right_child = 0;

    while(1){ 
        
        int idx = max;
        left_child = idx*2 + 1;
        right_child = idx*2 + 2;

        if((left_child < v->size) && (func(v->data[max], v->data[left_child]) < 0)){ 
            max = left_child;
        }
        if((right_child < v->size) && (func(v->data[max], v->data[right_child]) < 0)){ 
            max = right_child;
        }
        
        if(max == idx){
            break;
        }
        else if(max != idx){
            vector_swap(v, idx, max);
        }
        
    }

    return num;
}
