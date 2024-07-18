#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"


struct cidade{

    int tag;
    char nome[50];
    float coordX, coordY;
    int numVizinhos;
    int *vizinhos;
};


Cidade *cidade_construct(){

    Cidade *cidade = (Cidade*)malloc(sizeof(Cidade));

    scanf("%d %s %f %f %d", &cidade->tag, cidade->nome, &cidade->coordX, &cidade->coordY, &cidade->numVizinhos);

    cidade->vizinhos = (int*)malloc(sizeof(int) * (cidade->numVizinhos * 2));
    
    for(int i = 0; i < cidade->numVizinhos * 2; i++){
        scanf("%d", &cidade->vizinhos[i]);
    }

    return cidade;
}


void printa_cidade(void *data){

    if(data != NULL){

        Cidade *cidade = (Cidade*)data;

        printf("%d %s %.2f %.2f %d", cidade->tag, cidade->nome, cidade->coordX, cidade->coordY, cidade->numVizinhos);

        for(int i = 0; i < cidade->numVizinhos * 2; i++){
            printf(" %d", cidade->vizinhos[i]);
        }

        printf("\n");
    }
}


void cidade_destroy(void *data){

    if(data != NULL){

        Cidade *cidade = (Cidade*)data;
        free(cidade->vizinhos);
        free(cidade);
    }
}