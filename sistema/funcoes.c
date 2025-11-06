#ifndef FUNCOES_C
#define FUNCOES_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../estruturas/jogador.h"

/*

  for em posições:

    printar todas os jogadores de posição i
    usuário seleciona o jogador
    esse jogador é colocado na estrutura (matriz e lista)


*/

/*

  a print deve ser como:

    contador (para usar no fseek) buscando a posição no arquivo 'posicao.txt'
    guarda a posição (linha) e usa o fseek:
      vai para o arquivo 'jogadores.txt' e printa o nome do jogador
      vai para o arquivo 'nacionalidade.txt' e printa a nacao do jogador
      vai para o arquivo 'times.txt' e printa o time do jogador
    usuário seleciona o jogador titular disponível pela linha
    usuário seleciona o jogador reserva disponível pela linha
    vai para a próxima posição


*/

void lerArquivos(FILE **jg, FILE **nac, FILE **pos, FILE **time)
{
  *jg = fopen("../../archive/jogadores.txt", "r");

  if (*jg == NULL)
  {
    printf("\nErro ao ler o arquivo 'jogadores.txt'");
    return;
  }

  *nac = fopen("../../archive/nacionalidades.txt", "r");

  if (*nac == NULL)
  {
    printf("\nErro ao ler o arquivo 'nacionalidades.txt'");
    return;
  }

  *pos = fopen("../../archive/posicoes.txt", "r");

  if (*pos == NULL)
  {
    printf("\nErro ao ler o arquivo 'posicoes.txt'");
    return;
  }

  *time = fopen("../../archive/times.txt", "r");

  if (*time == NULL)
  {
    printf("\nErro ao ler o arquivo 'times.txt'");
    return;
  }
}

void imprimirJogadores(char *pos)
{

    FILE *posicoesArq = fopen("../../archive/posicoes.txt", "r");
    FILE *jgArq  = fopen("../../archive/jogadores.txt", "r");
    FILE *timesArq = fopen("../../archive/times.txt", "r");
    FILE *nacoesArq = fopen("../../archive/nacionalidades.txt", "r");

    if (posicoesArq == NULL || jgArq == NULL || timesArq == NULL || nacoesArq == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char posicao[MAX];
    char nome[MAX];
    char time[MAX];
    char nacao[MAX];
    int linha = 0;
    
    while (fgets(posicao, sizeof(posicao), posicoesArq) &&
           fgets(nome, sizeof(nome), jgArq) &&
           fgets(time, sizeof(time), timesArq)  &&
           fgets(nacao, sizeof(nacao), nacoesArq) )
    {


         // remover \n do final das linhas
        posicao[strcspn(posicao, "\n")] = '\0';
        nome[strcspn(nome, "\n")] = '\0';
        time[strcspn(time, "\n")] = '\0';
        nacao[strcspn(nacao, "\n")] = '\0';

      

        if (strcmp(posicao, pos) == 0)
        {
            printf("\n%d - %s - %s - %s", linha+1, nome, time, nacao);
        }

        linha++;
    }

    fclose(posicoesArq);
    fclose(jgArq);
    fclose(nacoesArq);
    fclose(timesArq);

    printf ("\n");
}


void montarTimeAleatorio()
{
  for (int i = 0; i < 11; i++)
  {
    printf("\nSelecione dois %s", posicoesTitularesReservas[i]);

    imprimirJogadores(posicoesChar[i]);    

  }
}

#endif