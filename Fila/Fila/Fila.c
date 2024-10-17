/*
Fila.c

Descrição: implementação das funções da fila.
*/

/* --- Includes. --- */

#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Estruturas. --- */

struct fila {
    elemento *inicio, *fim; //Elementos que estão no início e fim da fila.
};

struct elemento {
    int dado; //Dado armazenado na fila.
    elemento *prox; //Próximo elemento.
};

/* --- Funções. --- */

fila *criaFila() {
    fila *f = (fila *)malloc(sizeof(fila));
    if(!f) {
        return NULL;
    }
    /* Inicializando. */
    f->inicio = f->fim = NULL;
    return f;
}

int filaVazia(fila *f) {
    return f->inicio == NULL;
}

int insereFila(fila *f, int dado) {
    elemento *novo = (elemento *)malloc(sizeof(elemento));
    if(!novo) {
        return 0;
    }
    /* Inicializando elemento. */
    novo->dado = dado;
    novo->prox = NULL;
    /* Inserindo na fila. */
    if(filaVazia(f)) {
        f->inicio = f->fim = novo;
    }else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    return 1;
}

int removeFila(fila *f) {
    elemento *aux = f->inicio;
    int dado;
    /* Removendo. */
    if(!filaVazia(f)) {
        f->inicio = f->inicio->prox;
        dado = aux->dado;
        free(aux);
        aux = NULL;
        return dado;
    }
    return 0;
}
