# Árvore Binária de Busca
Serve para armazenar dados na memória principal, é um estrutura muito eficientes para representar relações de hierarquia e para buscar dados. 

Uma árvore é representada por um conjunto finito de nós que ou está vazio ou consiste de um elemento chamado raiz mais os elementos das subárvores esquerda e direita da raiz. Dessa forma cada nó contém uma chave e no máximo duas subárvores.

## Propriedades
- Todos os elementos da subárvore esquerda possuem elementos menores do que a raiz.
- Todos os elementos da subárvore direita possuem elementos maiores do que a raiz.
- Grau: número de subárvores de um nó. Caso seja 0 o nó é chamado de folha ou externo.
- Altura: comprimento do caminho mais longo da raiz até uma de suas folhas descendentes.
- Nível: número de ligações de um nó até a raiz da árvore, serve para denotar a profundidade do nó. O nível da raiz é zero.

## Classificação
- Estritamente binária: possui somente nós de grau 2 ou 0.
- Completa: se existe nós de grau 0, eles estão no penúltimo ou último nível.
- Cheia: se existe nós de grau 0, eles estão no último nível.
- Degenerada: árvore totalmente desbalanceada, tornando-se uma lista de complexidade O(n).
  
> [!NOTE]
> Vale notar que a árvore cheia é a árvore ideal, sua complexidade é O( $\log_2(n)$ ). A quantidade de nós por nível pode ser calculada por $2^{nível}$, e a altura por $\log_2(n+1) - 1$.

## Funcionamento
As operações principais de uma árvore são a inserção (adicionar uma folha), remoção (remover um nó), busca, e impressão da árvore. 

Das 4 operações citadas, a remoção é a que se deve tomar mais cuidado, pois dependendo da quantidade de filhos que o nó possui, a forma de se remover muda. Por exemplo, um nó com nenhum filho é simplesmente removido desvinculando ele do pai, mas um nó com dois filhos é necessário realizar outra estratégia, como cópia de predecessor ou sucessor.

Por fim, a impressão pode ser feita de 3 maneiras:

- Em ordem: imprime subárvore esquerda, depois a raiz, e por fim a subárvore direita.
- Pré-ordem: imprime a raiz, depois a subárvore esquerda, e por fim a subárvore direita.
- Pós-ordem: imprime a subárvore direita, depois a raiz, e por fim a subárvore esquerda.

## Objetivo
Este repositório tem o objetivo de mostrar o funcionamento de uma árvore binária comum por meio da implementação de uma interface por terminal.
