#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double *complexidadeMedia(void(func)(int *, int, int), int qntdVezesTestada, long int tamanho, int seed);
void insertionSort(int *arr, int n);
void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);
char loading(int i);
char *porcentagemBarra(int qntdTestes, int total, int tamanhoBarra);
void escreverEmArquivo(double *tempo, int qntdDeTestes, long int n, int i);
double **MMQ(double *temposMedios, long int *tamanhosN, int testes);
void temposMediosGet(double *temposMedios, int qntTamanhos);
int **transposta(int **A, int linhas, int colunas);

int main()
{
    int qntdTestes = 100;
    long int tamanho = 2000;
    int testes = 10;
    double *tempos;
    long int *tamanhos = (long int *)malloc(10 * sizeof(long int));
    double *temposMediosVet = (double *)malloc(10 * sizeof(double));
    for (int i = 0; i < testes; tamanho *= 2, i++)
    {
        tamanhos[i] = tamanho;
      /*   tempos = complexidadeMedia(merge_sort, qntdTestes, tamanho, time(NULL));
        escreverEmArquivo(tempos, qntdTestes, tamanho, i); */
    }
    temposMediosGet(temposMediosVet, 10);
    MMQ(temposMediosVet, tamanhos, testes);
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
double *complexidadeMedia(void(func)(int *, int, int), int qntdVezesTestada, long int tamanho, int seed)
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
        func(array, 0, tamanho - 1);
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

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(sizeof(int) * n1);
    int *R = (int *)malloc(sizeof(int) * n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
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
void escreverEmArquivo(double *tempo, int qntdDeTestes, long int n, int i)
{
    double tempoMedio = 0;
    char *nomeDoArquivo = (char *)malloc((20) * sizeof(char));
    sprintf(nomeDoArquivo, "Tempo%i.txt", i);
    nomeDoArquivo[strcspn(nomeDoArquivo, "\n")] = '\0';
    srand(time(NULL));
    FILE *arquivoDeTempo = fopen(nomeDoArquivo, "w");
    if (arquivoDeTempo == NULL)
    {
        printf("\nNão foi possivel abrir ou criar o arquivo");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoDeTempo, "\nTamanho do problema \t Tempo\n");

    for (int i = 0; i < qntdDeTestes; i++)
    {
        fprintf(arquivoDeTempo, "\n\t\t%li   \t\t   %f", n, tempo[i]);
        tempoMedio += tempo[i];
    }

    tempoMedio /= qntdDeTestes;

    fprintf(arquivoDeTempo, "\nTempo medio do algoritmo: %f", tempoMedio);
    fclose(arquivoDeTempo);
}
// Função que vai armazenar os tempos medios dos arquivos gerados anteriormente em um array de tempos medios
void temposMediosGet(double *temposMedios, int qntTamanhos)
{
    char *nomeDoArquivo = (char *)malloc(20 * sizeof(char));
    FILE *arch;
    char linha[100];
    char *linhaAlvo = "Tempo medio do algoritmo:";
    for (int i = 0; i < qntTamanhos; i++)
    {
        sprintf(nomeDoArquivo, "Tempo%i.txt", i);
        arch = fopen(nomeDoArquivo, "r");
        while (fgets(linha, sizeof(linha), arch))
        {
            if (strstr(linha, linhaAlvo))
            {
                char *string = strstr(linha, ":") + 1;
                temposMedios[i] = atof(string);
                printf("\nTempo [%i]: %f", i, temposMedios[i]);
                break;
            }
        }
    }
}

// Função a qual será usada para realizar o calculo do MMQ de uma matriz
double **MMQ(double *temposMedios, long int *tamanhosN, int testes)
{

    // Alocação para matriz dos tempos e tamanhos testados no algoritmo de ordenação
    double **matriz = (double **)malloc(testes * sizeof(double *));

    // Matriz para armazenar tempos de cada teste
    double **y = (double **)malloc(testes * sizeof(double *));
    double **x = (double **)malloc(2 * sizeof(double *));
    // Matriz para calculo da transposta
    int **A = (int **)malloc(testes * sizeof(int *));

    for (int i = 0; i < testes; i++)
    {

        matriz[i] = (double *)malloc(2 * sizeof(double));
        A[i] = (int *)malloc(2 * sizeof(int));
        y[i] = (double *)malloc(sizeof(double));
        if (i < 2)
        {
            x[i] = (double *)malloc(sizeof(double));
        }
    }

    for (int i = 0; i < testes; i++)
    {
        matriz[i][0] = tamanhosN[i];
        matriz[i][1] = temposMedios[i];
        A[i][0] = 1;
        A[i][1] = tamanhosN[i];
        y[i][0] = temposMedios[i];
    }
    printf("\n");
   /*  for (int i = 0; i < testes; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                printf(" %.0f ", matriz[i][j] / 1000);
            }
            else
            {
                printf(" %.2f ", matriz[i][j]);
            }
        }
        printf("\n");
    } */

    int **Atransposta = transposta(A, testes, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < testes; j++)
        {
            printf(" %i ", Atransposta[i][j]);
        }
        printf("\n");
    }
}

int **transposta(int **A, int linhas, int colunas)
{
    int **transposta = (int **)malloc(colunas * sizeof(int *));
    for (int i = 0; i < colunas; i++)
    {
        transposta[i] = (int *)malloc(linhas * sizeof(int));
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            transposta[j][i] = A[i][j];
        }
    }

    return transposta;
}
