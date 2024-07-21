
#include "VerificacaoDeAlocacao.h"

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