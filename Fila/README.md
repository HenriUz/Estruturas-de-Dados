# Fila
Assim como a pilha, a fila também é uma das estruturas de dados mais simples que existem. Como o próprio nome diz, a estrutura simula uma fila, comportamento `FIFO`, em que os elementos são removidos pelo começo e adicionados pelo fim.

Mesmo sendo uma estrutura simples, seu domínio é muito importante, pois diversos algoritmos e aplicações fazem uso dela. Um exemplo é o algoritmo de escalanomento de processos conhecido como `FIFO` ou `FCFS`.

## Funcionamento
As operações principais de uma fila são enfileirar (colocar algo no fim) e desenfileirar (tirar algo do início), perceba que as operações trabalham em lados opostos da fila, fazendo-se necessário ter o controle sobre o início e o fim. É interessante notar que ter o controle sobre ambos os lados da fila garante que ambas as operações sejam de complexidade `O(1)`.

> [!important]
> A fila implementada é para inteiros, então qualquer número inteiro pode ser devolvido na função `removeFila(fila *f)`. Foi estabelecido que a função irá retornar 0 caso a fila esteja vazia, então é necessário verificar a situação da fila quando um 0 for retornado.
>
> O correto na verdade, é verificar se a fila está vazia antes de chamar a função, pois se a fila tiver um único elemento, e esse elemento for 0, um falso erro será identificado.

## Objetivo
Este código tem o objetivo de mostrar o funcionamento de uma fila por meio da implementação de uma interface por terminal.
