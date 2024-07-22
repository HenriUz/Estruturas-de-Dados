#include "Arvore.h"
#include <stdlib.h>
#include <stdio.h>

/*** -- Estruturas. -- ***/

struct arvore {
    no *raiz;
    int numElementos;
};

struct no {
    int chave;
    no *pai, *filhoE, *filhoD;
};

/*** -- Funções. -- ***/

arvore *criaArvore() {
    /*** -- Criando a árvore. -- ***/
    arvore *arv = (arvore*)malloc(sizeof(arvore));
    if(!arv) {
        return NULL;
    }
    /*** -- Setando os valores. -- ***/
    arv->raiz = NULL;
    arv->numElementos = 0;
    return arv;
}

no *getRaiz(arvore *arv) {
    return arv->raiz;
}

int getNumElementos(arvore *arv) {
    return arv->numElementos;
}

no *criaNo(int chave) {
    /*** -- Criando o nó. -- ***/
    no *folha = (no*)malloc(sizeof(no));
    if(!folha) {
        return NULL;
    }
    /*** -- Setando os valores. -- ***/
    folha->chave = chave;
    folha->pai = folha->filhoD = folha->filhoE = NULL;
    return folha;
}

int insere(arvore *arv, int chave) {
    /*** -- Criando a folha e ponteiros auxiliares. -- ***/
    no *folha = criaNo(chave), *pai, *atual;
    if(!folha) {
        return 0;
    }
    /*** -- Inserindo. -- ***/
    if(!arv->numElementos) {
        //Árvore vazia, inserindo a folha na raiz.
        arv->raiz = folha;
    }else {
        //Árvore com elementos, percorrendo a árvore. Atual será o ponteiro que irá encontrar a folha onde iremos inserir, e pai será o ponteiro que guardará o pai.
        atual = arv->raiz;
        //Enquanto atual existir, percorra até achar a folha.
        while(atual) {
            pai = atual;
            if(chave < atual->chave) {
                atual = atual->filhoE;
            }else {
                atual = atual->filhoD;
            }
        }
        //Verificando em qual filho a folha irá entrar no pai.
        if(chave < pai->chave) {
            pai->filhoE = folha;
        }else {
            pai->filhoD = folha;
        }
        //Vinculando com o pai.
        folha->pai = pai;
    }
    //Aumentando a quantidade de elementos da árvore.
    arv->numElementos++;
    return 1;
}

int deleta(arvore *arv, int chave) {
    no *atual = arv->raiz, *aux;
    /*** -- Verificando se a árvore está vazia. -- ***/
    if(!arv->numElementos) {
        //Árvore vazia.
        return 0;
    }
    /*** -- Buscando o elemento. -- ***/
    while(atual && atual->chave != chave) {
        if(chave < atual->chave) {
            atual = atual->filhoE;
        }else {
            atual = atual->filhoD;
        }
    }
    /*** -- Verificando se o elemento foi encontrado. -- ***/
    if(atual) {
        //Elemento encontrado, verificando seus filhos.
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
            atual = atual->filhoE;
            while(atual->filhoD) {
                atual = atual->filhoD;
            }
            //Realizando a cópia por valor.
            aux->chave = atual->chave;
            //Removendo o nó predecessor.
            if(atual->pai->filhoE == atual) {
                atual->pai->filhoE = atual->filhoE;
            }else {
                atual->pai->filhoD = atual->filhoE;
            }
            if(atual->filhoE) {
                atual->filhoE->pai = atual->pai;
            }
        }else if(atual->filhoE) {
            //Elemento possui apenas o filho esquerdo, então vincula o pai com o filho, e vice-versa.
            if(atual == arv->raiz) {
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
            //Elemento possui apenas o filho direito, então vincula o pai com o filho, e vice-versa.
            if(atual == arv->raiz) {
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

int busca(arvore *arv, int chave) {
    no *raiz = arv->raiz;
    int encontrou = 0;
    /*** -- Procurando o elemento. -- ***/
    while(raiz) {
        if(chave == raiz->chave) {
            //Elemento encontrado, anulando raiz para sair do loop.
            encontrou = 1;
            raiz = NULL;
        }else if(chave < raiz->chave) {
            //Elemento só pode estar na sub-árvore esquerda.
            raiz = raiz->filhoE;
        }else {
            //Elemento só pode estar na sub-árvore direita.
            raiz = raiz->filhoD;
        }
    }
    return encontrou;
}

void preOrdem(no *raiz) {
    if(raiz) {
        printf("\n%d", raiz->chave);
        if(raiz->pai) {
            printf(" - %d", raiz->pai->chave);
        }
        preOrdem(raiz->filhoE);
        preOrdem(raiz->filhoD);
    }
}

void emOrdem(no *raiz) {
    if(raiz) {
        emOrdem(raiz->filhoE);
        printf("%d ", raiz->chave);
        emOrdem(raiz->filhoD);
    }
}

void posOrdem(no *raiz) {
    if(raiz) {
        posOrdem(raiz->filhoE);
        posOrdem(raiz->filhoD);
        printf("\n%d", raiz->chave);
        if(raiz->pai) {
            printf(" - %d", raiz->pai->chave);
        }
    }
}
