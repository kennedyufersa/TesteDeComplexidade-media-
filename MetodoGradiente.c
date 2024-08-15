#include "MetodoGradiente.h"

double mse(double *x, double *y, double w, int iteracoes)
{

    double E = 0.0;

    for (int i = 0; i < iteracoes; i++)
    {
        double y_pred = x[i] * w;
        double e = y_pred - y[i];
        E += e * e;
    }

    return E;
}

double *funcaoErroQuadratico(double *coeficientes, double *y, double *x, int qntPontos, double taxaDeAprendizado, double w)
{
    int i, j;
    double a_db, b_db;
    double error;
    for (int i = 0; i < qntPontos; i++)
    {
        double sum_ex = 0;
        double y_pred = x[i] * w;
        double e = y_pred - y[i];

        for (int j = 0; j < qntPontos; j++)
        {
            sum_ex += e * x[i];
        }

        a_db = (2 / qntPontos) * sum_ex;
        b_db = (2 / qntPontos) * sum_ex;

        coeficientes[0] -= taxaDeAprendizado * a_db;
        coeficientes[1] -= taxaDeAprendizado * b_db;

        double error = mse(x, y, w, qntPontos);

        printf("a = %f, b = %f, erro = %f\n", coeficientes[0], coeficientes[1], error);
    }

    return coeficientes;
}
