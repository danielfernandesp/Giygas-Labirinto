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
  int linhaEstudante, colunaEstudante;
  int  linhaArq, colunaArq;
  int poderArq,especiaisRestantesArq;
  char valorAux, arquivo[30];
  strcpy(arquivo, "\0"); //colocamos vazio em arquivo para impedir que o usuario acesse a opcao 2 antes de digitar o nome do arquivo
  FILE *arq;
  Labirinto labirinto;
  TipoNess ness;
  TipoMonstroDatabase monstroDatabase;
  TipoDados dados;
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

          // lemos a primeira linha e armazenamos os valores do poder e especiais restantes do ness
          fscanf(arq,"%d %d\n", &poderArq, &especiaisRestantesArq);

          labirinto = IniciarLabirinto(linhaArq, colunaArq, &ness, poderArq,especiaisRestantesArq); // criamos uma matriz com o tamanho passado pelo arquivo

          while(!feof(arq) && !ferror(arq)){// enquanto não for fim do arquivo e não for erro de leitura, continuamos lendo
            valorAux = fgetc(arq); //valorAux recebe um caracter
            valor = valorAux-48; //esse caracter é convertido para int e passado para valor
            if(valor == EOF){ //se esse valor for o final da leitura, encerramos o while
              break;
            }
            /*sempre que o valorAux for uma quebra de linha, aumentamos a linha e zeramos a coluna
            exemplo:
            012 <- quando chegar aqui, o i vai passar a valer 1 e a coluna que era 3 voltara para 0
            345
            678
            */
            if(valorAux == '\n'){
              i++;
              j = 0;
            }else{
              InserirPosicao(labirinto, i, j, valor);
              j++;
            }
          }
          printf("Arquivo carregado com sucesso!!\n");
          system("read -p 'Pressione Enter para continuar...' var");
          fclose(arq);
        break;
      case 2: // Processar e exibir resposta

        printf("%s\n", arquivo);
        if(strlen(arquivo) == 0){
          printf("Por favor carregue antes um arquivo de dados!\n");
          system("read -p 'Pressione Enter para continuar...' var");
          break;
        }
        else{
          linhaEstudante = LinhaEstudante(labirinto, linhaArq, colunaArq);
          colunaEstudante = ColunaEstudante(labirinto, linhaArq, colunaArq);

          if(MODOANALISE){
            numRecurcoes = -1; //inicializado como -1 para desconsiderar primeira chamada realizada pelo main
            Movimenta_Estudante_Analise(labirinto, &ness, linhaEstudante, colunaEstudante, linhaArq, colunaArq, &dados,&numRecurcoes);
            printf("\n\tMODO ANALISE!\n-->O numero total de chamadas recursivas foi de: %lld\n\n",numRecurcoes);
          }else{
            Movimenta_Estudante(labirinto, &ness, linhaEstudante,
                                colunaEstudante, linhaArq, colunaArq, &dados,
                                &monstroDatabase);
          }
          ImprimirLabirinto(labirinto, linhaArq, colunaArq);
          ImprimirDados(dados);
          system("read -p 'Pressione Enter para continuar...' var");
          system("clear");
        }
        free(labirinto);
        strcpy(arquivo, "\0");

        break;
        case 3:
          MenuPrincipalGerador();
          scanf("%d", &modo);
          switch (modo) {
            case 1: // Fácil
              ModoFacil();
              printf("Arquivo Criado com Sucesso!\n");
              system("read -p 'Pressione Enter para continuar...' var");
              break;
            case 2: // Intermediario
              ModoMedio();
              printf("Arquivo Criado com Sucesso!\n");
              system("read -p 'Pressione Enter para continuar...' var");
              break;
            case 3: // Dificil
              ModoDificil();
              printf("Arquivo Criado com Sucesso!\n");
              system("read -p 'Pressione Enter para continuar...' var");
              break;
            default:
              printf("Opção Invalida!\n");
              system("read -p 'Pressione Enter para continuar...' var");
              break;
          }
          break;
      default:
        MenuSaida();
        exit(0);
    }
  }

  return 0;
}