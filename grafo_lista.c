#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "grafo_lista.h"

GrafoLista* criarGrafoLista(int n, Jogador* jogs) {
    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->numVertices = n;
    g->jogadores = jogs;
    g->lista = (ListaAdj*)malloc(n * sizeof(ListaAdj));
    for (int i = 0; i < n; i++) {
        g->lista[i].cabeca = NULL;
    }
    return g;
}

void adicionarArestaLista(GrafoLista* g, int src, int dest, float peso) {
    No* novo = (No*)malloc(sizeof(No));
    novo->destino = dest;
    novo->peso = peso;
    novo->prox = g->lista[src].cabeca;
    g->lista[src].cabeca = novo;
    
    novo = (No*)malloc(sizeof(No));
    novo->destino = src;
    novo->peso = peso;
    novo->prox = g->lista[dest].cabeca;
    g->lista[dest].cabeca = novo;
}

void liberarGrafoLista(GrafoLista* g) {
    for (int i = 0; i < g->numVertices; i++) {
        No* atual = g->lista[i].cabeca;
        while (atual) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}

void dfsRecursivoLista(GrafoLista* g, int v, int* visitado) {
    visitado[v] = 1;
    printf("%s (%s) -> ", g->jogadores[v].nome, g->jogadores[v].posicao);
    
    No* adj = g->lista[v].cabeca;
    while (adj) {
        if (!visitado[adj->destino]) {
            dfsRecursivoLista(g, adj->destino, visitado);
        }
        adj = adj->prox;
    }
}

void dfsLista(GrafoLista* g, int inicio) {
    printf("\n=== DFS (Lista) iniciando em %s ===\n", g->jogadores[inicio].nome);
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    dfsRecursivoLista(g, inicio, visitado);
    printf("FIM\n");
    free(visitado);
}

void bfsLista(GrafoLista* g, int inicio) {
    printf("\n=== BFS (Lista) iniciando em %s ===\n", g->jogadores[inicio].nome);
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    int* fila = (int*)malloc(g->numVertices * sizeof(int));
    int frente = 0, tras = 0;
    
    visitado[inicio] = 1;
    fila[tras++] = inicio;
    
    while (frente < tras) {
        int v = fila[frente++];
        printf("%s (%s) -> ", g->jogadores[v].nome, g->jogadores[v].posicao);
        
        No* adj = g->lista[v].cabeca;
        while (adj) {
            if (!visitado[adj->destino]) {
                visitado[adj->destino] = 1;
                fila[tras++] = adj->destino;
            }
            adj = adj->prox;
        }
    }
    printf("FIM\n");
    free(visitado);
    free(fila);
}

typedef struct {
    int vertice;
    float dist;
} HeapNo;

typedef struct {
    HeapNo* array;
    int tamanho;
    int capacidade;
} MinHeap;

MinHeap* criarHeap(int cap) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->array = (HeapNo*)malloc(cap * sizeof(HeapNo));
    h->tamanho = 0;
    h->capacidade = cap;
    return h;
}

void trocar(HeapNo* a, HeapNo* b) {
    HeapNo temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* h, int idx) {
    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (h->array[idx].dist < h->array[pai].dist) {
            trocar(&h->array[idx], &h->array[pai]);
            idx = pai;
        } else break;
    }
}

void heapifyDown(MinHeap* h, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;
    
    if (esq < h->tamanho && h->array[esq].dist < h->array[menor].dist)
        menor = esq;
    if (dir < h->tamanho && h->array[dir].dist < h->array[menor].dist)
        menor = dir;
    
    if (menor != idx) {
        trocar(&h->array[idx], &h->array[menor]);
        heapifyDown(h, menor);
    }
}

void inserirHeap(MinHeap* h, int v, float d) {
    h->array[h->tamanho].vertice = v;
    h->array[h->tamanho].dist = d;
    heapifyUp(h, h->tamanho);
    h->tamanho++;
}

HeapNo extrairMin(MinHeap* h) {
    HeapNo min = h->array[0];
    h->array[0] = h->array[h->tamanho - 1];
    h->tamanho--;
    heapifyDown(h, 0);
    return min;
}

