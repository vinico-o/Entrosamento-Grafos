#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogador.h"
#include "grafo_lista.c"
#include "grafo_matriz.c"

#define MAX_JOGADORES 100

int lerArquivo(const char* nome, char dados[][100], int maxLinhas)
{
    int i; // contador de linhas lidas
    FILE* arquivo = fopen(nome, "r");
    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo)
    {
        printf("Erro ao abrir %s\n", nome);
        return 0;
    }

    for(i = 0; i < maxLinhas && fgets(dados[i], 100, arquivo); i++)
    {
        dados[i][strcspn(dados[i], "\n")] = 0; // remove o /n dos dados 
    }

    fclose(arquivo);
    return i;
}

// calcula o peso da aresta baseado no entrosamento
float calcularPeso(Jogador* j1, Jogador* j2)
{
    int entrosamento = 1; // o valor comeca com 1 para evitar dividir por 0

    // o entrosamento aumenta a cada atribuito igual entre os jogadores
    if(strcmp(j1->time, j2->time) == 0)
    {
        entrosamento++;
    }
    if(strcmp(j1->nacionalidade, j2->nacionalidade) == 0)
    {
        entrosamento++;
    }

    // Como o peso eh inversamente proporcional ao entrosamento,
    // dividdimos 1 pelo valor do entrosamento
    return 1.0 / entrosamento;
}

void conectarPosicoes(GrafoLista* grafoLista, GrafoMatriz* grafoMatriz, Jogador* jogadores, int n)
{
    // tamanho 22 para o caso em que todos os jogadores sejam da mesma posicao
    int goleiros[22], defensores[22], meios[22], atacantes[22];
    // contador de cada posicao
    int numGoleiros = 0, numDefensores = 0, numMeios = 0, numAtacantes = 0;

    for(int i = 0; i < n; i++)
    {
        if(strcmp(jogadores[i].posicao, "GOL") == 0)
        {
            goleiros[numGoleiros++] = i;
        }
        else if(strcmp(jogadores[i].posicao, "ZE") == 0 || strcmp(jogadores[i].posicao, "ZD") ||
                strcmp(jogadores[i].posicao, "LE") == 0 || strcmp(jogadores[i].posicao, "LD") == 0)
        {
            defensores[numDefensores++] = i;
        }
        else if(strcmp(jogadores[i].posicao, "MC") == 0 || strcmp(jogadores[i].posicao, "ME") == 0 || strcmp(jogadores[i].posicao, "MD") == 0)
        {
            meios[numMeios++] = i;
        }
        else if(strcmp(jogadores[i].posicao, "PD") == 0 || strcmp(jogadores[i].posicao, "CA") == 0 || strcmp(jogadores[i].posicao, "PE") == 0)
        {
            atacantes[numAtacantes++] = i;
        }
    }

    // Conectar goleiros com defensores
    for(int i = 0; i < numGoleiros; i++) 
    {
        for (int j = 0; j < numDefensores; j++)
        {
            float peso = calcularPeso(&jogadores[goleiros[i]], &jogadores[defensores[j]]);
            adicionarArestaLista(grafoLista, goleiros[i], defensores[j], peso);
            adicionarArestaMatriz(grafoMatriz, goleiros[i], defensores[j], peso);
        }
    }

    // Conectar defensores entre si
    for(int i = 0; i < numDefensores; i++)
    {
        for (int j = i + 1; j < numDefensores; j++)
        {
            float peso = calcularPeso(&jogadores[defensores[i]], &jogadores[defensores[j]]);
            adicionarArestaLista(grafoLista, defensores[i], defensores[j], peso);
            adicionarArestaMatriz(grafoMatriz, defensores[i], defensores[j], peso);
        }
    }

    // Conectar defensores com meios
    for(int i = 0; i < numDefensores; i++)
    {
        for (int j = 0; j < numMeios; j++)
        {
            float peso = calcularPeso(&jogadores[defensores[i]], &jogadores[meios[j]]);
            adicionarArestaLista(grafoLista, defensores[i], meios[j], peso);
            adicionarArestaMatriz(grafoMatriz, defensores[i], meios[j], peso);
        }
    }

    // Conectar meios entre si
    for(int i = 0; i < numMeios; i++)
    {
        for (int j = i + 1; j < numMeios; j++)
        {
            float peso = calcularPeso(&jogadores[meios[i]], &jogadores[meios[j]]);
            adicionarArestaLista(grafoLista, meios[i], meios[j], peso);
            adicionarArestaMatriz(grafoMatriz, meios[i], meios[j], peso);
        }
    }

    // Conectar meios com atacantes
    for(int i = 0; i < numMeios; i++)
    {
        for (int j = 0; j < numAtacantes; j++)
        {
            float peso = calcularPeso(&jogadores[meios[i]], &jogadores[atacantes[j]]);
            adicionarArestaLista(grafoLista, meios[i], atacantes[j], peso);
            adicionarArestaMatriz(grafoMatriz, meios[i], atacantes[j], peso);
        }
    }

    // Conectar atacantes entre si
    for(int i = 0; i < numAtacantes; i++)
    {
        for (int j = i + 1; j < numAtacantes; j++)
        {
            float peso = calcularPeso(&jogadores[atacantes[i]], &jogadores[atacantes[j]]);
            adicionarArestaLista(grafoLista, atacantes[i], atacantes[j], peso);
            adicionarArestaMatriz(grafoMatriz, atacantes[i], atacantes[j], peso);
        }
    }
}

