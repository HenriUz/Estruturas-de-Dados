/*
ArvoreRN.h

Descrição: definição das funções da árvore.
*/

/* --- Constantes. --- */

#define RED 1
#define BLACK 0

/* --- Estruturas. --- */

typedef struct no no;

typedef struct arvore arvore;

/* --- Funções. --- */

/*
Descrição: função responsável por criar e inicializar um novo nó.
Entrada: inteiro da chave.
Saída: ponteiro para o nó.
*/
no *criaNo(int chave);

/*
Descrição: função responsável por criar e inicializar uma árvore.
Entrada: nada.
Saída: ponteiro para a árvore.
*/
arvore *criaArvore();

/*
Descrição: função responsável por retornar a raiz da árvore.
Entrada: ponteiro para a árvore.
Saída: ponteiro para a raiz.
*/
no *getRaiz(const arvore *arv);

/*
Descrição: função responsável por retornar a quantidade de elementos na árvore.
Entrada: ponteiro para a árvore.
Saída: inteiro da quantidade de elementos.
*/
int getNumElementos(const arvore *arv);

/*
Descrição: função responsável por inserir um elemento na árvore.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: 1 - sucesso, 0 - erro.
*/
int insere(arvore *arv, int chave);

/*
Descrição: função responsável por remover um elemento da árvore.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: 1 - sucesso, 0 - árvore vazia, −1 - elemento não encontrado.
*/
int deleta(arvore *arv, int chave);

/*
Descrição: função responsável por imprimir a árvore em pré-ordem.
Entrada: ponteiro para o nó.
Saída: nada.
*/
void preOrdem(const no *elemento);

/*
Descrição: função responsável por buscar um elemento na árvore.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: cor do elemento - sucesso, −1 - elemento não encontrado.
*/
int buscaElemento(const arvore *arv, int chave);

/*
Descrição: função responsável por verificar e corrigir, se necessário, as propriedades da árvore após a inserção.
Entrada: ponteiro para a árvore, ponteiro para o nó inserido.
Saída: nada.
*/
void analisaInsercao(const arvore *arv, no *folha);

/*
Descrição: função responsável por verificar e corrigir, se necessário, as propriedades da árvore após a remoção.
Entrada: ponteiro para a árvore, ponteiro para o nó removido.
Saída: nada.
*/
void analisaRemocao(const arvore *arv, no *analisado);

/*
Descrição: função responsável por realizar uma rotação para a esquerda no nó informado.
Entrada: ponteiro para o nó que será rotacionado.
Saída: nada.
*/
void rotacaoEsq(no *noDesbalanceado);

/*
Descrição: função responsável por realizar uma rotação para a direita no nó informado.
Entrada: ponteiro para o nó que será rotacionado.
Saída: nada.
*/
void rotacaoDir(no *noDesbalanceado);
