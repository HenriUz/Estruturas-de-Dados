/*
Pilha.h

Descrição: definição das funções e estruturas de uma pilha.

Importante: essa pilha funciona por meio da heap (alocação dinâmica), então na memória os elementos não estarão em sequência. A ideia aqui é apenas representar o funcionamento da estrutura de dados pilha, que os programas usam para armazenar variáveis, e outros valores importantes.
*/

/* --- Estruturas. --- */

typedef struct Pilha Pilha;

typedef struct Elemento Elemento;

/* --- Funções. --- */

/*
Descrição: função responsável por criar e inicializar uma estrutura Pilha.
Entrada: nada.
Saída: ponteiro para a Pilha criada.
*/
Pilha *criaPilha();

/*
Descrição: função responsável por retornar o valor armazenado na variável erro da Pilha.
Entrada: ponteiro para a Pilha.
Saída: inteiro do erro.
*/
int getErro(Pilha *p);

/*
Descrição: função que retorna o estado da pilha.
Entrada: ponteiro para a pilha.
Saída: 1 - vazia, 0 - com elementos.
*/
int pilhaVazia(Pilha *p);

/*
Descrição: função responsável por empilhar o valor passado na pilha informada.
Entrada: ponteiro para a Pilha, inteiro do valor.
Saída: 1 - empilhado com sucesso, 0 - erro ao empilhar.
*/
int push(Pilha *p, int valor);

/*
Descrição: função responsável por desempilhar o valor que está no topo da pilha informada.
Entrada: ponteiro para a Pilha.
Saída: valor que estava no topo.
*/
int pop(Pilha *p);
