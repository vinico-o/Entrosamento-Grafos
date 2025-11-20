#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogador.h"
#include "grafo_lista.c"
#include "grafo_matriz.c"

#define MAX_JOGADORES 100

int lerArquivo(const char* nome, char dados[][100], int maxLinhas) {
    FILE* f = fopen(nome, "r");
    if (!f) {
        printf("Erro ao abrir %s\n", nome);
        return 0;
    }

    int i = 0;
    while (i < maxLinhas && fgets(dados[i], 100, f)) {
        dados[i][strcspn(dados[i], "\n")] = 0;
        i++;
    }

    fclose(f);
    return i;
}

float calcularPeso(Jogador* j1, Jogador* j2) {
    int entrosamento = 0;

    if (strcmp(j1->time, j2->time) == 0) entrosamento++;
    if (strcmp(j1->nacionalidade, j2->nacionalidade) == 0) entrosamento++;

    return 1.0 / (entrosamento + 0.1);
}

void conectarPosicoes(GrafoLista* gLista, GrafoMatriz* gMatriz,
                      Jogador* jogs, int n) {
    int goleiros[22], defensores[22], meios[22], atacantes[22];
    int ng = 0, nd = 0, nm = 0, na = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(jogs[i].posicao, "Goleiro") == 0) {
            goleiros[ng++] = i;
        } else if (strcmp(jogs[i].posicao, "Zagueiro") == 0 ||
                   strcmp(jogs[i].posicao, "Lateral") == 0) {
            defensores[nd++] = i;
        } else if (strcmp(jogs[i].posicao, "Meio-campo") == 0) {
            meios[nm++] = i;
        } else if (strcmp(jogs[i].posicao, "Atacante") == 0) {
            atacantes[na++] = i;
        }
    }

    // Conectar goleiros com defensores
    for (int i = 0; i < ng; i++) {
        for (int j = 0; j < nd; j++) {
            float peso = calcularPeso(&jogs[goleiros[i]], &jogs[defensores[j]]);
            adicionarArestaLista(gLista, goleiros[i], defensores[j], peso);
            adicionarArestaMatriz(gMatriz, goleiros[i], defensores[j], peso);
        }
    }

    // Conectar defensores entre si
    for (int i = 0; i < nd; i++) {
        for (int j = i + 1; j < nd; j++) {
            float peso = calcularPeso(&jogs[defensores[i]], &jogs[defensores[j]]);
            adicionarArestaLista(gLista, defensores[i], defensores[j], peso);
            adicionarArestaMatriz(gMatriz, defensores[i], defensores[j], peso);
        }
    }

    // Conectar defensores com meios
    for (int i = 0; i < nd; i++) {
        for (int j = 0; j < nm; j++) {
            float peso = calcularPeso(&jogs[defensores[i]], &jogs[meios[j]]);
            adicionarArestaLista(gLista, defensores[i], meios[j], peso);
            adicionarArestaMatriz(gMatriz, defensores[i], meios[j], peso);
        }
    }

    // Conectar meios entre si
    for (int i = 0; i < nm; i++) {
        for (int j = i + 1; j < nm; j++) {
            float peso = calcularPeso(&jogs[meios[i]], &jogs[meios[j]]);
            adicionarArestaLista(gLista, meios[i], meios[j], peso);
            adicionarArestaMatriz(gMatriz, meios[i], meios[j], peso);
        }
    }

    // Conectar meios com atacantes
    for (int i = 0; i < nm; i++) {
        for (int j = 0; j < na; j++) {
            float peso = calcularPeso(&jogs[meios[i]], &jogs[atacantes[j]]);
            adicionarArestaLista(gLista, meios[i], atacantes[j], peso);
            adicionarArestaMatriz(gMatriz, meios[i], atacantes[j], peso);
        }
    }

    // Conectar atacantes entre si
    for (int i = 0; i < na; i++) {
        for (int j = i + 1; j < na; j++) {
            float peso = calcularPeso(&jogs[atacantes[i]], &jogs[atacantes[j]]);
            adicionarArestaLista(gLista, atacantes[i], atacantes[j], peso);
            adicionarArestaMatriz(gMatriz, atacantes[i], atacantes[j], peso);
        }
    }
}

