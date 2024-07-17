#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdio.h>

/*** -- Estruturas -- ***/

typedef struct arvore arvore;

typedef struct pagina pagina;

typedef struct chave chave;

/*** -- Funções da Árvore -- ***/

/*
Descrição: Função que cria uma estrutura da B-Tree.
Entrada: Inteiro da ordem.
Saída: Ponteiro para a estrutura criada.
*/
arvore *criaArvore(int ordem);

/*
Descrição: Função que retorna o ponteiro para a raiz da árvore.
Entrada: Ponteiro para a árvore.
Saída: Ponteiro para a raiz.
*/
pagina *getRaiz(arvore *arv);

/*
Descrição: Função que retorna a quantidade de elementos da árvore.
Entrada: Ponteiro para a árvore.
Saída: Inteiro da quantidade de elementos da árvore.
*/
int getNumElementos(arvore *arv);

/*
Descrição: Função que retorna a ordem da árvore.
Entrada: Ponteiro para a árvore.
Saída: Inteiro da ordem da árvore.
*/
int getOrdem(arvore *arv);

/*** -- Funções da Inserção -- ***/

/*
Descrição: Função que cria uma nova página totalmente vazia.
Entrada: Inteiro representando a quantidade de elementos na página.
Saída: Ponteiro para a página criada.
*/
pagina *criaPagina(int maximoElementos);

/*
Descrição: Função que cria uma nova raiz para a B-Tree informada.
Entrada: Ponteiro para a estrutura da árvore, ponteiro para o novo filho direito (nova página criada, por padrão o filho esquerdo é a antiga raiz),
    ponteiro para a estrutura de chave que a raiz irá armazenar.
Saída: Ponteiro para a página criada.
*/
pagina *criaRaiz(arvore *arv, pagina *filhoD, chave *key);

/*
Descrição: Função que insere uma chave em uma página.
Entrada: Ponteiro para a página onde será inserido, ponteiro para o filho direito da nova chave (nulo se for folha), ponteiro para a nova chave,
    inteiro da posição onde a nova chave será inserida.
Saída: Nada.
*/
void insereNaPagina(pagina *page, pagina *filhoD, chave *newChave, int pos);

/*
Descrição: Função que realiza a divisão de uma página cheia em duas páginas, subindo um elemento da página cheia para o pai.
Entrada: Ponteiro para a árvore, ponteiro para a página cheia, ponteiro para o filho direito da nova chave, ponteiro de ponteiro para o filho direito
    (após a divisão da página cheia, o filho direito passa a ser a nova página criada), ponteiro para a nova chave, ponteiro de ponteiro para a nova
    chave (após a inserção, a nova chave passa a ser a chave que subiu para o pai), inteiro da posição onde a chave será inserida.
Saída: Nada.
*/
void split(arvore *arv, pagina *page, pagina *filhoD, pagina **salvaFilhoD, chave *newChave, chave **salvaChave, int pos);

/*
Descrição: Função que inicialmente busca a página folha em que a nova chave será inserida, e depois vai verificando se insere ou da split.
Entrada: Ponteiro para a árvore, ponteiro para a página atual na recursão, ponteiro de ponteiro para o filho direito, ponteiro para a nova chave,
    ponteiro de ponteiro para a nova chave.
Saída: 1 - insere ou da split, 0 - não faz nada.
*/
int procuraPaginaI(arvore *arv, pagina *page, pagina **filhoD, chave *newChave, chave **salvaChave);

/*
Descrição: Função que cria a nova chave inicial e chama a procuraPagina, dependendo do resultado cria uma nova raiz.
Entrada: Ponteiro para a árvore, inteiro da matrícula, inteiro da linha.
Saída: 1 - sucesso, 0 - falha.
*/
int insere(arvore *arv, int mat, int linha);

/*
Descrição: Função que insere todos os registros (matrícula) de um arquivo na B-Tree.
Entrada: Ponteiro para a árvore, ponteiro para o arquivo.
Saída: 1 - sucesso, 0 - falha.
*/
int processaCarga(arvore *arv, FILE *dataset);

/*** -- Funções da Remoção -- ***/

/*
Descrição: Função que recebe uma página não folha, copia (por valor) o predecessor do elemento para a posição do elemento.
Entrada: Ponteiro para página, inteiro da posição onde se encontra a chave.
Saída: Nada.
*/
void copiaPredecessor(pagina *page, int pos);

/*
Descrição: Função que remove o elemento da posição indicada na folha informada.
Entrada: Ponteiro para a página folha, inteiro para posição.
Saída: Nada.
*/
void removeDaPagina(pagina *page, int pos);

/*
Descrição: Função que junta duas páginas irmãs (a direita com a esquerda), descendo um elemento do pai.
Entrada: Ponteiro para a página pai, inteiro da página irmã direita.
Saída: Nada.
*/
void merge(pagina *pai, int pos);

/*
Descrição: Função que transefere uma chave de uma página irmã a direita para o pai, e uma chave do pai para a página irmã a esquerda.
Esntrada: Ponteiro para a página pai, inteiro da posição da página irmã esquerda.
Saída: Nada.
*/
void emprestaDireita(pagina *pai, int pos);

/*
Descrição: Função que transfere uma chave de uma página irmã a esquerda para o pai, e uma chave do pai para a página irmã a direita.
Entrada: Ponteiro para a página pai, inteiro da posição da página irmã direita.
Saída: Nada.
*/
void emprestaEsquerda(pagina *pai, int pos);

/*
Descrição: Função que decide qual função chamar quando um filho está com a quantidade abaixo da mínima.
Entrada: Ponteiro para a árvore, ponteiro para a página pai, inteiro da posição do filho.
Saída: Nada.
*/
void corrigiFilho(arvore *arv, pagina *pai, int pos);

/*
Descrição: Função recursiva que procura onde está o elemento que será removido, e identifica se o filho de alguma página precisa de correção.
Entrada: Ponteiro para a árvore, ponteiro para a página, inteiro da matrícula que será removida.
Saída: 1 - toma alguma decisão, 0 - não faz nada.
*/
int procuraPaginaD(arvore *arv, pagina *page, int mat);

/*
Descrição: Função que chama a função responsável por procurar a página, e por verificar se a raiz deu merge.
Entrada: Ponteiro para a árvore, inteiro da matrícula que será removida.
Saída: 1 - sucesso, 0 - elemento não encontrado, -1 - árvore vazia.
*/
int deleta(arvore *arv, int mat);

/*** -- Funções da Busca -- ***/

/*
Descrição: Função que busca iterativamente pela B-Tree a matrícula informada.
Entrada: Ponteiro para a arvore, inteiro da matrícula.
Saída: Inteiro da linha do elemento, -1 se não foi encontrado.
*/
int busca(arvore *arv, int mat);

/*** -- Funções da Impreção -- ***/

/*
Descrição: Função que imprime a B-Tree, tentando reporduzir ela em pre-ordem.
Entrada: Ponteiro para a página, inteiro do nível.
Saída: Nada.
*/
void imprimeArvore(pagina *page, int nivel);

#endif //ARVOREB_H
