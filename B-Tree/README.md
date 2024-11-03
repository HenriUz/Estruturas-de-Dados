# B-Tree
São uma generalização das árvores binárias de busca, pois cada nó de uma árvore binária armazena uma única chave de busca, enquanto as B-Tree armazenam um número maior de chaves em cada nó, ou no termo mais usual para essa árvore, em cada página. As B-Tree são árvores de pesquisa balanceadas projetadas para funcionar bem em discos magnéticos ou outros dispositivos de armazenamento secundário de acesso direto, sendo otimizadas para minizar operações de E/S do disco. A ideia é fazer com que cada nó da árvore contenha tanta informação quanto a que cabe num bloco de disco. 

A consequência disso tudo é que, em geral, a B-Tree possui grande largura e pouca profundidade, diminuindo o número de E/S do disco.

## Propriedades

- Ordem: quantidade máxima de filhos que uma página pode conter (dependendo da paridade, a ordem de algumas operações mudam).
- Grau mínimo (t): define os limites inferiores e superiores sobre o número de chaves (número máximo de chaves = $`2*t - 1`$, número mínimo de chaves = $`t - 1`$).

## Objetivo
Este repositório tem o objetivo de armazenar uma B-Tree funcional para ordens pares, além de também conter a implementação de testes comparativos entre o tempo de busca em um arquivo olhando linha por linha (direto) e usando a linha armazenada na B-Tree (índice).

## Organização
- ArvoreB: implementação da B-Tree.
- Datasets: datasets para os testes (o número antes do `.txt` indica a quantidade de elementos).
- ES: implementação dos geradores de datasets.
- Resultados: resultados dos testes (o número antes do `-` indica qual dataset foi utilizado e o número após indica quantas buscas foram realizadas).
- main.c: implementação de uma interface por terminal para o gerenciamento da B-Tree e realização dos testes.
