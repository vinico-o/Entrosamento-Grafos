#ifndef MATRIZ_H
#define MATRIZ_H
#include "jogador.h"
#include <stdio.h>

#define TAMANHO 22

typedef conexaoMatriz{

    Jogador j;
    int estaConectado;
    int peso;

}conexaoMatriz;

typedef grafoMatriz{

    conexaoMatriz adj[TAMANHO][TAMANHO];

}grafoMatriz;


void montarConexoesMatriz(grafoMatriz *g, int time)
{
    //O indice indica a posicao da outra componente conexa (time reserva)
    int indice;

    if (time == 1)
    {
        indice = 0;
    }

    if (time == 2)
    {
        indice = 11;
    }

    // formação 4-3-3
    // goleiro
    g->adj[GOL + indice][ZD + indice]->estaConectado = 1;
    g->adj[GOL + indice][ZE + indice]->estaConectado = 1;

    // zagueiro esquerda
    g->adj[ZE + indice][GOL + indice]->estaConectado = 1;
    g->adj[ZE + indice][ZD + indice]->estaConectado = 1;
    g->adj[ZE + indice][LE + indice]->estaConectado = 1;
    g->adj[ZE + indice][ME + indice]->estaConectado = 1;

    // zagueiro direita
    g->adj[ZD + indice][GOL + indice]->estaConectado = 1;
    g->adj[ZD + indice][ZE + indice]->estaConectado = 1;
    g->adj[ZD + indice][LD + indice]->estaConectado = 1;
    g->adj[ZD + indice][MD + indice]->estaConectado = 1;

    // lateral esquerda
    g->adj[LE + indice][ZE + indice]->estaConectado = 1;
    g->adj[LE + indice][ME + indice]->estaConectado = 1;

    // lateral direito
    g->adj[LD + indice][ZD + indice]->estaConectado = 1;
    g->adj[LD + indice][MD + indice]->estaConectado = 1;

    // meio campo esquerdo
    g->adj[ME + indice][LE + indice]->estaConectado = 1;
    g->adj[ME + indice][ZE + indice]->estaConectado = 1;
    g->adj[ME + indice][MC + indice]->estaConectado = 1;
    g->adj[ME + indice][PE + indice]->estaConectado = 1;

    // meio campo central
    g->adj[MC + indice][ME + indice]->estaConectado = 1;
    g->adj[MC + indice][MD + indice]->estaConectado = 1;
    g->adj[MC + indice][CA + indice]->estaConectado = 1;

    // meio campo direito
    g->adj[MD + indice][LD + indice]->estaConectado = 1;
    g->adj[MD + indice][ZD + indice]->estaConectado = 1;
    g->adj[MD + indice][MC + indice]->estaConectado = 1;
    g->adj[MD + indice][PD + indice]->estaConectado = 1;

    // ponta esquerda
    g->adj[PE + indice][ME + indice]->estaConectado = 1;
    g->adj[PE + indice][CA + indice]->estaConectado = 1;

    // ponta direita
    g->adj[PD + indice][MD + indice]->estaConectado = 1;
    g->adj[PD + indice][CA + indice]->estaConectado = 1;

    // centro avante
    g->adj[CA + indice][PE + indice]->estaConectado = 1;
    g->adj[CA + indice][PD + indice]->estaConectado = 1;
    g->adj[CA + indice][MC + indice]->estaConectado = 1;
}

void inicializarMatriz(grafoMatriz *g)
{
    for (int i = 1; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            g->adj[i][j]->estaConectado = 0;
            g->adj[i][j]->peso = 0;
        }
    }
}

int calcularEntrosamentoMatriz (Jogador j1, Jogador j2)
{
    int entrosamento = 0;

    if (j1.Nacionalidade == j2.Nacionalidade)
    {
        entrosamento = 1;
    }

    else if (j1.Time == j2.Time)
    {
        entrosamento = 2;
    }

    return entrosamento;
}






#endif