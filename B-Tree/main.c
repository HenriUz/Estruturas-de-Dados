/*
main.c

Descrição: código responsável por lidar com os inputs do usuário, por fornecer as funções de busca, e por informar o tempo de cada operação de busca.
*/

/* --- Includes. --- */

#include "ArvoreB/ArvoreB.h"
#include "ES/ES.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* --- Estruturas. --- */

typedef struct registro {
    char nome[6], dataNasc[11]; //Nome (por padrão são todos de 5 caracteres), data de nascimento (será lida como string).
    int mat; //Número de matrícula.
    long long int cpf; //Cpf.
}registro;

typedef struct metricas {
    double tempoMax, tempoMin; //Maior tempo de busca, menor tempo de busca.
    float media; //Média entre todos os tempos de busca.
}metricas;

/* --- Funções. --- */

/*
Descrição: função responsável por fazer a busca por uma matrícula usando o índice.
Entrada: ponteiro para o arquivo, inteiro da linha onde se encontra o registro.
Saída: nada.
*/
void buscaIndice(FILE *arq, const int linha) {
    registro reg;
    char line[100];
    int tam;
    /* Colocando o ponteiro do arquivo no início. */
    rewind(arq);
    /* Lendo uma linha até o \n e contando o seu tamanho. */
    fgets(line, 100, arq);
    tam = (int)strlen(line);
    /* Procurando a posição no arquivo (o +1 provavelmente é por causa do \r). */
    fseek(arq, (tam + 1) * linha, SEEK_SET);
    /* Lendo os dados da posição. */
    fscanf(arq, "%d %s %s %lld", &reg.mat, reg.nome, reg.dataNasc, &reg.cpf);
    printf("\nNome: %s -- Cpf: %lld -- Data de Nascimento: %s -- Matrícula: %d", reg.nome, reg.cpf, reg.dataNasc, reg.mat);
}

/*
Descrição: função responsável por fazer a busca diretamente no arquivo fornecido.
Entrada: ponteiro para o arquivo, inteiro da matrícula que se deseja buscar.
Saída: nada.
*/
void buscaDireta(FILE *arq, const int mat) {
    registro reg;
    /* Setando condição de parada. */
    reg.mat = -1;
    /* Colocando o ponteiro do arquivo no início. */
    rewind(arq);
    /* Procurando posição no arquivo. */
    while(!feof(arq) && reg.mat != mat) {
        fscanf(arq, "%d %s %s %lld", &reg.mat, reg.nome, reg.dataNasc, &reg.cpf);
        if(reg.mat == mat) {
            printf("\nNome: %s -- Cpf: %lld -- Data de Nascimento: %s -- Matrícula: %d", reg.nome, reg.cpf, reg.dataNasc, reg.mat);
        }
    }
}

