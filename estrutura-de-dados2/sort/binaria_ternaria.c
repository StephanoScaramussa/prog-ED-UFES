#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define N 50000

int* geraVetor(int size){
    int *vet = (int*) malloc(size * sizeof(int));
    for(int i=0; i<size; i++){
        vet[i] = rand() % 100;
    }
    return vet;
}

double insercaoBinaria(int vet[], int size, unsigned long* troc, unsigned long* compare){
    clock_t inicio, fim;
    double temp;

    inicio = clock();
    int auxiliar, esq, dir, meio;
    for (int i = 1; i < size; i++) {
        auxiliar = vet[i];
        esq = 0;
        dir = i - 1;

        while (esq <= dir) {
            meio = (esq + dir) / 2;
            *compare += 1;
            if (auxiliar > vet[meio]){
                esq = meio + 1;
            } else {
                dir = meio - 1;
            }
        }

        for (int j = i; j > esq; j--) {
            *troc += 1;
            vet[j] = vet[j - 1];
        }

        vet[esq] = auxiliar;
    }
    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

double insercaoTernaria(int vet[], int size, unsigned long* troc, unsigned long* compare){

    clock_t inicio, fim;
    double temp;

    inicio = clock();
    int auxiliar, esq, dir, m1, m2;
    for (int i = 1; i < size; i++) {
        auxiliar = vet[i];
        esq = 0;
        dir = i - 1;

        while (esq <= dir) {
            m1 = esq + (dir - esq) / 3;
            m2 = dir - (dir - esq) / 3;

            *compare += 1;
            if (auxiliar < vet[m1]) {
                dir = m1 - 1;
            } 
            else{
                *compare += 1;
                if (auxiliar > vet[m2]) {
                    esq = m2 + 1;
                } 
                else {
                    esq = m1 + 1;
                    dir = m2 - 1;
                }
            }
        }

        for (int j = i; j > esq; j--) {
            *troc += 1;
            vet[j] = vet[j - 1];
        }

        vet[esq] = auxiliar;
    }
    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

int main(){
    int *vet = geraVetor(N);
    int *vet2 = geraVetor(N);
    unsigned long comp1 = 0, tr1 = 0, comp2=0, tr2=0;
    double temp1 = insercaoBinaria(vet, N, &tr1, &comp1), temp2 = insercaoTernaria(vet2, N, &tr2, &comp2);
    printf("Insercao binaria: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp1, tr1, comp1);
    printf("Insercao ternaria: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp2, tr2, comp2);
    free(vet);
    free(vet2);
    return 0;
}