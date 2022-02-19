#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "headers/backtracking.h"
#include "headers/dados.h"
#include <time.h>

/*Nessa função criamos uma matriz dinamicamente alocada e adicionamos a quantidade que teram no labirnto*/
int ** IniciarLabirinto(int linha, int coluna, TipoHess *hess,int quantChave){
    int **labirintof;

    labirintof = (int**)calloc((linha+1),sizeof(int*));
    for(int i = 0; i <= linha; i++){
        labirintof[i] = (int*)calloc((coluna+1),sizeof(int));
    }
    hess->quantChave = quantChave;

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
    }else{ // posição com MOB
        labirinto[linha][coluna] = 3;
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
int ChegouNoFim(int **labirinto, int i, int j){
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
int EhPosicaoBatalha(int **labirinto, int linha, int coluna){
  if(labirinto[linha][coluna] == 3){
      return 1;
  }
  return 0;
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
int Movimenta_Estudante(int ** labirinto, TipoHess *itens, int i, int j, int linha, int coluna, TipoDados * dados){
    if(ChegouNoFim(labirinto, i, j)){ /*O estudante chegou no final do labirinto*/
        DadosFinais(dados, j);
        MarcarPosicao(labirinto, i, j);
        printf("Linha: %d Coluna: %d\n", i, j);
        return 1;
    }
    if(UltrapassouLimites(i, j, linha, coluna)){ //Posição fora do espaço do labirinto
        dados->consegueSair = 0;
        return 0;
    }
    if(!EhParede(labirinto, i, j) && !EhPosicaoBatalha(labirinto, i, j)){ //posição valida
        dados->quantMovimentacao++;
        printf("Linha: %d Coluna: %d\n", i, j);
    }
    if(EhPosicaoBatalha(labirinto, i, j) ){ //TODO: Criar verificacao de Batalha
      //TODO: Verificar qual monstro e (Criar funcao para isso)
      //TODO: verificar se o poder do monstro eh menor que o do heroi
      //TODO: caso nao seja, verificar se o heroi tem algum especial restante
      dados->quantMovimentacao++;
      printf("Monstro na Linha: %d Coluna: %d\n", i, j);
      //TODO: Caso o heroi tenha usado especial, deve ser subtraido dos especiais restantes
      MonstroEliminado(labirinto, i, j);
    }
    /*Caso o estudante esteja em uma posição valida, ou seja, não esteja na parede, em um local que já foi
    e não seja uma porta fechada, o estudante marca essa posição e testa os movimentos para cima, para direita,
    para esquerda e para baixo. */
    if(!EhParede(labirinto, i, j) && !EstudantePassou(labirinto, i, j) && !EhPosicaoBatalha(labirinto, i, j)){
        MarcarPosicao(labirinto, i, j);
        if(Movimenta_Estudante(labirinto, itens,i - 1, j, linha, coluna,dados)); // para cima
        else{
            if(Movimenta_Estudante(labirinto, itens, i, j + 1, linha, coluna,dados)); // para a direita
            else{
                if(Movimenta_Estudante(labirinto, itens, i, j - 1, linha, coluna,dados)); // para a esquerda
                else{
                    if(Movimenta_Estudante(labirinto, itens, i + 1, j, linha, coluna,dados)); //para baixo
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
int Movimenta_Estudante_Analise(int ** labirinto, TipoHess *itens, int i, int j, int linha, int coluna, TipoDados * dados,long long int* NUM){
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
    if(!EhParede(labirinto, i, j) && !EhPosicaoBatalha(labirinto, i, j)){ //posição valida
        dados->quantMovimentacao++;
        printf("Linha: %d Coluna: %d\n", i, j);
    }
    if(EhPosicaoBatalha(labirinto, i, j) && itens->quantChave > 0){ //chegou em uma posição que tem uma porta fechada, então abri a porta e perde uma chave
      dados->quantMovimentacao++;
      printf("Linha: %d Coluna: %d\n", i, j);
      itens->quantChave--;
      MonstroEliminado(labirinto, i, j);
    }
    /*Caso o estudante esteja em uma posição valida, ou seja, não esteja na parede, em um local que já foi
    e não seja uma porta fechada, o estudante marca essa posição e testa os movimentos para cima, para direita,
    para esquerda e para baixo. */
    if(!EhParede(labirinto, i, j) && !EstudantePassou(labirinto, i, j) && !EhPosicaoBatalha(labirinto, i, j)){
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
