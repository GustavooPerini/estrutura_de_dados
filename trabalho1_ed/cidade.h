#ifndef _CIDADE_H_
#define _CIDADE_H_

typedef struct cidade Cidade;


Cidade *cidade_construct(FILE *fp);

//printa o nome de uma cidade
void printa_cidade(void *data);

//retorna a tag(numero que representa a cidade) de uma cidade
int get_tag(Cidade *cidade);

//retorna o numero de vizinhos que a cidade tem
int get_num_vizinhos(Cidade *cidade);

//retornar qual a tag da cidade vizinha
int get_tag_vizinho(Cidade *cidade, int idx);

//retorna a distancia da cidade vizinha
float get_distacia_vizinho(Cidade *cidade, int idx);

//retorna a tag da cidade pai da cidade mandada como argumento
int get_tag_pai(Cidade *cidade);

//retorna a distancia da cidade pai da cidade mandada como argumento
float get_dist_pai(Cidade *cidade);

//retorna o custo ate a origem da cidade mandada como argumento
float get_custo_origem(Cidade *cidade);

//retorna a coordenada X da cidade mandada como argumento
float get_coordX(Cidade *cidade);

//retorna a coordenada Y da cidade mandada como argumento
float get_coordY(Cidade *cidade);

//atribui a distancia da cidade pai na cidade mandada como argumento
void set_distacia_pai(Cidade *cidade, float distPai);

//atribui a tag da cidade pai na cidade mandada como argumento
void set_tag_pai(Cidade *cidade, int tagPai);

//atribui o valor da tag na cidade mandada como argumento
void set_tag(Cidade *cidade, int tag);

//atribui o valor do custo ate a origem na cidade mandada como argumento
void set_custo_origem(Cidade *cidade, float custo);

//compara as tags de duas cidades
int compara_cidade_tag(const void *a, const void *b);

//faz uma copia de uma cidade
Cidade *cidade_copia(Cidade *cidade);

//desaloca uma cidade
void cidade_destroy(void *data);

#endif