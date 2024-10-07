# Árvore Rubro-Negra
As árvores rubros-negras são uma das variações da estrutura de dados árvore que garante o balanceamento de seus elementos. Ela foi inventada 10 anos após a criação da árvore avl, 1972, por Rudolf Bayer, sob o nome de B-árvores binárias simétricas. Foi em 1978 que ela ganhou seu nome atual por Leo J. Guibas e Robert Sedgewick. 

O fator de balanceamento dessa árvore é a cor dos nós, atributo extra de cada nó, que pode ser vermelho ou preto (por isso o nome). O interessante dessa árvore é que sua altura máxima é `2 * log₂(n+1)`.

> [!NOTE]
> Esse tipo de árvore é aproximadamente balanceada, pois ela permite leves desbalanceamentos.

## Propriedades
As árvores rubros-negras devem satisfazer as seguintes condições: 
1. Todo nó é vermelho ou preto.
2. A raiz da árvore é preta.
3. Se um nó é vermelho, seus filhos são pretos.
4. Para cada nó, todos os caminhos até as folhas contém o mesmo número de nós pretos.

O número de nós pretos de um caminho desde um nó x, sem incluir ele, até uma folha é chamado de altura de preto.

## Desbalanceamento na inserção
Por padrão, todo novo nó na árvore é vermelho, e por isso 2 propriedades podem ser quebradas. A primeira é a raiz ser preta, pois o novo nó pode se tornar a nova raiz, e a segunda é os filhos de um nó vermelho ser preto, pois o novo nó pode ser filho desse de um nó vermelho.

Então, analisando essas quebras da propriedade, podemos assumir 3 casos para corrigir essa situação:
1. O tio do elemento avaliado é vermelho.
2. O tio do elemento avaliado é preto, e o elemento avaliado é um filho a direita.
3. O tio do elemento avaliado é preto, e o elemento avaliado é um filho a esquerda.

No final da correção, a raiz é colorida de preto para garantir a propriedade.

> [!IMPORTANT]
> Esses casos, bem como as soluções, se espelham dependendo do lado da árvore.

### Caso 1
Nesse caso devemos fazer o pai e o tio ficarem pretos, o avô ficar vermelho, e por fim analisar o avô recursivamente.

### Caso 2
Nesse caso devemos fazer uma rotação para à esquerda no pai, que irá se tornar o elemento avaliado, e iremos ao caso 3.

### Caso 3
Nesse último caso devemos fazer o pai ficar preto, o avô vermelho, e uma rotação à direita no avô.

### Resumindo
Para elementos avaliados a esquerda do avô:
| Caso | Cor do Tio | Filho | Ações |
| ---- | ---------- | ----- | ----- |
| 1 | Vermelho | Direita ou Esquerda | Pai e Tio pretos \ Avô vermelho \ nova avaliação em cima do avô. |
| 2 | Preto | Direita | Rotação à esquerda no Pai \ Pai se torna novo elemento avaliado \ Caso 3 |
| 3 | Preto | Esquerda | Pai preto \ Avô vermelho \ Rotação à direita no avô |
| 1,2,3 | - | - | Raiz preto |

Para elementos avaliados a direita do avô:
| Caso | Cor do Tio | Filho | Ações |
| ---- | ---------- | ----- | ----- |
| 1 | Vermelho | Direita ou Esquerda | Pai e Tio pretos \ Avô vermelho \ nova avaliação em cima do avô. |
| 2 | Preto | Direita | Rotação à direita no Pai \ Pai se torna novo elemento avaliado \ Caso 3 |
| 3 | Preto | Esquerda | Pai preto \ Avô vermelho \ Rotação à esquerda no avô |
| 1,2,3 | - | - | Raiz preto |