void dijkstraLista(GrafoLista* g, int inicio, int fim) {
    printf("\n=== Dijkstra (Lista) de %s ate %s ===\n", 
           g->jogadores[inicio].nome, g->jogadores[fim].nome);
    
    float* dist = (float*)malloc(g->numVertices * sizeof(float));
    int* ant = (int*)malloc(g->numVertices * sizeof(int));
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = FLT_MAX;
        ant[i] = -1;
    }
    dist[inicio] = 0.0;
    
    MinHeap* h = criarHeap(g->numVertices * 10);
    inserirHeap(h, inicio, 0.0);
    
    while (h->tamanho > 0) {
        HeapNo atual = extrairMin(h);
        int u = atual.vertice;
        
        if (visitado[u]) continue;
        visitado[u] = 1;
        
        No* adj = g->lista[u].cabeca;
        while (adj) {
            int v = adj->destino;
            float peso = adj->peso;
            
            if (!visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                ant[v] = u;
                inserirHeap(h, v, dist[v]);
            }
            adj = adj->prox;
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

void primLista(GrafoLista* g) {
    printf("\n=== Arvore Geradora Minima - Prim (Lista) ===\n");
    
    int* inMST = (int*)calloc(g->numVertices, sizeof(int));
    float* chave = (float*)malloc(g->numVertices * sizeof(float));
    int* pai = (int*)malloc(g->numVertices * sizeof(int));
    
    for (int i = 0; i < g->numVertices; i++) {
        chave[i] = FLT_MAX;
        pai[i] = -1;
    }
    chave[0] = 0.0;
    
    MinHeap* h = criarHeap(g->numVertices * 10);
    inserirHeap(h, 0, 0.0);
    
    float pesoTotal = 0.0;
    
    while (h->tamanho > 0) {
        HeapNo atual = extrairMin(h);
        int u = atual.vertice;
        
        if (inMST[u]) continue;
        inMST[u] = 1;
        
        if (pai[u] != -1) {
            printf("%s -- %.2f -- %s\n", 
                   g->jogadores[pai[u]].nome, chave[u], g->jogadores[u].nome);
            pesoTotal += chave[u];
        }
        
        No* adj = g->lista[u].cabeca;
        while (adj) {
            int v = adj->destino;
            float peso = adj->peso;
            
            if (!inMST[v] && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
                inserirHeap(h, v, chave[v]);
            }
            adj = adj->prox;
        }
    }
    
    printf("Peso total da MST: %.2f\n", pesoTotal);
    
    free(inMST);
    free(chave);
    free(pai);
    free(h->array);
    free(h);
}

void componentesConexosLista(GrafoLista* g) {
    printf("\n=== Componentes Conexos (Lista) ===\n");
    
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
                
                No* adj = g->lista[v].cabeca;
                while (adj) {
                    if (!visitado[adj->destino]) {
                        visitado[adj->destino] = 1;
                        fila[tras++] = adj->destino;
                    }
                    adj = adj->prox;
                }
            }
            printf("\n");
            free(fila);
        }
    }
    
    printf("Total de componentes: %d\n", numComponentes);
    free(visitado);
}

int existeCaminhoLista(GrafoLista* g, int inicio, int fim) {
    if (inicio == fim) return 1;
    
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    int* fila = (int*)malloc(g->numVertices * sizeof(int));
    int frente = 0, tras = 0;
    
    visitado[inicio] = 1;
    fila[tras++] = inicio;
    
    while (frente < tras) {
        int v = fila[frente++];
        
        No* adj = g->lista[v].cabeca;
        while (adj) {
            if (adj->destino == fim) {
                free(visitado);
                free(fila);
                return 1;
            }
            if (!visitado[adj->destino]) {
                visitado[adj->destino] = 1;
                fila[tras++] = adj->destino;
            }
            adj = adj->prox;
        }
    }
    
    free(visitado);
    free(fila);
    return 0;
}

void recomendarPasseLista(GrafoLista* g, int jogador) {
    printf("\n=== Recomendacao de Passe (Lista) para %s ===\n", 
           g->jogadores[jogador].nome);
    
    float melhorPeso = FLT_MAX;
    int melhor = -1;
    
    No* adj = g->lista[jogador].cabeca;
    while (adj) {
        if (adj->peso < melhorPeso) {
            melhorPeso = adj->peso;
            melhor = adj->destino;
        }
        adj = adj->prox;
    }
    
    if (melhor != -1) {
        printf("Melhor passe: %s (entrosamento: %.2f)\n", 
               g->jogadores[melhor].nome, 1.0 / melhorPeso);
    } else {
        printf("Nenhum vizinho disponivel!\n");
    }
}