#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "grafo_matriz.h"

GrafoMatriz* criarGrafoMatriz(int n, Jogador* jogs) {
    GrafoMatriz* g = (GrafoMatriz*)malloc(sizeof(GrafoMatriz));
    g->numVertices = n;
    g->jogadores = jogs;
    g->matriz = (float**)malloc(n * sizeof(float*));

    for (int i = 0; i < n; i++) {
        g->matriz[i] = (float*)malloc(n * sizeof(float));
        for (int j = 0; j < n; j++) {
            g->matriz[i][j] = 0.0;
        }
    }
    return g;
}

void adicionarArestaMatriz(GrafoMatriz* g, int src, int dest, float peso) {
    g->matriz[src][dest] = peso;
    g->matriz[dest][src] = peso;
}

void liberarGrafoMatriz(GrafoMatriz* g) {
    for (int i = 0; i < g->numVertices; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}

void dfsRecursivoMatriz(GrafoMatriz* g, int v, int* visitado) {
    visitado[v] = 1;
    printf("%s (%s) -> ", g->jogadores[v].nome, g->jogadores[v].posicao);

    for (int i = 0; i < g->numVertices; i++) {
        if (g->matriz[v][i] > 0 && !visitado[i]) {
            dfsRecursivoMatriz(g, i, visitado);
        }
    }
}

void dfsMatriz(GrafoMatriz* g, int inicio) {
    printf("\n=== DFS (Matriz) iniciando em %s ===\n", g->jogadores[inicio].nome);
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    dfsRecursivoMatriz(g, inicio, visitado);
    printf("FIM\n");
    free(visitado);
}

void bfsMatriz(GrafoMatriz* g, int inicio) {
    printf("\n=== BFS (Matriz) iniciando em %s ===\n", g->jogadores[inicio].nome);
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    int* fila = (int*)malloc(g->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    visitado[inicio] = 1;
    fila[tras++] = inicio;

    while (frente < tras) {
        int v = fila[frente++];
        printf("%s (%s) -> ", g->jogadores[v].nome, g->jogadores[v].posicao);

        for (int i = 0; i < g->numVertices; i++) {
            if (g->matriz[v][i] > 0 && !visitado[i]) {
                visitado[i] = 1;
                fila[tras++] = i;
            }
        }
    }
    printf("FIM\n");
    free(visitado);
    free(fila);
}

typedef struct {
    int vertice;
    float dist;
} HeapNoMatriz;

typedef struct {
    HeapNoMatriz* array;
    int tamanho;
    int capacidade;
} MinHeapMatriz;

MinHeapMatriz* criarHeapMatriz(int cap) {
    MinHeapMatriz* h = (MinHeapMatriz*)malloc(sizeof(MinHeapMatriz));
    h->array = (HeapNoMatriz*)malloc(cap * sizeof(HeapNoMatriz));
    h->tamanho = 0;
    h->capacidade = cap;
    return h;
}

void trocarMatriz(HeapNoMatriz* a, HeapNoMatriz* b) {
    HeapNoMatriz temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUpMatriz(MinHeapMatriz* h, int idx) {
    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (h->array[idx].dist < h->array[pai].dist) {
            trocarMatriz(&h->array[idx], &h->array[pai]);
            idx = pai;
        } else break;
    }
}

void heapifyDownMatriz(MinHeapMatriz* h, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < h->tamanho && h->array[esq].dist < h->array[menor].dist)
        menor = esq;
    if (dir < h->tamanho && h->array[dir].dist < h->array[menor].dist)
        menor = dir;

    if (menor != idx) {
        trocarMatriz(&h->array[idx], &h->array[menor]);
        heapifyDownMatriz(h, menor);
    }
}

void inserirHeapMatriz(MinHeapMatriz* h, int v, float d) {
    h->array[h->tamanho].vertice = v;
    h->array[h->tamanho].dist = d;
    heapifyUpMatriz(h, h->tamanho);
    h->tamanho++;
}

HeapNoMatriz extrairMinMatriz(MinHeapMatriz* h) {
    HeapNoMatriz min = h->array[0];
    h->array[0] = h->array[h->tamanho - 1];
    h->tamanho--;
    heapifyDownMatriz(h, 0);
    return min;
}

void dijkstraMatriz(GrafoMatriz* g, int inicio, int fim) {
    printf("\n=== Dijkstra (Matriz) de %s ate %s ===\n",
           g->jogadores[inicio].nome, g->jogadores[fim].nome);

    float* dist = (float*)malloc(g->numVertices * sizeof(float));
    int* ant = (int*)malloc(g->numVertices * sizeof(int));
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));

    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = FLT_MAX;
        ant[i] = -1;
    }
    dist[inicio] = 0.0;

    MinHeapMatriz* h = criarHeapMatriz(g->numVertices * 10);
    inserirHeapMatriz(h, inicio, 0.0);

    while (h->tamanho > 0) {
        HeapNoMatriz atual = extrairMinMatriz(h);
        int u = atual.vertice;

        if (visitado[u]) continue;
        visitado[u] = 1;

        for (int v = 0; v < g->numVertices; v++) {
            float peso = g->matriz[u][v];
            if (peso > 0 && !visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                ant[v] = u;
                inserirHeapMatriz(h, v, dist[v]);
            }
        }
    }

    if (dist[fim] == FLT_MAX) {
        printf("Nao ha caminho!\n");
    } else {
        printf("Distancia: %.2f\n", dist[fim]);
        printf("Caminho: ");
        int caminho[22], tam = 0;
        for (int v = fim; v != -1; v = ant[v]) {
            caminho[tam++] = v;
        }
        for (int i = tam - 1; i >= 0; i--) {
            printf("%s", g->jogadores[caminho[i]].nome);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }

    free(dist);
    free(ant);
    free(visitado);
    free(h->array);
    free(h);
}

