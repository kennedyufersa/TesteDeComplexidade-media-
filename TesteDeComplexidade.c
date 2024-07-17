#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
double *complexidadeMedia(void(func)(int *, int, int), int qntdOrdenacoes, int tamanho, int seed);
void verificarAlocacaoMatriz(double **ptrr, char *local);
void verificarAlocacaoPonteiroDouble(double *ptr, char *local);
void verificarAlocacaoPonteiroint(int *ptr, char *local);
void insertionSort(int *arr, int n);
void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);
char loading(int i);
void geradorRandom(int *array, int seed, int qntd);
char *porcentagemBarra(int qntdTestes, int total, int tamanhoBarra);
void escreverEmArquivo(double *tempo, int qntdDeTestes, int n, int i);
double **MMQPrimeiroGrau(double *temposMedios, int *tamanhosN, int testes);
double **MMQSegundoGrau(double *temposMedios, int *tamanhosN, int testes);
double **MMQTerceiroGrau(double *temposMedios, int *tamanhosN, int testes);
char *extrairDoisPrimeirosDigitos(double numero, int qntExtracao);
void temposMediosGet(double *temposMedios, int qntTamanhos);
double **calcularTransposta(double **A, int linhas, int colunas);
double **produtoEntreMatrizes(double **A, double **AT, int linhasA, int colunasA, int colunasB);
double **calcularInversa(double **matriz, int n);
void imprimirMat(double **matriz, int lin, int col, int qntDigitos);
void plotGraphGNU(double *temposMedios, int *tamanhos, int testes);
int matrizInversivel(double **matriz, int n);
void liberarMatriz(double **matriz, int linhas);
double **alocarMatriz(int linhas, int colunas);
int main()
{
    int qntdOrdenacoes = 11;
    int tamanho = 10000;
    int testes = 11;
    double *tempos;
    int *tamanhos = (int *)malloc(testes * sizeof(int));
    double *temposMediosVet = (double *)malloc(testes * sizeof(double));
    verificarAlocacaoPonteiroint(tamanhos, "ponteiro de tamanhos");
    verificarAlocacaoPonteiroDouble(temposMediosVet, "Ponteiro com tempos medios");
    for (int i = 0; i < testes; tamanho += 10000, i++)
    {
        tamanhos[i] = tamanho;
        /* tempos = complexidadeMedia(merge_sort, qntdOrdenacoes, tamanho, time(NULL));
        escreverEmArquivo(tempos, qntdOrdenacoes, tamanho, i); */
    }

    temposMediosGet(temposMediosVet, testes);
    MMQPrimeiroGrau(temposMediosVet, tamanhos, testes);
    plotGraphGNU(temposMediosVet, tamanhos, testes);
    // free(tempos);
}
void geradorRandom(int *array, int seed, int qntd)
{
    int i = 0;
    srand(seed);

    verificarAlocacaoPonteiroint(array, "vetor no gerador random com numeros gerados aleatoriamente");

    for (i = 0; i < qntd; i++)
    {
        array[i] = rand() % qntd;
    }
}

