# Árvore Binária de Busca
Servem para armazenar dados na memória principal, e são estruturas muito eficientes para a busca de dados. Essas árvores são representadas por um conjunto finito de `nós` que ou está vazia ou consiste de um elemento chamado `raiz` mais os elementos das subárvores esquerda e direita da `raiz`.
Dessa forma cada `nó` contém uma chave, podendo ser um estrutura caso queira armazenar mais dados, e no máximo duas subárvores.

## Propriedades
- Todos os elementos da subárvore esquerda possuem elementos menores do que a `raiz`.
- Todos os elementos da subárvore direita possuem elementos maiores do que a `raiz`.
- Grau: número de subárvores de um `nó`. Caso seja `0` o `nó` é chamado de folha ou externo.
- Altura: comprimento do caminho mais longo da raiz até uma de suas folhas. A altura da raiz é 0, e a altura de uma árvore vazia é -1. Dessa forma podemos falar que o nível de cada `nó` é a distância (ou posição que ele está no caminho até a folha) dele até a raiz.

## Classificação
- Estritamente binária: possui somente `nós` de grau 2 ou 0.
- Completa: se existe `nós` de grau 0, eles estão no penúltimo ou último nível.
- Cheia: se existe `nós` de grau 0, eles estão no último nível.
- Degenerada: árvore totalmente desbalanceada, tornando-se uma lista de complexidade O(n).
  
> [!NOTE]
> Vale notar que a árvore cheia é a árvore ideal, pois sua complexidade é O($`\log_2(n)`$), e quantidade de `nós` em cada nível pode ser calculada por $`2^{nível}`$.
