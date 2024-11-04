/*
main.c

Descrição: programa responsável por tratar as entradas do usuário, e com base nelas chamar a função correspondente da árvore rubro-negra.
*/

/* --- Includes. --- */

#include "Arvore/ArvoreRN.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Funções. --- */

int main(void) {
    arvore *arv;
    int resp, retorno, chave; //Resposta para o menu, retorno das funções da árvore, chave que será inserida, removida, ou pesquisada.
    arv = criaArvore();
    if(!arv) {
        return 1;
    }
    /* Iniciando interface. */
    printf("\nMENU.\n1 - Insere.\n2 - Remove.\n3 - Busca.\n4 - Imprime.\n5 - Sair.\nSua Resposta: ");
    scanf("%d", &resp);
    while(resp != 5) {
        switch(resp) {
            case 1:
                /* Inserindo chave na árvore. */
                printf("\nDigite o elemento que será inserido: ");
                scanf("%d", &chave);
                if(!insere(arv, chave)) {
                    printf("\nErro na inserção.\n");
                }else {
                    printf("\nSucesso na inserção.\n");
                }
                break;
            case 2:
                /* Removendo chave da árvore. */
                printf("\nDigite o elemento que será removido: ");
                scanf("%d", &chave);
                retorno = deleta(arv, chave);
                if(retorno == 1) {
                    printf("\nSucesso na remoção.\n");
                }else if(retorno == 0) {
                    printf("\nÁrvore vazia.\n");
                }else {
                    printf("\nElemento não encontrado.\n");
                }
                break;
            case 3:
                /* Buscando chave na árvore. */
                printf("\nDigite o elemento que deseja procurar: ");
                scanf("%d", &chave);
                retorno = buscaElemento(arv, chave);
                if(retorno != -1) {
                    printf("\nElemento encontrado, cor: %d.\n", retorno);
                }else {
                    printf("\nElemento não encontrado.\n");
                }
            case 4:
                /* Imprimindo a árvore em pré-ordem. */
                printf("\nNúmero de elementos na árvore: %d\n", getNumElementos(arv));
                preOrdem(getRaiz(arv));
                printf("\n");
                break;
            default:
        }
        printf("\nMENU.\n1 - Insere.\n2 - Remove.\n3 - Busca.\n4 - Imprime.\n5 - Sair.\nSua Resposta: ");
        scanf("%d", &resp);
    }
    /* Liberando memória. */
    free(arv);
    arv = NULL;
    return 0;
}
