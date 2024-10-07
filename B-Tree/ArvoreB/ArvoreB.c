/*
ArvoreB.c

Descrição: implementação das funções da árvore-b.
*/

/* --- Includes. --- */

#include "ArvoreB.h"
#include <stdlib.h>

/* --- Estruturas. --- */

struct arvore {
    pagina *raiz; //Raiz da árvore.
    int ordem; //Ordem da árvore.
    int numElementos; //Quantidade de elementos na árvore.
};

struct pagina {
    chave **chaves; //Chaves armazenadas (ponteiro de ponteiro para ter mais controle sobre os elementos).
    pagina **filhos; //Filhos da página.
    pagina *pai; //Pai da página.
    int folha; //1 - folha, 0 - não é folha.
    int numChaves; //Quantidade de chaves na página.
};

struct chave {
    int matricula; //Matrícula.
    int linha; //Linha no arquivo.
};

/* --- Funções. --- */

arvore *criaArvore(int ordem) {
    /* Criando a árvore. */
    arvore *arv = (arvore*)malloc(sizeof(arvore));
    if(!arv) {
        return NULL;
    }
    /* Setando valores iniciais. */
    arv->ordem = ordem;
    arv->numElementos = 0;
    arv->raiz = NULL;
    return arv;
}

pagina *getRaiz(arvore *arv) {
    return arv->raiz;
}

int getNumElementos(arvore *arv) {
    return arv->numElementos;
}

int getOrdem(arvore *arv) {
    return arv->ordem;
}

pagina *criaPagina(int maximoElementos) {
    /* Criando a página. */
    pagina *page = (pagina*)malloc(sizeof(pagina));
    if(!page) {
        return NULL;
    }
    /* Criando as listas de ponteiros. */
    page->chaves = (chave**)malloc(sizeof(chave*) * maximoElementos);
    if(!page->chaves) {
        free(page);
        return NULL;
    }
    page->filhos = (pagina**)malloc(sizeof(pagina*) * (maximoElementos + 1));
    if(!page->filhos) {
        free(page->chaves);
        free(page);
        return NULL;
    }
    /* Setando valores. */
    page->numChaves = 0;
    //O restante dos elementos deve ser setados na função em que foi chamada.
    /* Fazendo os ponteiros da lista apontarem para nada. */
    for(int i = 0; i < maximoElementos; i++) {
        page->chaves[i] = NULL;
        page->filhos[i] = NULL;
    }
    page->filhos[maximoElementos] = NULL;
    return page;
}

pagina *criaRaiz(arvore *arv, pagina *filhoD, chave *key) {
    /* Criando a página. */
    pagina *raiz = criaPagina(arv->ordem - 1);
    if(!raiz) {
        return NULL;
    }
    /* Setando valores. */
    raiz->pai = NULL; //Raiz não tem pai.
    raiz->chaves[0] = key;
    raiz->numChaves++;
    if(filhoD) {
        raiz->folha = 0; //Se o filho existe, não é uma folha.
    }else {
        raiz->folha = 1; //Se o filho não existe, é uma folha.
    }
    /* Vinculando as páginas. */
    raiz->filhos[0] = arv->raiz; //Por padrão o filho esquerdo é a antiga raiz.
    raiz->filhos[1] = filhoD;
    if(raiz->filhos[0]) {
        raiz->filhos[0]->pai = raiz;
        raiz->filhos[1]->pai = raiz;
    }
    return raiz;
}

void insereNaPagina(pagina *page, pagina *filhoD, chave *newChave, int pos) {
    /* Deslocando os elementos para a direita. */
    for(int i = page->numChaves; i > pos; i--) {
        page->chaves[i] = page->chaves[i-1];
        page->filhos[i+1] = page->filhos[i];
    }
    /* Inserindo na página. */
    page->chaves[pos] = newChave;
    page->filhos[pos+1] = filhoD;
    if(page->filhos[pos+1]) {
        page->filhos[pos+1]->pai = page;
    }
    page->numChaves++;
}

