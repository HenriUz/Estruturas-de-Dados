/*
Fila.h

Descrição: definição das funções da fila.
*/

/* --- Estruturas. --- */

typedef struct fila fila;

typedef struct elemento elemento;

/* --- Funções. --- */

/*
Descrição: função responsável por criar e inicializar uma estrutura de fila.
Entrada: nada.
Saída: ponteiro para a fila.
*/
fila *criaFila();

/*
Descrição: função responsável por retornar o estado da fila.
Entrada: ponteiro para a fila.
Saída: 1 - vazia, 0 - não vazia.
*/
int filaVazia(fila *f);

/*
Descrição: função responsável por inserir um elemento na fila.
Entrada: ponteiro para a fila, inteiro que será inserido.
Saída: 1 - sucesso, 0 - erro.
*/
int insereFila(fila *f, int dado);

/*
Descrição: função responsável por remover um elemento da fila.
Entrada: ponteiro para a fila.
Saída: elemento no início da fila, 0 pode indicar que a fila está vazia.
*/
int removeFila(fila *f);
