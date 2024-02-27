#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double *complexidadeMedia(void(func)(int *, int), int qntdVezesTestada, int tamanho, int seed);
void insertionSort(int *arr, int n);
char loading(int i);
char *porcentagemBarra(int qntdTestes, int total, int tamanhoBarra);
void escreverEmArquivo(double *tempo, int qntdDeTestes);

int main()
{
    int qntdTestes = 10;
    int tamanho = 100000;
    double *tempos;
    for (int i = 0; i < 5; i++)
    {
       tempos = complexidadeMedia(insertionSort, qntdTestes, tamanho, rand() % tamanho);

        escreverEmArquivo(tempos, qntdTestes);
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
double *complexidadeMedia(void(func)(int *, int), int qntdVezesTestada, int tamanho, int seed)
{
    clock_t start_time, end_time;
    int i, j;
    // variavel que vai armazenar os tempos de cada ordenação de um determinado vetor
    double *tempos = (double *)malloc(qntdVezesTestada * sizeof(double));
    // Função que recebe uma seed qualquer e o tamanho do vetor, e vai gerar uma quantidade de valores para preencher o vetor igual ao tamanho
    int *array = geradorRandom(seed, tamanho);
    // Neste laço realizamos os testes com o algoritmo de ordenação em questão uma quantidade de vezes = qntdVezesTestada, para verificar e chegarmos a qual é o tempo mais proximo
    // Que o algoritmo em analise leva para ordenar essa quantidade definida de valores, quanto mais testes, mais preciso o calculo de tempo
    for (i = 0; i <= qntdVezesTestada + 1; i++)
    {

        j = 0;
        // Este laço serve para mostrar uma barra de progresso na conclusão dos testes com base na quantidade de vezes testada
        while (j <= 4)
        {
            printf("\r %s%% %c", porcentagemBarra(i, qntdVezesTestada, 100), loading(j));
            fflush(stdout);
            for (int delay = 0; delay < 100000000; delay++)
                ;
            j++;
        }

        // Uma pequena condição para que a barra anterior mostre o progresso quando chegar em 100%
        if (i == qntdVezesTestada)
        {
            break;
        }

        // Nesta parte do codigo iniciamos a cronometragem de quanto tempo leva o algoritmo de ordenação em questão para ordenar o vetor passado
        start_time = clock();
        func(array, tamanho);
        end_time = clock();
        // Encerra-se a cronometragem do tempo de execução do algoritmo e armazenamos na variavel "tempoPassado" que depois é armazenado em um vetor com os tempos
        double tempoPassado = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        tempos[i] = tempoPassado;
        seed = rand() % tamanho;
        array = geradorRandom(seed, tamanho);
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
    else if (i == 3)
        return '/';
    else
        return '-';
}

char *porcentagemBarra(int qntdTestes, int total, int tamanhoBarra)
{
    int porcentagem = (int)(((double)qntdTestes / total) * 100);

    int numPreenchidos = (porcentagem * tamanhoBarra) / 100;

    char *barraString = (char *)malloc((tamanhoBarra + 6) * sizeof(char));
    barraString[0] = '[';
    for (int i = 1; i <= tamanhoBarra; i++)
    {
        barraString[i] = (i <= numPreenchidos) ? '=' : ' ';
    }
    char aux[4];
    sprintf(aux, "%i", porcentagem);
    barraString[tamanhoBarra + 1] = ']';
    barraString[tamanhoBarra + 2] = ' ';
    barraString[tamanhoBarra + 3] = aux[0];
    barraString[tamanhoBarra + 4] = aux[1];
    barraString[tamanhoBarra + 5] = aux[2];
    barraString[tamanhoBarra + 6] = '\0';
    return barraString;
}
// Escreve os tempos em um novo arquivo com nome gerado aleatoriamente
void escreverEmArquivo(double *tempo, int qntdDeTestes)
{
    double tempoMedio = 0;
    char *nomeDoArquivo = (char *)malloc(20 * sizeof(char));
    srand(time(NULL));
    sprintf(nomeDoArquivo, "Tempos%i.txt", rand() % 100);
    FILE *arquivoDeTempo = fopen(nomeDoArquivo, "w");
    if (arquivoDeTempo == NULL)
    {
        printf("\nNão foi possivel abrir ou criar o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < qntdDeTestes; i++)
    {
        fprintf(arquivoDeTempo, "\nTempo [%i] = %f", i + 1, tempo[i]);
        tempoMedio += tempo[i];
    }

    tempoMedio /= qntdDeTestes;

    fprintf(arquivoDeTempo, "\nTempo medio do algoritmo: %f", tempoMedio);
    fclose(arquivoDeTempo);
}