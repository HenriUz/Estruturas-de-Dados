# B-Tree
## Objetivo
O objetivo deste repositório é mostrar a estrutura de dados da B-Tree funcionando em ordens pares, e realizar testes comparativos entre o tempo de busca em um arquivo de texto olhando linha por linha (direto) e usando a linha armazenada na B-Tree (indice).

## Organização
- ArvoreB: Contém os arquivos `.c` e `.h` da estrutura de dados da árvore b.
- Datasets: Contém os arquivos de texto usados como datasets para o teste. O número antes do `.txt` indica a quantidade de elementos.
- ES: Contém os arquivos `.c` e `.h` do código responsável por gerar os datasets.
- Resultados: Contém os arquivos de texto que armazenam os resultados dos testes. O número antes do `-` indica qual dataset foi utilizado e o número após indica quantas buscas foram realizadas.
- main.c: Código responsável por tratar as entradas do usuário e os resultados das operações.
