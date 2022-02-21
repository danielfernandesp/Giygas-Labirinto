#include <stdio.h>
#include <stdlib.h>
#include "headers/backtracking.h"


void LeArquivo(char **labirinto, FILE *arq,TipoNess *ness, TipoMonstroDatabase *monstroDatabase){
  char dadosIniciais[14];
  int sizeLinhaLabirinto, sizeColunaLabirinto;
  fgets(dadosIniciais,14,arq); // Le os dados do hess, dos monstros e tamanho do labirinto
  ness->poder = atoi(&dadosIniciais[0]);
  ness->EspeciaisRestantes = atoi(&dadosIniciais[1]);
  monstroDatabase->LilUfO.poder = atoi(&dadosIniciais[2]);
  monstroDatabase->LilUfO.drop = atoi(&dadosIniciais[3]);
  monstroDatabase->TerritorialOak.poder = atoi(&dadosIniciais[4]);
  monstroDatabase->TerritorialOak.drop = atoi(&dadosIniciais[5]);
  monstroDatabase->StarmanJr.poder = atoi(&dadosIniciais[6]);
  monstroDatabase->StarmanJr.drop = atoi(&dadosIniciais[7]);
  monstroDatabase->MasterBelch.poder = atoi(&dadosIniciais[8]);
  monstroDatabase->MasterBelch.drop = atoi(&dadosIniciais[9]);
  monstroDatabase->Giygas.poder = atoi(&dadosIniciais[10]);
  monstroDatabase->Giygas.drop = atoi(&dadosIniciais[11]);
  sizeLinhaLabirinto = atoi(&dadosIniciais[12]);
  sizeColunaLabirinto = atoi(&dadosIniciais[13]);
  /* A partir dqui o labirinto e criado com o tamanho certo*/
  labirinto = (char**)calloc((sizeLinhaLabirinto+1),sizeof(char*));
  for(int i = 0; i <= sizeLinhaLabirinto; i++){
    labirinto[i] = (char*)calloc((sizeColunaLabirinto+1),sizeof(char));
  }

    for(int i = 0; i <= sizeLinhaLabirinto; i++){
      for(int j = 0; j <= sizeColunaLabirinto; j++){
        fseek(arq,14+i+j,0);
        labirinto[i][j] = fgetc(arq);
      }
    }


}
