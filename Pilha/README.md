# Pilha
Pilha é uma das estruturas de dados mais simples que existem, mas o domínio sobre seu funcionamento é de extrema importância, visto que os programas (`.elf, .exe, ...`) usam a pilha para gerenciar variáveis, gerenciar chamadas de funções e muito mais. 

> [!IMPORTANT]
> Pela pilha ser um estrutura simples, ela acaba sendo alvo de diversos ataques como `Ret2win` ou `Ret2libc`. Claro que há diversas proteções, como `PIE` e `NX`, que são implementadas na compilação de um código, mas fique sempre atento se seu código permite um estouro de buffer ou não.

## Objetivo
Este código tem o objetivo de mostrar como usar uma pilha para converter número decimais positivos para binário. Porém a estrutura de pilha implementada funciona para qualquer inteiro. 

## Funcionamento
Como o próprio nome diz, essa estrutura simula uma pilha. Aqui as operações possíveis são empilhar (colocar algo no topo) e desempilhar (tirar algo do topo), ambas de complexidade `O(1)`. Note que todas as operações são feitas à partir do topo, então a primeira coisa para se ter em mente é ter o controle sobre quem é o topo da pilha.

Com o controle do topo, o resto da implementação depende de como o programador vai querer gerenciar sua pilha. No caso dos programas executáveis a pilha é uma região contínua de memória, então eles subtraem o valor do registrador `rsp` para criar espaço na pilha. Nesse caso, cada elemento da pilha é um chunk da heap, então para criar mais espaço é só criar outro chunk.

> [!NOTE]
> Nessa implementação os dados que serão empilhados são inteiros e podem ser tanto positivos quanto negativos, por isso também foi implementado a variável de erro.
