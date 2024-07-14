#ifndef _ATENDIMENTO_H_
#define _ATENDIMENTO_H_

typedef struct Atendimento Atendimento;

// Função para criar um Atendimento
Atendimento *atendimento_constructor(char *nome, char *cpf);

// Funções para acessar os campos do Atendimento
char *atendimento_get_nome(Atendimento *atendimento);
char *atendimento_get_cpf(Atendimento *atendimento);

// Função para destruir um Atendimento
void atendimento_destroy(Atendimento *atendimento);

#endif
