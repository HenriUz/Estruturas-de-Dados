/*
ArvoreB.h

Descrição: definição das funções da árvore-b.
*/

/* --- Includes. --- */

#include <stdio.h>

/* --- Estruturas --- */

typedef struct arvore arvore;

typedef struct pagina pagina;

typedef struct chave chave;

/* --- Funções. --- */

/*
Descrição: função responsável por criar uma estrutura da árvore-b.
Entrada: inteiro da ordem.
Saída: ponteiro para a estrutura criada.
*/
arvore *criaArvore(int ordem);

/*
Descrição: função responsável por retornar o ponteiro para a raiz da árvore.
Entrada: ponteiro para a árvore.
Saída: ponteiro para a raiz.
*/
pagina *getRaiz(const arvore *arv);

/*
Descrição: função responsável por retornar a quantidade de elementos da árvore.
Entrada: ponteiro para a árvore.
Saída: inteiro da quantidade de elementos da árvore.
*/
int getNumElementos(const arvore *arv);

/*
Descrição: função responsável por retornar a ordem da árvore.
Entrada: ponteiro para a árvore.
Saída: inteiro da ordem da árvore.
*/
int getOrdem(const arvore *arv);

/*
Descrição: função responsável por criar uma nova página totalmente vazia.
Entrada: inteiro representando a quantidade de elementos na página.
Saída: ponteiro para a página criada.
*/
pagina *criaPagina(int maximoElementos);

/*
Descrição: função responsável por criar uma nova raiz para a árvore-b informada.
Entrada: ponteiro para a árvore, ponteiro para o novo filho direito (nova página criada, por padrão o filho esquerdo é a antiga raiz), ponteiro a chave que a raiz irá armazenar.
Saída: ponteiro para a página criada.
*/
pagina *criaRaiz(const arvore *arv, pagina *filhoD, chave *key);

/*
Descrição: função responsável por inserir uma chave em uma página.
Entrada: ponteiro para a página onde será inserido, ponteiro para o filho direito da nova chave (nulo se for folha), ponteiro para a nova chave, inteiro da posição onde a nova chave será inserida.
Saída: nada.
*/
void insereNaPagina(pagina *page, pagina *filhoD, chave *newChave, int pos);

/*
Descrição: função responsável realizar a divisão de uma página cheia em duas páginas, subindo um elemento da página cheia para o pai.
Entrada: ponteiro para a árvore, ponteiro para a página cheia, ponteiro para o filho direito da nova chave, ponteiro de ponteiro para o filho direito (após a divisão da página cheia, o filho direito passa a ser a nova página criada), ponteiro para a nova chave, ponteiro de ponteiro para a nova chave (após a inserção, a nova chave passa a ser a chave que subiu para o pai), inteiro da posição onde a chave será inserida.
Saída: nada.
*/
void split(arvore *arv, pagina *page, pagina *filhoD, pagina **salvaFilhoD, chave *newChave, chave **salvaChave, int pos);

/*
Descrição: função que inicialmente busca a página folha em que a nova chave será inserida, e depois vai verificando se insere ou da split.
Entrada: ponteiro para a árvore, ponteiro para a página atual na recursão, ponteiro de ponteiro para o filho direito, ponteiro para a nova chave, ponteiro de ponteiro para a nova chave.
Saída: 1 - insere ou da split, 0 - não faz nada.
*/
int procuraPaginaI(arvore *arv, pagina *page, pagina **filhoD, chave *newChave, chave **salvaChave);

/*
Descrição: função responsável por criar a nova chave inicial e chama a procuraPaginaI, dependendo do resultado cria uma nova raiz.
Entrada: ponteiro para a árvore, inteiro da matrícula, inteiro da linha.
Saída: 1 - sucesso, 0 - falha.
*/
int insere(arvore *arv, int mat, int linha);

/*
Descrição: função responsável por inserir todos os registros (matrícula) de um arquivo na árvore-b.
Entrada: ponteiro para a árvore, ponteiro para o arquivo.
Saída: 1 - sucesso, 0 - falha.
*/
int processaCarga(arvore *arv, FILE *dataset);

/*
Descrição: função responsável por receber uma página não folha, copia (por valor) o predecessor do elemento para a posição do elemento.
Entrada: ponteiro para página, inteiro da posição onde se encontra a chave.
Saída: nada.
*/
void copiaPredecessor(const pagina *page, int pos);

/*
Descrição: função responsável por remover o elemento da posição indicada na folha informada.
Entrada: ponteiro para a página folha, inteiro para posição.
Saída: nada.
*/
void removeDaPagina(pagina *page, int pos);

/*
Descrição: função responsável por juntar duas páginas irmãs (a direita com a esquerda), descendo um elemento do pai.
Entrada: ponteiro para a página pai, inteiro da página irmã direita.
Saída: nada.
*/
void merge(pagina *pai, int pos);

/*
Descrição: função responsável por transferir uma chave de uma página irmã a direita para o pai, e uma chave do pai para a página irmã a esquerda.
Entrada: ponteiro para a página pai, inteiro da posição da página irmã esquerda.
Saída: nada.
*/
void emprestaDireita(const pagina *pai, int pos);

/*
Descrição: função responsável por transferir uma chave de uma página irmã a esquerda para o pai, e uma chave do pai para a página irmã a direita.
Entrada: ponteiro para a página pai, inteiro da posição da página irmã direita.
Saída: nada.
*/
void emprestaEsquerda(const pagina *pai, int pos);

/*
Descrição: função responsável por decidir qual função chamar quando um filho está com a quantidade abaixo da mínima.
Entrada: ponteiro para a árvore, ponteiro para a página pai, inteiro da posição do filho.
Saída: nada.
*/
void corrigiFilho(const arvore *arv, pagina *pai, int pos);

/*
Descrição: função recursiva responsável por procurar onde está o elemento que será removido, e identifica se o filho de alguma página precisa de correção.
Entrada: ponteiro para a árvore, ponteiro para a página, inteiro da matrícula que será removida.
Saída: 1 - toma alguma decisão, 0 - não faz nada.
*/
int procuraPaginaD(arvore *arv, pagina *page, int mat);

/*
Descrição: função responsável por chamar a função responsável por procurar a página, e por verificar se a raiz deu merge.
Entrada: ponteiro para a árvore, inteiro da matrícula que será removida.
Saída: 1 - sucesso, 0 - elemento não encontrado, −1 - árvore vazia.
*/
int deleta(arvore *arv, int mat);

/*
Descrição: função responsável por buscar iterativamente pela árvore-b a matrícula informada.
Entrada: ponteiro para a árvore, inteiro da matrícula.
Saída: inteiro da linha do elemento, −1 se não foi encontrado.
*/
int busca(const arvore *arv, int mat);

/*
Descrição: função responsável por imprimir a árvore-b, tentando reproduzir ela em pre-ordem.
Entrada: ponteiro para a página, inteiro do nível.
Saída: nada.
*/
void imprimeArvore(const pagina *page, int nivel);
