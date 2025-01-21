/*
Lista.c

Descrição: implementação das funções da lista simplesmente encadeada.
*/

/* --- Includes. --- */

#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Estruturas. --- */

struct elemento {
    int valor; //Valor armazenado pelo elemento.
    elemento *prox; //Próximo elemento na lista.
};

struct lista {
    elemento *com; //Começo da lista.
};

/* --- Funções. --- */

lista *criaLista() {
    lista *list = (lista *)malloc(sizeof(lista));
    if(!list) {
        return NULL;
    }
    /* Inicializando valor, e retornando. */
    list->com = NULL;
    return list;
}

int listaVazia(const lista *list) {
    return list->com == NULL;
}

elemento *getComeco(const lista *list) {
    return list->com;
}

elemento *criaElemento(const int valor) {
    elemento *element = (elemento *)malloc(sizeof(elemento));
    if(!element) {
        return NULL;
    }
    /* Inicializando valores, e retornando. */
    element->valor = valor;
    element->prox = NULL;
    return element;
}

int getValor(const elemento *element) {
    return element->valor;
}

int insereLista(lista *list, const int valor) {
    elemento *newElement = criaElemento(valor); //Elemento que será inserido.
    elemento *antecessor = NULL, *sucessor = list->com; //Antecessor e sucessor do elemento. A busca é feita a partir do sucessor.
    if(newElement) {
        /* Buscando posição do novo elemento. */
        while(sucessor && sucessor->valor < valor) {
            antecessor = sucessor;
            sucessor = sucessor->prox;
        }
        /* Inserindo. */
        newElement->prox = sucessor;
        if(!antecessor) {
            //Lista vazia ou elemento é menor do que o no início (antecessor não teve valor alterado, então nem entrou no loop).
            list->com = newElement;
        }else {
            antecessor->prox = newElement;
        }
        return 1;
    }
    return 0;
}

int removeLista(lista *list, const int valor) {
    elemento *antecessor = NULL, *element = list->com; //Antecessor do elemento, e elemento que será removido.
    if(!listaVazia(list)) {
        /* Buscando elemento. */
        while(element && element->valor != valor) {
            antecessor = element;
            element = element->prox;
        }
        /* Removendo elemento. */
        if(element) {
            if(!antecessor) {
                list->com = element->prox;
            }else {
                antecessor->prox = element->prox;
            }
            /* Liberando elemento. */
            free(element);
            element = NULL;
            return 1;
        }
        return -1; //Elemento não encontrado.
    }
    return 0;
}

const elemento *buscaLista(const lista *list, const int valor) {
    const elemento *element = list->com;
    /* Buscando elemento. */
    while(element && element->valor != valor) {
        element = element->prox;
    }
    /* Retornando. */
    return element;
}

void imprimeLista(const lista *list) {
    const elemento *element = list->com; //Elementos da lista.
    /* Imprimindo. */
    if(!listaVazia(list)) {
        printf("\nLista: ");
        while(element) {
            printf("%d ", element->valor);
            element = element->prox;
        }
    }else {
        printf("\nLista vazia");
    }
}

void destroiLista(lista *list) {
    /* Removendo elemetos. */
    while(!listaVazia(list)) {
        removeLista(list, list->com->valor);
    }
    free(list);
    list = NULL;
}