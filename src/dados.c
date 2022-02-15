#include "headers/dados.h"
#include <stdio.h>
#include <stdlib.h>

void IniciarDados(TipoDados *dados){
  dados->quantMovimentacao = -1; // começamos com -1 para desconsiderar a movimentação de quando ele está parado
  dados->ultimaColuna = -1;
  dados->consegueSair = 0;
}
void ImprimirDados(TipoDados dados){
    if(dados.consegueSair == 1) {
      printf("\nO estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n", dados.quantMovimentacao,dados.ultimaColuna);
    }
    else{
      printf("\nO estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n,", dados.quantMovimentacao);
    }
}
void DadosFinais(TipoDados * dados, int j){
  dados->quantMovimentacao ++;
  dados->ultimaColuna = j;
  dados->consegueSair = 1;
}