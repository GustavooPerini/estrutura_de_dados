#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

void busca_DFS(Vector *cidades, int cidadeInicio, int cidadeAlvo){

    //Vector *visitados = vector_construct(cidade_destroy);
    Deque *fronteira = deque_construct();
    deque_push_back(fronteira, vector_get(cidades, cidadeInicio));

    void *data = deque_pop_back(fronteira);
    printa_cidade(data);
    deque_destroy(fronteira);

    //CONTINUAR AQUI
}