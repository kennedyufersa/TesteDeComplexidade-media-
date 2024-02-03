#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double *complexidadeMedia(void(func)(int *, int), int qntdVezesTestada);
void insertionSort(int *arr, int n);

int main()
{
    int qntdTestes = 5;
    double *tempos = (double*)malloc(qntdTestes*sizeof(double));
    tempos = complexidadeMedia(insertionSort, qntdTestes);
    int i;
    for (i = 0; i < qntdTestes; i++)
    {
        printf("\nTempo [%i]: %f\n", i+1, tempos[i]);
    }

    //free(tempos);
}

// Essa função deve retornar um vetor de tempos do algoritmo que está sendo passado
double *complexidadeMedia(void(func)(int *, int), int qntdVezesTestada)
{
    clock_t start_time, end_time;
    int i;
    int tamanho = 10;
    int *array = (int*)malloc(tamanho*sizeof(int));
    double *tempos = (double *)malloc(qntdVezesTestada * sizeof(double));
    int valores[] = {1, 2, 7, 8, 14, 22, 65, 9, 10, 17};
    //Copia valores de um vetor para um espaço na memoria
    memcpy(array, valores, tamanho*sizeof(int));
    for (i = 0; i < qntdVezesTestada; i++)
    {
        start_time = clock();
        func(array, tamanho);
        end_time = clock();
        double tempoPassado = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        tempos[i] = tempoPassado;
    }
    //free(array);
    return tempos;
}

// Teste com insertion sort
void insertionSort(int *arr, int n)
{
    int i, chave, j;
    for (i = 1; i < n; i++)
    {
        chave = arr[i];
        j = i - 1;

        // Move os elementos do arr[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > chave)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}