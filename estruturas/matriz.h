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

    conexaoMatriz adj[11][11];

}grafoMatriz;


void inicializarMatriz(grafoMatriz *g)
{
    for (int i = 1; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            g->adj[i][j]->estaConectado = 0;
            g->adj[i][j]->peso = 0;
        }
    }

    // goleiro
    g->adj[GOL][ZD]->estaConectado = 1;
    g->adj[GOL][ZE]->estaConectado = 1;

    // zagueiro esquerda
    g->adj[ZE][GOL]->estaConectado = 1;
    g->adj[ZE][ZD]->estaConectado = 1;
    g->adj[ZE][LE]->estaConectado = 1;
    g->adj[ZE][ME]->estaConectado = 1;

    // zagueiro direita
    g->adj[ZD][GOL]->estaConectado = 1;
    g->adj[ZD][ZE]->estaConectado = 1;
    g->adj[ZD][LD]->estaConectado = 1;
    g->adj[ZD][MD]->estaConectado = 1;

    // lateral esquerda
    g->adj[LE][ZE]->estaConectado = 1;
    g->adj[LE][ME]->estaConectado = 1;

    // lateral direito
    g->adj[LD][ZD]->estaConectado = 1;
    g->adj[LD][MD]->estaConectado = 1;

    // meio campo esquerdo
    g->adj[ME][LE]->estaConectado = 1;
    g->adj[ME][ZE]->estaConectado = 1;
    g->adj[ME][MC]->estaConectado = 1;
    g->adj[ME][PE]->estaConectado = 1;

    // meio campo central
    g->adj[MC][ME]->estaConectado = 1;
    g->adj[MC][MD]->estaConectado = 1;
    g->adj[MC][CA]->estaConectado = 1;

    // meio campo direito
    g->adj[MD][LD]->estaConectado = 1;
    g->adj[MD][ZD]->estaConectado = 1;
    g->adj[MD][MC]->estaConectado = 1;
    g->adj[MD][PD]->estaConectado = 1;

    // ponta esquerda
    g->adj[PE][ME]->estaConectado = 1;
    g->adj[PE][CA]->estaConectado = 1;

    // ponta direita
    g->adj[PD][MD]->estaConectado = 1;
    g->adj[PD][CA]->estaConectado = 1;

    // centro avante
    g->adj[CA][PE]->estaConectado = 1;
    g->adj[CA][PD]->estaConectado = 1;
    g->adj[CA][MC]->estaConectado = 1;

}







#endif