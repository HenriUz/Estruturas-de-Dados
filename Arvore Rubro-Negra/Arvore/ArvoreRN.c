/*
ArvoreRN.c

Descrição: implementação das funções da árvore.
*/

/* --- Includes. --- */

#include "ArvoreRN.h"
#include <stdlib.h>
#include <stdio.h>

/* --- Estruturas. --- */

struct no {
    int chave; //Chave do nó.
    int cor; //Cor do nó.
    no *pai, *filhoE, *filhoD; //Nós parentes, aqueles que não existem serão nulos.
};

struct arvore {
    no *sentinela; //Ponteiro para o nó que salva a raiz da árvore.
    int numElementos; //Quantidade de elementos na árvore.
};

/* --- Funções. --- */

no *criaNo(int chave) {
    no *folha = (no*)malloc(sizeof(no));
    if(!folha) {
        return NULL;
    }
    /* Setando os valores. */
    folha->chave = chave;
    folha->cor = RED; //Os novos nós devem ser vermelho para manter a propriedade de sempre ter a mesma quantidade de nós pretos em cada sub-árvore.
    folha->pai = folha->filhoE = folha->filhoD = NULL;
    return folha;
}

arvore *criaArvore() {
    arvore *arv = (arvore*)malloc(sizeof(arvore));
    if(!arv) {
        return NULL;
    }
    /* Criando o sentinela. */
    arv->sentinela = criaNo(-1000);
    if(!arv->sentinela) {
        free(arv);
        return NULL;
    }
    /* Setando os valores. */
    arv->sentinela->cor = BLACK;
    arv->numElementos = 0;
    return arv;
}

no *getRaiz(arvore *arv) {
    return arv->sentinela->filhoD;
}

int getNumElementos(arvore *arv) {
    return arv->numElementos;
}

int insere(arvore *arv, int chave) {
    no *folha = criaNo(chave), *atual = NULL, *pai = NULL;
    if(!folha) {
        return 0;
    }
    /* Inserindo. */
    if(!arv->numElementos) {
        //Árvore vazia;
        arv->sentinela->filhoD = folha;
        folha->pai = arv->sentinela;
    }else {
        /* Buscando posição na árvore. */
        atual = arv->sentinela->filhoD;
        while(atual) {
            pai = atual;
            if(chave < atual->chave) {
                atual = atual->filhoE;
            }else {
                atual = atual->filhoD;
            }
        }
        /* Vinculando a folha com o pai. */
        if(chave < pai->chave) {
            pai->filhoE = folha;
        }else {
            pai->filhoD = folha;
        }
        folha->pai = pai;
    }
    /* Analisando as propriedades da árvore, e modificando quantidade. */
    analisaInsercao(arv, folha);
    arv->numElementos++;
    return 1;
}

int deleta(arvore *arv, int chave) {
    no *atual, *aux;
    /* Removendo. */
    if(arv->numElementos) {
        /* Buscando posição na árvore. */
        atual = arv->sentinela->filhoD;
        while(atual && atual->chave != chave) {
            if(chave < atual->chave) {
                atual = atual->filhoE;
            }else {
                atual = atual->filhoD;
            }
        }
        /* Desvinculando elemento. */
        if(atual) {
            //Elemento encontrado.
            if(atual->filhoE && atual->filhoD) {
                //Elemento possui os dois filhos, remove por cópia de predecessor.
                aux = atual;
                /* Buscando predecessor. */
                atual = atual->filhoE;
                while(atual->filhoD) {
                    atual = atual->filhoD;
                }
                /* Realizando a cópia por valor. */
                aux->chave = atual->chave;
                /* Desvinculando o predecessor. */
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = atual->filhoE;
                }else {
                    atual->pai->filhoD = atual->filhoE;
                }
                if(atual->filhoE) {
                    atual->filhoE->pai = atual->pai;
                }
            }else if(!atual->filhoE && !atual->filhoD) {
                //Elemento não possui nenhum filho, desvincula do pai.
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = NULL;
                }else {
                    atual->pai->filhoD = NULL;
                }
            }else if(atual->filhoE) {
                //Elemento possui somente o filho esquerdo, desvincula do pai e vincula o filho.
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = atual->filhoE;
                }else {
                    atual->pai->filhoD = atual->filhoE;
                }
                atual->filhoE->pai = atual->pai;
            }else {
                //Elemento possui somente o filho direito, desvincula do pai e vincula o filho.
                if(atual == atual->pai->filhoE) {
                    atual->pai->filhoE = atual->filhoD;
                }else {
                    atual->pai->filhoD = atual->filhoD;
                }
                atual->filhoD->pai = atual->pai;
            }
            /* Analisando as propriedades da árvore, e modificando quantidade. */
            if(atual->cor == BLACK) {
                analisaRemocao(arv, atual);
            }
            arv->numElementos--;
            /* Liberando memória. */
            free(atual);
            atual = NULL;
            return 1;
        }
        //Elemento não encontrado.
        return -1;
    }
    //Árvore vazia.
    return 0;
}

