/*
ES.c

Descrição: implementação das funções responsáveis por criar um dataset.
*/

/* --- Includes. --- */

#include "ES.h"
#include <stdlib.h>

/* --- Estruturas --- */

struct linha {
    char nome[6];
    int dia, mes, ano;
    long long int cpf;
};

/* --- Funções --- */

void geraLinha(linha *line, const int seed) {
    /* Setando a seed. */
    srand(seed);
    /* Aleatorizando a data de nascimento. */
    line->dia = (rand() % 31) + 1;
    line->mes = (rand() % 12) + 1;
    line->ano = (rand() % 75) + 1950;
    /* Aleatorizando o nome, usando a tabela ascII. */
    for(int i = 0; i < 5; i++) {
        line->nome[i] = (char)((rand() % 26) + 97);
    }
    /* Aleatorizando o cpf. */
    line->cpf = (rand() % 1000000000000) + 10000000000;
}

int criaDataset(FILE *arq, const int tam) {
    linha line;
    /* Colocando o byte nulo na última posição. */
    line.nome[5] = '\0';
    /* Gerando o arquivo. */
    for(int i = 0; i < tam; i++) {
        geraLinha(&line, i);
        fprintf(arq, "%05d %s %02d/%02d/%04d %lld\n", i, line.nome, line.dia, line.mes, line.ano, line.cpf);
    }
    return 1;
}
