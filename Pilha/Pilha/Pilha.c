/*
Pilha.c

Descrição: implementação das funções e estruturas da pilha.
*/

/* --- Includes. --- */

#include <stdlib.h>
#include "Pilha.h"

/* --- Estruturas. --- */

struct Pilha{
    Elemento *topo; //Elemento que está no topo da pilha.
    int erro; //Será setado para 1 caso a pilha esteja vazia na operação de pop.
};

struct Elemento {
    int valor; //Valor armazenado.
    Elemento *prox; //Ponteiro para o elemento "abaixo".
};

/* --- Funções. --- */

Pilha *criaPilha() {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if(!p) {
        return NULL;
    }
    /* Inicializando valores. */
    p->topo = NULL;
    p->erro = 0;
    return p;
}

int getErro(Pilha *p) {
    return p->erro;
}

int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}

int push(Pilha *p, int valor) {
    Elemento *top = (Elemento *)malloc(sizeof(Elemento));
    if(!top) {
        return 0;
    }
    /* Inicializando Elemento. */
    top->valor = valor;
    top->prox = p->topo;
    /* Alterando valores da pilha. */
    p->topo = top;
    p->erro = 0;
    return 1;
}

int pop(Pilha *p) {
    int valor; //Valor que será retornado.
    Elemento *top; //Topo da pilha que será liberado.
    if(pilhaVazia(p)) {
        /* Pilha vazia, setando variável de erro e retornando. */
        p->erro = 1;
        return 0;
    }
    /* Setando as variáveis. */
    valor = p->topo->valor;
    top = p->topo;
    /* Modificando a pilha. */
    p->topo = p->topo->prox;
    p->erro = 0;
    /* Liberando o retornando. */
    free(top);
    top = NULL;
    return valor;
}
