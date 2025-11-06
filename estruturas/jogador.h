#ifndef JOGADOR_H
#define JOGADOR_H

#define MAX 50
/* 
 time = 2
 nacionalidade = 1 
padrao = 0
 */


enum Nacionalidade
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
};

enum Time
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
};

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

typedef struct jogador
{
    char nome_jogador[MAX];
    Time time;
    Nacionalidade nacionalidade;
    Posicao posicao;
} Jogador;

#endif