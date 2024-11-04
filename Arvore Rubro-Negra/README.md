# Árvore Rubro-Negra
A Árvore Rubro-Negra é uma das variações da estrutura de dados árvore que garante o balanceamento de seus elementos. Ela foi inventada 10 anos após a criação da Árvore AVL, 1972, por Rudolf Bayer, sob o nome de B-árvores binárias simétricas. Foi em 1978 que ela ganhou seu nome atual por Leo J. Guibas e Robert Sedgewick. 

O fator de balanceamento dessa árvore é a cor dos nós, atributo extra de cada nó, que pode ser vermelho ou preto (por isso o nome). O interessante dessa árvore é que sua altura máxima é $2 * \log_2(n+1)$.

> [!NOTE]
> Esse tipo de árvore é aproximadamente balanceada, pois ela permite leves desbalanceamentos.

## Propriedades
Além das propriedades de uma árvore binária, as árvores rubros-negras devem satisfazer as seguintes condições: 
1. Todo nó é vermelho ou preto.
2. A raiz da árvore é preta.
3. Se um nó é vermelho, seus filhos são pretos.
4. Para cada nó, todos os caminhos até as folhas contém o mesmo número de nós pretos.

O número de nós pretos de um caminho desde um nó x, sem incluir ele, até uma folha é chamado de altura de preto.

## Funcionamento
Assim como a Árvore AVL, esta árvore contém as operações básicas de uma árvore binária, mais as operações necessárias para verificar e corrigir desbalanceamentos.

### Desbalanceamento na inserção
Por padrão, todo novo nó na árvore é vermelho, e por isso 2 propriedades podem ser quebradas. A primeira é a raiz ser preta, pois o novo nó pode se tornar a nova raiz, e a segunda é os filhos de um nó vermelho ser preto, pois o novo nó pode ser filho desse de um nó vermelho.

Então, analisando essas quebras da propriedade, podemos assumir 3 casos para corrigir essa situação:
1. O tio do elemento avaliado é vermelho.
2. O tio do elemento avaliado é preto, e o elemento avaliado é um filho a direita.
3. O tio do elemento avaliado é preto, e o elemento avaliado é um filho a esquerda.

No final da correção, a raiz é colorida de preto para garantir a propriedade.

> [!IMPORTANT]
> Esses casos, bem como as soluções, se espelham dependendo do lado da árvore.

- Caso 1: neste caso devemos fazer o pai e o tio ficarem pretos, o avô ficar vermelho, e por fim analisar o avô recursivamente.
- Caso 2: neste caso devemos fazer uma rotação para à esquerda no pai, que irá se tornar o elemento avaliado, e iremos ao caso 3.
- Caso 3: neste último caso devemos fazer o pai ficar preto, o avô vermelho, e uma rotação à direita no avô.

### Resumindo
Para elementos avaliados a esquerda do avô:
| Caso | Cor do Tio | Filho | Ações |
| ---- | ---------- | ----- | ----- |
| 1 | Vermelho | Direita ou Esquerda | Pai e Tio pretos / Avô vermelho / nova avaliação em cima do avô. |
| 2 | Preto | Direita | Rotação à esquerda no Pai / Pai se torna novo elemento avaliado / Caso 3 |
| 3 | Preto | Esquerda | Pai preto / Avô vermelho / Rotação à direita no avô |
| 1,2,3 | - | - | Raiz preto |

Para elementos avaliados a direita do avô:
| Caso | Cor do Tio | Filho | Ações |
| ---- | ---------- | ----- | ----- |
| 1 | Vermelho | Direita ou Esquerda | Pai e Tio pretos / Avô vermelho / nova avaliação em cima do avô. |
| 2 | Preto | Direita | Rotação à direita no Pai / Pai se torna novo elemento avaliado / Caso 3 |
| 3 | Preto | Esquerda | Pai preto / Avô vermelho / Rotação à esquerda no avô |
| 1,2,3 | - | - | Raiz preto |

## Desbalanceamento na remoção
Como sempre, a remoção é sempre um pouco mais complexa do que a inserção. Na remoção devemos pensar na cor do elemento que estamos removendo, pois na remoção de um nó vermelho nenhuma propriedade é quebrada, mas por outro lado, a remoção de um nó preto pode quebrar 3 propriedades, a primeira é a da raiz ser preta, a segunda é um nó vermelho ter somente filhos pretos, e a terceira é a quantidade de nós pretos ser a mesma nos diferentes caminhos até a raiz.

Com isso, temos quatro casos para se analisar (8 se considerarmos que é espelhado):
1. Irmão é vermelho.
2. Irmão é preto, e ambos os seus filhos são pretos.
3. Irmão é preto, e seu filho esquerdo é vermelho e o direito é preto.
4. Irmão é preto, e seu filho direito é vermelho.

- Caso 1: neste caso, o irmão se torna preto, o pai se torna vermelho, rotação à esquerda no pai, levando aos outros casos.
- Caso 2: neste caso, o irmão se torna vermelho, e analisa o pai recursivamente.
- Caso 3: neste caso, o irmão se torna vermelho, e rotação à direita no irmão, levando ao caso 4.
- Caso 4: neste caso, o irmão fica na cor do pai, o pai do elemento se torna pret, o filho direito do irmão também se torna preto, e por fim rotação à esquerda no pai do elemento.

### Resumindo
Para elementos avaliados a esquerda do pai:
| Situação | Elemento | Sucessor | Irmão | Ações |
| -------- | -------- | -------- | ----- | ----- |
| 1 | Vermelho | - | - | Nada |
| 2 | Preto | Vermelho | - | Sucessor preto |
| 3 | Preto | Preto | Vermelho | Irmão preto / Pai vermelho / Rotação à esquerda no pai / Irmão passa a ser o filho direito do pai / Casos 2,3 ou 4 |
| 3 | Preto | Preto | Preto e ambos os filhos pretos | Irmão vermelho / Pai preto |
| 3 | Preto | Preto | Preto e filho da esquerda vermelho e direita preto | Filho esquerdo do irmão preto / Irmão vermelho / Rotação à direita no irmão / Caso 4 |
| 3 | Preto | Preto | Preto e filho direito vermelho | Irmão cor do pai / Pai preto / Filho direito do irmão preto / Rotação à esquerda no pai |

Para elementos avaliados a direita do pai:
| Situação | Elemento | Sucessor | Irmão | Ações |
| -------- | -------- | -------- | ----- | ----- |
| 1 | Vermelho | - | - | Nada |
| 2 | Preto | Vermelho | - | Sucessor preto |
| 3 | Preto | Preto | Vermelho | Irmão preto / Pai vermelho / Rotação à direita no pai / Irmão passa a ser o filho esquerdo do pai / Casos 2,3 ou 4 |
| 3 | Preto | Preto | Preto e ambos os filhos pretos | Irmão vermelho / Pai preto |
| 3 | Preto | Preto | Preto e filho da direita vermelho e esquerda preto | Filho direito do irmão preto / Irmão vermelho / Rotação à esquerda no irmão / Caso 4 |
| 3 | Preto | Preto | Preto e filho esquerdo vermelho | Irmão cor do pai / Pai preto / Filho esquerdo do irmão preto / Rotação à direita no pai |

## Objetivo
Este repositório tem o objetivo de mostrar o funcionamento de uma Árvore Rubro-Negra por meio da implementação de uma interface por terminal.
