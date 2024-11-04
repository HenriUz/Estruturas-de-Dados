/*
ArvoreAvl.h

Descrição: definição das funções da árvore.
*/

/* --- Estruturas. --- */

typedef struct chave chave;

typedef struct no no;

typedef struct arvore arvore;

/* --- Funções. --- */

/*
Descrição: função responsável por criar e iniciar um nó folha.
Entrada: inteiro do índice, char do caractere.
Saída: ponteiro para o nó criado.
*/
no *criaNo(int indice, char caractere);

/*
Descrição: função responsável por criar e iniciar uma árvore.
Entrada: nada.
Saída: ponteiro para a árvore.
*/
arvore *criaArvore();

/*
Descrição: função responsável por retornar o ponteiro para a raiz da árvore.
Entrada: ponteiro para a árvore.
Saída: ponteiro para a raiz, ou NULL caso esteja vazia.
*/
no *getRaiz(arvore *arv);

/*
Descrição: função responsável por retornar o número de elementos armazenados na árvore.
Entrada: ponteiro para a árvore.
Saída: inteiro da quantidade.
*/
int getNumElementos(arvore *arv);

/*
Descrição: função responsável por inserir o nó na árvore.
Entrada: ponteiro para a árvore, inteiro do índice, char do caractere.
Saída: 1 - sucesso, 0 - erro.
*/
int insere(arvore *arv, int indice, char caractere);

/*
Descrição: função responsável por remover um elemento da árvore, usando o predecessor se necessário.
Entrada: ponteiro para a árvore, inteiro do índice.
Saída: 1 - sucesso, 0 - elemento não econtrado, -1 - árvore vazia.
*/
int deleta(arvore *arv, int indice);

/*
Descrição: função responsável por buscar um elemento na árvore.
Entrada: Ponteiro para a árvore, inteiro do índice.
Saída: 1 - elemento encontrado, 0 - elemento não encontrado.
Observação: o correto seria retornar o nó ou o elemento, mas para fins didáticos foi implementado somente o aviso se achou ou não.
*/
int busca(arvore *arv, int indice);

/*
Descrição: função responsável por imprimir a árvore em pré-ordem da seguinte forma: (indice, caractere) - fb - pai (indice, caractere).
Entrada: ponteiro para o nó.
Saída: nada.
*/
void preOrdem(no *raiz);

/*
Descrição: função responsável por remover todos os elementos da árvore.
Entrada: ponteiro para a árvore.
Saída: nada.
*/
void esvaziaArvore(arvore *arv);

/*
Descrição: função responsável por atualizar os fb dos nós na subárvore onde o novo nó foi inserido. Caso identifique um balanceamento, chama a função de balancear.
Entrada: ponteiro para a árvore, ponteiro para o nó inserido.
Saída: nada.
*/
void atualizaFB_Insercao(arvore *arv, no *folha);

/*
Descrição: função responsável por atualizar os fb dos nós na subárvore onde o elemento foi removido. Diferente da inserção, não para de verificar após realizar um balanceamento.
Entrada: ponteiro para a árvore, ponteiro para o pai do elemento removido, inteiro do indice (para identificar em qual subárvore estava).
Saída: nada.
*/
void atualizaFB_Remocao(arvore *arv, no *pai, int indice);

/*
Descrição: função responsável por identificar qual tipo de rotação deve ser feito para balancear a árvore. Além corrigir os fbs dos nós envolvidos na rotação (existe uma tabela para isso).
Entrada: ponteiro para a árvore, ponteiro para o nó desbalanceado.
Saída: nada.
*/
void balanceia(arvore *arv, no *noDesbalanceado);

/*
Descrição: função responsável por realizar uma rotação para a esquerda no nó informado.
Entrada: ponteiro para o nó.
Saída: nada.
*/
void rotacaoEsq(no *noDesbalanceado);

/*
Descrição: função responsável por realizar uma rotação para a direita no nó informado.
Entrada: ponteiro para o nó.
Saída: nada.
*/
void rotacaoDir(no *noDesbalanceado);
