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

double shellSort(int vet[], int size, unsigned long* troc, unsigned long* compare) {

    clock_t inicio, fim;
    double tempo;

    int h = 1, auxiliar, j;

    while (h < size) {
        h = 3 * h + 1;
    }

    inicio = clock();

    while (h > 1) {
        h = h / 3;

        for (int i = h; i < size; i++) {
            auxiliar = vet[i];
            j = i - h;

            while (j >= 0) {
                (*compare)++;               
                if (auxiliar < vet[j]) {
                    vet[j + h] = vet[j];
                    (*troc)++;                 
                    j -= h;
                } else {
                    break;
                }
            }
            vet[j + h] = auxiliar;             
        }
    }

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    return tempo;
}

double selectionSort(int vet[], int size, unsigned long* troc, unsigned long* compare){

    clock_t inicio, fim;
    double temp;

    inicio = clock();
    int min, aux;
    for (int i = 0; i < size - 1; i++) {
        min = i;

        for (int j = i + 1; j < size; j++) {
            *compare += 1;              
            if (vet[j] < vet[min]) {
                min = j;
            }
        }

        if (min != i) {
            aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
            *troc += 1;                   
        }
    }
    fim = clock();

    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;
    return temp;
}

int main(){
    int *vet = geraVetor(N);
    int *vet2 = geraVetor(N);
    unsigned long comp1 = 0, tr1 = 0, comp2=0, tr2=0;
    double temp1 = shellSort(vet, N, &tr1, &comp1), temp2 = selectionSort(vet2, N, &tr2, &comp2);
    printf("ShellSort: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp1, tr1, comp1);
    printf("SelectionSort: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp2, tr2, comp2);
    free(vet);
    free(vet2);
    return 0;
}