int main(void) {
    arvore *arv;
    FILE *arq, *res = NULL; //Arquivo do dataset, e arquivo dos resultados.
    metricas direta, indice;
    clock_t inicio, fim;
    int resp, linha, mat, tamDat = 0, aux; //Resposta do usuário, linha do registro no arquivo, matrícula que será removida, ou buscada, tamanho do dataset, auxiliar para retornos de funções e operações de média.
    double tempo;
    char dataset[50], path[190] = "path";
    char line[100], pathR[190] = "path";
    /* Identificando o dataset. */
    printf("\nVocê deseja criar um novo dataset?\nResposta (Sim - 1, Não - 0): ");
    scanf("%d", &resp);
    printf("\nDigite o nome do dataset (com o .txt): ");
    scanf(" %49s", dataset);
    strcat(path, dataset); //Concatenando o nome do arquivo com o caminho para a pasta dele.
    if(resp) {
        /* Criando um novo dataset, com a quantidade de linhas fornecida pelo usuário. */
        printf("\nDigite quantas linhas você deseja no dataset: ");
        scanf("%d", &tamDat);
        arq = fopen(path, "w+");
        if(!arq) {
            printf("\nNão foi possível criar o arquivo.");
            return 1;
        }
        criaDataset(arq, tamDat);
    }else {
        /* Abrindo um dataset existente. */
        arq = fopen(path, "r");
        if(!arq) {
            printf("\nNão foi possível ler o arquivo.");
            return 1;
        }
        /* Contando quantas linhas tem o arquivo. */
        while(fgets(line, 100, arq)) {
            tamDat++;
        }
    }
    /* Iniciando árvore-b */
    printf("\nDigite a ordem da árvore-b (somente ordens pares): ");
    scanf("%d", &resp);
    if(resp % 2 != 0) {
        printf("\nOrdem não par!");
        return 1;
    }
    arv = criaArvore(resp);
    if(!arv) {
        return 1;
    }
    /* Iniciando interface. */
    printf("\nMENU:\n1 - Criar indices.\n2 - Remover.\n3 - Busca.\n4 - Imprimir.\n5 - Sair.\nSua resposta: ");
    scanf("%d", &resp);
    while(resp != 5) {
        switch (resp) {
            case 1:
                /* Inserindo elementos do dataset na árvore. */
                if(!processaCarga(arv, arq)) {
                    printf("\nErro na criação da árvore.");
                }
                break;
            case 2:
                /* Removendo elemento da árvore. */
                printf("\nInforme qual matrícula você deseja remover: ");
                scanf("%d", &mat);
                aux = deleta(arv, mat);
                if(aux == -1) {
                    printf("\nÁrvore vazia.");
                }else if(aux == 0) {
                    printf("\nElemento não encontrado.");
                }else {
                    printf("\nElemento removido com sucesso.");
                }
                printf("\n");
                break;
            case 3:
                /* Buscando elemento na árvore. */
                printf("\n1 - Busca específica.\n2 - Elementos aleatórios.\nSua resposta: ");
                scanf("%d", &resp);
                if(resp == 1) {
                    /* Realizando uma busca específica, aqui não importa as métricas de tempo. */
                    printf("\nInforme qual matrícula você deseja buscar: ");
                    scanf("%d", &mat);
                    linha = busca(arv, mat);
                    if(linha == -1) {
                        printf("\nElemento não encontrado na árvore.");
                    }else {
                        printf("\nRealizando a busca pelo indice.");
                        buscaIndice(arq, linha);
                        printf("\nRealizando a busca direta.");
                        buscaDireta(arq, mat);
                    }
                    printf("\n");
                }else {
                    /* Realizando buscas aleatórias, aqui as métricas de tempo importam. */
                    srand(time(NULL));
                    /* Setando as métricas. */
                    direta.media = direta.tempoMax = direta.tempoMin = 0;
                    indice.media = indice.tempoMax = indice.tempoMin = 0;
                    aux = 0; //Servirá para corrigir na hora de calcular a média (caso um elemento não seja encontrado.)
                    printf("\nInforme quantas buscas aleatórias você deseja buscar: ");
                    scanf("%d", &resp);
                    for(int i = 0; i < resp; i++) {
                        /* Gerando matrícula aleatória. */
                        mat = rand() % tamDat;
                        /* Início da busca pela árvore. */
                        inicio = clock();
                        linha = busca(arv, mat);
                        if(linha == -1) {
                            //Elemento não encontrado, então não continua a busca e aumenta aux.
                            printf("\nElemento não encontrada, busca %d não realizada.", i);
                            aux++;
                        }else {
                            buscaIndice(arq, linha);
                            fim = clock();
                            /* Fim da busca pela árvore, atualizando métricas. */
                            tempo = (fim - inicio)/(CLOCKS_PER_SEC/1000);
                            if(tempo > indice.tempoMax) {
                                indice.tempoMax = tempo;
                            }else if(tempo < indice.tempoMin || indice.tempoMin == 0) {
                                indice.tempoMin = tempo;
                            }
                            indice.media += tempo;
                            /* Início da busca direta. */
                            inicio = clock();
                            buscaDireta(arq, mat);
                            fim = clock();
                            /* Fim da busca direta, atualizando métricas. */
                            tempo = (fim - inicio)/(CLOCKS_PER_SEC/1000);
                            if(tempo > direta.tempoMax) {
                                direta.tempoMax = tempo;
                            }else if(tempo < direta.tempoMin || direta.tempoMin == 0) {
                                direta.tempoMin = tempo;
                            }
                            direta.media += tempo;
                        }
                    }
                    /* Fazendo a média. */
                    indice.media /= resp - aux;
                    direta.media /= resp - aux;
                    /* Escrevendo os resultados em um arquivo. */
                    printf("\nBuscas realizadas!\nDigite o nome do arquivo de resultados (com o .txt): ");
                    scanf(" %49s", dataset);
                    strcat(pathR, dataset); //Concatenando o nome do arquivo com o caminho para a pasta dele.
                    res = fopen(pathR, "w");
                    if(!res) {
                        printf("\nErro ao criar o arquivo de resultados.");
                    }else {
                        fprintf(res, "%s\n%s: %f\n%s: %f\n%s: %f\n", "Resultados da busca por indice:", "Tempo Máximo", indice.tempoMax, "Tempo Mínimo", indice.tempoMin, "Média", indice.media);
                        fprintf(res, "\n%s\n%s: %f\n%s: %f\n%s: %f\n", "Resultados da busca direta:", "Tempo Máximo", direta.tempoMax, "Tempo Mínimo", direta.tempoMin, "Média", direta.media);
                    }
                    fclose(res);
                    res = NULL;
                }
                break;
            case 4:
                /* Imprimindo a árvore. */
                imprimeArvore(getRaiz(arv), 0);
                break;
            default:
                break;
        }
        printf("\nMENU:\n1 - Criar indices.\n2 - Remover.\n3 - Busca.\n4 - Imprimir.\n5 - Sair.\nSua resposta: ");
        scanf("%d", &resp);
    }
    /* Fechando arquivos. */
    fclose(arq);
    arq = NULL;
    free(arv);
    arv = NULL;
    return 0;
}
