/*
ArvoreAvl.c

Descrição: implementação das funções da árvore.
*/

/* --- Includes. --- */

#include "ArvoreAvl.h"
#include <stdio.h>
#include <stdlib.h>

/* --- Estruturas. --- */

struct chave {
    int indice;
    char caractere;
};

struct no {
    chave *key;
    int fb;
    no *pai, *filhoE, *filhoD;
};

struct arvore {
    no *sentinela;
    int numElementos;
};

/* --- Funções. --- */

no *criaNo(int indice, char caractere) {
    no *folha = (no*)malloc(sizeof(no));
    if(!folha) {
        return NULL;
    }
    folha->key = (chave*)malloc(sizeof(chave));
    if(!folha->key) {
        free(folha);
        return NULL;
    }
    /* Setando os valores. */
    folha->key->indice = indice;
    folha->key->caractere = caractere;
    folha->fb = 0;
    folha->pai = folha->filhoE = folha->filhoD = NULL;
    return folha;
}

arvore *criaArvore() {
    arvore *arv = (arvore*)malloc(sizeof(arvore));
    if(!arv) {
        return NULL;
    }
    /* Criando o sentinela. */
    arv->sentinela = criaNo(1000, 'S'); //Índice do sentinela é -1000 por padrão, e o caractere é a inicial do nome.
    if(!arv->sentinela) {
        free(arv);
        return NULL;
    }
    /* Setando o valor. */
    arv->numElementos = 0; //Número de elemento na árvore.
    return arv;
}

no *getRaiz(arvore *arv) {
    return arv->sentinela->filhoD;
}

int getNumElementos(arvore *arv) {
    return arv->numElementos;
}

int insere(arvore *arv, int indice, char caractere) {
    no *folha = criaNo(indice, caractere), *atual = arv->sentinela->filhoD, *aux = NULL; //Aux guardará o pai do atual, enquanto atual busca a posição nula para a inserção.
    if(!folha) {
        return 0;
    }
    /* Inserindo. */
    if(!atual) {
        /* Inserindo a raiz. */
        arv->sentinela->filhoD = folha;
        folha->pai = arv->sentinela;
    }else {
        /* Buscando posição para inserir. */
        while(atual) {
            aux = atual;
            if(folha->key->indice < atual->key->indice) {
                atual = atual->filhoE;
            }else {
                atual = atual->filhoD;
            }
        }
        /* Vinculando a folha com o pai. */
        if(folha->key->indice < aux->key->indice) {
            aux->filhoE = folha;
        }else {
            aux->filhoD = folha;
        }
        folha->pai = aux;
    }
    /* Verificando balanceamento. */
    atualizaFB_Insercao(arv, folha); //Atualizando os fb de todos os nós da subárvore onde a folha foi inserida.
    /* Atualizando a árvore. */
    arv->numElementos++;
    return 1;
}

int deleta(arvore *arv, int indice) {
    no *atual, *aux;
    /* Removendo. */
    if(arv->sentinela->filhoD) {
        /* Buscando o elemento. */
        atual = arv->sentinela->filhoD;
        while(atual && atual->key->indice != indice) {
            if(indice < atual->key->indice) {
                atual = atual->filhoE;
            }else {
                atual = atual->filhoD;
            }
        }
        if(atual) {
            //Elemento encontrado.
            if(atual->filhoE && atual->filhoD) {
                //Elemento possui os dois filhos. Remove por cópia de predecessor, atual busca o predecessor e o aux guarda o elemento atual.
                aux = atual;
                /* Buscando predecessor. */
                atual = atual->filhoE;
                while(atual->filhoD) {
                    atual = atual->filhoD;
                }
                /* Realizando a cópia. */
                aux->key->indice = atual->key->indice;
                aux->key->caractere = atual->key->caractere;
                /* Removendo predecessor. */
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = atual->filhoE;
                }else {
                    atual->pai->filhoD = atual->filhoE;
                }
                if(atual->filhoE) {
                    atual->filhoE->pai = atual->pai;
                }
            }else if(!atual->filhoE && !atual->filhoD) {
                //Elemento não possui nenhum filho.
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = NULL;
                }else {
                    atual->pai->filhoD = NULL;
                }
            }else if(atual->filhoE) {
                //Elemento possui somente o filho esquerdo.
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = atual->filhoE;
                }else {
                    atual->pai->filhoD = atual->filhoE;
                }
                atual->filhoE->pai = atual->pai;
            }else {
                //Elemento possui somente o filho direito.
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = atual->filhoD;
                }else {
                    atual->pai->filhoD = atual->filhoD;
                }
                atual->filhoD->pai = atual->pai;
            }
            /* Verificando balanceamento. */
            atualizaFB_Remocao(arv, atual->pai, atual->key->indice); //Atualizando FBs.
            /* Atualizando a árvore. */
            arv->numElementos--; //Atualizando quantidade.
            /* Liberando memória. */
            free(atual->key);
            free(atual);
            atual = NULL;
            return 1;
        }
        return 0;
    }
    return -1;
}