void preOrdem(no *elemento) {
    if(elemento) {
        printf("Elemento: (%d, %d) - Pai: (%d, %d)\n", elemento->chave, elemento->cor, elemento->pai->chave, elemento->pai->cor);
        preOrdem(elemento->filhoE);
        preOrdem(elemento->filhoD);
    }
}

int buscaElemento(arvore *arv, int chave) {
    no *elemento = arv->sentinela->filhoD;
    /* Buscando elemento. */
    while(elemento && elemento->chave != chave) {
        if(chave < elemento->chave) {
            elemento = elemento->filhoE;
        }else {
            elemento = elemento->filhoD;
        }
    }
    /* Retornando valores correspondentes. */
    if(elemento) {
        return elemento->cor;
    }
    return -1;
}

void analisaInsercao(arvore *arv, no *folha) {
    no *tio;
    /* Percorrendo a árvore. */
    while(folha->pai != arv->sentinela && folha->pai->cor == RED) {
        if(folha->pai == folha->pai->pai->filhoE) {
            //Elemento está na sub-árvore esquerda do avô.
            tio = folha->pai->pai->filhoD;
            if(tio && tio->cor == RED) {
                //Tio vermelho, caso 1:
                // - Pai e Tio se tornam pretos, avô se torna vermelho.
                // - Avô se torna o novo nó analisado (folha).
                folha->pai->cor = tio->cor = BLACK;
                folha->pai->pai->cor = RED;
                folha = folha->pai->pai;
            }else {
                //Tio é preto ou não existe.
                if(folha == folha->pai->filhoD) {
                    //O elemento analisado (folha) é um filho direito, caso 2:
                    // - Rotação à esquerda no pai (que passa a ser o elemento analisado).
                    folha = folha->pai;
                    rotacaoEsq(folha);
                }
                //O elemento analisado (folha) é um filho esquerdo, caso 3:
                // - Pai se torna preto, e avô se torna vermelho.
                // - Rotação à direita no avô.
                folha->pai->cor = BLACK;
                folha->pai->pai->cor = RED;
                rotacaoDir(folha->pai->pai);
            }
        }else {
            //Elemento está na sub-árvore direita do avô.
            tio = folha->pai->pai->filhoE;
            if(tio && tio->cor == RED) {
                //Tio vermelho, caso 1:
                // - Pai e Tio se tornam pretos, avô se torna vermelho.
                // - Avô se torna o novo nó analisado (folha).
                folha->pai->cor = tio->cor = BLACK;
                folha->pai->pai->cor = RED;
                folha = folha->pai->pai;
            }else {
                //Tio é preto ou não existe.
                if(folha == folha->pai->filhoE) {
                    //O elemento analisado (folha) é um filho esquerdo, caso 2:
                    // - Rotação à direita no pai (que passa a ser o elemento analisado).
                    folha = folha->pai;
                    rotacaoDir(folha);
                }
                //O elemento analisado (folha) é um filho direito, caso 3:
                // - Pai se torna preto, e avô se torna vermelho.
                // - Rotação à esquerda no avô.
                folha->pai->cor = BLACK;
                folha->pai->pai->cor = RED;
                rotacaoEsq(folha->pai->pai);
            }
        }
    }
    /* Modificando cor da raiz para garantir propriedade da raiz sempre preta. */
    arv->sentinela->filhoD->cor = BLACK;
}

