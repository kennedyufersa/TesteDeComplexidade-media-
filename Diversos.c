#include "Diversos.h"
#include "VerificacaoDeAlocacao.h"

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

void plotGraphGNU(double *temposMedios, double *tamanhos, int testes, double a, double b, int j)
{
    FILE *dados = fopen("dados.txt", "w");
    if (dados == NULL)
    {
        perror("Erro ao abrir o arquivo dados.txt");
        return;
    }

    for (int i = 0; i < testes; i++)
    {
        fprintf(dados, " %f %f\n", temposMedios[i], tamanhos[i]);
    }

    fclose(dados);

    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL)
    {
        perror("Erro ao abrir o pipe para Gnuplot");
        return;
    }

    fprintf(gnuplotPipe, "set terminal pngcairo enhanced size 1280,1280\n");
    fprintf(gnuplotPipe, "set output 'grafico%i.png'\n", j);
    fprintf(gnuplotPipe, "set title 'Grafico de complexidade'\n");
    fprintf(gnuplotPipe, "set xlabel 'Tamanho do problema'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tempo medio'\n");
    fprintf(gnuplotPipe, "set grid\n");
    // fprintf(gnuplotPipe, "f(x) = 5533*x**2-209*x + 0\n");
    // fprintf(gnuplotPipe, "f(x) = %f*x**3 - 211*x**2 + 3998*x - 0.2\n");
    fprintf(gnuplotPipe, "f(x) = %f*x + %f\n", a, b);
    // fprintf(gnuplotPipe, "f(x) = (log(x) / log(2))\n");
    fprintf(gnuplotPipe, "plot 'dados.txt' using 1:2 title 'Pontos' with points pointtype 7 pointsize 1 lc rgb 'blue', \
         f(x) title 'O(n)' with lines lw 2 lc rgb 'green'\n");

    pclose(gnuplotPipe);
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