void split(arvore *arv, pagina *page, pagina *filhoD, pagina **salvaFilhoD, chave *newChave, chave **salvaChave, int pos) {
    int posMediana = page->numChaves/2;
    /* Criando a nova página. */
    *salvaFilhoD = criaPagina(page->numChaves); //Criando a nova página, que consequentemente se tornará o novo filho direito para o pai.
    if(!*salvaFilhoD) {
        return;
    }
    /* Setando os valores iniciais. */
    (*salvaFilhoD)->pai = page->pai;
    (*salvaFilhoD)->folha = page->folha;
    /* Deslocando os elementos da página cheia para a nova página. */
    for(int i = posMediana + 1; i < page->numChaves; i++) {
        (*salvaFilhoD)->chaves[i - posMediana - 1] = page->chaves[i];
        (*salvaFilhoD)->filhos[i - posMediana - 1] = page->filhos[i];
        if(page->filhos[i]) {
            page->filhos[i]->pai = *salvaFilhoD;
        }
        page->chaves[i] = NULL;
        page->filhos[i] = NULL;
    }
    (*salvaFilhoD)->filhos[posMediana] = page->filhos[page->numChaves];
    if((*salvaFilhoD)->filhos[posMediana]) {
        (*salvaFilhoD)->filhos[posMediana]->pai = *salvaFilhoD;
    }
    page->filhos[page->numChaves] = NULL;
    /* Atualizando a quantidade de chaves em cada página. */
    page->numChaves -= posMediana;
    (*salvaFilhoD)->numChaves = posMediana;
    /* Inserindo o elemento na página correta. */
    if(pos <= posMediana) {
        //Se a posição é igual ou menor do que a posição mediana, o elemento deve ser inserido na página que estava cheia.
        insereNaPagina(page, filhoD, newChave, pos);
    }else {
        //Se a posição é maior do que a posição da mediana, o elemento deve ser inserido na nova página.
        insereNaPagina(*salvaFilhoD, filhoD, newChave, pos - posMediana - 1);
    }
    /* Fazendo a chave mediana se tornar a nova chave para o pai. */
    *salvaChave = page->chaves[page->numChaves-1];
    page->chaves[page->numChaves-1] = NULL;
    page->numChaves--;
}

int procuraPaginaI(arvore *arv, pagina *page, pagina **filhoD, chave *newChave, chave **salvaChave) {
    int pos;
    if(!page) {
        //Se a página for nula, significa que chegamos em uma folha e devemos inserir na folha (ou criar uma raiz se a árvore estiver vazia).
        *filhoD = NULL;
        return 1;
    }
    /* Procurando o filho/posição onde a chave será inserida. */
    for(pos = 0; pos < page->numChaves && newChave->matricula > page->chaves[pos]->matricula; pos++);
    /* Verificando se devemos inserir (chegamos em uma folha, ou ocorreu uma operação de split em um dos filhos). */
    if(procuraPaginaI(arv, page->filhos[pos], filhoD, newChave, salvaChave)) {
        if(page->numChaves < arv->ordem - 1) {
            //Página ainda tem espaço.
            insereNaPagina(page, *filhoD, *salvaChave, pos);
        }else {
            //Página está cheia, devemos realizar o split.
            split(arv, page, *filhoD, filhoD, *salvaChave, salvaChave, pos);
            return 1;
        }
    }
    return 0;
}

int insere(arvore *arv, int mat, int linha) {
    pagina *filhoD, *raiz; //Ponteiro que irá salvar o filho direito, e ponteiro que irá salvar a raiz anterior.
    chave *newChave = (chave*)malloc(sizeof(chave)); //Nova chave.
    chave **salvaChave = &newChave; //Ponteiro que salva a chave.
    if(!newChave) {
        return 0;
    }
    newChave->linha = linha;
    newChave->matricula = mat;
    /* Inserindo o novo elemento. */
    if(procuraPaginaI(arv, arv->raiz, &filhoD, newChave, salvaChave)) {
        //A árvore está vazia ou a raiz sofreu um split.
        raiz = arv->raiz;
        arv->raiz = criaRaiz(arv, filhoD, *salvaChave);
        if(!arv->raiz) {
            //Um erro ocorreu na alocação de memória. Recriando raiz até não ocorrer mais erros.
            while(!arv->raiz) {
                arv->raiz = raiz;
                arv->raiz = criaRaiz(arv, filhoD, *salvaChave);
            }
        }
    }
    arv->numElementos++;
    return 1;
}

int processaCarga(arvore *arv, FILE *dataset) {
    /* Simulando o registro da main para a leitura da linha. */
    char nome[6], dataNasc[11];
    int mat, i = 0;
    long long int cpf;
    /* Colocando o ponteiro do arquivo no início. */
    rewind(dataset);
    /* Inserindo na árvore. */
    while(!feof(dataset)) {
        //Se a fscanf identificar que a linha acabou antes de converter tudo, não insere.
        if(fscanf(dataset, "%d %s %s %lld", &mat, nome, dataNasc, &cpf) != EOF) {
            if(!insere(arv, mat, i++)) {
                return 0;
            }
        }
    }
    return 1;
}

