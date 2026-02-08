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

void intercalarMarge(int vet[], int ini, int meio, int fim, unsigned long* troc, unsigned long* compare){
    int i = ini;
    int j = meio + 1;
    int k = 0;

    int *tmp = (int*) malloc((fim - ini + 1) * sizeof(int));

    while (i <= meio || j <= fim) {
        *compare += 1;
        if (i == meio + 1){
            tmp[k++] = vet[j++];
            *troc += 1;
        }else if(j == fim + 1){
            tmp[k++] = vet[i++];
            *troc += 1;
        }else if(vet[j] < vet[i]){
            tmp[k++] = vet[j++];
            *troc += 1;
        }else{
            tmp[k++] = vet[i++];
            *troc += 1;
        }

    }

    for (i = ini, k = 0; i <= fim; i++, k++) {
        *troc += 1;
        vet[i] = tmp[k];
    }

    free(tmp);
}

double mergeSort(int vet[], int ini, int fim, unsigned long* troc, unsigned long* compare){
    clock_t inicio, end;
    double temp;
    
    inicio = clock();
    int meio;
    
    if (ini < fim){  
        meio = (ini + fim)/2;
        mergeSort(vet, ini, meio,troc, compare);
        mergeSort(vet, meio + 1, fim, troc, compare);
        intercalarMarge(vet, ini, meio, fim, troc, compare) ;
    }
    end = clock();
    temp = (double)(end - inicio)/CLOCKS_PER_SEC;

    return temp;
}

int main(){
    int *vet = geraVetor(N);
    unsigned long comp = 0, tr = 0;
    double temp = mergeSort(vet, 0, N-1, &tr, &comp);
    printf("HeapSort: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp, tr, comp);
    free(vet);
    return 0;
}