#ifndef JOGADOR_H
#define JOGADOR_H

#define TAMANHO 22
#define MAX 50
/* 
 time = 2
 nacionalidade = 1 
padrao = 0
 */


typedef enum
{
    BRASIL,
    ARGENTINA,
    COLOMBIA,
    VENEZUELA,
    URUGUAI,
    PARAGUAI,
    HOLANDA,
    ITALIA,
    FRANCA
}Nacionalidade;

typedef enum
{
    PALMEIRAS,
    FLAMENGO,
    CORINTHIANS,
    SAO_PAULO,
    FLUMINENSE,
    BOTAFOGO,
    MIRASSOL,
    CRUZEIRO,
    BRAGANTINO,
    VITORIA,
    JUVENTUDE,
    SPORT,
    ATLETICO_MINEIRO,
    VASCO,
    GREMIO,
    INTERNACIONAL,
    BAHIA,
    FORTALEZA,
    CEARA,
    SANTOS
}Time;

typedef enum {
    GOL,      // Goleiro
    LD,       // Lateral Direito
    ZD,       // Zagueiro Direito
    ZE,       // Zagueiro Esquerdo
    LE,       // Lateral Esquerdo
    MC,       // Meia Central
    MD,       // Meia Central Direito
    ME,       // Meia Central Esquerdo
    PD,       // Ponta Direita
    CA,       // Centro Avante (Atacante Central)
    PE        // Ponta Esquerda
} Posicao;

char *posicoesTitularesReservas[] = {"Goleiros", "Laterais Direito", "Zagueiros Direito", "Zagueiros Esquerdo", "Laterais Esquerdo", 
                    "Meias Central", "Meias Central Direito", "Meias Central Esquerdo", "Pontas Direita", 
                    "Centro Avante", "Ponta Esquerda"};
char *posicoesChar[] = {"GOL", "LD", "LE", "ZD", "ZE", "MC", "ME", "MD", "PE", "PD", "CA"};


typedef struct jogador
{
    char nome_jogador[MAX];
    Time time;
    Nacionalidade nacionalidade;
    Posicao posicao;
} Jogador;

#endif