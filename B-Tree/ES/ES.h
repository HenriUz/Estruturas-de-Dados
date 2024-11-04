/*
ES.h

Descrição: definição das funções responsáveis por criar um dataset.
*/

/* --- Includes. --- */

#include <stdio.h>

/* --- Estruturas --- */

typedef struct linha linha;

/* --- Funções --- */

/*
Descrição: função responsável por preencher os dados da estrutura linha com valores aleatórios.
Entrada: ponteiro para a estrutura, inteiro para a semente do srand.
Saída: nada.
*/
void geraLinha(linha *line, int seed);

/*
Descrição: função responsável por escrever no arquivo a quantidade de informações.
Entrada: ponteiro para um arquivo, inteiro do número de linhas.
Saída: 1 - sucesso, 0 - erro.
*/
int criaDataset(FILE *arq, int tam);
