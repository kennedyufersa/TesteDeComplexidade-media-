#include "MetodoGradiente.h"

double *funcaoErroQuadratico(double *coeficientes, double *tempos, double *tamanhos, int iteracoes, int qntPontos, double taxaDeAprendizado)
{
    int i, j;
    double erro = 2;
    double a_db, b_db;
    while (erro > 1)
    {
        erro = 0;

        for (int i = 0; i < qntPontos; i++)
        {
            erro += pow((tempos[i] - coeficientes[1] - coeficientes[0] * tamanhos[i]), 2);
        }

        a_db = b_db = 0.0;

        for (i = 0; i < qntPontos; i++)
        {
            a_db += (tempos[i] - coeficientes[1] - coeficientes[0]) * (-tamanhos[i]);
            b_db += (tempos[i] - coeficientes[1] - coeficientes[0]) * (-1);
        }

        coeficientes[0] -= taxaDeAprendizado * (a_db/qntPontos);
        coeficientes[1] -= taxaDeAprendizado * (b_db/qntPontos);

        printf("a = %f, b = %f, erro = %f\n", coeficientes[0], coeficientes[1], erro);
    }

    return coeficientes;
}