void copiaPredecessor(pagina *page, int pos) {
    /* Procurando o predecessor. */
    pagina *filho = page->filhos[pos];
    while(!filho->folha) {
        filho = filho->filhos[filho->numChaves];
    }
    /* Fazendo a cópia por valor. */
    page->chaves[pos]->matricula = filho->chaves[filho->numChaves - 1]->matricula;
    page->chaves[pos]->linha = filho->chaves[filho->numChaves - 1]->linha;
}

void removeDaPagina(pagina *page, int pos) {
    chave *aux = page->chaves[pos];
    /* Deslocando valores. */
    for(int i = pos; i < page->numChaves - 1; i++) {
        page->chaves[i] = page->chaves[i+1];
    }
    /* Removendo o valor. */
    page->chaves[page->numChaves - 1] = NULL;
    page->numChaves--;
    free(aux);
    aux = NULL;
}

void merge(pagina *pai, int pos) {
    pagina *filhoE = pai->filhos[pos - 1], *filhoD = pai->filhos[pos];
    /* Descendo o pai. */
    filhoE->chaves[filhoE->numChaves] = pai->chaves[pos-1];
    filhoE->numChaves++;
    /* Jogando os elementos do filho direito. */
    filhoE->filhos[filhoE->numChaves] = filhoD->filhos[0];
    if(filhoE->filhos[filhoE->numChaves]) {
        filhoE->filhos[filhoE->numChaves]->pai = filhoE;
    }
    for(int i = 0; i < filhoD->numChaves; i++){
        filhoE->chaves[filhoE->numChaves++] = filhoD->chaves[i];
        filhoE->filhos[filhoE->numChaves] = filhoD->filhos[i+1];
        if(filhoE->filhos[filhoE->numChaves]) {
            filhoE->filhos[filhoE->numChaves]->pai = filhoE;
        }
    }
    /* Deslocando elementos na página pai. */
    for(int i = pos - 1; i < pai->numChaves - 1; i++) {
        pai->chaves[i] = pai->chaves[i+1];
        pai->filhos[i+1] = pai->filhos[i+2];
    }
    pai->chaves[pai->numChaves - 1] = NULL;
    pai->filhos[pai->numChaves] = NULL;
    pai->numChaves--;
    /* Liberando o filho direito e retornando. */
    free(filhoD->chaves);
    free(filhoD->filhos);
    free(filhoD);
    filhoD = NULL;
}

void emprestaDireita(pagina *pai, int pos) {
    pagina *filhoE = pai->filhos[pos], *filhoD = pai->filhos[pos+1];
    /* Descendo o pai. */
    filhoE->chaves[filhoE->numChaves] = pai->chaves[pos];
    /* Fazendo o filho mais à esquerda da página direita, se tornar o filho mais à direita da página esquerda. */
    filhoE->filhos[++filhoE->numChaves] = filhoD->filhos[0];
    if(filhoE->filhos[filhoE->numChaves]) {
        filhoE->filhos[filhoE->numChaves]->pai = filhoE;
    }
    /* Jogando elemento para o pai. */
    pai->chaves[pos] = filhoD->chaves[0];
    /* Deslocando elementos no filho direito. */
    filhoD->numChaves--;
    for(int i = 0; i < filhoD->numChaves; i++) {
        filhoD->chaves[i] = filhoD->chaves[i+1];
        filhoD->filhos[i] = filhoD->filhos[i+1];
    }
    filhoD->filhos[filhoD->numChaves] = filhoD->filhos[filhoD->numChaves + 1];
    filhoD->chaves[filhoD->numChaves] = NULL;
    filhoD->filhos[filhoD->numChaves + 1] = NULL;
}

void emprestaEsquerda(pagina *pai, int pos) {
    pagina *filhoE = pai->filhos[pos-1], *filhoD = pai->filhos[pos];
    /* Deslocando elementos do filho direito. */
    for(int i = filhoD->numChaves; i > 0; i--) {
        filhoD->chaves[i] = filhoD->chaves[i-1];
        filhoD->filhos[i+1] = filhoD->filhos[i];
    }
    filhoD->filhos[1] = filhoD->filhos[0];
    /* Jogando elementos para o filho direito. */
    filhoD->chaves[0] = pai->chaves[pos-1];
    filhoD->filhos[0] = filhoE->filhos[filhoE->numChaves];
    if(filhoD->filhos[0]) {
        filhoD->filhos[0]->pai = filhoD;
    }
    filhoD->numChaves++;
    /* Jogando elemento para o pai. */
    pai->chaves[pos-1] = filhoE->chaves[--filhoE->numChaves];
    /* Removendo elemento do filho esquerdo. */
    filhoE->chaves[filhoE->numChaves] = NULL;
    filhoE->filhos[filhoE->numChaves+1] = NULL;
}

