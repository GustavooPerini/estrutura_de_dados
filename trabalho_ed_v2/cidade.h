#ifndef _CIDADE_H_
#define _CIDADE_H_

typedef struct cidade Cidade;


Cidade *cidade_construct();

void printa_cidade(void *data);

int get_tag(Cidade *cidade);

int get_num_vizinhos(Cidade *cidade);

int get_tag_vizinho(Cidade *cidade, int idx);

float get_distacia_vizinho(Cidade *cidade, int idx);

int get_tag_pai(Cidade *cidade);

float get_dist_pai(Cidade *cidade);

void set_distacia_pai(Cidade *cidade, float distPai);

void set_tag_pai(Cidade *cidade, int tagPai);

void set_tag(Cidade *cidade, int tag);

int compara_cidade_tag(const void *a, const void *b);

void cidade_destroy(void *data);

#endif