int main() {
    srand(time(NULL));

    printf("=================================================\n");
    printf("   SISTEMA DE GRAFOS DE JOGADORES DE FUTEBOL\n");
    printf("=================================================\n\n");

    char nomes[MAX_JOGADORES][100];
    char posicoes[MAX_JOGADORES][100];
    char times[MAX_JOGADORES][100];
    char nacionalidades[MAX_JOGADORES][100];

    printf("Lendo arquivos...\n");
    int n1 = lerArquivo("..\\nomes.txt", nomes, MAX_JOGADORES);
    int n2 = lerArquivo("..\\posicoes.txt", posicoes, MAX_JOGADORES);
    int n3 = lerArquivo("..\\times.txt", times, MAX_JOGADORES);
    int n4 = lerArquivo("..\\nacionalidade.txt", nacionalidades, MAX_JOGADORES);

    if (n1 == 0 || n2 == 0 || n3 == 0 || n4 == 0) {
        printf("Erro: verifique se todos os arquivos existem!\n");
        return 1;
    }

    int totalJogadores = (n1 < n2) ? n1 : n2;
    totalJogadores = (totalJogadores < n3) ? totalJogadores : n3;
    totalJogadores = (totalJogadores < n4) ? totalJogadores : n4;

    printf("Total de jogadores lidos: %d\n\n", totalJogadores);

    if (totalJogadores < 22) {
        printf("Erro: necessario pelo menos 22 jogadores!\n");
        return 1;
    }

    // Sortear 22 jogadores sem repetição
    int indices[MAX_JOGADORES];
    for (int i = 0; i < totalJogadores; i++) indices[i] = i;

    for (int i = 0; i < 22; i++) {
        int j = i + rand() % (totalJogadores - i);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    Jogador* jogadores = (Jogador*)malloc(22 * sizeof(Jogador));

    printf("=== ESCALACAO (22 jogadores sorteados) ===\n\n");
    printf("TITULARES:\n");
    for (int i = 0; i < 11; i++) {
        int idx = indices[i];
        jogadores[i].id = i;
        strcpy(jogadores[i].nome, nomes[idx]);
        strcpy(jogadores[i].posicao, posicoes[idx]);
        strcpy(jogadores[i].time, times[idx]);
        strcpy(jogadores[i].nacionalidade, nacionalidades[idx]);
        printf("%d. %s - %s (%s, %s)\n", i+1,
               jogadores[i].nome, jogadores[i].posicao,
               jogadores[i].time, jogadores[i].nacionalidade);
    }

    printf("\nRESERVAS:\n");
    for (int i = 11; i < 22; i++) {
        int idx = indices[i];
        jogadores[i].id = i;
        strcpy(jogadores[i].nome, nomes[idx]);
        strcpy(jogadores[i].posicao, posicoes[idx]);
        strcpy(jogadores[i].time, times[idx]);
        strcpy(jogadores[i].nacionalidade, nacionalidades[idx]);
        printf("%d. %s - %s (%s, %s)\n", i-10,
               jogadores[i].nome, jogadores[i].posicao,
               jogadores[i].time, jogadores[i].nacionalidade);
    }

    printf("\n=================================================\n");
    printf("   CRIANDO GRAFOS\n");
    printf("=================================================\n");

    GrafoLista* gLista = criarGrafoLista(22, jogadores);
    GrafoMatriz* gMatriz = criarGrafoMatriz(22, jogadores);

    conectarPosicoes(gLista, gMatriz, jogadores, 22);

    printf("\nGrafos criados com sucesso!\n");

    printf("\n=================================================\n");
    printf("   EXECUTANDO ALGORITMOS\n");
    printf("=================================================\n");

    // DFS
    dfsLista(gLista, 0);
    dfsMatriz(gMatriz, 0);

    // BFS
    bfsLista(gLista, 0);
    bfsMatriz(gMatriz, 0);

    // Dijkstra
    dijkstraLista(gLista, 0, 10);
    dijkstraMatriz(gMatriz, 0, 10);

    // Prim
    primLista(gLista);
    primMatriz(gMatriz);

    // Componentes Conexos
    componentesConexosLista(gLista);
    componentesConexosMatriz(gMatriz);

    // Existe Caminho
    printf("\n=== Existe Caminho (Lista) ===\n");
    int existe = existeCaminhoLista(gLista, 0, 21);
    printf("De %s ate %s: %s\n", jogadores[0].nome, jogadores[21].nome,
           existe ? "SIM" : "NAO");

    printf("\n=== Existe Caminho (Matriz) ===\n");
    existe = existeCaminhoMatriz(gMatriz, 0, 21);
    printf("De %s ate %s: %s\n", jogadores[0].nome, jogadores[21].nome,
           existe ? "SIM" : "NAO");

    // Recomendação de Passe
    recomendarPasseLista(gLista, 5);
    recomendarPasseMatriz(gMatriz, 5);

    printf("\n=================================================\n");
    printf("   FINALIZANDO\n");
    printf("=================================================\n");

    liberarGrafoLista(gLista);
    liberarGrafoMatriz(gMatriz);
    free(jogadores);

    printf("\nPrograma finalizado com sucesso!\n");

    return 0;
}
