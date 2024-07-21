#include <string.h>
#include "CalculoDeMatrizes.c"
#include "Diversos.c"
#include "FuncoesMMQ.c"
#include "VerificacaoDeAlocacao.c"
#include "AlgoritmosDeOrdenacao.c"

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