int busca(arvore *arv, int indice) {
    no *atual = arv->sentinela->filhoD;
    /* Buscando elemento. */
    while(atual && atual->key->indice != indice) {
        if(indice < atual->key->indice) {
            atual = atual->filhoE;
        }else {
            atual = atual->filhoD;
        }
    }
    /* Verificando se o elemento foi encontrado. */
    if(atual) {
        return 1;
    }
    return 0;
}

void preOrdem(no *raiz) {
    if(raiz) {
        printf_s("\n(%d, %c) - FB: %d", raiz->key->indice, raiz->key->caractere, raiz->fb);
        printf_s(" - Pai: (%d, %c)", raiz->pai->key->indice, raiz->pai->key->caractere);
        preOrdem(raiz->filhoE);
        preOrdem(raiz->filhoD);
    }
}

void esvaziaArvore(arvore *arv) {
    while(arv->sentinela->filhoD) {
        deleta(arv, arv->sentinela->filhoD->key->indice);
    }
    free(arv->sentinela);
    arv->sentinela = NULL;
}

void atualizaFB_Insercao(arvore *arv, no *folha) {
    no *atual = folha;
    /* Atualizando os FBs. */
    do {
        if(atual == atual->pai->filhoE && atual->pai != arv->sentinela) {
            atual->pai->fb--;
        }else if(atual->pai != arv->sentinela) {
            atual->pai->fb++;
        }
        atual = atual->pai;
    }while(atual->fb != 0 && atual->fb != 2 && atual->fb != -2 && atual != arv->sentinela);
    /* Verificando se houve um desbalanceamento. */
    if(atual->fb == 2 || atual->fb == -2) {
        balanceia(arv, atual);
    }
}

void atualizaFB_Remocao(arvore *arv, no *pai, int indice) {
    no *atual = pai;
    /* Atualizando os FBs. */
    if(atual != arv->sentinela) {
        //O elemento removido não foi a raiz.
        if(indice <= atual->key->indice) { //<= pois estamos usando o predecessor, logo na remoção, o pai pode passar a ter o mesmo valor da chave removida na esquerda.
            atual->fb++;
        }else {
            atual->fb--;
        }
        while(atual->pai != arv->sentinela && atual->fb != 1 && atual->fb != -1 && atual->fb != 2 && atual->fb != -2) {
            atual = atual->pai;
            if(indice <= atual->key->indice) {
                atual->fb++;
            }else {
                atual->fb--;
            }
        }
        /* Verificando se houve um desbalanceamento. */
        if(atual->fb == 2 || atual->fb == -2) {
            balanceia(arv, atual);
            if(atual->pai != arv->sentinela && atual->pai->fb == 0) {
                atualizaFB_Remocao(arv, atual->pai->pai, indice);
            }
        }
    }
}

