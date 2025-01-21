# Lista Simples
Lista é uma estrutura de dados que permite a preservação de uma ordem linear que existe entre os dados, no caso implementado é a ordem crescente. O motivo do nome conter `Simples` é pela forma como essa lista foi implementada, que consiste em fazer cada elemento da lista apontar diretamente para o próximo elemento. Porém, existem muitas outras formas de implementar uma lista, por exemplo, a lista duplamente encadeada, que consiste em cada elemento apontar para o próximo e o anterior, outro exemplo pode ser a lista circular, que consiste em fazer a lista não ter um fim, ou seja, o elemento no final aponta para o elemento no começo.

Um exemplo de aplicação das listas, é a memória heap, mais especificamente nas `bins`. Simplificando, as `bins` são vetores que armazenam listas em seus elementos, a função deles é armazenar pedaços de memória de mesmo tamanho em um mesmo elemento, e para isso acabam gerando uma lista.

## Funcionamento
As operações principais de uma lista são: criação, inserção, remoção, e busca. Mas, existem outras operações que podem ser implementadas dependendo do contexto, como operações de impressão e de esvaziar a lista.

O comportamento dessa lista tende a ser `O(n)`, pois todas as suas operações, no pior dos casos, terão que percorrer todos os elementos. Porém, ela pode ser modificada para algumas operações funcionarem em complexidade `O(1)`, por exemplo, se a ordem dos elementos não importa, a inserção pode inserir um novo elemento diretamente no começo da lista.

## Objetivo
Este código tem o objetivo de mostrar o funcionamento de uma lista simples por meio da implementação de uma interface por terminal.
