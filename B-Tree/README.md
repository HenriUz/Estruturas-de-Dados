# B-Tree
São uma generalização das árvores binárias de busca, pois cada nó de uma árvore binária armazena uma única chave de busca, enquanto as árvores B armazenam um número maior de chaves em cada nó, ou no termo mais usual para essa árvore, em cada página. As árvores B são árvores de pesquisa balanceadas projetadas para funcionar bem em discos magnéticos ou outros dispositivos de armazenamento secundário de acesso direto, sendo otimizadas para minizar operações de E/S do disco. A ideia é fazer com que cada nó da árvore contenha tanta informação quanto a que cabe num bloco de disco. 

A consequência disso tudo é que, em geral, a árvore B possui grande largura e pouca profundidade, diminuindo o número de E/S do disco.

Algumas propriedades da árvore B são a ordem e o grau mínimo. A ordem é a quantidade máxima de filhos que uma página pode conter, e o grau mínimo (t) é um inteiro que define os limites inferiores e superiores sobre o número de chaves (número máximo de chaves = 2t – 1, número mínimo de chaves = t-1). A paridade da ordem faz com que seja necessário mudar a ordem de algumas funções.

## Objetivo
O objetivo deste repositório é mostrar a estrutura de dados da B-Tree funcionando em ordens pares, e realizar testes comparativos entre o tempo de busca em um arquivo de texto olhando linha por linha (direto) e usando a linha armazenada na B-Tree (indice).

## Organização
- ArvoreB: Contém os arquivos `.c` e `.h` da estrutura de dados da árvore b.
- Datasets: Contém os arquivos de texto usados como datasets para o teste. O número antes do `.txt` indica a quantidade de elementos.
- ES: Contém os arquivos `.c` e `.h` do código responsável por gerar os datasets.
- Resultados: Contém os arquivos de texto que armazenam os resultados dos testes. O número antes do `-` indica qual dataset foi utilizado e o número após indica quantas buscas foram realizadas.
- main.c: Código responsável por tratar as entradas do usuário e os resultados das operações.
