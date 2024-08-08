 #include "CalculoDeMatrizes.h"

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

int matrizInversivel(double **matriz, int n)
{
    double **temp = alocarMatriz(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = matriz[i][j];
        }
    }

    int *indexes = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        indexes[i] = i;
    }

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        int max_row = f;
        for (int i = f + 1; i < n; i++)
        {
            if (fabs(temp[i][f]) > fabs(temp[max_row][f]))
            {
                max_row = i;
            }
        }

        if (max_row != f)
        {
            for (int j = 0; j < n; j++)
            {
                double temp_val = temp[f][j];
                temp[f][j] = temp[max_row][j];
                temp[max_row][j] = temp_val;
            }

            int temp_index = indexes[f];
            indexes[f] = indexes[max_row];
            indexes[max_row] = temp_index;

            sign = -sign;
        }

        if (temp[f][f] == 0.0)
        {
            liberarMatriz(temp, n);
            free(indexes);
            return 0;
        }

        for (int i = f + 1; i < n; i++)
        {
            double factor = temp[i][f] / temp[f][f];
            for (int j = f; j < n; j++)
            {
                temp[i][j] -= factor * temp[f][j];
            }
        }
    }

    double det = 1.0;
    for (int i = 0; i < n; i++)
    {
        det *= temp[i][i];
    }

    liberarMatriz(temp, n);
    free(indexes);

    return (det != 0);
} 