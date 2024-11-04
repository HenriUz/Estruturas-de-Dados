/*
main.c

Descrição: programa responsável por lidar com os inputs do usuário e por gerenciar as funções da árvore.
*/

/* --- Includes. --- */

#include "Arvore/ArvoreAvl.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Funções. --- */

int main(void) {
    arvore *arv;
    int resp, indice, retornoDeleta;
    char caractere;
    arv = criaArvore();
    if(!arv) {
        return 1;
    }
    /* Iniciando interface. */
    printf("\nMENU.\n1 - Inserir.\n2 - Remover.\n3 - Buscar.\n4 - Imprimir.\n5 - Sair\nSua resposta: ");
    scanf("%d", &resp);
    while(resp != 5) {
        switch (resp) {
            case 1:
                /* Inserindo elemento. */
                printf("\nDigite o índice que será inserido: ");
                scanf("%d", &indice);
                printf("\nDigite o caractere que será inserido: ");
                scanf(" %1c", &caractere);
                if(!insere(arv, indice, caractere)) {
                    printf("\nErro na inserção.\n");
                }else {
                    printf("\nElemento inserido com sucesso.\n");
                }
                break;
            case 2:
                /* Removendo elemento. */
                printf("\nDigite o índice que será removido: ");
                scanf("%d", &indice);
                retornoDeleta = deleta(arv, indice);
                if(retornoDeleta == 0) {
                    printf("\nElemento não encontrado.\n");
                }else if(retornoDeleta == -1) {
                    printf("\nÁrvore vazia.\n");
                }else {
                    printf("\nElemento removido com sucesso.\n");
                }
                break;
            case 3:
                /* Buscando elemento. */
                printf("\nDigite o índice que será buscado: ");
                scanf("%d", &indice);
                if(!busca(arv, indice)) {
                    printf("\nElemento não encontrado.\n");
                }else {
                    printf("\nElemento encontrado.\n");
                }
                break;
            case 4:
                /* Imprimindo árvore. */
                printf("\nQuantidade de elementos na árvore: %d", getNumElementos(arv));
                preOrdem(getRaiz(arv));
                printf("\n");
                break;
            default:
        }
        printf("\nMENU.\n1 - Inserir.\n2 - Remover.\n3 - Buscar.\n4 - Imprimir.\n5 - Sair\nSua resposta: ");
        scanf("%d", &resp);
    }
    /* Liberando memória. */
    esvaziaArvore(arv);
    free(arv);
    arv = NULL;
    return 0;
}
