#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"


struct cidade{

    int tag;
    char nome[50];
    float coordX, coordY;
    int numVizinhos;
    int *tagVizinhos;
    float *distVizinhos;

    int tagPai;
    float distPai;
};


Cidade *cidade_construct(){

    Cidade *cidade = (Cidade*)malloc(sizeof(Cidade));

    scanf("%d %s %f %f %d", &cidade->tag, cidade->nome, &cidade->coordX, &cidade->coordY, &cidade->numVizinhos);

    cidade->tagVizinhos = (int*)malloc(sizeof(int) * cidade->numVizinhos);
    cidade->distVizinhos = (float*)malloc(sizeof(float) * cidade->numVizinhos);
    
    for(int i = 0; i < cidade->numVizinhos ; i++){
        scanf("%d %f", &cidade->tagVizinhos[i], &cidade->distVizinhos[i]);
    }

    cidade->tagPai = -1;
    cidade->distPai = 0;

    return cidade;
}


void printa_cidade(void *data){

    if(data != NULL){

        Cidade *cidade = (Cidade*)data;

        printf("%d %s %.2f %.2f %d", cidade->tag, cidade->nome, cidade->coordX, cidade->coordY, cidade->numVizinhos);

        for(int i = 0; i < cidade->numVizinhos; i++){
            printf(" %d %.2f", cidade->tagVizinhos[i], cidade->distVizinhos[i]);
        }

        printf("\n");
    }
}


int get_tag(Cidade *cidade){
    return cidade->tag;
}


int get_num_vizinhos(Cidade *cidade){
    return cidade->numVizinhos;
}


int get_tag_vizinho(Cidade *cidade, int idx){
    return cidade->tagVizinhos[idx];
}


float get_distacia_vizinho(Cidade *cidade, int idx){
    return cidade->distVizinhos[idx];
}


int get_tag_pai(Cidade *cidade){
    return cidade->tagPai;
}

float get_dist_pai(Cidade *cidade){
    return cidade->distPai; 
}


void set_distacia_pai(Cidade *cidade, float distPai){
    cidade->distPai = distPai;
}


void set_tag_pai(Cidade *cidade, int tagPai){
    cidade->tagPai = tagPai;
}


int compara_cidade_tag(const void *a, const void *b){

    Cidade *c1 = (Cidade*)a;
    Cidade *c2 = (Cidade*)b;

    if(c1->tag == c2->tag){
        return 1;
    }
    return 0;
}


void cidade_destroy(void *data){

    if(data != NULL){

        Cidade *cidade = (Cidade*)data;
        free(cidade->tagVizinhos);
        free(cidade->distVizinhos);
        free(cidade);
    }
}