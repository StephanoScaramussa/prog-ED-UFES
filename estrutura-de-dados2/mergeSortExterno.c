#include <stdio.h>
#define MAX_MEMORIA 100
#define MAX_RUNS 20
void merge(int v[], int ini, int meio, int fim) {
    int aux[MAX_MEMORIA];
    int i = ini, j = meio + 1, k = 0;
    while (i <= meio && j <= fim) {
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    }
    while (i <= meio)
        aux[k++] = v[i++];

    while (j <= fim)
        aux[k++] = v[j++];

    for (i = ini, k = 0; i <= fim; i++, k++)
        v[i] = aux[k];
}
void mergeSort(int v[], int ini, int fim) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        mergeSort(v, ini, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, ini, meio, fim);
    }
}
int criaRuns(const char *entrada, int tamBloco) {
    FILE *in = fopen(entrada, "r");
    int memoria[MAX_MEMORIA];
    int qtdRuns = 0, i;
    while (!feof(in)) {
        int count = 0;
        while (count < tamBloco && fscanf(in, "%d", &memoria[count]) == 1)
            count++;
        if (count > 0) {
            mergeSort(memoria, 0, count - 1);
            char nome[20];
            sprintf(nome, "run%d.txt", qtdRuns);
            FILE *out = fopen(nome, "w");
            for (i = 0; i < count; i++)
                fprintf(out, "%d ", memoria[i]);
            fclose(out);
            qtdRuns++;
        }
    }
    fclose(in);
    return qtdRuns;
}
void mergeArquivos(const char *a, const char *b, const char *saida) {
    FILE *fa = fopen(a, "r");
    FILE *fb = fopen(b, "r");
    FILE *fs = fopen(saida, "w");
    int x, y;
    int ha = fscanf(fa, "%d", &x);
    int hb = fscanf(fb, "%d", &y);
    while (ha == 1 && hb == 1) {
        if (x <= y) {
            fprintf(fs, "%d ", x);
            ha = fscanf(fa, "%d", &x);
        } else {
            fprintf(fs, "%d ", y);
            hb = fscanf(fb, "%d", &y);
        }
    }
    while (ha == 1) {
        fprintf(fs, "%d ", x);
        ha = fscanf(fa, "%d", &x);
    }
    while (hb == 1) {
        fprintf(fs, "%d ", y);
        hb = fscanf(fb, "%d", &y);
    }
    fclose(fa);
    fclose(fb);
    fclose(fs);
}
void mergeExterno(int qtdRuns) {
    int i;
    int novaQtd = 0;
    for (i = 0; i < qtdRuns; i += 2) {
        char a[20], b[20], s[20];
        sprintf(a, "run%d.txt", i);
        if (i + 1 < qtdRuns) {
            sprintf(b, "run%d.txt", i + 1);
            sprintf(s, "run_merge%d.txt", novaQtd);
            mergeArquivos(a, b, s);
        } else {
            sprintf(s, "run_merge%d.txt", novaQtd);
            mergeArquivos(a, a, s);
        }
        novaQtd++;
    }
    if (novaQtd > 1)
        mergeExterno(novaQtd);
}
int main() {
    int tamBloco;
    printf("Digite o tamanho do bloco de memoria: ");
    scanf("%d", &tamBloco);
    if (tamBloco > MAX_MEMORIA) {
        printf("Tamanho excede memoria maxima.\n");
        return 1;
    }
    int qtdRuns = criaRuns("entrada.txt", tamBloco);
    mergeExterno(qtdRuns);
    printf("Ordenacao externa concluida.\n");
    printf("Arquivo final: run_merge0.txt\n");
    return 0;
}
