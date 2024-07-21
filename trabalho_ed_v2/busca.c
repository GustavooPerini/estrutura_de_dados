#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

void busca_DFS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    Vector *visitados = vector_construct(cidade_destroy);
    Deque *fronteira = deque_construct();
    deque_push_back(fronteira, vector_get(cidades, cidadeInicio));
    int achouCidade = 0;

    while(deque_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)deque_pop_back(fronteira);

        //verifico se ja foi visitado a cidade que estou visitando atualmente
        int jaExplrou = 0;
        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(cidadeVisitada, vector_get(visitados, i))){
                jaExplrou = 1;
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

                    set_distacia_pai(cidadeVizinha, distVizinho); //deixo gravado na cidade vizinha a distancia dela até a cidade de onde ela veio
                    set_tag_pai(cidadeVizinha, get_tag(cidadeVisitada)); //deixo gravado na cidade vizinha de onde ela veio

                    deque_push_back(fronteira, cidadeVizinha);//boto a cidade viznha na fronteira
                }
            }
        }
    }

    if(achouCidade == 0){
        printf("IMPOSSIVEL\n");
    }

    deque_destroy(fronteira);
    vector_pacial_destroy(visitados);
}


void busca_BFS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    Vector *visitados = vector_construct(cidade_destroy);
    Deque *fronteira = deque_construct();
    deque_push_back(fronteira, vector_get(cidades, cidadeInicio));
    int achouCidade = 0;

    while(deque_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)deque_pop_front(fronteira);

        //verifico se ja foi visitado a cidade que estou visitando atualmente
        int jaExplrou = 0;
        for(int i = 0; i < vector_size(visitados); i++){

            if(compara_cidade_tag(cidadeVisitada, vector_get(visitados, i))){
                jaExplrou = 1;
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

                    set_distacia_pai(cidadeVizinha, distVizinho); //deixo gravado na cidade vizinha a distancia dela até a cidade de onde ela veio
                    set_tag_pai(cidadeVizinha, get_tag(cidadeVisitada)); //deixo gravado na cidade vizinha de onde ela veio

                    deque_push_back(fronteira, cidadeVizinha);//boto a cidade viznha na fronteira
                }
            }
        }
    }

    if(achouCidade == 0){
        printf("IMPOSSIVEL\n");
    }

    deque_destroy(fronteira);
    vector_pacial_destroy(visitados);
}


void busca_UCS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

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

        cidadeAtual = vector_get(cidades, tagCidade);
    }
    
    int dequeSize = deque_size(rota);
    for(int i = 0; i < dequeSize; i++){
        printa_cidade(deque_pop_back(rota));
    }

    printf("Custo: %.2f Num_expandidos: %d\n", distTotal, vector_size(visitados));

    deque_destroy(rota);
}