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

typedef char ** Labirinto;

int **IniciarLabirinto(int linha, int coluna, TipoNess *hess, int poder,
                       int especiaisRestantes);
void InserirPosicao(char **labirinto, int linha, int coluna, int valor);
int NessPassou(char **labirinto, int linha, int coluna);
int NessEsta(char **labirinto, int linha, int coluna);
int ChegouNoFim(TipoNess *pNess);
int UltrapassouLimites(int i, int j, int linha, int coluna);
int LinhaNess(char **labirinto, int linha, int coluna);
int ColunaNess(char **labirinto, int linha, int coluna);
int EhParede(char **labirinto, int linha, int coluna);
void MonstroEliminado(char **labirinto, int linha, int coluna);
short EhPosicaoBatalha(char **labirinto, int linha, int coluna);
TipoMob IdentificaAmeaca(char **labirinto, int linha, int coluna, TipoMonstroDatabase *monstroDatabase);
short Batalha(char ** labirinto, TipoNess * ness, TipoMob monstro);
int Movimenta_Ness(char **labirinto, TipoNess **ness, int x, int y,int linha, int coluna, TipoDados *dados,TipoMonstroDatabase *monstrodatabase);
int Movimenta_Estudante_Analise(char **labirinto, TipoNess *itens, int x, int y, int linha, int coluna, TipoDados *dados,long long int* NUM);
void ImprimirLabirinto(char **labirinto, int linha, int coluna);

#endif