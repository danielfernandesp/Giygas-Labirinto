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
void InserirPosicao(char **labirinto, int linha, int coluna, int valor){
    if(valor == 0){ // posição inicial do estudante
        labirinto[linha][coluna] = '@';
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
void ImprimirLabirinto(char **labirinto, int linha, int coluna){
    for(int i = 0; i < linha; i++){
      for(int j = 0; j < coluna; j++){

          printf("%c ",labirinto[i][j]);

      }
    printf("\n");
  }
}
/*Função para mostrar que o local já foi percorrido pelo estudante*/
void MarcarPosicao(char **labirinto, int linha, int coluna){
  labirinto[linha][coluna] = '*';
}
/*Função para mostrar local onde o estudante já passou*/
int NessPassou(char **labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == '*'){
    return 1;
  }
  return 0;
}
/*Função para encontrar a posição inicial do estudante*/
int NessEsta(char **labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == '@'){
    return 1;
  }
  return 0;
}
/*Função para encontrar se tá no final do labirinto*/
int ChegouNoFim(TipoNess *pNess) { //TODO: passar uma flag se o Giygas esta morto
  if(pNess->derrotouGiygas == 1){
    return 1;
  }else{
    if(pNess->derrotado == 1){
      return 1;
    }
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
int EhParede(char **labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == '.'){
    return 1;
  }
  return 0;
}
/*Função para abrir portas*/
void MonstroEliminado(char **labirinto, int linha, int coluna){
  labirinto[linha][coluna] = '*';
}
/*Função para conferir se determinada posição é uma porta fechada*/
short EhPosicaoBatalha(char **labirinto, int linha, int coluna) {
  if(labirinto[linha][coluna] >= 66 && labirinto[linha][coluna]<= 85){
    return 1;
  }
  return 0; // Nao tem monstro
}

TipoMob IdentificaAmeaca(char **labirinto, int linha, int coluna, TipoMonstroDatabase *monstroDatabase){
    if(labirinto[linha][coluna] == 'U'){
      return monstroDatabase->LilUfO;
    }else if(labirinto[linha][coluna] == 'T'){
      return monstroDatabase->TerritorialOak;
    }else if(labirinto[linha][coluna] == 'S'){
      return monstroDatabase->StarmanJr;
    }else if(labirinto[linha][coluna] == 'B'){
      return monstroDatabase->MasterBelch;
    }else if(labirinto[linha][coluna] == 'G'){
      return monstroDatabase->Giygas;
    }

}

/*Realiza a batalha, modificando os valores do ness e talvez do labirinto*/
short Batalha(char ** labirinto, TipoNess * ness, TipoMob monstro){
  if(monstro.identificador =='G'){
    if(ness->poder >= monstro.poder){
      ness->derrotouGiygas = 1;
      return 1;
    } else{
      ness->derrotado = 1;
      return 0;
    }
  }else{
    if(ness->poder >= monstro.poder){
      ness->poder += monstro.drop;
      return 1;
    }else{
      if(ness->EspeciaisRestantes > 0){
        ness->poder += monstro.drop;
        return 1;
      }
      ness->derrotado = 1;
      return 0;
    }
  }
}

/*Função para encontrar a posição da linha onde o estudante está*/
int LinhaNess(char **labirinto, int linha, int coluna){
  for(int i = 0; i < linha; i ++){
    for(int j = 0; j < coluna; j ++){
      if(labirinto[i][j] == '@'){
        return i;
      }
    }
  }
  return -1;
}
/*Função para encontrar a posição da coluna onde o estudante está*/
int ColunaNess(char **labirinto, int linha, int coluna){
  for(int i = 0; i < linha; i ++){
    for(int j = 0; j < coluna; j ++){
      if(labirinto[i][j] == '@'){
        return j;
      }
    }
  }
  return -1;
}

/*Função principal do programa, onde conferimos sempre se o estudante já chegou no final do labirinto e utilizamos o backtracking*/
int Movimenta_Ness(char **labirinto, TipoNess **ness, int x, int y,int linha, int coluna, TipoDados *dados,TipoMonstroDatabase *monstrodatabase) {
    if(ChegouNoFim(*ness)){ /*O estudante chegou no final do labirinto*/
        DadosFinais(dados, y);
        MarcarPosicao(labirinto, x, y);
        printf("Linha: %d Coluna: %d\n", x, y);
        return 1;
    }
    if(UltrapassouLimites(x, y, linha, coluna)){ //Posição fora do espaço do labirinto
        dados->consegueSair = 0;
        return 0;
    }
    if(!EhParede(labirinto, x, y) && !EhPosicaoBatalha(labirinto, x, y)){ //posição valida
        dados->quantMovimentacao++;
        printf("Linha: %d Coluna: %d\n", x, y);
    }
    if(EhPosicaoBatalha(labirinto, x, y)){
      if(Batalha(labirinto,*ness, IdentificaAmeaca(labirinto,x,y,monstrodatabase)) == 0){

      }
      dados->quantMovimentacao++;
      printf("Monstro %c na Linha: %d Coluna: %d\n",IdentificaAmeaca(labirinto, x, y,monstrodatabase).identificador, x, y);


    }
    /*Caso o estudante esteja em uma posição valida, ou seja, não esteja na parede, em um local que já foi
    e não seja uma porta fechada, o estudante marca essa posição e testa os movimentos para cima, para direita,
    para esquerda e para baixo. */
    if(!EhParede(labirinto, x, y) && !NessPassou(labirinto, x, y) && !EhPosicaoBatalha(labirinto, x, y)){
        MarcarPosicao(labirinto, x, y);
        if(Movimenta_Ness(labirinto, ness, x - 1, y, linha, coluna, dados,
                           monstrodatabase)); // para cima
        else{
            if(Movimenta_Ness(labirinto, ness, x, y + 1, linha, coluna, dados,
                             monstrodatabase)); // para a direita
            else{
                if(Movimenta_Ness(labirinto, ness, x, y - 1, linha, coluna,
                                 dados, monstrodatabase)); // para a esquerda
                else{
                    if(Movimenta_Ness(labirinto, ness, x + 1, y, linha, coluna,
                                     dados, monstrodatabase)); //para baixo
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
int Movimenta_Estudante_Analise(char **labirinto, TipoNess *itens, int x, int y, int linha, int coluna, TipoDados * dados,long long int* NUM){
    *NUM = *NUM + 1;
    if(ChegouNoFim(NULL)){  /*O estudante chegou no final do labirinto*/
        DadosFinais(dados, y);
        MarcarPosicao(labirinto, x, y);
        printf("Linha: %d Coluna: %d\n", x, y);
        return 1;
    }
    if(UltrapassouLimites(x, y, linha, coluna)){ //Posição fora do espaço do labirinto
        dados->consegueSair = 0;
        return 0;
    }
    if(!EhParede(labirinto, x, y) && !EhPosicaoBatalha(labirinto, x, y)){ //posição valida
        dados->quantMovimentacao++;
        printf("Linha: %d Coluna: %d\n", x, y);
    }
    if(EhPosicaoBatalha(labirinto, x, y) && itens->quantChave > 0){ //chegou em uma posição que tem uma porta fechada, então abri a porta e perde uma chave
      dados->quantMovimentacao++;
      printf("Linha: %d Coluna: %d\n", x, y);
      itens->quantChave--;
      MonstroEliminado(labirinto, x, y);
    }
    /*Caso o estudante esteja em uma posição valida, ou seja, não esteja na parede, em um local que já foi
    e não seja uma porta fechada, o estudante marca essa posição e testa os movimentos para cima, para direita,
    para esquerda e para baixo. */
    if(!EhParede(labirinto, x, y) && !NessPassou(labirinto, x, y) && !EhPosicaoBatalha(labirinto, x, y)){
        MarcarPosicao(labirinto, x, y);
        if(Movimenta_Estudante_Analise(labirinto, itens, x - 1, y, linha, coluna,dados,NUM)); // para cima
        else{
            if(Movimenta_Estudante_Analise(labirinto, itens, x, y + 1, linha, coluna,dados,NUM)); // para a direita
            else{
                if(Movimenta_Estudante_Analise(labirinto, itens, x, y - 1, linha, coluna,dados,NUM)); // para a esquerda
                else{
                    if(Movimenta_Estudante_Analise(labirinto, itens, x + 1, y, linha, coluna,dados,NUM)); //para baixo
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