// Essa função deve retornar um vetor de tempos do algoritmo que está sendo passado
double *complexidadeMedia(void(func)(int *, int, int), int qntdOrdenacoes, int tamanho, int seed)
{
    clock_t start_time, end_time;
    int i, j;
    // variavel que vai armazenar os tempos de cada ordenação de um determinado vetor
    double *tempos = (double *)malloc(qntdOrdenacoes * sizeof(double));
    verificarAlocacaoPonteiroDouble(tempos, "ponteiro com os tempos na função complexidade media");
    // Função que recebe uma seed qualquer e o tamanho do vetor, e vai gerar uma quantidade de valores para preencher o vetor igual ao tamanho
    int *array = (int *)malloc(tamanho * sizeof(int));
    verificarAlocacaoPonteiroint(array, "vetor com os numeros aleatorios na função complexidade media");
    geradorRandom(array, seed, tamanho);

    // Neste laço realizamos os testes com o algoritmo de ordenação em questão uma quantidade de vezes = qntdOrdenacoes, para verificar e chegarmos a qual é o tempo mais proximo
    // Que o algoritmo em analise leva para ordenar essa quantidade definida de valores, quanto mais testes, mais preciso o calculo de tempo
    for (i = 0; i <= qntdOrdenacoes + 1; i++)
    {

        j = 0;
        // Este laço serve para mostrar uma barra de progresso na conclusão dos testes com base na quantidade de vezes testada
        while (j <= 4)
        {
            printf("\r %s% %%c", porcentagemBarra(i, qntdOrdenacoes, 100), loading(j));
            fflush(stdout);
            for (int delay = 0; delay < 100000000; delay++)
                ;
            j++;
        }

        // Uma pequena condição para que a barra anterior mostre o progresso quando chegar em 100%
        if (i == qntdOrdenacoes)
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
        geradorRandom(array, seed, tamanho);
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
void escreverEmArquivo(double *tempo, int qntTempos, int n, int i)
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

    for (int i = 0; i < qntTempos; i++)
    {
        fprintf(arquivoDeTempo, "\n\t\t%i   \t\t   %f", n, tempo[i]);
        tempoMedio += tempo[i];
    }

    tempoMedio /= qntTempos;

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
double **MMQPrimeiroGrau(double *temposMedios, int *tamanhosN, int linhas)
{
    double **A = (double **)malloc(linhas * sizeof(double *));
    double **y = (double **)malloc(linhas * sizeof(double *));
    verificarAlocacaoMatriz(A, "Matriz A MMQ");
    verificarAlocacaoMatriz(y, "Matriz y MMQ");
    for (int i = 0; i < linhas; i++)
    {
        A[i] = (double *)malloc(2 * sizeof(double));
        y[i] = (double *)malloc(2 * sizeof(double));
        verificarAlocacaoPonteiroDouble(A[i], "colunas da matriz A");
        verificarAlocacaoPonteiroDouble(y[i], "colunas da matriz y");
        A[i][0] = 1;
        A[i][1] = tamanhosN[i];
        y[i][0] = 1;
        y[i][1] = temposMedios[i];
    }
    // Realizando calculos necessarios para resolver o sistema A e B
    printf("\n\n");
    printf("Matriz A: \n");
    imprimirMat(A, linhas, 2, 5);
    printf("\n");
    printf("Matriz Y: \n");

    imprimirMat(y, linhas, 2, 6);
    printf("\n");

    double **Atransposta = calcularTransposta(A, linhas, 2);
    printf("Matriz A transposta: \n");
    imprimirMat(Atransposta, 2, linhas, 6);
    printf("\n");
    double **AtA = produtoEntreMatrizes(Atransposta, A, 2, linhas, 2);
    printf("Matriz A * A transposta: \n");
    imprimirMat(AtA, 2, 2, 6);
    printf("\n");

    double **AtY = produtoEntreMatrizes(Atransposta, y, 2, linhas, 2);

    printf("Matriz A tranposta*y: \n");
    imprimirMat(AtY, 2, 2, 10);
    printf("\n");
    if (matrizInversivel(AtA, 2))
    {
        printf("\nA matriz eh inversivel.\n");
        double **AtA_inv = calcularInversa(AtA, 2);
        printf("Matriz inversa de: A * A transposta: \n");
        imprimirMat(AtA_inv, 2, 2, 10);
        printf("\n");
        double **result = produtoEntreMatrizes(AtA_inv, AtY, 2, 2, 2);
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
        printf("\nA matriz nao eh inversivel.\n");
    }

    for (int i = 0; i < linhas; i++)
    {
        free(A[i]);
        free(y[i]);
    }
    free(A);
    free(y);
}

double **MMQSegundoGrau(double *temposMedios, int *tamanhosN, int linhas)
{
    double **A = (double **)malloc(linhas * sizeof(double *));
    double **y = (double **)malloc(linhas * sizeof(double *));
    verificarAlocacaoMatriz(A, "Matriz A MMQ");
    verificarAlocacaoMatriz(y, "Matriz y MMQ");
    for (int i = 0; i < linhas; i++)
    {
        A[i] = (double *)malloc(3 * sizeof(double));
        y[i] = (double *)malloc(3 * sizeof(double));
        verificarAlocacaoPonteiroDouble(A[i], "colunas da matriz A");
        verificarAlocacaoPonteiroDouble(y[i], "colunas da matriz y");
        A[i][0] = 1;
        A[i][1] = tamanhosN[i];
        A[i][2] = pow(tamanhosN[i], 2);
        y[i][0] = 1;
        y[i][1] = temposMedios[i];
        y[i][2] = pow(temposMedios[i], 2);
    }
    // Realizando calculos necessarios para resolver o sistema A, B e C
    printf("\n\n");
    printf("Matriz A: \n");
    imprimirMat(A, linhas, 3, 5);
    printf("\n");
    printf("Matriz Y: \n");

    imprimirMat(y, linhas, 3, 6);
    printf("\n");

    double **Atransposta = calcularTransposta(A, linhas, 3);
    printf("Matriz A transposta: \n");
    imprimirMat(Atransposta, 3, linhas, 6);
    printf("\n");
    double **AtA = produtoEntreMatrizes(Atransposta, A, 3, linhas, 3);
    printf("Matriz A * A transposta: \n");
    imprimirMat(AtA, 3, linhas, 6);
    printf("\n");

    double **AtY = produtoEntreMatrizes(y, Atransposta, linhas, 3, linhas);
    printf("Matriz y * A tranposta: \n");
    imprimirMat(AtY, 3, 3, 5);
    printf("\n");
    if (matrizInversivel(AtA, 3))
    {
        printf("\nA matriz eh inversivel.\n");
        double **AtA_inv = calcularInversa(AtA, 3);
        printf("Matriz inversa de: A transposta * A : \n");
        imprimirMat(AtA_inv, 3, 3, 5);
        printf("\n");
        double **result = produtoEntreMatrizes(AtA_inv, AtY, 3, 3, 3);

        printf("\n");
        printf("a = %s\n", extrairDoisPrimeirosDigitos(result[0][0], 5));
        printf("b = %s\n", extrairDoisPrimeirosDigitos(result[1][0], 5));
        printf("c = %s\n", extrairDoisPrimeirosDigitos(result[2][0], 5));
        for (int i = 0; i < 3; i++)
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
        printf("\nA matriz nao eh inversivel.\n");
    }

    for (int i = 0; i < linhas; i++)
    {
        free(A[i]);
        free(y[i]);
    }
    free(A);
    free(y);
}

double **MMQTerceiroGrau(double *temposMedios, int *tamanhosN, int linhas)
{
    double **A = (double **)malloc(linhas * sizeof(double *));
    double **y = (double **)malloc(linhas * sizeof(double *));
    verificarAlocacaoMatriz(A, "Matriz A MMQ");
    verificarAlocacaoMatriz(y, "Matriz y MMQ");
    for (int i = 0; i < linhas; i++)
    {
        A[i] = (double *)malloc(4 * sizeof(double));
        y[i] = (double *)malloc(4 * sizeof(double));
        verificarAlocacaoPonteiroDouble(A[i], "colunas da matriz A");
        verificarAlocacaoPonteiroDouble(y[i], "colunas da matriz y");
        A[i][0] = 1;
        A[i][1] = tamanhosN[i];
        A[i][2] = pow(tamanhosN[i], 2);
        A[i][3] = pow(tamanhosN[i], 3);
        y[i][0] = 1;
        y[i][1] = temposMedios[i];
        y[i][2] = pow(temposMedios[i], 2);
        y[i][3] = pow(temposMedios[i], 3);
    }
    // Realizando calculos necessarios para resolver o sistema A, B e C
    printf("\n\n");
    printf("Matriz A: \n");
    imprimirMat(A, linhas, 4, 5);
    printf("\n");
    printf("Matriz Y: \n");

    imprimirMat(y, linhas, 4, 6);
    printf("\n");

    double **Atransposta = calcularTransposta(A, linhas, 4);
    printf("Matriz A transposta: \n");
    imprimirMat(Atransposta, 4, linhas, 6);
    printf("\n");
    double **AtA = produtoEntreMatrizes(Atransposta, A, 4, linhas, 4);
    printf("Matriz A * A transposta: \n");
    imprimirMat(AtA, 4, 4, 6);
    printf("\n");

    double **AtY = produtoEntreMatrizes(y, Atransposta, linhas, 4, linhas);
    printf("Matriz y * A tranposta: \n");
    imprimirMat(AtY, 4, 4, 5);
    printf("\n");
    if (matrizInversivel(AtA, 4))
    {
        printf("\nA matriz eh inversivel.\n");
        double **AtA_inv = calcularInversa(AtA, 4);
        printf("Matriz inversa de: A transposta * A : \n");
        imprimirMat(AtA_inv, 4, 4, 5);
        printf("\n");
        double **result = produtoEntreMatrizes(AtA_inv, AtY, 4, 4, 4);

        printf("\n");
        printf("a = %s\n", extrairDoisPrimeirosDigitos(result[0][0], 5));
        printf("b = %s\n", extrairDoisPrimeirosDigitos(result[1][0], 5));
        printf("c = %s\n", extrairDoisPrimeirosDigitos(result[2][0], 5));
        printf("d = %s\n", extrairDoisPrimeirosDigitos(result[3][0], 5));

        for (int i = 0; i < 4; i++)
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
        printf("\nA matriz nao eh inversivel.\n");
    }

    for (int i = 0; i < linhas; i++)
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
    verificarAlocacaoMatriz(transposta, "Matriz transposta");
    for (int i = 0; i < colunas; i++)
    {
        transposta[i] = (double *)malloc(linhas * sizeof(double));
        verificarAlocacaoPonteiroDouble(transposta[i], "colunas da matriz transposta");
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
    verificarAlocacaoMatriz(result, "Matriz result produto entre matrizes");

    for (int i = 0; i < linhasA; i++)
    {

        result[i] = (double *)malloc(colunasB * sizeof(double));
        verificarAlocacaoPonteiroDouble(result[i], "colunas da matriz result (produto entre matrizes)");
    }

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
    double **inversa = alocarMatriz(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inversa[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int k = 0; k < n; k++)
    {
        int max_row = k;
        for (int i = k + 1; i < n; i++)
        {
            if (fabs(matriz[i][k]) > fabs(matriz[max_row][k]))
            {
                max_row = i;
            }
        }

        if (max_row != k)
        {
            for (int j = 0; j < n; j++)
            {
                double temp = matriz[k][j];
                matriz[k][j] = matriz[max_row][j];
                matriz[max_row][j] = temp;

                temp = inversa[k][j];
                inversa[k][j] = inversa[max_row][j];
                inversa[max_row][j] = temp;
            }
        }

        double pivot = matriz[k][k];
        if (pivot == 0.0)
        {
            printf("Erro: Pivô zero encontrado. A matriz não é inversível.\n");
            liberarMatriz(inversa, n);
            return NULL;
        }

        for (int j = 0; j < n; j++)
        {
            matriz[k][j] /= pivot;
            inversa[k][j] /= pivot;
        }

        for (int i = k + 1; i < n; i++)
        {
            double factor = matriz[i][k];
            for (int j = 0; j < n; j++)
            {
                matriz[i][j] -= factor * matriz[k][j];
                inversa[i][j] -= factor * inversa[k][j];
            }
        }
    }

    for (int k = n - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            double factor = matriz[i][k];
            for (int j = 0; j < n; j++)
            {
                matriz[i][j] -= factor * matriz[k][j];
                inversa[i][j] -= factor * inversa[k][j];
            }
        }
    }

    return inversa;
}

void imprimirMat(double **matriz, int lin, int col, int qntDigitos)
{
    if (matriz == NULL)
    {
        printf("Matriz não inicializada\n");
        return;
    }

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf(" %f ", matriz[i][j]);
        }
        printf("\n");
    }
}

char *extrairDoisPrimeirosDigitos(double numero, int qntExtracao)
{
    char strNumero[30];
    snprintf(strNumero, sizeof(strNumero), "%.2f", numero);

    char *extrair = (char *)malloc(qntExtracao * sizeof(char));
    if (extrair == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    for (int i = 0; i < qntExtracao - 1; i++)
    {
        extrair[i] = strNumero[i];
    }
    extrair[qntExtracao - 1] = '\0';

    return extrair;
}

void verificarAlocacaoPonteiroint(int *ptr, char *local)
{
    if (ptr == NULL)
    {
        printf("\nFalha na alocação de memoria %s", local);
        exit(EXIT_FAILURE);
    }
}
void verificarAlocacaoPonteiroDouble(double *ptr, char *local)
{
    if (ptr == NULL)
    {
        printf("\nFalha na alocação de memoria %s", local);
        exit(EXIT_FAILURE);
    }
}
void verificarAlocacaoMatriz(double **ptrr, char *local)
{
    if (ptrr == NULL)
    {
        printf("\nFalha na alocação de memoria %s", local);
        exit(EXIT_FAILURE);
    }
}

void plotGraphGNU(double *temposMedios, int *tamanhos, int testes)
{
    FILE *dados = fopen("dados.txt", "w");
    if (dados == NULL)
    {
        perror("Erro ao abrir o arquivo dados.txt");
        return;
    }

    for (int i = 0; i < testes; i++)
    {
        fprintf(dados, " %i %f\n", tamanhos[i], temposMedios[i]);
    }

    fclose(dados);

    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL)
    {
        perror("Erro ao abrir o pipe para Gnuplot");
        return;
    }
    fprintf(gnuplotPipe, "set terminal pngcairo enhanced size 1280,1280\n");
    fprintf(gnuplotPipe, "set output 'grafico.png'\n");
    fprintf(gnuplotPipe, "set title 'Grafico de complexidade'\n");
    fprintf(gnuplotPipe, "set xlabel 'Tamanho do problema'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tempo medio'\n");
    fprintf(gnuplotPipe, "set grid\n");
    // fprintf(gnuplotPipe, "f(x) = 5533*x**2-209*x + 0\n");
    // fprintf(gnuplotPipe, "f(x) = 3012*x**3 - 211*x**2 + 3998*x - 0.2\n");
    // fprintf(gnuplotPipe, "f(x) = 9333*x -0.13\n");
    fprintf(gnuplotPipe, "f(x) = (log(x) / log(2))\n");
    fprintf(gnuplotPipe, "plot 'dados.txt' using 1:2 title 'Pontos' with points pointtype 7 pointsize 1 lc rgb 'blue', \
     f(x) title 'O(n)' with lines lw 2 lc rgb 'purple'\n");

    pclose(gnuplotPipe);
}

double **alocarMatriz(int linhas, int colunas)
{
    double **matriz = (double **)malloc(linhas * sizeof(double *));
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (double *)malloc(colunas * sizeof(double));
    }
    return matriz;
}

