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
    float custoOrigem;
};


Cidade *cidade_construct(FILE *fp){

    Cidade *cidade = (Cidade*)malloc(sizeof(Cidade));

    fscanf(fp, "%s %f %f %d", cidade->nome, &cidade->coordX, &cidade->coordY, &cidade->numVizinhos);

    cidade->tag = -1;

    cidade->tagVizinhos = (int*)malloc(sizeof(int) * cidade->numVizinhos);
    cidade->distVizinhos = (float*)malloc(sizeof(float) * cidade->numVizinhos);
    
    for(int i = 0; i < cidade->numVizinhos ; i++){
        fscanf(fp, "%d %f", &cidade->tagVizinhos[i], &cidade->distVizinhos[i]);
    }

    cidade->tagPai = -1;
    cidade->distPai = 0;
    cidade->custoOrigem = 0;

    return cidade;
}


void printa_cidade(void *data){

    if(data != NULL){

        Cidade *cidade = (Cidade*)data;
        printf("%s\n", cidade->nome);
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


float get_custo_origem(Cidade *cidade){
    return cidade->custoOrigem;
}


float get_coordX(Cidade *cidade){
    return cidade->coordX;
}


float get_coordY(Cidade *cidade){
    return cidade->coordY;
}


char *get_nome(Cidade *cidade){
    return cidade->nome;
}


void set_distacia_pai(Cidade *cidade, float distPai){ 
    cidade->distPai = distPai;
}


void set_tag_pai(Cidade *cidade, int tagPai){
    cidade->tagPai = tagPai;
}


void set_tag(Cidade *cidade, int tag){
    cidade->tag = tag;
}


void set_custo_origem(Cidade *cidade, float custo){
    cidade->custoOrigem += custo;
}


int compara_cidade_tag(const void *a, const void *b){

    Cidade *c1 = (Cidade*)a;
    Cidade *c2 = (Cidade*)b;

    if(c1->tag == c2->tag){
        return 1;
    }
    return 0;
}

Cidade *cidade_copia(Cidade *cidade){

    Cidade *copia = (Cidade*)malloc(sizeof(Cidade));

    copia->tag = cidade->tag;
    strcpy(copia->nome, cidade->nome);
    copia->coordX = cidade->coordX;
    copia->coordY = cidade->coordY;
    copia->numVizinhos = cidade->numVizinhos;

    copia->tagVizinhos = (int*)malloc(sizeof(int) * cidade->numVizinhos);
    copia->distVizinhos = (float*)malloc(sizeof(float) * cidade->numVizinhos);

    for(int i = 0; i < copia->numVizinhos ; i++){

        copia->tagVizinhos[i] = cidade->tagVizinhos[i];
        copia->distVizinhos[i] = cidade->distVizinhos[i];
    }

    copia->tagPai = cidade->tagPai;
    copia->distPai = cidade->distPai;
    copia->custoOrigem = cidade->custoOrigem;

    return copia;
}


void cidade_destroy(void *data){

    if(data != NULL){

        Cidade *cidade = (Cidade*)data;
        free(cidade->tagVizinhos);
        free(cidade->distVizinhos);
        free(cidade);
    }
}