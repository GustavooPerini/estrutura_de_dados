#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rota.h"


struct rota{

    C_array *fronteira;
    Heap *fronteira_h;
    int num_fronteira;

    Vector *visistadas;
    int num_visitadas;
};


Rota *rota_construct(int cidadeInicio, Vector *cidades){

    Rota *r = (Rota*)malloc(sizeof(Rota));

    r->fronteira = array_construct();
    r->fronteira_h = heap_constructor(compara_dist_total);
    r->visistadas = vector_construct();

    data_type cidade_inicial = vector_get(cidades, cidadeInicio);

    set_cidade_pai(cidade_inicial, cidadeInicio);
    set_dist_pai(cidade_inicial, 0);

    array_push_back(r->fronteira, cidade_inicial); //colocando a cidade inicial na fronteira
    heap_push(r->fronteira_h, cidade_inicial);
    r->num_fronteira = 1;
    r->num_visitadas = 0;

    return r;
}


void rota_destroy(Rota *r){

    if(r != NULL){
        array_destroy(r->fronteira);
        heap_destroy(r->fronteira_h);
        vector_destroy(r->visistadas);
        free(r);
    }
}


/*void printa_fronteira(Rota *r){
    printa_dado(r->fronteira, printa_cidade);
}*/


void printa_visitados(Rota *r){
    printa_dado(r->visistadas, printa_cidade);
}


int realiza_rota(Rota *r, char *metodo, Vector *cidades){ //essa função ficará dentro de um while na main, e vai retornar uma cidade visitada.
    
    if(strcmp(metodo, "DFS") == 0){
        return rota_DFS(r, cidades);
    }
    else if(strcmp(metodo, "BFS") == 0){
        return rota_BFS(r, cidades);
    }
    else if(strcmp(metodo, "UCS") == 0){
        return rota_UCS(r, cidades);
    }
    else if(strcmp(metodo, "A*") == 0){
        return rota_Astar(r, cidades);
    }

    return -1;
}


int rota_DFS(Rota *r, Vector *cidades){

    if(r->num_fronteira == 0){
        return -1;
    }
    
    data_type cidade_fronteira = array_get(r->fronteira, array_size(r->fronteira) - 1);

    int tag = retorna_tag(cidade_fronteira);
    int num_vizinhas = retorna_num_vizinhas(cidade_fronteira);

    vector_push_back(r->visistadas, array_pop_back(r->fronteira));
    r->num_fronteira--;
    r->num_visitadas++;

    for(int i = 0; i < num_vizinhas; i++){
        
        int ja_visitou = 0;
        int ta_na_fronteira = 0;

        int tag_vizinha = retorna_tag_vizinha(cidade_fronteira, i);
        float dist_vizinha = retorna_dist_vizinha(cidade_fronteira, i);

        for(int j = 0; j < r->num_visitadas; j++){ //VERIFICANDO SE A VIZINHA JA FOI VISITADA

            int tag_visitada = retorna_tag(vector_get(r->visistadas, j));

            if(tag_vizinha == tag_visitada){
                ja_visitou = 1;
                break;
            }
        }

        for(int k = 0; k < r->num_fronteira; k++){ // VERIFICANDO SE A VIZINHA JA ESTA NA FRONTEIRA

            int tag_fronteira = retorna_tag(array_get(r->fronteira, k));

            if(tag_vizinha == tag_fronteira){
                ta_na_fronteira = 1;
                break;
            }
        }

        if(ja_visitou == 0 && ta_na_fronteira == 0){ //se ele nao visitou a cidade e ela nao ta na fronteira, pode por na fronteira.

            data_type cidade_vizinha = vector_get(cidades, tag_vizinha);

            set_cidade_pai(cidade_vizinha, tag); //mando a cidade vizinha e de onde ela veio(pai).
            set_dist_pai(cidade_vizinha, dist_vizinha); // mando a cidade vizinha e a distancia dela do pai

            array_push_back(r->fronteira, cidade_vizinha); //botando cidade na fronteira.
            r->num_fronteira++;
        }
        
    }

    return tag;
}


