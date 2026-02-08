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

int calculoMediana(int vet[], int esq, int dir){
    int meio = (esq + dir)/2;
    int aux = 0;

    if(vet[esq] > vet[meio]){
        aux = vet[esq];
        vet[esq] = vet[meio];
        vet[meio] = aux;
    }

    if(vet[meio] > vet[dir]){
        aux = vet[meio];
        vet[meio] = vet[dir];
        vet[dir] = aux;
    }

    if(vet[meio] < vet[esq]){
        aux = vet[esq];
        vet[esq] = vet[meio];
        vet[meio] = aux;
    }

    return vet[meio];
}

void particaoQuick(int* dados, int esq, int dir, int *i, int *j, int posiPivo, unsigned long* troc, unsigned long* compare){
    int pivo, aux;
    *i = esq;
    *j = dir;

    switch (posiPivo)
    {
    //pivo = 1 (centro)
    case 1:
        pivo = dados[(esq + dir)/2];
        break;
    //pivo = 2 (último) -> POSSÍVEL PIOR CASO O(n^2)
    case 2:
        pivo = dados[dir];
        break;
    case 3:
    //pivo = 3 (mediana)
        pivo = calculoMediana(dados, esq, dir);
        break;
    default:
        break;
    }

    while(*i <= *j){

        while(*i < dir){
            *compare += 1;
            if (dados[*i] < pivo ){
                (*i)++;
            }
            else{
                break;
            }
        }

        while(*j > esq){
            *compare += 1;
            if(dados[*j] > pivo){
                (*j)--;
            }else{
                break;
            }
        }

        if(*i <= *j){
            *troc += 1;
            aux = dados[*i];
            dados[*i] = dados[*j];
            dados[*j] = aux;
            (*i)++;
            (*j)--;
        }
    }
}

double quickSortCentro(int vet[], int esq, int dir, unsigned long* troc, unsigned long* compare){
    clock_t inicio, fim;
    double temp;

    inicio = clock();

    while (esq < dir) {
        int i, j;
        particaoQuick(vet, esq, dir, &i, &j, 1, troc, compare);

        if (j - esq < dir - i) {
            if (j > esq) quickSortCentro(vet, esq, j, troc, compare);
            esq = i;
        } else {
            if (i < dir) quickSortCentro(vet, i, dir, troc, compare);
            dir = j;
        }
    }

    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

double quickSortFim(int vet[], int esq, int dir, unsigned long* troc, unsigned long* compare){ 
    clock_t inicio, fim;
    double temp;

    inicio = clock();

    while (esq < dir) {
        int i, j;
        particaoQuick(vet, esq, dir, &i, &j, 2, troc, compare);

        if (j - esq < dir - i) {
            if (j > esq) quickSortFim(vet, esq, j, troc, compare);
            esq = i;
        } else {
            if (i < dir) quickSortFim(vet, i, dir, troc, compare);
            dir = j;
        }
    }

    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

double quickSortMediana(int vet[], int esq, int dir, unsigned long* troc, unsigned long* compare){ 
    clock_t inicio, fim;
    double temp;

    inicio = clock();

    while (esq < dir) {
        int i, j;
        particaoQuick(vet, esq, dir, &i, &j, 3, troc, compare);

        if (j - esq < dir - i) {
            if (j > esq) quickSortMediana(vet, esq, j, troc, compare);
            esq = i;
        } else {
            if (i < dir) quickSortMediana(vet, i, dir, troc, compare);
            dir = j;
        }
    }

    fim = clock();
    temp = (double)(fim - inicio)/CLOCKS_PER_SEC;

    return temp;
}

int main(){
    int *vet = geraVetor(N);
    int *vet2 = geraVetor(N);
    int *vet3 = geraVetor(N);
    unsigned long comp1 = 0, tr1 = 0, comp2=0, tr2=0, comp3=0, tr3=0;
    double temp1 = quickSortCentro(vet,0,N-1,&tr1,&comp1), temp2 = quickSortFim(vet2,0,N-1,&tr2,&comp2), temp3 = quickSortMediana(vet3,0,N-1,&tr3,&comp3);
    printf("Quicksort centro: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp1, tr1, comp1);
    printf("Quicksort Fim: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp2, tr2, comp2);
    printf("Quicksort Mediana: Tempo de execucao : %5.2f seg. | Trocas: %lu | Comparacoes: %lu\n", temp3, tr3, comp3);
    free(vet);
    free(vet2);
    free(vet3);
    return 0;
}