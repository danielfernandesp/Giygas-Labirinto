#ifndef DADOS_H
#define DADOS_H

typedef struct{
    int quantMovimentacao;
    int consegueSair;
    int ultimaColuna;
}TipoDados;

#endif

void IniciarDados(TipoDados *dados);
void ImprimirDados(TipoDados dados);
void DadosFinais(TipoDados * dados, int j);