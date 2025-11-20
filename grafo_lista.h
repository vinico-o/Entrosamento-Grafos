#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "jogador.h"

typedef struct No {
    int destino;
    float peso;
    struct No* prox;
} No;

typedef struct {
    No* cabeca;
} ListaAdj;

typedef struct {
    int numVertices;
    Jogador* jogadores;
    ListaAdj* lista;
} GrafoLista;

GrafoLista* criarGrafoLista(int n, Jogador* jogs);
void adicionarArestaLista(GrafoLista* g, int src, int dest, float peso);
void liberarGrafoLista(GrafoLista* g);

void dfsLista(GrafoLista* g, int inicio);
void bfsLista(GrafoLista* g, int inicio);
void dijkstraLista(GrafoLista* g, int inicio, int fim);
void primLista(GrafoLista* g);
void componentesConexosLista(GrafoLista* g);
int existeCaminhoLista(GrafoLista* g, int inicio, int fim);
void recomendarPasseLista(GrafoLista* g, int jogador);

#endif