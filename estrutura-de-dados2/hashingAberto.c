#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50
#define M 101

void inicializaTabela(int* tabela) {
    for (int i = 0; i < M; i++) {
        tabela[i] = -1;
    }
}

int funcaoHash(int chave) {
    return chave % M;
}

void insereAberto(int* tabela, int chave) {
    int idx = funcaoHash(chave);
    while (tabela[idx] != -1) {
        idx = (idx + 1) % M;
    }
    tabela[idx] = chave;
}

int buscaAberto(int* tabela, int chave) {
    int idx = funcaoHash(chave);
    int startIdx = idx;
    while (tabela[idx] != -1) {
        if (tabela[idx] == chave) {
            return idx;
        }
        idx = (idx + 1) % M;
        if (idx == startIdx) break;
    }
    return -1;
}

void geraChaves(int* chaves) {
    for (int i = 0; i < N; i++) {
        chaves[i] = rand() % 1000;
    }
}

int main() {
    srand(time(NULL));
    int chaves[N];
    int tabelaHash[M];
    geraChaves(chaves);
    inicializaTabela(tabelaHash);
    for (int i = 0; i < N; i++) {
        insereAberto(tabelaHash, chaves[i]);
    }

    double fc = (double)N / M;
    printf("Fator de Carga: %.2f\n", fc);

    int chaveTeste = chaves[0];
    int pos = buscaAberto(tabelaHash, chaveTeste);
    
    if(pos != -1)
        printf("Chave %d encontrada na posicao %d\n", chaveTeste, pos);
    else
        printf("Chave nao encontrada.\n");

    return 0;
}