void corrigiFilho(arvore *arv, pagina *pai, int pos) {
    /* Verificando onde está o filho com a quantidade abaixo do mínimo. */
    if(!pos) {
        //Filho é o mais a esquerda, então só pode emprestar do irmão direito ou dar merge.
        if(pai->filhos[pos+1]->numChaves > arv->ordem/2 - 1) {
            emprestaDireita(pai, pos);
        }else {
            merge(pai, 1);
        }
    }else {
        if(pos == pai->numChaves) {
            //Filho é o mais a direita, então só pode emprestar do irmão esquerdo ou dar merge.
            if(pai->filhos[pos-1]->numChaves > arv->ordem/2 - 1) {
                emprestaEsquerda(pai, pos);
            }else {
                merge(pai, pos);
            }
        }else {
            //Filho está no meio, pode emprestar de ambos os irmãos ou dar merge.
            if(pai->filhos[pos-1]->numChaves > arv->ordem/2 - 1) {
                emprestaEsquerda(pai, pos);
            }else if(pai->filhos[pos + 1]->numChaves > arv->ordem/2 - 1) {
                emprestaDireita(pai, pos);
            }else {
                merge(pai, pos);
            }
        }
    }
}

int procuraPaginaD(arvore *arv, pagina *page, int mat) {
    int cond = 0, pos;
    if(page) {
        /* Procurando elemento. */
        for(pos = 0; pos < page->numChaves && mat > page->chaves[pos]->matricula; pos++);
        if(pos < page->numChaves && mat == page->chaves[pos]->matricula) {
            cond = 1;
        }
        /* Verificando o que fazer. */
        if(cond) {
            //Elemento está na página atual, então se não for folha copia o predecessor e remove recursivamente, e se for folha remove.
            if(!page->folha) {
                copiaPredecessor(page, pos);
                cond = procuraPaginaD(arv, page->filhos[pos], page->chaves[pos]->matricula);
            }else {
                removeDaPagina(page, pos);
                arv->numElementos--;
            }
        }else {
            //Elemento não está na página atual, continua procurando.
            cond = procuraPaginaD(arv, page->filhos[pos], mat);
        }
        if(!page->folha) {
            //Se o filho no qual foi removido o elemento estiver com a quantidade de elementos abaixo do mínimo, corrige.
            if(page->filhos[pos]->numChaves < arv->ordem/2 - 1) {
                corrigiFilho(arv, page, pos);
            }
        }
    }
    return cond;
}

int deleta(arvore *arv, int mat) {
    pagina *aux;
    int cond;
    /* Verificando condições. */
    if(arv->numElementos) {
        //Árvore não está vazia, procurando elemento.
        cond = procuraPaginaD(arv, arv->raiz, mat);
        if(cond) {
            //Elemento removido com sucesso, verificando se a raiz não ficou vazia.
            if(!arv->raiz->numChaves) {
                //Raiz vazia, por padrão a nova raiz será o filho esquerdo.
                aux = arv->raiz;
                arv->raiz = arv->raiz->filhos[0];
                if(arv->raiz) {
                    arv->raiz->pai = NULL;
                }
                free(aux->chaves);
                free(aux->filhos);
                free(aux);
                aux = NULL;
            }
        }
        return cond;
    }
    return -1;
}

int busca(arvore *arv, int mat) {
    pagina *aux, *atual = arv->raiz;
    int linha = -1;
    /* Iniciando a busca. */
    while(atual) {
        aux = atual;
        /* Percorrendo os elementos da página. */
        for(int i = 0; aux == atual && i < atual->numChaves; i++) {
            if(mat < atual->chaves[i]->matricula) {
                //Elemento é menor, então entra no filho esquerdo.
                atual = atual->filhos[i];
            }else if(mat == atual->chaves[i]->matricula) {
                //Elemento é igual, salva a linha e anula o atual para sair do for e do while.
                linha = atual->chaves[i]->linha;
                atual = NULL;
            }else if(i == atual->numChaves - 1) {
                //Se estamos na última iteração do for, e não entramos em nenhuma condição anterior, então entra no último filho.
                atual = atual->filhos[atual->numChaves];
            }
        }
    }
    return linha;
}

void imprimeArvore(pagina *page, int nivel) {
    if(page) {
        printf("\n%d - Número de Elementos: %d - Elementos: ", nivel, page->numChaves);
        for(int i = 0; i < page->numChaves; i++) {
            printf("%d ", page->chaves[i]->matricula);
        }
        printf("- Folha: %d", page->folha);
        if(page->pai) {
            printf(" - Pai: %d", page->pai->chaves[0]->matricula);
        }
        for(int i = 0; i <= page->numChaves; i++) {
            imprimeArvore(page->filhos[i], nivel+1);
        }
    }
}
