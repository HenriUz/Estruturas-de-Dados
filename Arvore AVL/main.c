#include <stdio.h>
#include <stdlib.h>
#include "Arvore/ArvoreAvl.h"

int main(void) {
    arvore *arv;
    int resp, indice, retornoDeleta;
    char caractere;
    /*** -- Criando a árvore. -- ***/
    arv = criaArvore();
    if(!arv) {
        return 1;
    }
    /*** -- Menu. -- ***/
    printf_s("\nMENU.\n1 - Inserir.\n2 - Remover.\n3 - Buscar.\n4 - Imprimir.\n5 - Sair\nSua resposta: ");
    scanf_s("%d", &resp);
    while(resp != 5) {
        switch (resp) {
            case 1:
                //Inserção.
                printf_s("\nDigite o índice que será inserido: ");
                scanf_s("%d", &indice);
                printf_s("\nDigite o caractere que será inserido: ");
                scanf_s(" %c", &caractere, (unsigned)sizeof(caractere));
                if(!insere(arv, indice, caractere)) {
                    printf_s("\nErro na inserção.\n");
                }else {
                    printf_s("\nElemento inserido com sucesso.\n");
                }
                break;
            case 2:
                //Remoção.
                printf_s("\nDigite o índice que será removido: ");
                scanf_s("%d", &indice);
                retornoDeleta = deleta(arv, indice);
                if(retornoDeleta == 0) {
                    printf_s("\nElemento não encontrado.\n");
                }else if(retornoDeleta == -1) {
                    printf_s("\nÁrvore vazia.\n");
                }else {
                    printf_s("\nElemento removido com sucesso.\n");
                }
                break;
            case 3:
                printf_s("\nDigite o índice que será buscado: ");
                scanf_s("%d", &indice);
                if(!busca(arv, indice)) {
                    printf_s("\nElemento não encontrado.\n");
                }else {
                    printf_s("\nElemento encontrado.\n");
                }
                break;
            case 4:
                //Impreção.
                printf_s("\nQuantidade de elementos na árvore: %d", getNumElementos(arv));
                preOrdem(getRaiz(arv));
                printf_s("\n");
                break;
            default:
                //Nada.
                break;
        }
        printf_s("\nMENU.\n1 - Inserir.\n2 - Remover.\n3 - Buscar.\n4 - Imprimir.\n5 - Sair\nSua resposta: ");
        scanf_s("%d", &resp);
    }
    esvaziaArvore(arv);
    free(arv);
    arv = NULL;
    return 0;
}
