#ifndef ARVOREAVL_H
#define ARVOREAVL_H

/*** -- Estruturas. -- ***/

typedef struct chave chave;

typedef struct no no;

typedef struct arvore arvore;

/*** -- Funções. -- ***/

/*
Descrição: Função que cria e inicia um nó folha.
Entrada: Inteiro do índice, char do caractere.
Saída: Ponteiro para o nó criado.
*/
no *criaNo(int indice, char caractere);

/*
Descrição: Função que cria e inicia uma árvore.
Entrada: Nada.
Saída: Ponteiro para a árvore.
*/
arvore *criaArvore();

/*
Descrição: Função que retorna o ponteiro para a raiz da árvore.
Entrada: Ponteiro para a árvore.
Saída: Ponteiro para a raiz, ou NULL caso esteja vazia.
*/
no *getRaiz(arvore *arv);

/*
Descrição: Função que retorna o número de elementos armazenados na árvore.
Entrada: Ponteiro para a árvore.
Saída: Inteiro da quantidade.
*/
int getNumElementos(arvore *arv);

/*
Descrição: Função que insere o nó na árvore, e chama a função de atualizar fb.
Entrada: Ponteiro para a árvore, inteiro do índice, char do caractere.
Saída: 1 - sucesso, 0 - fracasso.
*/
int insere(arvore *arv, int indice, char caractere);

/*
Descrição: Função que remove um elemento da árvore, usando o predecessor se necessário.
Entrada: Ponteiro para a árvore, inteiro do índice.
Saída: 1 - sucesso, 0 - elemento não econtrado, -1 - árvore vazia.
*/
int deleta(arvore *arv, int indice);

/*
Descrição: Função que busca um elemento na árvore. O elemento não é retornado por não ter necessidade, mas caso seja necessário, troque o tipo de retorno.
Entrada: Ponteiro para a árvore, inteiro do índice.
Saída: 1 - Elemento encontrado, 0 - Elemento não encontrado.
*/
int busca(arvore *arv, int indice);

/*
Descrição: Função que imprime a árvore em pré-ordem da seguinte forma: (indice, caractere) - fb - pai (indice, caractere).
Entrada: Ponteiro para o nó.
Saída: Nada.
*/
void preOrdem(no *raiz);

/*
Descrição: Função que remove todos os elementos da árvore (usado no fim do programa, mas pode ser usado em qualquer lugar).
Entrada: Ponteiro para a árvore.
Saída: Nada.
*/
void esvaziaArvore(arvore *arv);

/*** -- Funções de balanceamento da avl. -- ***/

/*
Descrição: Função que atualiza os fb dos nós na subárvore onde o novo nó foi enserido. Caso identifique um balanceamento, chama a função de balancear.
Entrada: Ponteiro para a árvore, ponteiro para o nó inserido.
Saída: Nada.
*/
void atualizaFB_Insercao(arvore *arv, no *folha);

/*
Descrição: Função que atualiza os fb dos nós na subárvore onde o elemento foi removido. Diferente da inserção, não para de verificar após realizar um balanceamento.
Entrada: Ponteiro para a árvore, ponteiro para o pai do elemento removido, inteiro do indice (para identificar em qual subárvore estava).
Saída: Nada.
*/
void atualizaFB_Remocao(arvore *arv, no *pai, int indice);

/*
Descrição: Função que identifica qual tipo de rotação deve ser feito para balancear a árvore. E corrige os fb dos nós envolvidos na rotação (existe uma tabela para isso).
Entrada: Ponteiro para a árvore, ponteiro para o nó desbalanceado.
Saída: Nada.
*/
void balanceia(arvore *arv, no *noDesbalanceado);

/*
Descrição: Função que realiza uma rotação para a esquerda no nó informado.
Entrada: Ponteiro para o nó.
Saída: Nada.
*/
void rotacaoEsq(no *noDesbalanceado);

/*
Descrição: Função que realiza uma rotação para a direita no nó informado.
Entrada: Ponteiro para o nó.
Saída: Nada.
*/
void rotacaoDir(no *noDesbalanceado);

#endif
