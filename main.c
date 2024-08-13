#include <string.h>
#include "Diversos.c"
#include "VerificacaoDeAlocacao.c"
#include "AlgoritmosDeOrdenacao.c"
#include "MetodoGradiente.c"
#include "FuncoesMMQ.c"
int main()
{
    int qntdOrdenacoes = 100;
    int tamanho = 1000;
    int testes = 100;
    double *tempos;
    double *tamanhos = (double *)malloc(testes * sizeof(double));
    double *temposMediosVet = (double *)malloc(testes * sizeof(double));
    double *coeficientes_e = (double *)malloc(2 * sizeof(double));

    verificarAlocacaoPonteiroint(tamanhos, "ponteiro de tamanhos");
    verificarAlocacaoPonteiroDouble(temposMediosVet, "Ponteiro com tempos medios");
    for (int i = 0; i < testes; tamanho += 1000, i++)
    {
        tamanhos[i] = tamanho;
        /* tempos = complexidadeMedia(merge_sort, qntdOrdenacoes, tamanho, time(NULL));
        escreverEmArquivo(tempos, qntdOrdenacoes, tamanho, i); */
    }

    temposMediosGet(temposMediosVet, testes);
    coeficientes_e[0] = (temposMediosVet[testes-1] - temposMediosVet[0]) / (tamanhos[testes - 1] - tamanhos[0]);
    coeficientes_e[1] = 0;

    coeficientes_e = funcaoErroQuadratico(coeficientes_e, temposMediosVet, tamanhos, testes, 0.00000001);
    plotGraphGNU(temposMediosVet, tamanhos, testes, coeficientes_e[0], coeficientes_e[1], 1);
    free(tempos);
}