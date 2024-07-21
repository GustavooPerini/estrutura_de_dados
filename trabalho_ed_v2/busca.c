#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

void busca_DFS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    //Vector *visitados = vector_construct(cidade_destroy);
    Deque *fronteira = deque_construct();
    deque_push_back(fronteira, vector_get(cidades, cidadeInicio));

    /*void *data = deque_pop_back(fronteira);
    printa_cidade(data);*/

    while(deque_size(fronteira) > 0){

        Cidade *cidadeVisitada = (Cidade*)deque_pop_back(fronteira);
        //void *cidadeVisitada = deque_pop_back(fronteira);
        int result = compara_cidade_tag(cidadeVisitada, vector_get(cidades, cidadeAlvo));

        if(result){
            printf("achei a cidade\n");
            break;
        }
        else{

            for(int i = 0; i < get_num_vizinhos(cidadeVisitada); i++){
                
                int tagVizinho = get_tag_vizinho(cidadeVisitada, i);
                float distVizinho = get_distacia_vizinho(cidadeVisitada, i);

                Cidade *cidadeVizinha = (Cidade*)vector_get(cidades, tagVizinho);

                set_distacia_pai(cidadeVizinha, distVizinho);
                set_tag_pai(cidadeVizinha, get_tag(cidadeVisitada));

                deque_push_back(fronteira, cidadeVizinha);
            }

            for(int i = 0; i < 3; i++){
                printa_cidade(deque_pop_back(fronteira));
            }

            //CONTINUAR AQUI

            printf("nao achei a cidade\n");
            break;
        }
    }

    deque_destroy(fronteira);
}