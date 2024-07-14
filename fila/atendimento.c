#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h"

struct Atendimento
{
    char nome[50];
    char cpf[12];
};

Atendimento *atendimento_constructor(char *nome, char *cpf)
{
    Atendimento *atendimento = (Atendimento *)malloc(sizeof(Atendimento));
    if (!atendimento)
        return NULL;

    strcpy(atendimento->nome, nome);
    strcpy(atendimento->cpf, cpf);

    return atendimento;
}

char *atendimento_get_nome(Atendimento *atendimento)
{
    return atendimento->nome;
}

char *atendimento_get_cpf(Atendimento *atendimento)
{
    return atendimento->cpf;
}

void atendimento_destroy(Atendimento *atendimento)
{
    if (atendimento)
        free(atendimento);
}
