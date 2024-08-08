#include <string.h>
#include "Diversos.c"
#include "VerificacaoDeAlocacao.c"
#include "AlgoritmosDeOrdenacao.c"
#include "MetodoGradiente.c"
int main()
{
    int qntdOrdenacoes = 100;
    int tamanho = 100;
    int testes = 88;
    double *tempos;
    double *tamanhos = (double *)malloc(testes * sizeof(double));
    double *temposMediosVet = (double *)malloc(testes * sizeof(double));
    double *coeficientes = (double *)malloc(2 * sizeof(double));
    coeficientes[0] = 50;
    coeficientes[1] = 20;
    verificarAlocacaoPonteiroint(tamanhos, "ponteiro de tamanhos");
    verificarAlocacaoPonteiroDouble(temposMediosVet, "Ponteiro com tempos medios");
    for (int i = 0; i < testes; tamanho += 100, i++)
    {
        tamanhos[i] = tamanho;
        /*   tempos = complexidadeMedia(merge_sort, qntdOrdenacoes, tamanho, time(NULL));
       escreverEmArquivo(tempos, qntdOrdenacoes, tamanho, i);   */
    }

    temposMediosGet(temposMediosVet, testes);
  /*   double max_tamanho = tamanhos[0];
    for (int i = 1; i < testes; i++)
    {
        if (tamanhos[i] > max_tamanho)
        {
            max_tamanho = tamanhos[i];
        }
    }

    if (max_tamanho != 0) // Garantir que não há divisão por zero
    {
        for (int i = 0; i < testes; i++)
        {
            tamanhos[i] = tamanhos[i] / max_tamanho; // Normalização
        }
    } */

    coeficientes = funcaoErroQuadratico(coeficientes, temposMediosVet, tamanhos, 1000, testes, 0.0000000001);
    plotGraphGNU(temposMediosVet, tamanhos, testes, coeficientes[0], coeficientes[1], 1);
    // free(tempos);
}