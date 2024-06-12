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
double **calcularTransposta(double **A, int linhas, int colunas);
double **produtoEntreMatrizes(double **A, double **AT, int linhasA, int colunasA, int colunasB);
double **calcularInversa(double **matriz, int n);
double determinant(double **matriz, int n);
void getCofactor(double **matriz, double **temp, int p, int q, int n);
int ehInversivel(double **matriz, int n);
void imprimirMat(double **matriz, int lin, int col);
int main()
{
    int qntdTestes = 10;
    long int tamanho = 200;
    int testes = 10;
    double *tempos;
    long int *tamanhos = (long int *)malloc(10 * sizeof(long int));
    double *temposMediosVet = (double *)malloc(10 * sizeof(double));
    for (int i = 0; i < testes; tamanho *= 2, i++)
    {
        tamanhos[i] = tamanho;
        /* tempos = complexidadeMedia(merge_sort, qntdTestes, tamanho, time(NULL));
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
        double tempoPassado = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
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
    free(nomeDoArquivo);
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
    double **A = (double **)malloc(testes * sizeof(double *));
    double **y = (double **)malloc(testes * sizeof(double *));
    for (int i = 0; i < testes; i++)
    {
        A[i] = (double *)malloc(2 * sizeof(double));
        y[i] = (double *)malloc(2 * sizeof(double));
        A[i][0] = 1;
        A[i][1] = tamanhosN[i];
        y[i][0] = 1;
        y[i][1] = temposMedios[i];
    }
    // Realizando calculos necessarios para resolver o sistema A e B
    printf("\n");
    printf("Matriz A: \n");
    imprimirMat(A, 10, 2);
    printf("\n");
    printf("Matriz Y: \n");

    imprimirMat(y, 10, 2);
    printf("\n");

    double **Atransposta = calcularTransposta(A, testes, 2);
    printf("Matriz A transposta: \n");
    imprimirMat(Atransposta, 2, 10);
    printf("\n");
    double **AtA = produtoEntreMatrizes(A, Atransposta, testes, 2, testes);
    printf("Matriz A * A transposta: \n");
    imprimirMat(AtA,testes, testes);
    printf("\n");
    if (ehInversivel(AtA, 2) == 1)
    {

        double **AtY = produtoEntreMatrizes(Atransposta, y, 2, testes, 2);
        printf("Matriz A tranposta*y: \n");
        imprimirMat(AtY, 2, 2);
        printf("\n");
        double **AtA_inv = calcularInversa(AtA, 2);
        printf("Matriz inversa de: A * A transposta: \n");
        imprimirMat(AtA_inv, 2, 2);
        printf("\n");
        double **result = produtoEntreMatrizes(AtA_inv, AtY, 2, 2, 1);
        printf("\n");
        printf("a = %f\n", result[0][0]);
        printf("b = %f\n", result[1][0]);
        for (int i = 0; i < 2; i++)
        {
            free(Atransposta[i]);
            free(AtA[i]);
            free(AtY[i]);
            free(AtA_inv[i]);
            free(result[i]);
        }
        free(Atransposta);
        free(AtA);
        free(AtY);
        free(AtA_inv);
        free(result);
    }
    else
    {
        printf("\nA matriz gerada não é inversivel\n");
    }

    for (int i = 0; i < testes; i++)
    {
        free(A[i]);
        free(y[i]);
    }
    free(A);
    free(y);
}

double **calcularTransposta(double **A, int linhas, int colunas)
{
    double **transposta = (double **)malloc(colunas * sizeof(double *));
    for (int i = 0; i < colunas; i++)
    {
        transposta[i] = (double *)malloc(linhas * sizeof(double));
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

double **produtoEntreMatrizes(double **A, double **B, int linhasA, int colunasA, int colunasB)
{
    double **result = (double **)malloc(linhasA * sizeof(double *));
    for (int i = 0; i < linhasA; i++)
        result[i] = (double *)malloc(colunasB * sizeof(double));
    for (int i = 0; i < linhasA; i++)
        for (int j = 0; j < colunasB; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < colunasA; k++)
                result[i][j] += A[i][k] * B[k][j];
        }
    return result;
}

double **calcularInversa(double **matriz, int n)
{
    double **inversa = (double **)malloc(n * sizeof(double *));
    double **temp = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        inversa[i] = (double *)malloc(n * sizeof(double));
        temp[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                inversa[i][j] = 1;
            }
            else
            {
                inversa[i][j] = 0;
            }
            temp[i][j] = matriz[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        double pivo = temp[i][i];
        if (pivo == 0)
        {
            printf("Matriz não é inversível\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < n; j++)
        {
            temp[i][j] /= pivo;
            inversa[i][j] /= pivo;
        }
        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                double fator = temp[k][i];
                for (int j = 0; j < n; j++)
                {
                    temp[k][j] -= fator * temp[i][j];
                    inversa[k][j] -= fator * inversa[i][j];
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        free(temp[i]);
    }
    free(temp);
    return inversa;
}

double determinant(double **matriz, int n)
{
    double det = 0;

    // Caso base: se a matriz for 1x1, o determinante é o único elemento
    if (n == 1)
    {
        return matriz[0][0];
    }

    // Alocando memória para a matriz temporária
    double **temp = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        temp[i] = (double *)malloc(n * sizeof(double));
    }

    int sign = 1;

    // Iterar para cada elemento da primeira linha
    for (int f = 0; f < n; f++)
    {
        // Obtendo o cofactor da matriz[0][f]
        getCofactor(matriz, temp, 0, f, n);
        det += sign * matriz[0][f] * determinant(temp, n - 1);

        // Alternar o sinal
        sign = -sign;
    }

    // Liberando memória da matriz temporária
    for (int i = 0; i < n; i++)
    {
        free(temp[i]);
    }
    free(temp);

    return det;
}

void getCofactor(double **matriz, double **temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Iterar para cada elemento da matriz
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // Copiar na matriz temporária apenas os elementos que não estão na linha p e coluna q
            if (row != p && col != q)
            {
                temp[i][j++] = matriz[row][col];

                // Fila é preenchida, aumentar o índice da fila e redefinir o índice da coluna
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int ehInversivel(double **matriz, int n)
{
    double det = determinant(matriz, n);
    // printf("\n%f\n", det);
    if (det != 0)
    {
        return 1;
    }
    else if (det == 0)
    {
        return 0;
    }
}

void imprimirMat(double **matriz, int lin, int col)
{
    int i, j;

    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf(" %.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}