void balanceia(arvore *arv, no *noDesbalanceado) {
    no *filho;
    /* Balanceando. */
    if(noDesbalanceado->fb == 2) {
        //Subárvore direita tem mais elementos.
        filho = noDesbalanceado->filhoD;
        if(filho->fb >= 0) {
            //Rotação simples.
            /* Corrigindo FBs. */
            if(filho->fb == 1) {
                noDesbalanceado->fb = filho->fb = 0;
            }else {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
            /* Rotacionando. **/
            rotacaoEsq(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->filhoD == noDesbalanceado) {
                arv->sentinela->filhoD = filho;
            }
        }else {
            //Rotação dupla.
            /* Corrigindo FBs. */
            if(filho->filhoE->fb == 0){
                noDesbalanceado->fb = filho->fb = 0;
            }else if(filho->filhoE->fb == 1){
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }else{
                noDesbalanceado->fb = 0;
                filho->fb = 1;
            }
            filho->filhoE->fb = 0;
            /* Rotacionando. */
            rotacaoDir(filho);
            rotacaoEsq(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->filhoD == noDesbalanceado){
                arv->sentinela->filhoD = noDesbalanceado->pai;
            }
        }
    }else {
        //Subárvore esquerda tem mais elementos.
        filho = noDesbalanceado->filhoE;
        if(filho->fb <= 0) {
            //Rotação simples.
            /* Corrigindo FBs. */
            if(filho->fb == -1) {
                noDesbalanceado->fb = filho->fb = 0;
            }else {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
            /* Rotacionando. */
            rotacaoDir(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->filhoD == noDesbalanceado) {
                arv->sentinela->filhoD = filho;
            }
        }else {
            //Rotação dupla.
            /* Corrigindo FBs. */
            if(filho->filhoD->fb == 0){
                noDesbalanceado->fb = filho->fb = 0;
            }else if(filho->filhoD->fb == 1){
                noDesbalanceado->fb = 0;
                filho->fb = -1;
            }else{
                noDesbalanceado->fb = 1;
                filho->fb = 0;
            }
            filho->filhoD->fb = 0;
            /* Rotacionando. */
            rotacaoEsq(filho);
            rotacaoDir(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->filhoD == noDesbalanceado){
                arv->sentinela->filhoD = noDesbalanceado->pai;
            }
        }
    }
}

void rotacaoEsq(no *noDesbalanceado) {
    /* Vinculando o pai com o novo filho (filhoD). */
    if(noDesbalanceado == noDesbalanceado->pai->filhoE) {
        noDesbalanceado->pai->filhoE = noDesbalanceado->filhoD;
    }else {
        noDesbalanceado->pai->filhoD = noDesbalanceado->filhoD;
    }
    noDesbalanceado->filhoD->pai = noDesbalanceado->pai;
    /* Atualizando o novo pai do nó. */
    noDesbalanceado->pai = noDesbalanceado->filhoD;
    /* Vinculando o novo filho direito do nó. */
    noDesbalanceado->filhoD = noDesbalanceado->pai->filhoE;
    if(noDesbalanceado->filhoD) {
        noDesbalanceado->filhoD->pai = noDesbalanceado;
    }
    /* Vinculando o nó como o novo filho esquerdo do pai. */
    noDesbalanceado->pai->filhoE = noDesbalanceado;
}

void rotacaoDir(no *noDesbalanceado) {
    /* Vinculando o pai com o novo filho (filhoE). */
    if(noDesbalanceado == noDesbalanceado->pai->filhoE) {
        noDesbalanceado->pai->filhoE = noDesbalanceado->filhoE;
    }else {
        noDesbalanceado->pai->filhoD = noDesbalanceado->filhoE;
    }
    noDesbalanceado->filhoE->pai = noDesbalanceado->pai;
    /* Atualizando o novo pai do nó. */
    noDesbalanceado->pai = noDesbalanceado->filhoE;
    /* Vinculando o novo filho esquerdo do nó. */
    noDesbalanceado->filhoE = noDesbalanceado->pai->filhoD;
    if(noDesbalanceado->filhoE) {
        noDesbalanceado->filhoE->pai = noDesbalanceado;
    }
    /* Vinculando o nó como o novo filho direito do pai. */
    noDesbalanceado->pai->filhoD = noDesbalanceado;
}