int main()
{
    // seed para aleatorizar os jogadores
    srand(time(NULL));

    printf("=================================================\n");
    printf("   SISTEMA DE GRAFOS DE JOGADORES DE FUTEBOL\n");
    printf("=================================================\n\n");

    char nomes[MAX_JOGADORES][100];
    char posicoes[MAX_JOGADORES][100];
    char times[MAX_JOGADORES][100];
    char nacionalidades[MAX_JOGADORES][100];

    // leitura dos arquivos
    int n1 = lerArquivo("..\\nomes.txt", nomes, MAX_JOGADORES);
    int n2 = lerArquivo("..\\posicoes.txt", posicoes, MAX_JOGADORES);
    int n3 = lerArquivo("..\\times.txt", times, MAX_JOGADORES);
    int n4 = lerArquivo("..\\nacionalidade.txt", nacionalidades, MAX_JOGADORES);

    // verifica se foi possivel abrir os arquivos
    if(n1 == 0 || n2 == 0 || n3 == 0 || n4 == 0)
    {
        printf("Erro ao abrir algum dos arquivos!\n");
        return 1;
    }

    // Sortear 22 jogadores sem repetição
    int indices[MAX_JOGADORES];

    for (int i = 0; i < 22; i++) {
        indices[i] = rand() % MAX_JOGADORES ;  // pode repetir jogador
    }

    Jogador* jogadores = (Jogador*)malloc(22 * sizeof(Jogador));

    printf("=== ESCALACAO (22 jogadores sorteados) ===\n\n");
    printf("TITULARES:\n");
    for(int i = 0; i < 11; i++)
    {
        int idx = indices[i];
        jogadores[i].id = i;
        strcpy(jogadores[i].nome, nomes[idx]);
        strcpy(jogadores[i].posicao, posicoes[idx]);
        strcpy(jogadores[i].time, times[idx]);
        strcpy(jogadores[i].nacionalidade, nacionalidades[idx]);
        printf("%d. %s - %s (%s, %s)\n", i+1, jogadores[i].nome, jogadores[i].posicao, jogadores[i].time, jogadores[i].nacionalidade);
    }

    printf("\nRESERVAS:\n");
    for (int i = 11; i < 22; i++)
    {
        int idx = indices[i];
        jogadores[i].id = i;
        strcpy(jogadores[i].nome, nomes[idx]);
        strcpy(jogadores[i].posicao, posicoes[idx]);
        strcpy(jogadores[i].time, times[idx]);
        strcpy(jogadores[i].nacionalidade, nacionalidades[idx]);
        printf("%d. %s - %s (%s, %s)\n", i-10, jogadores[i].nome, jogadores[i].posicao,jogadores[i].time, jogadores[i].nacionalidade);
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
    printf("De %s ate %s: %s\n", jogadores[0].nome, jogadores[21].nome, existe ? "SIM" : "NAO");

    printf("\n=== Existe Caminho (Matriz) ===\n");
    existe = existeCaminhoMatriz(gMatriz, 0, 21);
    printf("De %s ate %s: %s\n", jogadores[0].nome, jogadores[21].nome, existe ? "SIM" : "NAO");

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
