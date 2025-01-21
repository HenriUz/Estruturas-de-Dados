/*
Lista.h

Descrição: definição das funções da lista simplesmente encadeada.
*/

#ifndef LISTA_H
#define LISTA_H

/* --- Estruturas. --- */

typedef struct elemento elemento;

typedef struct lista lista;

/* --- Funções. --- */

/*
Descrição: função responsável por criar e inicializar uma lista.
Entrada: nada.
Saída: ponteiro para a lista.
*/
lista *criaLista();

/*
Descrição: função responsável por indicar se a lista está vazia ou não.
Entrada: ponteiro para a lista.
Saída: 1 - vazia, 0 - com elementos.
*/
int listaVazia(const lista *list);

/*
Descrição: função getter, responsável por devolver o elemento no início da lista.
Entrada: ponteiro para a lista.
Saída: ponteiro para o elemento no início.
*/
elemento *getComeco(const lista *list);

/*
Descrição: função responsável por criar e inicializar um elemento.
Entrada: inteiro do valor.
Saída: ponteiro para o elemento.
*/
elemento *criaElemento(int valor);

/*
Descrição: função getter, responsável por devolver o valor no elemento.
Entrada: ponteiro para o elemento.
Saída: inteiro do valor.
*/
int getValor(const elemento *element);

/*
Descrição: função responsável por inserir, de maneira ordenada, um elemento na lista.
Entrada: ponteiro para a lista, inteiro do valor que será inserido.
Saída: 1 - inserido, 0 - erro.
*/
int insereLista(lista *list, int valor);

/*
Descrição: função responsável por remover um elemento da lista.
Entrada: ponteiro para a lista, inteiro do valor que será removido.
Saída: 1 - removido, 0 - lista vazia, −1 - elemento não encontrado.
*/
int removeLista(lista *list, int valor);

/*
Descrição: função responsável por buscar um elemento na lista.
Entrada: ponteiro para a lista, inteiro do valor.
Saída: elemento - encontrado, NULL - elemento não encontrado.
Observação: o retorno é do tipo const, pois não queremos que o elemento seja modificado em outros locais.
*/
const elemento *buscaLista(const lista *list, int valor);

/*
Descrição: função responsável por imprimir a lista.
Entrada: ponteiro para a lista.
Saída: nada.
*/
void imprimeLista(const lista *list);

/*
Descrição: função responsável por esvaziar a lista, e liberar ela.
Entrada: ponteiro para a lista.
Saída: nada.
*/
void destroiLista(lista *list);

#endif //LISTA_H
