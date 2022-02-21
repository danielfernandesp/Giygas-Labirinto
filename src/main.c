#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers/backtracking.h"
#include "headers/menu.h"
#include "headers/dados.h"
#include "headers/gerador.h"

#define MODOANALISE 0  //SETAR 1 PARA ATIVAR, 0 PARA DESATIVAR

int main(int argc, char const *argv[]) {
  //Váriveis necessárias para criação do programa
  int i, j, valor, opcao, modo;
  int linhaNess, colunaNess;
  int poderArq,especiaisRestantesArq;
  char valorAux, arquivo[30];
  strcpy(arquivo, "\0"); //colocamos vazio em arquivo para impedir que o usuario acesse a opcao 2 antes de digitar o nome do arquivo
  FILE *arq;
  Labirinto labirinto;
  TipoNess ness;
  TipoMonstroDatabase monstroDatabase;
  TipoDados dados;
  TipoTamanhoArquivo tamanhoArquivo;
  long long int numRecurcoes;
  while(1){

    IniciarDados(&dados); // Iniciando uma nova analise do labirinto
    i = 0; //zerando as variaveis de leitura para evitar falha de segmentação
    j = 0; //zerando as variaveis de leitura para evitar falha de segmentação
    system("clear");
    MenuPrincipal(); //chamada do menu que mostra as opções ao usuário.
    scanf("%d", &opcao);
    system("clear");
    switch (opcao) {
      case 1: // Carregar novo arquivo de dados
        printf("Por favor digite o nome do arquivo: ");
        scanf("%s", arquivo);
        arq = fopen(arquivo, "r");
        while (!arq){
          printf("Erro ao ler o arquivo! \n");
          printf("Por favor digite o nome do arquivo: ");
          scanf("%s", arquivo);
          arq = fopen(arquivo, "r");
        }
        if (LeArquivo(labirinto, arq, &ness, &monstroDatabase, &tamanhoArquivo)){
          printf("Arquivo carregado com sucesso!!\n");
          system("read -p 'Pressione Enter para continuar...' var");
          fclose(arq);
        }


        break;
      case 2: // Processar e exibir resposta

        printf("%s\n", arquivo);
        if(strlen(arquivo) == 0){
          printf("Por favor carregue antes um arquivo de dados!\n");
          system("read -p 'Pressione Enter para continuar...' var");
          break;
        }
        else{
          linhaNess = LinhaNess(labirinto, tamanhoArquivo.qtdLinhas, tamanhoArquivo.qtdColunas);
          colunaNess = ColunaNess(labirinto, tamanhoArquivo.qtdLinhas, tamanhoArquivo.qtdColunas);

          if(MODOANALISE){
            numRecurcoes = -1; //inicializado como -1 para desconsiderar primeira chamada realizada pelo main
            Movimenta_Ness_Analise(labirinto, &ness, linhaNess, colunaNess, 0, 0, &dados,&monstroDatabase,&numRecurcoes);
            printf("\n\tMODO ANALISE!\n-->O numero total de chamadas recursivas foi de: %lld\n\n",numRecurcoes);
          }else{
            Movimenta_Ness(labirinto, &ness, linhaNess, colunaNess,tamanhoArquivo.qtdLinhas, tamanhoArquivo.qtdColunas, &dados, &monstroDatabase);
          }
          ImprimirLabirinto(labirinto, tamanhoArquivo.qtdLinhas, tamanhoArquivo.qtdColunas);
          ImprimirDados(dados);
          system("read -p 'Pressione Enter para continuar...' var");
          system("clear");
        }
        free(labirinto);
        strcpy(arquivo, "\0");

        break;

      default:
        MenuSaida();
        exit(0);
    }
  }

  return 0;
}