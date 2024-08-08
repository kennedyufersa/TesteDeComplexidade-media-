#include "MetodoGradiente.h"

double *funcaoErroQuadratico(double *coeficientes, double *tempos, double *tamanhos, int iteracoes, int qntPontos, double taxaDeAprendizado)
{
    int i, j;

    for (j = 0; j < iteracoes; j++)
    {
        double erro_a = 0.0, erro_b = 0.0;
        for (i = 0; i < qntPontos; i++)
        {
            double previsao = coeficientes[1] + coeficientes[0] * tamanhos[i];
            double erro = tempos[i] - previsao;
            erro_a += erro * tamanhos[i];
            erro_b += erro;
        }

        coeficientes[0] -= taxaDeAprendizado * (2 * erro_a / qntPontos);
        coeficientes[1] -= taxaDeAprendizado * (2 * erro_b / qntPontos);

        printf("Iteracao %d: a = %f, b = %f\n", j, coeficientes[0], coeficientes[1]);
    }

    return coeficientes;
}
