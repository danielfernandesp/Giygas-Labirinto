#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "dados.h"

typedef struct{
    int poder;
    int EspeciaisRestantes;
    short derrotado;
    short derrotouGiygas;
} TipoNess;

typedef struct {
  char identificador;
  int poder;
  int drop;
} TipoMob;

typedef struct{
  TipoMob LilUfO;
  TipoMob TerritorialOak;
  TipoMob StarmanJr;
  TipoMob MasterBelch;
  TipoMob Giygas;
}TipoMonstroDatabase;

typedef int ** Labirinto;

int **IniciarLabirinto(int linha, int coluna, TipoNess *hess, int poder,
                       int especiaisRestantes);
void InserirPosicao(int ** labirinto, int linha, int coluna, int valor);
int EstudantePassou(int ** labirinto, int linha, int coluna);
int EstudanteEsta(int ** labirinto, int linha, int coluna);
int ChegouNoFim(int **labirinto, int i, int j);
int UltrapassouLimites(int i, int j, int linha, int coluna);
int LinhaEstudante(int ** labirinto, int linha, int coluna);
int ColunaEstudante(int ** labirinto, int linha, int coluna);
int EhParede(int ** labirinto, int linha, int coluna);
void MonstroEliminado(int ** labirinto, int linha, int coluna);
short EhPosicaoBatalha(int **labirinto, int linha, int coluna,TipoMonstroDatabase *monstroDatabase);
TipoMob IdentificaAmeaca(int **labirinto, int linha, int coluna, TipoMonstroDatabase *monstroDatabase);
int Movimenta_Estudante(int **labirinto, TipoNess *ness, int x, int y,int linha, int coluna, TipoDados *dados, TipoMonstroDatabase *monstrodatabase);
int Movimenta_Estudante_Analise(int ** labirinto, TipoNess *itens, int x, int y, int linha, int coluna, TipoDados *dados,long long int* NUM);
void ImprimirLabirinto(int ** labirinto, int linha, int coluna);

#endif