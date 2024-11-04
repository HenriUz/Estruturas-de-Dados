/*
Arvore.c

Descrição: implementação das funções da árvore.
*/

/* --- Includes. --- */

#include "Arvore.h"
#include <stdlib.h>
#include <stdio.h>

/* --- Estruturas. --- */

struct arvore {
    no *raiz;
    int numElementos;
};

struct no {
    int chave;
    no *pai, *filhoE, *filhoD;
};

/* --- Funções. --- */

arvore *criaArvore() {
    arvore *arv = (arvore*)malloc(sizeof(arvore));
    if(!arv) {
        return NULL;
    }
    /* Setando os valores da árvore. */
    arv->raiz = NULL;
    arv->numElementos = 0;
    return arv;
}

no *getRaiz(const arvore *arv) {
    return arv->raiz;
}

int getNumElementos(const arvore *arv) {
    return arv->numElementos;
}

no *criaNo(const int chave) {
    no *folha = (no*)malloc(sizeof(no));
    if(!folha) {
        return NULL;
    }
    /* Setando os valores do nó. */
    folha->chave = chave;
    folha->pai = folha->filhoD = folha->filhoE = NULL;
    return folha;
}

int insere(arvore *arv, const int chave) {
    no *folha = criaNo(chave), *pai, *atual; //Atual será o ponteiro que irá encontrar a folha onde iremos inserir, e pai será o ponteiro que guardará o pai do atual.
    if(!folha) {
        return 0;
    }
    /* Inserindo. */
    if(!arv->numElementos) {
        /* Inserindo a raiz */
        arv->raiz = folha;
    }else {
        /* Buscando posição para inserir. */
        atual = arv->raiz;
        while(atual) {
            pai = atual;
            if(chave < atual->chave) {
                atual = atual->filhoE;
            }else {
                atual = atual->filhoD;
            }
        }
        /* Vinculando folha com o pai. */
        if(chave < pai->chave) {
            pai->filhoE = folha;
        }else {
            pai->filhoD = folha;
        }
        folha->pai = pai;
    }
    /* Atualizando a árvore. */
    arv->numElementos++;
    return 1;
}

int deleta(arvore *arv, const int chave) {
    no *atual = arv->raiz, *aux;
    if(!arv->numElementos) {
        //Árvore vazia.
        return 0;
    }
    /* Buscando o elemento. */
    while(atual && atual->chave != chave) {
        if(chave < atual->chave) {
            atual = atual->filhoE;
        }else {
            atual = atual->filhoD;
        }
    }
    /* Removendo. */
    if(atual) {
        //Elemento encontrado.
        if(!atual->filhoE && !atual->filhoD) {
            //Elemento é folha, apenas desvincula do pai.
            if(atual == arv->raiz) {
                arv->raiz = NULL;
            }else {
                if(atual->pai->filhoE == atual) {
                    atual->pai->filhoE = NULL;
                }else{
                    atual->pai->filhoD = NULL;
                }
            }
        }else if(atual->filhoE && atual->filhoD) {
            //Elemento tem os dois filhos. Aux irá guardar o elemento atual, e o atual irá buscar o predecessor.
            aux = atual;
            /* Buscando predecessor. */
            atual = atual->filhoE;
            while(atual->filhoD) {
                atual = atual->filhoD;
            }
            /* Realizando cópia. */
            aux->chave = atual->chave;
            /* Removendo o nó predecessor. */
            if(atual->pai->filhoE == atual) {
                atual->pai->filhoE = atual->filhoE;
            }else {
                atual->pai->filhoD = atual->filhoE;
            }
            if(atual->filhoE) {
                atual->filhoE->pai = atual->pai;
            }
        }else if(atual->filhoE) {
            //Elemento possui apenas o filho esquerdo.
            if(atual == arv->raiz) { //Necessário quando não há um sentinela implementado.
                arv->raiz = atual->filhoE;
            }else {
                if(atual->pai->filhoE == atual) {
                    atual->pai->filhoE = atual->filhoE;
                }else {
                    atual->pai->filhoD = atual->filhoE;
                }
            }
            atual->filhoE->pai = atual->pai;
        }else {
            //Elemento possui apenas o filho direito.
            if(atual == arv->raiz) { //Necessário quando não há um sentinela implementado.
                arv->raiz = atual->filhoD;
            }else {
                if(atual->pai->filhoE == atual) {
                    atual->pai->filhoE = atual->filhoD;
                }else {
                    atual->pai->filhoD = atual->filhoD;
                }
            }
            atual->filhoD->pai = atual->pai;
        }
        /* Liberando o nó e atualizando a árvore. */
        free(atual);
        atual = NULL;
        arv->numElementos--;
        return 1;
    }
    //Elemento não encontrado.
    return -1;
}

void esvaziaArvore(arvore *arv) {
    while(arv->raiz) {
        deleta(arv, arv->raiz->chave);
    }
}

int busca(const arvore *arv, const int chave) {
    no *raiz = arv->raiz;
    int encontrou = 0;
    /* Buscando o elemento. */
    while(raiz) {
        if(chave == raiz->chave) {
            //Elemento encontrado, anulando raiz para sair do loop.
            encontrou = 1;
            raiz = NULL;
        }else if(chave < raiz->chave) {
            raiz = raiz->filhoE;
        }else {
            raiz = raiz->filhoD;
        }
    }
    return encontrou;
}

void preOrdem(const no *raiz) {
    if(raiz) {
        printf("\n%d", raiz->chave);
        if(raiz->pai) {
            printf(" - %d", raiz->pai->chave);
        }
        preOrdem(raiz->filhoE);
        preOrdem(raiz->filhoD);
    }
}

void emOrdem(const no *raiz) {
    if(raiz) {
        emOrdem(raiz->filhoE);
        printf("%d ", raiz->chave);
        emOrdem(raiz->filhoD);
    }
}

void posOrdem(const no *raiz) {
    if(raiz) {
        posOrdem(raiz->filhoE);
        posOrdem(raiz->filhoD);
        printf("\n%d", raiz->chave);
        if(raiz->pai) {
            printf(" - %d", raiz->pai->chave);
        }
    }
}
