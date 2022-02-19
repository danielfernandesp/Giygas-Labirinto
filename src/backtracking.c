#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "headers/backtracking.h"
#include "headers/dados.h"
#include <time.h>

/*Nessa função criamos uma matriz dinamicamente alocada e adicionamos a quantidade que teram no labirnto*/
int **IniciarLabirinto(int linha, int coluna, TipoNess *hess, int poder, int especiaisRestantes) {
    int **labirintof;

    labirintof = (int**)calloc((linha+1),sizeof(int*));
    for(int i = 0; i <= linha; i++){
        labirintof[i] = (int*)calloc((coluna+1),sizeof(int));
    }
    hess->poder = poder;
    hess->EspeciaisRestantes = especiaisRestantes;

    return labirintof;
}
/*Nessa função inserimos os valores nos locais certos de cada celula da matriz*/
void InserirPosicao(int ** labirinto, int linha, int coluna, int valor){
    if(valor == 0){ // posição inicial do estudante
        labirinto[linha][coluna] = 0;
    }else if(valor == 1){ // posição livre
        labirinto[linha][coluna] = 1;
    }else if(valor == 2){ //posição com parede
        labirinto[linha][coluna] = 2;
    }else if(valor == 3){ // posição com LiL UFO
        labirinto[linha][coluna] = 3;
    }else if(valor == 4){ // posição com Territorial Oak
        labirinto[linha][coluna] = 4;
    }else if(valor == 5){ // posição com Starman Junior
        labirinto[linha][coluna] = 5;
    }else if(valor == 6){ // posição com Master Belch
        labirinto[linha][coluna] = 6;
    }else{
        labirinto[linha][coluna] = 7; //posiçao com Giygas
    }
}
/*Função para exibir o labirinto percorrido pelo estudante*/
void ImprimirLabirinto(int ** labirinto, int linha, int coluna){
    for(int i = 0; i < linha; i++){
      for(int j = 0; j < coluna; j++){
        if(labirinto[i][j] == -1){ // trocamos  a posição do estudandte por * pra mostrar que ele passou ali
            printf("* ");
        }else{
          printf("%d ",labirinto[i][j]);
        }
      }
    printf("\n");
  }
}
/*Função para mostrar que o local já foi percorrido pelo estudante*/
void MarcarPosicao(int ** labirinto, int linha, int coluna){
  labirinto[linha][coluna] = -1;
}
/*Função para mostrar local onde o estudante já passou*/
int EstudantePassou(int ** labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == -1){
    return 1;
  }
  return 0;
}
/*Função para encontrar a posição inicial do estudante*/
int EstudanteEsta(int ** labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == 0){
    return 1;
  }
  return 0;
}
/*Função para encontrar se tá no final do labirinto*/
int ChegouNoFim(int **labirinto, int i, int j){ //TODO: passar uma flag se o Giygas esta morto
  if(i <= 0 && !EhParede(labirinto, i, j)){
    return 1;
  }
  return 0;
}
int UltrapassouLimites(int i, int j, int linha, int coluna){
  if(j >= coluna || i >= linha || j < 0){
    return 1;
  }
  return 0;
}
/*Função para conferir se determinada posição é uma parede*/
int EhParede(int ** labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == 2){
    return 1;
  }
  return 0;
}
/*Função para abrir portas*/
void MonstroEliminado(int ** labirinto, int linha, int coluna){
  labirinto[linha][coluna] = 1;
}
/*Função para conferir se determinada posição é uma porta fechada*/
short EhPosicaoBatalha(int **labirinto, int linha, int coluna, TipoMonstroDatabase *monstroDatabase) {
  if(labirinto[linha][coluna] >= 3 && labirinto[linha][coluna]<= 7){
    return 1;
  }
  return 0; // Nao tem monstro
}

TipoMob IdentificaAmeaca(int **labirinto, int linha, int coluna, TipoMonstroDatabase *monstroDatabase){
  if(labirinto[linha][coluna] >= 3 && labirinto[linha][coluna]<= 7){
    if(labirinto[linha][coluna] == 3){
      return monstroDatabase->LilUfO;
    }else if(labirinto[linha][coluna] == 4){
      return monstroDatabase->TerritorialOak;
    }else if(labirinto[linha][coluna] == 5){
      return monstroDatabase->StarmanJr;
    }else if(labirinto[linha][coluna] == 6){
      return monstroDatabase->MasterBelch;
    }else {
      return monstroDatabase->Giygas;
    }
  }
}

/*Função para encontrar a posição da linha onde o estudante está*/
int LinhaEstudante(int ** labirinto, int linha, int coluna){
  for(int i = 0; i < linha; i ++){
    for(int j = 0; j < coluna; j ++){
      if(labirinto[i][j] == 0){
        return i;
      }
    }
  }
  return -1;
}
/*Função para encontrar a posição da coluna onde o estudante está*/
int ColunaEstudante(int ** labirinto, int linha, int coluna){
  for(int i = 0; i < linha; i ++){
    for(int j = 0; j < coluna; j ++){
      if(labirinto[i][j] == 0){
        return j;
      }
    }
  }
  return -1;
}

