#ifndef _ROTA_H_
#define _ROTA_H_

#include "vector.h"
#include "array.h"
#include "heap.h"
#include "cidade.h"

typedef struct rota Rota;

Rota *rota_construct(int cidade_inicio, Vector *cidades);

void rota_destroy(Rota *r);

void printa_fronteira(Rota *r);

void printa_visitados(Rota *r);

int realiza_rota(Rota *r, char *metodo, Vector *cidades);

int rota_DFS(Rota *r, Vector *cidades);

int rota_BFS(Rota *r, Vector *cidades);

int rota_UCS(Rota *r, Vector *cidades);

int rota_Astar(Rota *r, Vector *cidades);

void retorna_rota(Rota *r, int cidadeInicio, Vector *cidades);

#endif