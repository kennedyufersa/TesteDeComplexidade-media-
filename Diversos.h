#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void plotGraphGNU(double *, int *, int );
void temposMediosGet(double *, int );
void geradorRandom(int *, int , int );
char *porcentagemBarra(int , int , int );
void escreverEmArquivo(double *, int , int , int );
char loading(int i);
void imprimirMat(double **matriz, int lin, int col, int qntDigitos);
