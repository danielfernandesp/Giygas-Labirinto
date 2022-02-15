#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void ModoFacil(){ // Labirintos de 5x5 até 10x10
  srand( (unsigned)time(NULL) );
  int linha = 0, coluna = 0, quantChave = 0, valor = 0, estudanteLinha = 0, estudanteColuna = 0;
  char arquivo[30];
  FILE *arq;
  linha = 5 + rand() % 6;
  estudanteLinha = rand() % linha; // estudante fica em uma posição aleatoria da linha
  coluna = 5 + rand() % 6;
  estudanteColuna = rand() % coluna; // estudante fica em uma posição aleatoria da coluna
  quantChave = rand() % 3;
  printf("Nome do arquivo(exemplo.txt): ");
  scanf("%s", arquivo);
  arq = fopen(arquivo, "w"); // w para escrita
  if(arq == NULL){
    printf ("Houve um erro ao abrir o arquivo.\n");
  }
  else{
    fprintf(arq, "%d %d %d \n", linha, coluna, quantChave);
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if( i == estudanteLinha && j == estudanteColuna){ // quando chegar na posição[i][j] correspondente ao local onde o estudante está, ele escreve o valor 0
                valor = 0;
            }
            else if (i == rand() % linha && j == rand() % coluna){ // dificilmente terá portas ou paredes
                valor = 2 + rand() % 2; // somamaos 1 pra nunca cair no local onde o estudante já está
            }
            else{
                valor = 1;
            }
            fprintf(arq, "%d", valor);
        }
        fputc('\n', arq); // no final de cada linha adicionamos uma quebra de linha
    }
    fclose(arq);
  }
}
void ModoMedio(){   // Labirintos de 10x10 até 25x25
  srand( (unsigned)time(NULL) );
  int linha = 0, coluna = 0, quantChave = 0, valor = 0, estudanteLinha = 0, estudanteColuna = 0;
  char arquivo[30];
  FILE *arq;
  linha = 10 + rand() % 16;
  estudanteLinha = 10 + rand() % 10; // estudante fica em uma posição aleatoria da linha
  while(estudanteLinha > linha){
    estudanteLinha = 10 + rand() % 16; // estudante fica em uma posição aleatoria da linha
  }
  coluna = 10 + rand() % 16;
  estudanteColuna = rand() % coluna; // estudante fica em uma posição aleatoria da coluna
  quantChave = (rand() % linha + rand() % coluna) * 2;
  printf("Nome do arquivo(exemplo.txt): ");
  scanf("%s", arquivo);
  arq = fopen(arquivo, "w"); // w para escrita
  if(arq == NULL){
    printf ("Houve um erro ao abrir o arquivo.\n");
  }
  else{
    fprintf(arq, "%d %d %d \n", linha, coluna, quantChave);
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
          if(i == estudanteLinha && j == estudanteColuna){ // quando chegar na posição[i][j] correspondente ao local onde o estudante está, ele escreve o valor 0
              valor = 0;
          }
          else{
              valor = 1 + rand() % 3;
          }
            fprintf(arq, "%d", valor);
        }
        fputc('\n', arq); // no final de cada linha adicionamos uma quebra de linha
    }
    fclose(arq);
  }
}
void ModoDificil(){   // Labirintos de 25x25 até 50x50
  srand( (unsigned)time(NULL) );
  int linha = 0, coluna = 0, quantChave = 0, valor = 0, estudanteLinha = 0, estudanteColuna = 0;
  char arquivo[30];
  FILE *arq;
  linha = 25 + rand() % 26;
  estudanteLinha = linha-1; // estudante fica na ultima posicao da linha
  coluna = 25 + rand() % 26;
  estudanteColuna = rand() % coluna-1; // estudante fica em uma posição aleatoria da coluna
  quantChave = rand() % linha + rand() % coluna;
  printf("Nome do arquivo(exemplo.txt): ");
  scanf("%s", arquivo);
  arq = fopen(arquivo, "w"); // w para escrita
  if(arq == NULL){
    printf ("Houve um erro ao abrir o arquivo.\n");
  }
  else{
    fprintf(arq, "%d %d %d \n", linha, coluna, quantChave);
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if( i == estudanteLinha && j == estudanteColuna){ // quando chegar na posição[i][j] correspondente ao local onde o estudante está, ele escreve o valor 0
                valor = 0;
            }
            else{
                valor = 1 + rand() % 3;
            }
            fprintf(arq, "%d", valor);
        }
        fputc('\n', arq); // no final de cada linha adicionamos uma quebra de linha
    }
    fclose(arq);
  }
}