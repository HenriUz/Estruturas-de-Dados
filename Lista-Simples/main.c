/*
main.c

Descrição: programa responsável por lidar com os inputs do usuário e com as saídas das funções da lista.
*/

/* --- Includes. --- */

#include "Lista/Lista.h"
#include <stdio.h>

/* --- Funções. --- */

int main(void) {
    int resposta; //Resposta do usuário.
    int valor, retorno; //Variáveis para as funções da lista.
    const elemento *element; //Elemento da busca.
    lista *list = NULL;
    /* Iniciando interface. */
    printf("\nMenu:\n1 - Criar lista.\n2 - Inserir.\n3 - Remover.\n4 - Buscar.\n5 - Imprimir.\n6 - Esvaziar lista.\n7 - Sair.\nSua resposta: ");
    scanf("%d", &resposta);
    while(resposta != 7) {
        switch(resposta) {
            case 1:
                /* Criando lista. */
                if(!list) {
                    list = criaLista();
                }else {
                    printf("\nLista já existe.");
                }
                break;
            case 2:
                /* Inserindo elemento. */
                if(list) {
                    printf("\nDigite o valor do novo elemento: ");
                    scanf("%d", &valor);
                    if(!insereLista(list, valor)) {
                        printf("\nErro ao inserir.");
                    }else {
                        printf("\nElemento inserido com sucesso.");
                    }
                }
                break;
            case 3:
                /* Removendo elemento. */
                if(list) {
                    printf("\nDigite o valor do elemento: ");
                    scanf("%d", &valor);
                    retorno = removeLista(list, valor);
                    if(retorno == -1) {
                        printf("\nElemento não encontrado.");
                    }else if(retorno == 0) {
                        printf("\nLista vazia.");
                    }else {
                        printf("\nElemento removido com sucesso.");
                    }
                }
                break;
            case 4:
                /* Buscando o elemento. */
                if(list) {
                    printf("\nDigite o valor do elemento: ");
                    scanf("%d", &valor);
                    element = buscaLista(list, valor);
                    if(element) {
                        printf("\nElemento encontrado, valor: %d", getValor(element));
                        element = NULL;
                    }else {
                        printf("\nElemento não encontrado.");
                    }
                }
                break;
            case 5:
                /* Imprimindo a lista. */
                if(list) {
                    imprimeLista(list);
                }
                break;
            case 6:
                /* Esvaziando a lista. */
                if(list) {
                    destroiLista(list);
                    list = NULL;
                }
                break;
            default:
                printf("\nOpção inválida.");
        }
        printf("\nMenu:\n1 - Criar lista.\n2 - Inserir.\n3 - Remover.\n4 - Buscar.\n5 - Imprimir.\n6 - Esvaziar lista.\n7 - Sair.\nSua resposta: ");
        scanf("%d", &resposta);
    }
    /* Liberando memória (caso ainda esteja alocado). */
    if(list) {
        destroiLista(list);
        list = NULL;
    }
    return 0;
}
