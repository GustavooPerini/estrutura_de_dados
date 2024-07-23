#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

int main(){

    int n, cidadeInicio, cidadeAlvo;
    char comando[5];

    Vector *cidades = vector_construct(cidade_destroy);

    scanf("%s %d %d %d", comando, &cidadeInicio, &cidadeAlvo, &n);

    //gravando todas as cidades de entrada em um vetor
    for(int i = 0; i < n; i++){
        vector_push_back(cidades, cidade_construct());
        set_tag(vector_get(cidades, i), i);
    }

    if(!strcmp(comando, "DFS")){

        busca_DFS(cidades, cidadeInicio, cidadeAlvo);
    }
    else if(!strcmp(comando, "BFS")){

        busca_BFS(cidades, cidadeInicio, cidadeAlvo);
    }
    else if(!strcmp(comando, "UCS")){

        busca_UCS(cidades, cidadeInicio, cidadeAlvo);
    }
    else if(!strcmp(comando, "A*")){

        busca_Astar(cidades, cidadeInicio, cidadeAlvo);
    }

    vector_destroy(cidades);

    return 0;
}