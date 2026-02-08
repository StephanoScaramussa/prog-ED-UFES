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

double bolhaParada(int vet[], int size, unsigned long* troc, unsigned long* compare){
    clock_t inicio, fim;
    double temp;

    inicio = clock();
    int indice = size - 1;
    bool mudou = true;
    while(mudou){
        int j = 1;
        mudou = false;
        while(j < size){
            *compare += 1;
            if(vet[j-1] > vet[j]){
                *troc += 1;
                int auxiliar = vet[j - 1];
                vet[j - 1] = vet[j];
                vet[j] = auxiliar;
                mudou = true;
            }
            indice = j;
            j = j + 1;
        }
        size = indice;
    }
    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;
    return temp;
}

double insercaoDireta(int vet[], int size, unsigned long* troc, unsigned long* compare){
    clock_t inicio, fim;
    double temp;
    inicio = clock();
    for (int i = 1; i < size; i++) {
        int chave = vet[i];
        int j = i - 1;
        while (j >= 0) {
            *compare += 1;
            if(vet[j] > chave){
                *troc += 1;
                vet[j + 1] = vet[j];
                j--;
            }else{
                break;
            }
        }
        vet[j + 1] = chave;
    }
    *compare += 1;
    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;
    return temp;
}

int main(){
    int *vet = geraVetor(N);
    int *vet2 = geraVetor(N);
    unsigned long comp1 = 0, tr1 = 0, comp2=0, tr2=0;
    double temp1 = bolhaParada(vet, N, &tr1, &comp1), temp2 = insercaoDireta(vet2, N, &tr2, &comp2);
    printf("Bolha(parada): Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp1, tr1, comp1);
    printf("Insercao direta: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp2, tr2, comp2);
    free(vet);
    free(vet2);
    return 0;
}