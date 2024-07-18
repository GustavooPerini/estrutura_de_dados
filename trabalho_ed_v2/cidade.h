#ifndef _CIDADE_H_
#define _CIDADE_H_

typedef struct cidade Cidade;


Cidade *cidade_construct();

void printa_cidade(void *data);

void cidade_destroy(void *data);

#endif