void liberarMatriz(double **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}
int matrizInversivel(double **matriz, int n)
{
    // Alocando memória para a matriz temporária
    double **temp = alocarMatriz(n, n);

    // Copiando os elementos da matriz original para a matriz temporária
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = matriz[i][j];
        }
    }

    // Vetor de índices para permutação
    int *indexes = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        indexes[i] = i;
    }

    int sign = 1; // Inicialmente positivo

    // Iterando sobre as colunas
    for (int f = 0; f < n; f++)
    {
        // Encontrar a linha com o maior elemento na coluna f
        int max_row = f;
        for (int i = f + 1; i < n; i++)
        {
            if (fabs(temp[i][f]) > fabs(temp[max_row][f]))
            {
                max_row = i;
            }
        }

        // Trocar a linha de máxima magnitude com a linha atual (swap)
        if (max_row != f)
        {
            // Trocar as linhas na matriz original
            for (int j = 0; j < n; j++)
            {
                double temp_val = temp[f][j];
                temp[f][j] = temp[max_row][j];
                temp[max_row][j] = temp_val;
            }

            // Trocar as linhas nos índices de permutação
            int temp_index = indexes[f];
            indexes[f] = indexes[max_row];
            indexes[max_row] = temp_index;

            // Mudar o sinal da determinante a cada troca de linha
            sign = -sign;
        }

        // Se a matriz se tornar singular durante o processo
        if (temp[f][f] == 0.0)
        {
            liberarMatriz(temp, n);
            free(indexes);
            return 0; // Matriz não é inversível
        }

        // Reduzir a matriz em forma triangular inferior
        for (int i = f + 1; i < n; i++)
        {
            double factor = temp[i][f] / temp[f][f];
            for (int j = f; j < n; j++)
            {
                temp[i][j] -= factor * temp[f][j];
            }
        }
    }

    // Calculando o determinante final
    double det = 1.0;
    for (int i = 0; i < n; i++)
    {
        det *= temp[i][i];
    }

    // Liberando memória
    liberarMatriz(temp, n);
    free(indexes);

    // Verificando se o determinante é não nulo (matriz inversível)
    return (det != 0);
}