# B-Tree
São uma generalização das árvores binárias de busca, pois cada nó de uma árvore binária armazena uma única chave de busca, enquanto as B-Tree armazenam um número maior de chaves em cada nó, ou no termo mais usual para essa árvore, em cada página. 

As B-Tree são árvores de pesquisa balanceadas projetadas para funcionar bem em discos magnéticos ou outros dispositivos de armazenamento secundário de acesso direto, sendo otimizadas para minizar operações de E/S do disco. A ideia é fazer com que cada página da árvore contenha tanta informação quanto a que cabe num bloco de disco. 

A consequência disso tudo é que, em geral, a B-Tree possui grande largura e pouca profundidade, diminuindo o número de E/S do disco.

> [!note]
> A altura máxima de uma B-Tree em seu pior caso é $h \leq \log_t(\frac{n + 1}{2})$, em que t é o grau mínimo e n é o número de páginas.

## Propriedades

- A raiz deve ter pelo menos 2 filhos, a menos que seja folha.
- Ordem (m): quantidade máxima de filhos que uma página intermediária pode conter (dependendo da paridade, a ordem de algumas operações mudam).
- Grau mínimo (t): define os limites inferiores e superiores sobre o número de chaves que uma página pode conter (número máximo de chaves = $`2*t - 1`$, número mínimo de chaves = $`t - 1`$).
- Cada página interna contém k filhos, e consequentemente $k - 1$ chaves, sendo $\lfloor \frac{m}{2} \rfloor \leq k \leq m$.

> [!important]
> Uma página intermediária é uma página que não é raiz e nem folha.

## Estrutura de uma página
Uma página na B-Tree contém o número de chaves armazenadas, as chaves, os ponteiros para os filhos, e pode conter uma indicação se é folha ou não. Claro que as páginas folhas podem ser feitas em outra estrutura, mas isso aumentaria a complexidade do código.

```
(n), (leaf)
+---+----------+---+----------+---+----------+---+
| f |   chave  | f |   chave  | f |   chave  | f |
+---+----------+---+----------+---+----------+---+

f = ponteiro para o filho.
n = número de chaves
leaf = folha ou não
```

## Funcionamento
Assim como qualquer árvore, as operações principais são a inserção, remoção, e busca. Porém, como a B-Tree não é uma árvore binária, algumas operações adicionais são necessárias.

A inserção necessita de operações adicionais porque 3 casos podem acontecer. O 1º é a folha ter espaço para o novo elemento, aí é só inserir. O 2º é a folha não ter espaço para inserir, mas o pai tem, então cria um novo filho para o pai, dividindo a folha em duas e subindo um elemento para o pai (operação split). E por fim o 3º é o pai também não ter espaço, então repete-se recursivamente a subdivisão. 

Além disso, a operação split varia de acordo com a ordem da árvore. Se a ordem for par, há um número ímpar de elementos, e a divisão da folha acontece facilmente. Se a ordem for ímpar, há um número par de elementos, causando uma dificuldade na divisão da folha (solução é implementar um espaço extra em uma página). Por fim, há uma variação que realiza o split enquanto desce na árvore (preemptive split).

A remoção é parecida com as remoções das árvores binárias, se o elemento está em uma folha, remove ele, se ele estiver em uma página intermediária, remove por cópia. Mas é necessário ficar esperto, pois se a folha ficar com menos do que $t - 1$ elementos, é necessário reorganizar a árvore, juntando folhas, ou emprestando elementos.

## Objetivo
Este repositório tem o objetivo de armazenar uma B-Tree funcional para ordens pares, além de também conter a implementação de testes comparativos entre o tempo de busca em um arquivo olhando linha por linha (direto) e usando a linha armazenada na B-Tree (índice).

## Organização
- ArvoreB: implementação da B-Tree.
- Datasets: datasets para os testes (o número antes do `.txt` indica a quantidade de elementos).
- ES: implementação dos geradores de datasets.
- Resultados: resultados dos testes (o número antes do `-` indica qual dataset foi utilizado e o número após indica quantas buscas foram realizadas).
- main.c: implementação de uma interface por terminal para o gerenciamento da B-Tree e realização dos testes.