/*Função principal do programa, onde conferimos sempre se o estudante já chegou no final do labirinto e utilizamos o backtracking*/
int Movimenta_Estudante(int **labirinto, TipoNess *ness, int x, int y,int linha, int coluna, TipoDados *dados,TipoMonstroDatabase *monstrodatabase) {
    if(ChegouNoFim(labirinto, x,y)){ /*O estudante chegou no final do labirinto*/
        DadosFinais(dados, y);
        MarcarPosicao(labirinto, x, y);
        printf("Linha: %d Coluna: %d\n", x, y);
        return 1;
    }
    if(UltrapassouLimites(x, y, linha, coluna)){ //Posição fora do espaço do labirinto
        dados->consegueSair = 0;
        return 0;
    }
    if(!EhParede(labirinto, x, y) && !EhPosicaoBatalha(labirinto, x, y, monstrodatabase)){ //posição valida
        dados->quantMovimentacao++;
        printf("Linha: %d Coluna: %d\n", x, y);
    }
    if(EhPosicaoBatalha(labirinto, x, y,monstrodatabase) != 0){
      if(ness->poder >= IdentificaAmeaca(labirinto, x, y,monstrodatabase).poder){
        if(IdentificaAmeaca(labirinto, x, y,monstrodatabase).identificador == monstrodatabase->Giygas.identificador){
          ness->derrotouGiygas = 1;
        }
      }else if(IdentificaAmeaca(labirinto, x, y,monstrodatabase).identificador != monstrodatabase->Giygas.identificador && ness->EspeciaisRestantes > 0){
        MonstroEliminado(labirinto, x, y);
        ness->EspeciaisRestantes--;
      }
      dados->quantMovimentacao++;
      printf("Monstro %c na Linha: %d Coluna: %d\n",IdentificaAmeaca(labirinto, x, y,monstrodatabase).identificador, x, y);


    }
    /*Caso o estudante esteja em uma posição valida, ou seja, não esteja na parede, em um local que já foi
    e não seja uma porta fechada, o estudante marca essa posição e testa os movimentos para cima, para direita,
    para esquerda e para baixo. */
    if(!EhParede(labirinto, x, y) && !EstudantePassou(labirinto, x, y) && !EhPosicaoBatalha(labirinto, x, y, NULL)){
        MarcarPosicao(labirinto, x, y);
        if(Movimenta_Estudante(labirinto, ness, x - 1, y, linha, coluna,
                                dados, NULL)); // para cima
        else{
            if(Movimenta_Estudante(labirinto, ness, x, y + 1, linha, coluna,
                                  dados, NULL)); // para a direita
            else{
                if(Movimenta_Estudante(labirinto, ness, x, y - 1, linha, coluna,
                                      dados, NULL)); // para a esquerda
                else{
                    if(Movimenta_Estudante(labirinto, ness, x + 1, y, linha,
                                          coluna, dados, NULL)); //para baixo
                    else{
                        return 0;
                    }
                }
            }
        }
    }else{
      return 0;
    }
    return 1;
}

/*Mesma função, porém com o modo analise*/
int Movimenta_Estudante_Analise(int ** labirinto, TipoNess *itens, int i, int j, int linha, int coluna, TipoDados * dados,long long int* NUM){
    *NUM = *NUM + 1;
    if(ChegouNoFim(labirinto, i, j)){  /*O estudante chegou no final do labirinto*/
        DadosFinais(dados, j);
        MarcarPosicao(labirinto, i, j);
        printf("Linha: %d Coluna: %d\n", i, j);
        return 1;
    }
    if(UltrapassouLimites(i, j, linha, coluna)){ //Posição fora do espaço do labirinto
        dados->consegueSair = 0;
        return 0;
    }
    if(!EhParede(labirinto, i, j) && !EhPosicaoBatalha(labirinto, i, j, NULL)){ //posição valida
        dados->quantMovimentacao++;
        printf("Linha: %d Coluna: %d\n", i, j);
    }
    if(EhPosicaoBatalha(labirinto, i, j, NULL) && itens->quantChave > 0){ //chegou em uma posição que tem uma porta fechada, então abri a porta e perde uma chave
      dados->quantMovimentacao++;
      printf("Linha: %d Coluna: %d\n", i, j);
      itens->quantChave--;
      MonstroEliminado(labirinto, i, j);
    }
    /*Caso o estudante esteja em uma posição valida, ou seja, não esteja na parede, em um local que já foi
    e não seja uma porta fechada, o estudante marca essa posição e testa os movimentos para cima, para direita,
    para esquerda e para baixo. */
    if(!EhParede(labirinto, i, j) && !EstudantePassou(labirinto, i, j) && !EhPosicaoBatalha(labirinto, i, j, NULL)){
        MarcarPosicao(labirinto, i, j);
        if(Movimenta_Estudante_Analise(labirinto, itens,i - 1, j, linha, coluna,dados,NUM)); // para cima
        else{
            if(Movimenta_Estudante_Analise(labirinto, itens, i, j + 1, linha, coluna,dados,NUM)); // para a direita
            else{
                if(Movimenta_Estudante_Analise(labirinto, itens, i, j - 1, linha, coluna,dados,NUM)); // para a esquerda
                else{
                    if(Movimenta_Estudante_Analise(labirinto, itens, i + 1, j, linha, coluna,dados,NUM)); //para baixo
                    else{
                        return 0;
                    }
                }
            }
        }
    }else{
      return 0;
    }
    return 1;
}
