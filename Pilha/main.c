/*
main.c

Descrição: o objetivo desse programa é mostrar como usar a pilha para converter números decimais para binários.
*/

/* --- Includes. --- */

#include <stdio.h>
#include <stdlib.h>
#include "Pilha/Pilha.h"

/* --- Função. --- */

int main(void) {
    Pilha *p = criaPilha();
    int valor; //Valor que será convertido para binário.
    if(!p) {
        printf("\nErro na criação da Pilha");
        return 1;
    }
    /* Recebendo o valor que será convertido. */
    printf("\nDigite o valor, inteiro positivo, que você deseja converter para binário: ");
    scanf("%d", &valor);
    if(valor <= 0) {
        printf("\nValor invalido.");
        return 1;
    }
    /* Empilhando os restos gerados na conversão. */
    while(valor) {
        push(p, valor%2);
        valor = valor/2;
    }
    /* Desempilhando e informando ao usuário. */
    printf("\nValor em binário: ");
    while(getQuantidade(p)) {
        printf("%d", pop(p));
    }
    /* Liberando memória. */
    free(p);
    p = NULL;
    return 0;
}