void primMatriz(GrafoMatriz* g) {
    printf("\n=== Arvore Geradora Minima - Prim (Matriz) ===\n");

    int* inMST = (int*)calloc(g->numVertices, sizeof(int));
    float* chave = (float*)malloc(g->numVertices * sizeof(float));
    int* pai = (int*)malloc(g->numVertices * sizeof(int));

    for (int i = 0; i < g->numVertices; i++) {
        chave[i] = FLT_MAX;
        pai[i] = -1;
    }
    chave[0] = 0.0;

    MinHeapMatriz* h = criarHeapMatriz(g->numVertices * 10);
    inserirHeapMatriz(h, 0, 0.0);

    float pesoTotal = 0.0;

    while (h->tamanho > 0) {
        HeapNoMatriz atual = extrairMinMatriz(h);
        int u = atual.vertice;

        if (inMST[u]) continue;
        inMST[u] = 1;

        if (pai[u] != -1) {
            printf("%s -- %.2f -- %s\n",
                   g->jogadores[pai[u]].nome, chave[u], g->jogadores[u].nome);
            pesoTotal += chave[u];
        }

        for (int v = 0; v < g->numVertices; v++) {
            float peso = g->matriz[u][v];
            if (peso > 0 && !inMST[v] && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
                inserirHeapMatriz(h, v, chave[v]);
            }
        }
    }

    printf("Peso total da MST: %.2f\n", pesoTotal);

    free(inMST);
    free(chave);
    free(pai);
    free(h->array);
    free(h);
}

void componentesConexosMatriz(GrafoMatriz* g) {
    printf("\n=== Componentes Conexos (Matriz) ===\n");

    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    int numComponentes = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visitado[i]) {
            numComponentes++;
            printf("Componente %d: ", numComponentes);

            int* fila = (int*)malloc(g->numVertices * sizeof(int));
            int frente = 0, tras = 0;

            visitado[i] = 1;
            fila[tras++] = i;

            while (frente < tras) {
                int v = fila[frente++];
                printf("%s ", g->jogadores[v].nome);

                for (int j = 0; j < g->numVertices; j++) {
                    if (g->matriz[v][j] > 0 && !visitado[j]) {
                        visitado[j] = 1;
                        fila[tras++] = j;
                    }
                }
            }
            printf("\n");
            free(fila);
        }
    }

    printf("Total de componentes: %d\n", numComponentes);
    free(visitado);
}

int existeCaminhoMatriz(GrafoMatriz* g, int inicio, int fim) {
    if (inicio == fim) return 1;

    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    int* fila = (int*)malloc(g->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    visitado[inicio] = 1;
    fila[tras++] = inicio;

    while (frente < tras) {
        int v = fila[frente++];

        for (int i = 0; i < g->numVertices; i++) {
            if (g->matriz[v][i] > 0) {
                if (i == fim) {
                    free(visitado);
                    free(fila);
                    return 1;
                }
                if (!visitado[i]) {
                    visitado[i] = 1;
                    fila[tras++] = i;
                }
            }
        }
    }

    free(visitado);
    free(fila);
    return 0;
}

void recomendarPasseMatriz(GrafoMatriz* g, int jogador) {
    printf("\n=== Recomendacao de Passe (Matriz) para %s ===\n",
           g->jogadores[jogador].nome);

    float melhorPeso = FLT_MAX;
    int melhor = -1;

    for (int i = 0; i < g->numVertices; i++) {
        if (g->matriz[jogador][i] > 0 && g->matriz[jogador][i] < melhorPeso) {
            melhorPeso = g->matriz[jogador][i];
            melhor = i;
        }
    }

    if (melhor != -1) {
        printf("Melhor passe: %s (entrosamento: %.2f)\n",
               g->jogadores[melhor].nome, 1.0 / melhorPeso);
    } else {
        printf("Nenhum vizinho disponivel!\n");
    }
}
