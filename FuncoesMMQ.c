#include "FuncoesMMQ.h"

double *complexidadeMedia(void(func)(int *, int, int), int qntdOrdenacoes, int tamanho, int seed)
{
    clock_t start_time, end_time;
    int i, j;
    double *tempos = (double *)malloc(qntdOrdenacoes * sizeof(double));
    verificarAlocacaoPonteiroDouble(tempos, "ponteiro com os tempos na função complexidade media");
    int *array = (int *)malloc(tamanho * sizeof(int));
    verificarAlocacaoPonteiroint(array, "vetor com os numeros aleatorios na função complexidade media");
    geradorRandom(array, seed, tamanho);

    for (i = 0; i <= qntdOrdenacoes + 1; i++)
    {

        j = 0;
        while (j <= 4)
        {
            printf("\r %s% %%c", porcentagemBarra(i, qntdOrdenacoes, 100), loading(j));
            fflush(stdout);
            for (int delay = 0; delay < 100000000; delay++)
                ;
            j++;
        }

        if (i == qntdOrdenacoes)
        {
            break;
        }

        start_time = clock();
        func(array, 0, tamanho - 1);
        end_time = clock();
        double tempoPassado = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
        tempos[i] = tempoPassado;
        seed = rand() % tamanho;
        geradorRandom(array, seed, tamanho);
    }
    free(array);
    return tempos;
}

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

    if (matrizInversivel(AtA, 2))
    {
        printf("\nA matriz eh inversivel.\n");
        double **AtA_inv = calcularInversa(AtA, 2);
        printf("Matriz inversa de: A * A transposta: \n");
        imprimirMat(AtA_inv, 2, 2, 10);
        printf("\n");

        printf("\n");
        double **result = produtoEntreMatrizes(AtA_inv, y, 2, 2, 2);
        printf("\n");
        printf("a = %f\n", result[0][0]);
        printf("b = %f\n", result[1][0]);
        for (int i = 0; i < 2; i++)
        {
            free(Atransposta[i]);
            free(AtA[i]);
            free(AtA_inv[i]);
            free(result[i]);
        }
        free(Atransposta);
        free(AtA);
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
        printf("a = %f\n", result[0][0]);
        printf("b = %f\n", result[1][0]);
        printf("c = %f\n", result[2][0]);
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
        printf("a = %f\n", result[0][0]);
        printf("b = %f\n", result[1][0]);
        printf("c = %f\n", result[2][0]);
        printf("d = %f\n", result[3][0]);

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