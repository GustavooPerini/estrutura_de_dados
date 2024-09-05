#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "busca.h"

void busca_DFS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    Vector *visitados = vector_construct(cidade_destroy);
    Deque *fronteira = deque_construct();

    Cidade *cidadeInicial = cidade_copia((Cidade*)vector_get(cidades, cidadeInicio));

    deque_push_back(fronteira, cidadeInicial);
    int achouCidade = 0;

    while(deque_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)deque_pop_back(fronteira);

        //verifico se ja foi visitado a cidade que estou visitando atualmente
        int jaExplrou = 0;
        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(cidadeVisitada, vector_get(visitados, i))){
                jaExplrou = 1;
                cidade_destroy(cidadeVisitada);
                break;
            }
        }
        if(jaExplrou == 1){
            continue;
        }

        int result = compara_cidade_tag(cidadeVisitada, vector_get(cidades, cidadeAlvo));
        vector_push_back(visitados, cidadeVisitada);

        if(result){
            printa_rota(visitados, cidades);
            achouCidade = 1;
            break;
        }
        else{

            for(int i = 0; i < get_num_vizinhos(cidadeVisitada); i++){
                
                int tagVizinho = get_tag_vizinho(cidadeVisitada, i); //quem é o vizinho
                float distVizinho = get_distacia_vizinho(cidadeVisitada, i); //qual a distância do vizinho em relação a cidade visitada

                Cidade *cidadeVizinha = (Cidade*)vector_get(cidades, tagVizinho); //pego a cidade vizinha

                int jaVisitou = 0;
                for(int i = 0; i < vector_size(visitados); i++){ //verifico se ja visitei a cidade vizinha

                    if(compara_cidade_tag(cidadeVizinha, vector_get(visitados, i))){
                        jaVisitou = 1;
                        break;
                    }
                }

                if(jaVisitou == 0){ //se ele não visitou a cidade vizinha, pode por na fronteira

                    Cidade *copia = cidade_copia(cidadeVizinha);

                    set_distacia_pai(copia, distVizinho); //deixo gravado na cidade vizinha a distancia dela até a cidade de onde ela veio
                    set_tag_pai(copia, get_tag(cidadeVisitada)); //deixo gravado na cidade vizinha de onde ela veio

                    deque_push_back(fronteira, copia);//boto a cidade vizinha na fronteira
                }
            }
        }
    }

    if(achouCidade == 0){
        printf("IMPOSSIVEL\n");
    }

    //verificando se ainda tem cidades na fronteira para desalocar
    if(deque_size(fronteira) > 0){
        for(int i = 0; i < deque_size(fronteira); i++){
            cidade_destroy(deque_get(fronteira, i));
        }
    }
    
    deque_destroy(fronteira);
    vector_destroy(visitados);
}


void busca_BFS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    Vector *visitados = vector_construct(cidade_destroy);
    Deque *fronteira = deque_construct();

    Cidade *cidadeInicial = cidade_copia((Cidade*)vector_get(cidades, cidadeInicio));

    deque_push_back(fronteira, cidadeInicial);
    int achouCidade = 0;

    while(deque_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)deque_pop_front(fronteira);

        //verifico se ja foi visitado a cidade que estou visitando atualmente
        int jaExplrou = 0;
        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(cidadeVisitada, vector_get(visitados, i))){
                jaExplrou = 1;
                cidade_destroy(cidadeVisitada);
                break;
            }
        }
        if(jaExplrou == 1){
            continue;
        }

        int result = compara_cidade_tag(cidadeVisitada, vector_get(cidades, cidadeAlvo));
        vector_push_back(visitados, cidadeVisitada);

        if(result){
            printa_rota(visitados, cidades);
            achouCidade = 1;
            break;
        }
        else{

            for(int i = 0; i < get_num_vizinhos(cidadeVisitada); i++){
                
                int tagVizinho = get_tag_vizinho(cidadeVisitada, i); //quem é o vizinho
                float distVizinho = get_distacia_vizinho(cidadeVisitada, i); //qual a distância do vizinho em relação a cidade visitada

                Cidade *cidadeVizinha = (Cidade*)vector_get(cidades, tagVizinho); //pego a cidade vizinha

                int jaVisitou = 0;
                for(int i = 0; i < vector_size(visitados); i++){ //verifico se ja visitei a cidade vizinha

                    if(compara_cidade_tag(cidadeVizinha, vector_get(visitados, i))){
                        jaVisitou = 1;
                        break;
                    }
                }

                if(jaVisitou == 0){ //se ele não visitou a cidade vizinha, pode por na fronteira

                    Cidade *copia = cidade_copia(cidadeVizinha);

                    set_distacia_pai(copia, distVizinho); //deixo gravado na cidade vizinha a distancia dela até a cidade de onde ela veio
                    set_tag_pai(copia, get_tag(cidadeVisitada)); //deixo gravado na cidade vizinha de onde ela veio

                    deque_push_back(fronteira, copia);//boto a cidade vizinha na fronteira
                }
            }
        }
    }

    if(achouCidade == 0){
        printf("IMPOSSIVEL\n");
    }

    //verificando se ainda tem cidades na fronteira para desalocar
    if(deque_size(fronteira) > 0){
        for(int i = 0; i < deque_size(fronteira); i++){
            cidade_destroy(deque_get(fronteira, i));
        }
    }

    deque_destroy(fronteira);
    vector_destroy(visitados);
}


