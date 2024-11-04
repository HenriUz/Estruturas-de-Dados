/*
Arvore.h

Descrição: definição das funções da árvore.
*/

/* --- Estruturas. --- */

typedef struct arvore arvore;

typedef struct no no;

/* --- Funções. --- */

/*
Descrição: função responsável criar e inicializar uma árvore.
Entrada: nada.
Saída: ponteiro para a árvore.
*/
arvore *criaArvore();

/*
Descrição: função responsável por retornar a raiz da árvore informada.
Entrada: ponteiro para a árvore.
Saída: ponteiro para a raiz.
*/
no *getRaiz(const arvore *arv);

/*
Descrição: função responsável por retornar a quantidade de elementos na árvore.
Entrada: ponteiro para a árvore.
Saída: inteiro da quantidade de elementos na árvore.
*/
int getNumElementos(const arvore *arv);

/*
Descrição: função responsável por criar e inicializar um nó.
Entrada: inteiro da chave.
Saída: ponteiro para o nó.
*/
no *criaNo(int chave);

/*
Descrição: função responsável por inserir um nó na árvore.
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
Descrição: função responsável por esvaziar a árvore (libera a memória alocada para cada nó).
Entrada: ponteiro para a árvore.
Saída: nada.
*/
void esvaziaArvore(arvore *arv);

/*
Descrição: função responsável por buscar um elemento na árvore.
Entrada: ponteiro para a árvore, inteiro da chave.
Saída: 1 - encontrou, 0 - não encontrou.
Observação: o correto seria retornar o nó ou a chave, mas para fins didáticos, a função apenas informa se encontrou ou não.
*/
int busca(const arvore *arv, int chave);

/*
Descrição: função responsável por imprimir a árvore em pré-ordem (raiz, filho esquerdo, filho direito). Se o nó tiver pai, ele será impresso na frente.
Entrada: ponteiro para o nó (inicialmente a raiz).
Saída: nada.
*/
void preOrdem(const no* raiz);

/*
Descrição: função responsável por imprimir a árvore em ordem (filho esquerdo, raiz, filho direito).
Entrada: ponteiro para o nó (inicialmente a raiz).
Saída: nada.
*/
void emOrdem(const no *raiz);

/*
Descrição: função responsável por imprimir a árvore em pós-ordem (filho esquerdo, filho direito, raiz). Se o nó tiver pai, ele será impresso na frente.
Entrada: ponteiro para o nó (inicialmente a raiz).
Saída: nada.
*/
void posOrdem(const no *raiz);