void analisaRemocao(arvore *arv, no *analisado) {
    no *aux; //Inicialmente será o sucessor, e depois passará a ser o irmão.
    if(analisado->chave <= analisado->pai->chave) {
        aux = analisado->pai->filhoE;
    }else {
        aux = analisado->pai->filhoD;
    }
    if(aux && aux->cor == RED) {
        //Sucessor é vermelho, então se torna preto.
        aux->cor = BLACK;
    }else {
        //Sucessor é preto.
        /* Percorrendo a árvore. */
        while(analisado->pai != arv->sentinela && analisado->cor == BLACK) {
            if(analisado->chave < analisado->pai->chave) {
                //Irmão está na sub-árvore direita.
                aux = analisado->pai->filhoD;
                if(aux->cor == RED) {
                    //Irmão é vermelho, caso 1:
                    // - Irmão se torna preto, e pai se torna vermelho.
                    // - Rotação à esquerda no pai.
                    // - Leva aos casos 2, 3 ou 4.
                    aux->cor = BLACK;
                    analisado->pai->cor = RED;
                    rotacaoEsq(analisado->pai);
                    aux = analisado->pai->filhoD;
                }
                if((!aux->filhoE || aux->filhoE->cor == BLACK) && (!aux->filhoD || aux->filhoD->cor == BLACK)) {
                    //Irmão é preto e seus dois filhos também são pretos, caso 2:
                    // - Irmão se torna vermelho.
                    // - Pai se torna o analisado.
                    aux->cor == RED;
                    analisado = analisado->pai;
                }else {
                    if(!aux->filhoD || aux->filhoD->cor == BLACK) {
                        //Irmão é preto e seu filho esquerdo é vermelho, caso 3:
                        // - Irmão se torna vermelho, e o filho esquerdo se torna preto.
                        // - Rotação à direita no irmão.
                        // - Leva ao caso 4.
                        aux->cor = RED;
                        aux->filhoE->cor = BLACK;
                        rotacaoDir(aux);
                        aux = analisado->pai->filhoD;
                    }
                    //Irmão é preto e seu filho direito é vermelho, caso 4:
                    // - Irmão se torna da cor do pai, e o pai e o filho direito se tornam pretos.
                    // - Rotação à esquerda no pai.
                    // - Finaliza.
                    aux->cor = analisado->pai->cor;
                    analisado->pai->cor = aux->filhoD->cor = BLACK;
                    rotacaoEsq(analisado->pai);
                    analisado = arv->sentinela->filhoD;
                }
            }else {
                //Irmão está na sub-árvore esquerda.
                aux = analisado->pai->filhoE;
                if(aux->cor == RED) {
                    //Irmão é vermelho, caso 1:
                    // - Irmão se torna preto, e pai se torna vermelho.
                    // - Rotação à direita no pai.
                    // - Leva aos casos 2, 3 ou 4.
                    aux->cor = BLACK;
                    analisado->pai->cor = RED;
                    rotacaoDir(analisado->pai);
                    aux = analisado->pai->filhoE;
                }
                if((!aux->filhoE || aux->filhoE->cor == BLACK) && (!aux->filhoD || aux->filhoD->cor == BLACK)) {
                    //Irmão é preto e seus filhos também são pretos, caso 2:
                    // - Irmão se torna vermelho.
                    // - Pai se torna o analisado.
                    aux->cor = RED;
                    analisado = analisado->pai;
                }else {
                    if(!aux->filhoE || aux->filhoE->cor == BLACK) {
                        //Irmão é preto e seu filho direito é preto, caso 3:
                        // - Irmão se torna vermelho, e seu filho direito se torna preto.
                        // - Rotação à esquerda no irmão.
                        // - Leva ao caso 4.
                        aux->cor = RED;
                        aux->filhoD->cor = BLACK;
                        rotacaoEsq(aux);
                        aux = analisado->pai->filhoE;
                    }
                    //Irmão é preto e seu filho esquerdo é vermelho, caso 4:
                    // - Irmão se torna da cor do pai, e o pai e seu filho esquerdo se tornam pretos.
                    // - Rotação à direita no pai.
                    // - Finaliza.
                    aux->cor = analisado->pai->cor;
                    analisado->pai->cor = aux->filhoE->cor = BLACK;
                    rotacaoDir(analisado->pai);
                    analisado = arv->sentinela->filhoD;
                }
            }
        }
        analisado->cor = BLACK;
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
