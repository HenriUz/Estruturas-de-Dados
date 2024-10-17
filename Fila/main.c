/*
main.c

Descrição: programa responsável por lidar com os inputs do usuário e por lidar com as funções da fila.
*/

/* --- Includes. --- */

#include "Fila/Fila.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Funções. --- */

int main(void) {
    fila *f = criaFila();
    int resp; //Resposta do usuário.
    int elemento; //Elemento que será inserido, ou devolvido pela função.
    /* Menu. */
    printf("\nMenu:\n1. Inserir.\n2. Remover.\n3. Sair.\nResposta: ");
    scanf("%d", &resp);
    /* Loop. */
    while(resp != 3) {
        switch(resp) {
            case 1:
                /* Inserindo. */
                printf("\nDigite o elemento que você deseja enfileirar: ");
                scanf("%d", &elemento);
                if(!insereFila(f, elemento)) {
                    printf("\nErro ao inserir na fila.");
                }else {
                    printf("\nElemento %d inserido com sucesso.", elemento);
                }
                break;
            case 2:
                /* Removendo. */
                elemento = removeFila(f);
                if(!elemento && filaVazia(f)) {
                    printf("\nNenhum elemento removido, fila está vazia.");
                }else {
                    printf("\nO elemento %d foi removido com sucesso.", elemento);
                }
                break;
            default:
                /* Padrão. */
                printf("\nResposta invalida!");
        }
        /* Menu. */
        printf("\nMenu:\n1. Inserir.\n2. Remover.\n3. Sair.\nResposta: ");
        scanf("%d", &resp);
    }
    /* Liberando memória. */
    free(f);
    return 0;
}
