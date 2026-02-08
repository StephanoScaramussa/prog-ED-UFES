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

int getMax(int vet[], int n){
    int max = vet[0];
    for (int i = 1; i < n; i++){
        if (vet[i] > max){
            max = vet[i];
        }
    }
    return max;
}

void countSort(int vet[], int n, int exp, unsigned long* troc){
    int output[n];

    int i, count[10] = { 0 };

    for (i = 0; i < n; i++){
        count[(vet[i] / exp) % 10]++;

    }

    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        output[count[(vet[i] / exp) % 10] - 1] = vet[i];
        count[(vet[i] / exp) % 10]--;
        (*troc) += 1;
    }

    for (i = 0; i < n; i++) {
        vet[i] = output[i];
        (*troc) += 1;
    }
}


double radixSort(int vet[], int size, unsigned long* troc, unsigned long* compare){
    clock_t inicio, fim;
    double temp;
    
    inicio = clock();
    int maximo = getMax(vet, size);

    for(int exp = 1; maximo/exp > 0; exp *= 10){
        countSort(vet, size, exp, troc);
    }
    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

double bucketSort(int vet[], int size, unsigned long* troc, unsigned long* compare) {
    clock_t inicio, fim;
    double temp;

    inicio = clock();

    if (size <= 1) {
        fim = clock();
        return (double)(fim - inicio)/CLOCKS_PER_SEC;
    }

    int max = vet[0];
    for (int i = 1; i < size; i++) {
        (*compare)++;
        if (vet[i] > max)
            max = vet[i];
    }

    int *count = (int *)calloc(size, sizeof(int));
    if (count == NULL) return 0.0;

    for (int i = 0; i < size; i++) {
        int indice = (int)((long long)size * vet[i] / (max + 1));
        if (indice < 0) indice = 0;
        if (indice >= size) indice = size - 1;
        count[indice]++;
    }

    int **buckets = (int **)malloc(size * sizeof(int *));
    if (buckets == NULL) { free(count); return 0.0; }

    for (int i = 0; i < size; i++) {
        if (count[i] > 0) {
            buckets[i] = (int *)malloc(count[i] * sizeof(int));
            if (buckets[i] == NULL) {
                for (int j = 0; j < i; j++) if (count[j] > 0) free(buckets[j]);
                free(buckets);
                free(count);
                return 0.0;
            }
        } else {
            buckets[i] = NULL;
        }
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        int indice = (int)((long long)size * vet[i] / (max + 1));
        if (indice < 0) indice = 0;
        if (indice >= size) indice = size - 1;
        buckets[indice][count[indice]++] = vet[i];
    }

    int k = 0;
    for (int i = 0; i < size; i++) {
        if (count[i] > 0) {
            insercaoDireta(buckets[i], count[i], troc, compare);
            for (int j = 0; j < count[i]; j++) {
                vet[k++] = buckets[i][j];
            }
            free(buckets[i]);
        }
    }

    free(buckets);
    free(count);

    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

int main(){
    int *vet = geraVetor(N);
    int *vet2 = geraVetor(N);
    unsigned long comp1 = 0, tr1 = 0, comp2=0, tr2=0;
    double temp1 = bucketSort(vet, N, &tr1, &comp1), temp2 = radixSort(vet2, N, &tr2, &comp2);
    printf("BucketSort: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp1, tr1, comp1);
    printf("RadixSort: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp2, tr2, comp2);
    free(vet);
    free(vet2);
    return 0;
}