int rota_BFS(Rota *r, Vector *cidades){ 

    if(r->num_fronteira == 0){
        return -1;
    }

    data_type cidade_fronteira = array_get(r->fronteira, 0);

    int tag = retorna_tag(cidade_fronteira);
    int num_vizinhas = retorna_num_vizinhas(cidade_fronteira);

    vector_push_back(r->visistadas, array_pop_front(r->fronteira));
    r->num_fronteira--;
    r->num_visitadas++;

    for(int i = 0; i < num_vizinhas; i++){
        
        int ja_visitou = 0;
        int ta_na_fronteira = 0;

        int tag_vizinha = retorna_tag_vizinha(cidade_fronteira, i);
        float dist_vizinha = retorna_dist_vizinha(cidade_fronteira, i);

        for(int j = 0; j < r->num_visitadas; j++){ //VERIFICANDO SE A VIZINHA JA FOI VISITADA

            int tag_visitada = retorna_tag(vector_get(r->visistadas, j));

            if(tag_vizinha == tag_visitada){
                ja_visitou = 1;
                break;
            }
        }

        for(int k = 0; k < r->num_fronteira; k++){ // VERIFICANDO SE A VIZINHA JA ESTA NA FRONTEIRA

            int tag_fronteira = retorna_tag(array_get(r->fronteira, k));

            if(tag_vizinha == tag_fronteira){
                ta_na_fronteira = 1;
                break;
            }
        }

        if(ja_visitou == 0 && ta_na_fronteira == 0){ //se ele nao visitou a cidade e ela nao ta na fronteira, pode por na fronteira.

            data_type cidade_vizinha = vector_get(cidades, tag_vizinha);

            set_cidade_pai(cidade_vizinha, tag); //mando a cidade vizinha e de onde ela veio(pai).
            set_dist_pai(cidade_vizinha, dist_vizinha); // mando a cidade vizinha e a distancia dela do pai

            array_push_back(r->fronteira, cidade_vizinha); //botando cidade na fronteira.
            r->num_fronteira++;
        }
        
    }

    return tag;
}


int rota_UCS(Rota *r, Vector *cidades){
    
    if(r->num_fronteira == 0){
        return -1;
    }

    data_type cidade_fronteira = heap_pop(r->fronteira_h);

    int tag = retorna_tag(cidade_fronteira);
    int num_vizinhas = retorna_num_vizinhas(cidade_fronteira);

    vector_push_back(r->visistadas, cidade_fronteira);
    r->num_fronteira--;
    r->num_visitadas++;
    
    for(int i = 0; i < num_vizinhas; i++){
        
        int ja_visitou = 0;
        int ta_na_fronteira = 0;
        int posi_fronteira = 0;

        int tag_vizinha = retorna_tag_vizinha(cidade_fronteira, i);
        float dist_vizinha = retorna_dist_vizinha(cidade_fronteira, i);

        for(int j = 0; j < r->num_visitadas; j++){ //VERIFICANDO SE A VIZINHA JA FOI VISITADA

            int tag_visitada = retorna_tag(vector_get(r->visistadas, j));

            if(tag_vizinha == tag_visitada){
                ja_visitou = 1;
                break;
            }
        }

        for(int k = 0; k < r->num_fronteira; k++){ // VERIFICANDO SE A VIZINHA JA ESTA NA FRONTEIRA

            int tag_fronteira = retorna_tag(heap_get(r->fronteira_h, k));

            if(tag_vizinha == tag_fronteira){
                ta_na_fronteira = 1;
                posi_fronteira = k;
                break;
            }
        }

        if(ja_visitou == 0){ //se ele nao visitou a cidade, pode por na fronteira.

            data_type cidade_vizinha = vector_get(cidades, tag_vizinha);

            set_cidade_pai(cidade_vizinha, tag); //mando a cidade vizinha e de onde ela veio(pai).
            set_dist_pai(cidade_vizinha, dist_vizinha); // mando a cidade vizinha e a distancia dela do pai

            float dist = retorna_dist_total(cidade_fronteira);
            set_dist_total(cidade_vizinha, dist); // botando a distancia daquela cidade em relação a origem

            if(ta_na_fronteira == 1){ //caso tenha a mesma cidade na fronteira
                if(compara_dist_total(heap_get(r->fronteira_h, posi_fronteira), cidade_vizinha) < 0){
                    heap_remove(r->fronteira_h, posi_fronteira); //tira a cidade que tem um preço maior, depois bota a de preço menor
                }
                else if(compara_dist_total(heap_get(r->fronteira_h, posi_fronteira), cidade_vizinha) > 0){
                    //a cidade na fronteira ja tem um preço menor, entao não adiciona essa cidade nova na fronteira.
                    continue;
                }
            }

            heap_push(r->fronteira_h, cidade_vizinha); //botando cidade na fronteira.
            r->num_fronteira++;
        }

    }

    return tag;
}

