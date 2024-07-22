#ifndef _BUSCA_H_
#define _BUSCA_H_

#include "vector.h"
#include "deque.h"
#include "heap.h"
#include "cidade.h"

void busca_DFS(Vector *cidades, int cidadeInicio, int cidadeAlvo);

void busca_BFS(Vector *cidades, int cidadeInicio, int cidadeAlvo);

void busca_UCS(Vector *cidades, int cidadeInicio, int cidadeAlvo);

void busca_Astar(Vector *cidades, int cidadeInicio, int cidadeAlvo);

void printa_rota(Vector *visitados, Vector *cidades);

#endif