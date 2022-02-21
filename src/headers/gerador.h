#ifndef GERADOR_H
#define GERADOR_H

/*2) Vocês podem ainda criar uma opção (ou um outro programa) para a geração de
labirintos de teste, considerando todos os dados envolvidos e o formato, como descrito
acima. Labirintos não necessariamente possuem saída. Seu programa de geração de
arquivos de teste deverá ter alguns parâmetros de configuração, como largura e altura do
labirinto, quantidade de portas, quantidade de chaves iniciais, e “dificuldade” do
labirinto, entre outros, que vocês poderão colocar.*/
typedef struct {
  int qtdLinhas;
  int qtdColunas;
}TipoTamanhoArquivo;

short LeArquivo(char **labirinto, FILE *arq, TipoNess *ness,
                TipoMonstroDatabase *monstroDatabase,
                TipoTamanhoArquivo *tamanhoArquivo);
#endif