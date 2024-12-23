/*
main.c

Descrição: programa responsável por lidar com os inputs do usuário e por gerenciar as funções da árvore.
*/

/* --- Includes. --- */

#include "Arvore/Arvore.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Funções. --- */

int main(void) {
    int resp, resultadoRem;
    arvore *arv = criaArvore();
    if(!arv) {
        printf("\nErro ao criar a árvore.");
        return 1;
    }
    /* Iniciando interface. */
    printf("\nMENU:\n1 - Inserir.\n2 - Remover.\n3 - Buscar.\n4 - Imprimir.\n5 - Sair.\nSua resposta: ");
    scanf("%d", &resp);
    while(resp != 5) {
        switch (resp) {
            case 1:
                /* Inserindo um elemento. */
                printf("\nQual elemento você deseja inserir: ");
                scanf("%d", &resp);
                if(!insere(arv, resp)) {
                    printf("\nErro ao inserir.");
                }
                break;
            case 2:
                /* Removendo um elemento. */
                printf("\nQual elemento você deseja remover: ");
                scanf("%d", &resp);
                resultadoRem = deleta(arv, resp);
                if(resultadoRem == 1) {
                    printf("\nElemento removido com sucesso.\n");
                }else if(resultadoRem == 0) {
                    printf("\nÁrvore vazia.\n");
                }else {
                    printf("\nElemento não encontrado.\n");
                }
                break;
            case 3:
                /* Buscando um elemento. */
                printf("\nQual elemento você deseja buscar: ");
                scanf("%d", &resp);
                if(busca(arv, resp)) {
                    printf("\nElemento encontrado.\n");
                }else {
                    printf("\nElemento não encontrado.\n");
                }
                break;
            case 4:
                /* Imprimindo a árvore. */
                printf("\n1 - Pré Ordem.\n2 - Em Ordem.\n3 - Pós Ordem.\nSua resposta: ");
                scanf("%d", &resp);
                printf("\nNúmero de elementos: %d", getNumElementos(arv));
                if(resp == 1) {
                    preOrdem(getRaiz(arv));
                }else if(resp == 2) {
                    printf("\nElementos: ");
                    emOrdem(getRaiz(arv));
                }else {
                    posOrdem(getRaiz(arv));
                }
                printf("\n");
                break;
            default:
                break;
        }
        printf("\nMENU:\n1 - Inserir.\n2 - Remover.\n3 - Buscar.\n4 - Imprimir.\n5 - Sair.\nSua resposta: ");
        scanf("%d", &resp);
    }
    /* Esvaziando a árvore. */
    esvaziaArvore(arv);
    free(arv);
    arv = NULL;
    return 0;
}
