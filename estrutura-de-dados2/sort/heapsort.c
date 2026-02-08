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

void criaHeap(int vet[], int ini, int fim, unsigned long* troc, unsigned long* compare){
    int auxiliar = vet[ini];
    int j = ini*2 + 1;

    while(j <= fim){
        //*compare += 1;
        if(j < fim){
            *compare += 1;
            if(vet[j] < vet[j + 1]){
                j += 1;
            }
        }
        if(auxiliar < vet[j]){
            *troc += 1;
            vet[ini] = vet[j];
            ini = j;
            j = 2*ini + 1;   
        }else{
            j = fim + 1;
        }
    }
    vet[ini] = auxiliar;
}

double heapSort(int vet[], int size, unsigned long* troc, unsigned long* compare){

    clock_t inicio, fim;
    double temp;

    inicio = clock();
    int aux;
    for(int i = (size - 1)/2; i >= 0; i--){
        criaHeap(vet, i, size - 1, troc, compare);
    }

    for(int i = size - 1; i > 0; i--){
        *troc += 1;
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;

        criaHeap(vet, 0, i - 1, troc, compare);
    }
    fim = clock();

    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;
    return temp;
}

int main(){
    int *vet = geraVetor(N);
    unsigned long comp = 0, tr = 0;
    double temp = heapSort(vet, N, &tr, &comp);
    printf("HeapSort: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp, tr, comp);
    free(vet);
    return 0;
}