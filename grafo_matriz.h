#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "jogador.h"

typedef struct {
    int numVertices;
    Jogador* jogadores;
    float** matriz;
} GrafoMatriz;

GrafoMatriz* criarGrafoMatriz(int n, Jogador* jogs);
void adicionarArestaMatriz(GrafoMatriz* g, int src, int dest, float peso);
void liberarGrafoMatriz(GrafoMatriz* g);

void dfsMatriz(GrafoMatriz* g, int inicio);
void bfsMatriz(GrafoMatriz* g, int inicio);
void dijkstraMatriz(GrafoMatriz* g, int inicio, int fim);
void primMatriz(GrafoMatriz* g);
void componentesConexosMatriz(GrafoMatriz* g);
int existeCaminhoMatriz(GrafoMatriz* g, int inicio, int fim);
void recomendarPasseMatriz(GrafoMatriz* g, int jogador);

#endif