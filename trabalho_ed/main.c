#include <stdio.h>
#include <string.h>
#include "cidade.h"
#include "vector.h"
#include "rota.h"


int main(){

    int cidade_inicio = 0;
    int cidade_alvo = 6;
    char metodo[5] = "A*";

    int num_cidades;
    Vector *cidades = vector_construct();

    scanf("%d%*c", &num_cidades);

    for(int i = 0; i < num_cidades; i++){

        Cidade *c = cidade_construct();

        vector_push_back(cidades, c);
    }

    if(strcmp(metodo, "A*") == 0){
        
        data_type destino_final = vector_get(cidades, cidade_alvo);

        for(int i = 0; i < num_cidades; i++){

            if(i != cidade_alvo){
                data_type cidade = vector_get(cidades, cidade_alvo);
                calcula_custo_final(cidade, destino_final);
            }
        }
    }

    Rota *r = rota_construct(cidade_inicio, cidades);

    while(1){

        /*printf("Fronteira: ");
        printa_fronteira(r);
        printf("\n");
        printf("Visitados: ");
        printa_visitados(r);
        printf("\n----------------------------------\n");*/

        int a = realiza_rota(r, metodo, cidades);

        if(a == cidade_alvo){
            retorna_rota(r, cidade_inicio, cidades);
            break;
        }
        else if(a == -1){
            printf("Nao achei a cidade\n");
            break;
        }
    }

    printa_visitados(r);
    //printa_dado(cidades, printa_cidade);
    rota_destroy(r);

    for(int i = 0; i < num_cidades; i++){
        cidade_destroy(vector_get(cidades, i));
    }
    vector_destroy(cidades);

    return 0;
}