void busca_UCS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    Vector *visitados = vector_construct(cidade_destroy);
    Heap *fronteira = heap_construct();

    Cidade *cidadeInicial = cidade_copia((Cidade*)vector_get(cidades, cidadeInicio));

    heap_push(fronteira, cidadeInicial, 0);
    int achouCidade = 0;

    while(heap_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)heap_pop(fronteira);

        //verifico se ja foi visitado a cidade que estou visitando atualmente
        int jaExplrou = 0;
        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(cidadeVisitada, vector_get(visitados, i))){
                jaExplrou = 1;
                cidade_destroy(cidadeVisitada);
                break;
            }
        }
        if(jaExplrou == 1){
            continue;
        }

        int result = compara_cidade_tag(cidadeVisitada, vector_get(cidades, cidadeAlvo));
        vector_push_back(visitados, cidadeVisitada);

        if(result){
            printa_rota(visitados, cidades);
            achouCidade = 1;
            break;
        }
        else{

            for(int i = 0; i < get_num_vizinhos(cidadeVisitada); i++){
                
                int tagVizinho = get_tag_vizinho(cidadeVisitada, i); //quem é o vizinho
                float distVizinho = get_distacia_vizinho(cidadeVisitada, i); //qual a distância do vizinho em relação a cidade visitada

                Cidade *cidadeVizinha = (Cidade*)vector_get(cidades, tagVizinho); //pego a cidade vizinha

                int jaVisitou = 0;
                for(int i = 0; i < vector_size(visitados); i++){ //verifico se ja visitei a cidade vizinha

                    if(compara_cidade_tag(cidadeVizinha, vector_get(visitados, i))){
                        jaVisitou = 1;
                        break;
                    }
                }

                if(jaVisitou == 0){ //se ele não visitou a cidade vizinha, pode por na fronteira

                    Cidade *copia = cidade_copia(cidadeVizinha);

                    set_distacia_pai(copia, distVizinho); //deixo gravado na cidade vizinha a distancia dela até a cidade de onde ela veio
                    set_tag_pai(copia, get_tag(cidadeVisitada)); //deixo gravado na cidade vizinha de onde ela veio

                    set_custo_origem(copia, get_custo_origem(cidadeVisitada) + distVizinho);

                    heap_push(fronteira, copia, get_custo_origem(copia));//boto a cidade vizinha na fronteira
                }
            }
        }
    }

    if(achouCidade == 0){
        printf("IMPOSSIVEL\n");
    }

    //verificando se ainda tem cidades na fronteira para desalocar
    if(heap_size(fronteira) > 0){
        for(int i = 0; i < heap_size(fronteira); i++){
            cidade_destroy(heap_get(fronteira, i));
        }
    }

    heap_destroy(fronteira);
    vector_destroy(visitados);
}


