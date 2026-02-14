#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50
#define M 101

typedef struct No {
    int valor;
    struct No* prox;
} No;

void inicializaTabela(No* tabela[]) {
    for (int i = 0; i < M; i++) {
        tabela[i] = NULL;
    }
}

int funcaoHash(int chave) {
    return chave % M;
}

void insereEncadeado(No* tabela[], int chave) {
    int idx = funcaoHash(chave);
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = chave;
    novo->prox = tabela[idx];
    tabela[idx] = novo;
}

No* buscaEncadeado(No* tabela[], int chave) {
    int idx = funcaoHash(chave);
    No* atual = tabela[idx];
    while (atual != NULL) {
        if (atual->valor == chave) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void geraChaves(int* chaves) {
    for (int i = 0; i < N; i++) {
        chaves[i] = rand() % 1000;
    }
}

void imprimeTabela(No* tabela[]) {
    for (int i = 0; i < M; i++) {
        if (tabela[i] != NULL) {
            printf("[%d]: ", i);
            No* atual = tabela[i];
            while (atual != NULL) {
                printf("%d -> ", atual->valor);
                atual = atual->prox;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    srand(time(NULL));
    int chaves[N];
    No* tabelaHash[M];
    geraChaves(chaves);
    inicializaTabela(tabelaHash);
    for (int i = 0; i < N; i++) {
        insereEncadeado(tabelaHash, chaves[i]);
    }
    printf("--- Tabela Hash (Encadeada) ---\n");
    imprimeTabela(tabelaHash);
    int chaveTeste = chaves[N-1];
    No* resultado = buscaEncadeado(tabelaHash, chaveTeste);
    if(resultado != NULL)
        printf("\nSucesso: Chave %d encontrada no endereco de memoria %p\n", chaveTeste, (void*)resultado);
    else
        printf("\nChave nao encontrada.\n");
    return 0;
}