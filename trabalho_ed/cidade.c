#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cidade.h"


struct cidade{

    int tag;
    char nome[50];
    float coordX;
    float coordY;
    int numVizinhas;
    int *vizinhas;
    float *distancias;
    int cidade_pai;
    float dist_pai;
    float dist_total;
    float custo_final;
};


Cidade *cidade_construct(){

    Cidade *c = (Cidade*)malloc(sizeof(Cidade));

    scanf("%d %s %f %f %d%*c", &c->tag, c->nome, &c->coordX, &c->coordY, &c->numVizinhas);

    c->vizinhas = (int*)calloc(c->numVizinhas, sizeof(int));
    c->distancias = (float*)calloc(c->numVizinhas, sizeof(float));

    for(int i = 0; i < c->numVizinhas; i++){
        
        scanf("%d %f%*c", &c->vizinhas[i], &c->distancias[i]);
    }

    c->cidade_pai = -1;
    c->dist_pai = -1;
    c->dist_total = 0;
    c->custo_final = 0;


    return c;
}


void cidade_destroy(void *data){

    Cidade *c = (Cidade*)data;

    if(c != NULL){
        free(c->vizinhas);
        free(c->distancias);
        free(c);
    }
}


void printa_cidade(void *data){ //teste

    Cidade *c = (Cidade*)data;

    printf("%s ", c->nome);

    /*printf("%d %s %.2f %.2f %d", c->tag, c->nome, c->coordX, c->coordY, c->numVizinhas);

    for(int i = 0; i < c->numVizinhas; i++){
        printf(" %d %d", c->vizinhas[i], c->distancias[i]);
    }

    printf(" cidade pai: %d distancia do pai: %d\n", c->cidade_pai, c->dist_pai);*/
}


int retorna_tag(void *data){
    
    Cidade *c = (Cidade*)data;

    return c->tag;
}

int retorna_num_vizinhas(void *data){

    Cidade *c = (Cidade*)data;

    return c->numVizinhas;
}

int retorna_tag_vizinha(void *data, int position){

    Cidade *c = (Cidade*)data;

    return c->vizinhas[position];
}

float retorna_dist_vizinha(void *data, int position){

    Cidade *c = (Cidade*)data;

    return c->distancias[position];
}


void set_cidade_pai(void *data, int tag){

    Cidade *c = (Cidade*)data;

    c->cidade_pai = tag;
}


void set_dist_pai(void *data, float dist){

    Cidade *c = (Cidade*)data;

    c->dist_pai = dist;
}


int retorna_cidade_pai(void *data){

    Cidade *c = (Cidade*)data;

    return c->cidade_pai;
}


float retorna_dist_pai(void *data){
    
    Cidade *c = (Cidade*)data;

    return c->dist_pai;
}


void set_dist_total(void *data, float dist){ //TESTE

    Cidade *c = (Cidade*)data;

    c->dist_total = c->dist_pai + dist;
}


float retorna_dist_total(void *data){ //TESTE

    Cidade *c = (Cidade*)data;

    return c->dist_total;
}


int compara_dist_total(const void *a, const void *b){

    Cidade *c1 = (Cidade*)a;
    Cidade *c2 = (Cidade*)b;

    float custo1 = c1->dist_total + c1->custo_final;
    float custo2 = c2->dist_total + c2->custo_final;

    if(custo1 < custo2){
        return 1;
    }
    else{
        return -1;
    }

}

void calcula_custo_final(const void *a, const void *b){

    Cidade *c1 = (Cidade*)a;
    Cidade *c2 = (Cidade*)b;

    float result = sqrt(pow(c1->coordX - c2->coordX, 2) + pow(c1->coordY - c2->coordY, 2));

    c1->custo_final = result;

}