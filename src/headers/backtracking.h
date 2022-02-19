#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "dados.h"

typedef struct{
    int poder;
    int EspeciaisRestantes;
} TipoHess;

typedef int ** Labirinto;

int ** IniciarLabirinto(int linha, int coluna, TipoHess *hess,int quantChave);
void InserirPosicao(int ** labirinto, int linha, int coluna, int valor);
int EstudantePassou(int ** labirinto, int linha, int coluna);
int EstudanteEsta(int ** labirinto, int linha, int coluna);
int ChegouNoFim(int **labirinto, int i, int j);
int UltrapassouLimites(int i, int j, int linha, int coluna);
int LinhaEstudante(int ** labirinto, int linha, int coluna);
int ColunaEstudante(int ** labirinto, int linha, int coluna);
int EhParede(int ** labirinto, int linha, int coluna);
void MonstroEliminado(int ** labirinto, int linha, int coluna);
int EhPosicaoBatalha(int **labirinto, int linha, int coluna);
int Movimenta_Estudante(int ** labirinto, TipoHess *itens, int x, int y, int linha, int coluna, TipoDados *dados);
int Movimenta_Estudante_Analise(int ** labirinto, TipoHess *itens, int x, int y, int linha, int coluna, TipoDados *dados,long long int* NUM);
void ImprimirLabirinto(int ** labirinto, int linha, int coluna);

#endif