//implementado, porem é necessário casos de testes para verificar se está funcionando direito
int rota_Astar(Rota *r, Vector *cidades){

    if(r->num_fronteira == 0){
        return -1;
    }

    data_type cidade_fronteira = heap_pop(r->fronteira_h);

    int tag = retorna_tag(cidade_fronteira);
    int num_vizinhas = retorna_num_vizinhas(cidade_fronteira);

    vector_push_back(r->visistadas, cidade_fronteira);
    r->num_fronteira--;
    r->num_visitadas++;

    for(int i = 0; i < num_vizinhas; i++){
        
        int ja_visitou = 0;
        int ta_na_fronteira = 0;
        int posi_fronteira = 0;

        int tag_vizinha = retorna_tag_vizinha(cidade_fronteira, i);
        float dist_vizinha = retorna_dist_vizinha(cidade_fronteira, i);

        for(int j = 0; j < r->num_visitadas; j++){ //VERIFICANDO SE A VIZINHA JA FOI VISITADA

            int tag_visitada = retorna_tag(vector_get(r->visistadas, j));

            if(tag_vizinha == tag_visitada){
                ja_visitou = 1;
                break;
            }
        }

        for(int k = 0; k < r->num_fronteira; k++){ // VERIFICANDO SE A VIZINHA JA ESTA NA FRONTEIRA

            int tag_fronteira = retorna_tag(heap_get(r->fronteira_h, k));

            if(tag_vizinha == tag_fronteira){
                ta_na_fronteira = 1;
                posi_fronteira = k;
                break;
            }
        }

        if(ja_visitou == 0){ //se ele nao visitou a cidade, pode por na fronteira.

            data_type cidade_vizinha = vector_get(cidades, tag_vizinha);

            set_cidade_pai(cidade_vizinha, tag); //mando a cidade vizinha e de onde ela veio(pai).
            set_dist_pai(cidade_vizinha, dist_vizinha); // mando a cidade vizinha e a distancia dela do pai

            float dist = retorna_dist_total(cidade_fronteira);
            set_dist_total(cidade_vizinha, dist); // botando a distancia daquela cidade em relação a origem

            if(ta_na_fronteira == 1){ //caso tenha a mesma cidade na fronteira
                if(compara_dist_total(heap_get(r->fronteira_h, posi_fronteira), cidade_vizinha) < 0){
                    heap_remove(r->fronteira_h, posi_fronteira); //tira a cidade que tem um preço maior, depois bota a de preço menor
                }
                else if(compara_dist_total(heap_get(r->fronteira_h, posi_fronteira), cidade_vizinha) > 0){
                    //a cidade na fronteira ja tem um preço menor, entao não adiciona essa cidade nova na fronteira.
                    continue;
                }
            }

            heap_push(r->fronteira_h, cidade_vizinha); //botando cidade na fronteira.
            r->num_fronteira++;
        }

    }

    return tag;
}


void retorna_rota(Rota *r, int cidadeInicio, Vector *cidades){

    Vector *caminho = vector_construct();

    float distancia = 0;
    int i = retorna_tag(vector_get(r->visistadas, r->num_visitadas - 1));

    while(1){

        data_type cidade_atual = vector_get(cidades, i);

        distancia += retorna_dist_pai(cidade_atual);
        i = retorna_cidade_pai(cidade_atual);
        vector_push_back(caminho, cidade_atual);

        if(i == cidadeInicio){
        
            cidade_atual = vector_get(cidades, i);
            vector_push_back(caminho, cidade_atual);
            break;
        }
    }

    for(int j = vector_size(caminho) - 1; j >= 0; j--){

        data_type cidade = vector_get(caminho, j);

        printa_cidade(cidade);
    }
    printf("\n%.2fKm\n", distancia);

    printf("cidades visitadas: %d\n", r->num_visitadas);

    vector_destroy(caminho);
}