void busca_Astar(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    Vector *visitados = vector_construct(cidade_destroy);
    Heap *fronteira = heap_construct();

    Cidade *cidadeInicial = cidade_copia((Cidade*)vector_get(cidades, cidadeInicio));

    heap_push(fronteira, cidadeInicial, 0);
    int achouCidade = 0;

    while(heap_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)heap_pop(fronteira);

        //verifico se ja foi visitado a cidade que estou visitando atualmente
        int jaExplrou = 0;
        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(cidadeVisitada, vector_get(visitados, i))){
                jaExplrou = 1;
                cidade_destroy(cidadeVisitada);
                break;
            }
        }
        if(jaExplrou == 1){
            continue;
        }

        int result = compara_cidade_tag(cidadeVisitada, vector_get(cidades, cidadeAlvo));
        vector_push_back(visitados, cidadeVisitada);

        if(result){
            printa_rota(visitados, cidades);
            achouCidade = 1;
            break;
        }
        else{

            for(int i = 0; i < get_num_vizinhos(cidadeVisitada); i++){
                
                int tagVizinho = get_tag_vizinho(cidadeVisitada, i); //quem é o vizinho
                float distVizinho = get_distacia_vizinho(cidadeVisitada, i); //qual a distância do vizinho em relação a cidade visitada

                Cidade *cidadeVizinha = (Cidade*)vector_get(cidades, tagVizinho); //pego a cidade vizinha

                int jaVisitou = 0;
                for(int i = 0; i < vector_size(visitados); i++){ //verifico se ja visitei a cidade vizinha

                    if(compara_cidade_tag(cidadeVizinha, vector_get(visitados, i))){
                        jaVisitou = 1;
                        break;
                    }
                }

                if(jaVisitou == 0){ //se ele não visitou a cidade vizinha, pode por na fronteira

                    Cidade *copia = cidade_copia(cidadeVizinha);

                    set_distacia_pai(copia, distVizinho); //deixo gravado na cidade vizinha a distancia dela até a cidade de onde ela veio
                    set_tag_pai(copia, get_tag(cidadeVisitada)); //deixo gravado na cidade vizinha de onde ela veio

                    set_custo_origem(copia, get_custo_origem(cidadeVisitada) + distVizinho);

                    float distAteFinal = calcula_dist_heuristica(copia, vector_get(cidades, cidadeAlvo));

                    heap_push(fronteira, copia, get_custo_origem(copia) + distAteFinal);//boto a cidade vizinha na fronteira
                }
            }
        }
    }

    if(achouCidade == 0){
        printf("IMPOSSIVEL\n");
    }

    //verificando se ainda tem cidades na fronteira para desalocar
    if(heap_size(fronteira) > 0){
        for(int i = 0; i < heap_size(fronteira); i++){
            cidade_destroy(heap_get(fronteira, i));
        }
    }

    heap_destroy(fronteira);
    vector_destroy(visitados);
}


void printa_rota(Vector *visitados, Vector *cidades){

    float distTotal = 0;
    int tagCidade = vector_size(visitados) - 1;
    Cidade *cidadeAtual = vector_get(visitados, tagCidade);

    Deque *rota = deque_construct();

    while(1){

        distTotal += get_dist_pai(cidadeAtual);
        tagCidade = get_tag_pai(cidadeAtual);

        deque_push_back(rota, cidadeAtual);

        if(tagCidade < 0){
            break;
        }

        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(vector_get(cidades, tagCidade), vector_get(visitados, i))){

                cidadeAtual = vector_get(visitados, i);
                break;
            }
        }
    }
    
    int dequeSize = deque_size(rota);
    for(int i = 0; i < dequeSize; i++){
        printa_cidade(deque_pop_back(rota));
    }

    printf("Custo: %.2f Num_Expandidos: %d\n", distTotal, vector_size(visitados));

    deque_destroy(rota);
}

float calcula_dist_heuristica(void *data1, void *data2){

    Cidade *c1 = (Cidade*)data1;
    Cidade *cidadeAlvo = (Cidade*)data2;

    float dx = get_coordX(cidadeAlvo) - get_coordX(c1);
    float dy = get_coordY(cidadeAlvo) - get_coordY(c1);

    float distancia_quadrada = (dx * dx) + (dy * dy);

    return sqrt(distancia_quadrada);
}