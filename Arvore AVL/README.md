# Árvore AVL
Árvores Binárias podem apresentar o comportamento de uma lista (`O(n)`) caso elas estajam totalmente desbalanceadas, por exemplo uma árvore resultante da inserção de elementos ordenados. Então, em 1962, foi apresentado um modelo de "arvore avl" por Adelson-Velskii e Landis. Esse modelo mostra uma árvore de pesquisa binária de altura balanceada, ou seja, para cada `nó` x as alturas das subárvores direita e esquerda se diferem por no máximo 1.

Para representar isso, cada `nó` guarda seu fator de balanceamento (`fb`), e no caso será considerado que o `fb` é a altura da subárvore direita menos a altura da subárvore esquerda.
> [!note]
> Para o balanceamento de uma árvore é sempre importante considerar as seguintes condições:
> Não balancear: aumenta o tempo médio de pesquisa
> Balancear sempre: alto custo computacional, e árvore sempre cheia.
> Bom balanceamento: permite um pouco de desbalanceamento.

## Desbalanceamento
Uma `Árvore AVL` pode se tornar desbalanceada em 2 situações (na realidade são 4, mas são simétricas 2 a 2):
- O `nó` inserido é descendente direito de um `nó` com `fb` igual a 1.
- O `nó` inserido é descendente esquerdo de um `nó` com `fb` igual a -1.

### Rotações
Quando um `nó` se torna desbalanceado, rotações são aplicadas para que a `árvore` volte a ser balanceada. As rotações podem ser para a esquerda (`fb` positivo) ou para direita (`fb` negativo), e em alguns casos ainda podem ser aplicadas rotações duplas, para esquerda e depois direita, ou para direita e depois para a esquerda. As rotações seguem a seguinte tabela:
| Diferença de altura no nó | Diferença de altura no filho do nó | Rotação |
| ------------------------- | ---------------------------------- | ------- |
| 2 | 1 ou 0 | Simples para a esquerda |
| 2 | -1 | Dupla: direita - esquerda |
| -2 | 1 | Dupla: esquerda - direita |
| -2 | 0 ou -1 | Simples para a direita |

### Ajuste no FB
Após realizar uma rotação, os fatores de balanceamento de cada `nó` envolvido deve ser ajustado seguindo a seguinte tabela:
| Nó Antes | Filho Antes | Neto Antes | Rotação | Nó Depois | Filho Depois | Neto Depois |
| -------- | ----------- | ---------- | ------- | --------- | ------------ | ----------- |
| -2 | -1 | | Simples para a direita | 0 | 0 | |
| -2 | 0 | | Simples para a direita | -1 | 1 | |
| 2 | 1 | | Simples para a esquerda | 0 | 0 | |
| 2 | 0 | | Simples para a esquerda | 1 | -1 | |
| -2 | 1 | 0 | Dupla: esquerda - direita | 0 | 0 | 0 |
| -2 | 1 | -1| Dupla: esquerda - direita | 1 | 0 | 0 |
| -2 | 1 | 1 | Dupla: esquerda - direita | 0 | -1 | 0 |
| 2 | -1 | 0 | Dupla: direita - esquerda | 0 | 0 | 0 |
| 2 | -1 | -1 | Dupla: direita - esquerda | 0 | 1 | 0 |
| 2 | -1 | 1 | Dupla: direita - esquerda | -1 | 0 | 0 |

> [!important]
> A remoção na `Árvore AVL` pode necessitar de mais de uma rotação, então sua complexidade é O($`k * log (n)`$)

## Links para visualização
https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
