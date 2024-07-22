#ifndef ARVORE_H
#define ARVORE_H

/*** -- Estruturas. -- ***/

typedef struct arvore arvore;

typedef struct no no;

/*** -- Funções. -- ***/

/*
Descrição: Função que cria e inicializa uma estrutura de árvore.
Entrada: Nada.
Saída: Ponteiro para a árvore.
*/
arvore *criaArvore();

/*
Descrição: Função que retorna a raiz da árvore informada.
Entrada: Ponteiro para a árvore.
Saída: Ponteiro para a raiz.
*/
no *getRaiz(arvore *arv);

/*
Descrição: Função que retorna a quantidade de elementos na árvore.
Entrada: Ponteiro para a árvore.
Saída: Inteiro da quantidade de elementos na árvore.
*/
int getNumElementos(arvore *arv);

/*
Descrição: Função que cria e inicializa uma estrutura de nó.
Entrada: Inteiro da chave.
Saída: Ponteiro para o nó.
*/
no *criaNo(int chave);

/*
Descrição: Função que insere uma chave na árvore.
Entrada: Ponteiro para a árvore, inteiro da chave.
Saída: 1 - sucesso, 0 - erro.
*/
int insere(arvore *arv, int chave);

/*
Descrição: Função que remove um elemento da árvore.
Entrada: Ponteiro para a árvore, inteiro da chave.
Saída: 1 - sucesso, 0 - árvore vazia, -1 - elemento não encontrado.
*/
int deleta(arvore *arv, int chave);

/*
Descrição: Função que esvazia a árvore (libera a memória alocada para cada nó).
Entrada: Ponteiro para a árvore.
Saída: Nada.
*/
void esvaziaArvore(arvore *arv);

/*
Descrição: Função que busca um elemento na árvore.
Entrada: Ponteiro para a árvore, inteiro da chave.
Saída: 1 - encontrou, 0 - não encontrou. (Aqui não há utilidade no nó, mas se a estrutura for alterada, é só fazer retornar o nó).
*/
int busca(arvore *arv, int chave);

/*
Descrição: Função que imprime a árvore em pré ordem (raiz, filho esquerdo, filho direito). Se o nó tiver pai, ele será impresso na frente.
Entrada: Ponteiro para o nó (inicialmente a raiz).
Saída: Nada.
*/
void preOrdem(no* raiz);

/*
Descrição: Função que imprime a árvore em ordem (filho esquerdo, raiz, filho direito).
Entrada: Ponteiro para o nó (inicialmente a raiz).
Saída: Nada.
*/
void emOrdem(no *raiz);

/*
Descrição: Função que imprime a árvore em pós ordem (filho esquerdo, filho direito, raiz). Se o nó tiver pai, ele será impresso na frente.
Entrada: Ponteiro para o nó (inicialmente a raiz).
Saída: Nada.
*/
void posOrdem(no *raiz);

#endif
