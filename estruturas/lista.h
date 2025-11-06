#ifndef LISTA_H
#define LISTA_H


typedef conexaoLista {

    Jogador j;
    int peso;
    conexaoLista *prox;

}conexaoLista;

typedef grafoLista{

    conexaoLista adj[11];

}grafoLista;


void inicializarLista(grafoLista *g)
{
    for (int i = 0; i < 11; j++)
    {
        g->adj[i] = malloc(sizeof(conexaoLista));
        g->adj[i]->prox = NULL;
        g->adj[i]->peso = 0;
    }


}





#endif