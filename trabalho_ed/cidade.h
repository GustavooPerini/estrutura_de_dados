#ifndef _CIDADE_H_
#define _CIDADE_H_

#include "vector.h"

typedef struct cidade Cidade;

Cidade *cidade_construct();

void cidade_destroy(void *data);

void printa_cidade(void *data); //teste

int retorna_tag(void *data);

int retorna_num_vizinhas(void *data);

int retorna_tag_vizinha(void *data, int position);

float retorna_dist_vizinha(void *data, int position);

void set_cidade_pai(void *data, int tag);

void set_dist_pai(void *data, float dist);

int retorna_cidade_pai(void *data);

float retorna_dist_pai(void *data);

//pra baixo é teste
void set_dist_total(void *data, float dist);

float retorna_dist_total(void *data);

int compara_dist_total(const void *a, const void *b);

void calcula_custo_final(const void *a, const void *b);

#endif