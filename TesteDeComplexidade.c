#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double *complexidadeMedia(void(func)(int *, int), int qntdVezesTestada);
void insertionSort(int *arr, int n);
char loading( int i);
char *setPorcentagem(int qntdTestes, int total, int tamanhoBarra);

int main()
{
    int qntdTestes = 5;
    double *tempos = complexidadeMedia(insertionSort, qntdTestes);
    int i;
    for (i = 0; i < qntdTestes; i++)
    {
        printf("\nTempo [%i]: %f\n", i + 1, tempos[i]);
    }

    free(tempos);
}

int *geradorRandom(int seed, int qntd)
{
    int i = 0;
    srand(seed);
    int *vetor = (int *)malloc(qntd * sizeof(int));
    for (i = 0; i < qntd; i++)
    {
        vetor[i] = rand() % qntd;
    }
    return vetor;
}

// Essa função deve retornar um vetor de tempos do algoritmo que está sendo passado
double *complexidadeMedia(void(func)(int *, int), int qntdVezesTestada)
{
    clock_t start_time, end_time;
    int i, j;
    double *tempos = (double *)malloc(qntdVezesTestada * sizeof(double));
    int tamanho = 100;
    int *array = geradorRandom(1000, tamanho);
    int *valores = geradorRandom(1000, tamanho);
    for (i = 0; i <= qntdVezesTestada + 1; i++)
    {
        j = 0;
        while (j <= 4){
            printf("\r %s%% %c", setPorcentagem(i,qntdVezesTestada, 100),loading(j));
            fflush(stdout);
            for (int delay = 0; delay < 100000000; delay++);
            j++;
            
        } 
        if(i == qntdVezesTestada){
            break;
        }
        start_time = clock();
        func(array, tamanho);
        end_time = clock();
        double tempoPassado = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        tempos[i] = tempoPassado;
        memcpy(array, valores, tamanho * sizeof(int));
        
        
        
    }
    free(array);
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

char loading(int i)
{
    if (i == 0)
        return '-';
    else if (i == 1)
        return '\\';
    else if (i == 2)
        return '|';
    else if(i == 3)
        return '/';
    else 
    return '-';
}

char *setPorcentagem(int qntdTestes, int total, int tamanhoBarra){
     int porcentagem = (int)(((double)qntdTestes / total) * 100);

    int numPreenchidos = (porcentagem * tamanhoBarra + 50) / 100;

    char *barraString = (char *)malloc((tamanhoBarra + 6) * sizeof(char));
    barraString[0] = '[';
    for (int i = 1; i <= tamanhoBarra; i++)
    {
        barraString[i] = (i <= numPreenchidos) ? '=' : ' ';
    }
    char aux[4];
    sprintf(aux,"%i", porcentagem);
    barraString[tamanhoBarra + 1] = ']';
    barraString[tamanhoBarra + 2] = ' ';
    barraString[tamanhoBarra + 3] = aux[0];
    barraString[tamanhoBarra + 4] = aux[1];
    barraString[tamanhoBarra + 5] = aux[2];
    barraString[tamanhoBarra + 6] = '\0';
    return barraString;

}