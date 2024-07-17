#ifndef ES_H
#define ES_H

#include <stdio.h>

/*** -- Estruturas -- ***/

typedef struct linha linha;

/*** -- Funções -- ***/

/*
Descrição: Função que irá preencher os dados da estrutura linha com valores aleatórios.
Entrada: Ponteiro para a estrutura, inteiro para a semente do srand.
Saída: Nada.
*/
void geraLinha(linha *linha, int seed);

/*
Descrição: Função que irá escrever no arquivo a quantidade de informações.
Entrada: Ponteiro para um array de char, inteiro do número de linhas.
Saída: 1 - Sucesso, 0 - Erro.
*/
int criaDataset(FILE *arq, int tam);

#endif //ES_H
