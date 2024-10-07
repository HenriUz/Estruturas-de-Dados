/*
ArvoreRN.h

Descrição: definição das funções da árvore rubro-negra.
*/

/* --- Constantes. --- */

#define RED 1
#define BLACK 0

/* --- Estruturas. --- */

typedef struct no no;

typedef struct arvore arvore;

/* --- Funções. --- */

/*
Descrição: função que cria e inicializa um novo nó.
Entrada: inteiro da chave.
Saída: ponteiro para o nó.
*/
no *criaNo(int chave);

/*
Descrição: função que cria e inicializa uma árvore.
Entrada: nada.
Saída: ponteiro para a árvore.
*/
arvore *criaArvore();

/*
Descrição: função que retorna a raiz da árvore.
Entrada: ponteiro para a árvore.
Saída: ponteiro para a raiz.
*/
no *getRaiz(arvore *arv);

/*
Descrição: função que retorna a quantidade de elementos na árvore.
Entrada: ponteiro para a árvore.
Saída: inteiro da quantidade de elementos.
*/
int getNumElementos(arvore *arv);

/*
Descrição: função que insere um elemento na árvore.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: 1 - sucesso, 0 - erro.
*/
int insere(arvore *arv, int chave);

/*
Descrição: função que remove um elemento da árvore.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: 1 - sucesso, 0 - árvore vazia, −1 - elemento não encontrado.
*/
int deleta(arvore *arv, int chave);

/*
Descrição: função que imprime a árvore em pré-ordem.
Entrada: ponteiro para o nó.
Saída: nada.
*/
void preOrdem(no *elemento);

/*
Descrição: busca um elemento na árvore rubro-negra.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: cor do elemento - sucesso, −1 - elemento não encontrado.
*/
int buscaElemento(arvore *arv, int chave);

/* --- Funções de balanceamento da Rubro-Negra. --- */

/*
Descrição: função que verifica e corrige, se necessário, as propriedades da árvore após a inserção.
Entrada: ponteiro para a árvore, ponteiro para o nó inserido.
Saída: nada.
*/
void analisaInsercao(arvore *arv, no *folha);

/*
Descrição: função que verifica e corrige, se necessário, as propriedades da árvore após a remoção.
Entrada: ponteiro para a árvore, ponteiro para o nó removido.
Saída: nada.
*/
void analisaRemocao(arvore *arv, no *analisado);

/*
Descrição: função que realiza uma rotação para a esquerda.
Entrada: ponteiro para o nó que será rotacionado.
Saída: nada.
*/
void rotacaoEsq(no *noDesbalanceado);

/*
Descrição: função que realiza uma rotação para a direita.
Entrada: ponteiro para o nó que será rotacionado.
Saída: nada.
*/
void rotacaoDir(no *noDesbalanceado);
