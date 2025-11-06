#ifndef LISTA_H
#define LISTA_H


typedef conexaoLista {

    Jogador j;
    int peso;
    conexaoLista *prox;

}conexaoLista;

typedef grafoLista{

    conexaoLista adj[TAMANHO];

}grafoLista;


void inicializarLista(grafoLista *g)
{
    for (int i = 0; i < TAMANHO; j++)
    {
        g->adj[i] = malloc(sizeof(conexaoLista));
        g->adj[i]->prox = NULL;
        g->adj[i]->peso = 0;
    }
}

void inserirNoVazio(conexaoLista *j)
{
    conexaoLista novaConexao = malloc(sizeof(conexaoLista));
    novaConexao->peso = 0;
    novaConexao->prox = j->prox;

    j->prox = novaConexao;

}

void montarConexoesLista (grafoLista *g, int time)
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

    // apenas criando nós vazios -> depois passam os jogadores
    inserirNoVazio(g->adj[GOL + indice]);
    inserirNoVazio(g->adj[GOL + indice]);

    inserirNoVazio(g->adj[ZE + indice]);
    inserirNoVazio(g->adj[ZE + indice]);
    inserirNoVazio(g->adj[ZE + indice]);
    inserirNoVazio(g->adj[ZE + indice]);

    inserirNoVazio(g->adj[ZD + indice]);
    inserirNoVazio(g->adj[ZD + indice]);
    inserirNoVazio(g->adj[ZD + indice]);
    inserirNoVazio(g->adj[ZD + indice]);

    inserirNoVazio(g->adj[LE + indice]);
    inserirNoVazio(g->adj[LE + indice]);

    inserirNoVazio(g->adj[LD + indice]);
    inserirNoVazio(g->adj[LD + indice]);

    inserirNoVazio(g->adj[ME + indice]);
    inserirNoVazio(g->adj[ME + indice]);
    inserirNoVazio(g->adj[ME + indice]);
    inserirNoVazio(g->adj[ME + indice]);

    inserirNoVazio(g->adj[MC + indice]);
    inserirNoVazio(g->adj[MC + indice]);
    inserirNoVazio(g->adj[MC + indice]);

    inserirNoVazio(g->adj[MD + indice]);
    inserirNoVazio(g->adj[MD + indice]);
    inserirNoVazio(g->adj[MD + indice]);
    inserirNoVazio(g->adj[MD + indice]);

    inserirNoVazio(g->adj[PE + indice]);
    inserirNoVazio(g->adj[PE + indice]);

    inserirNoVazio(g->adj[PD + indice]);
    inserirNoVazio(g->adj[PD + indice]);

    inserirNoVazio(g->adj[CA + indice]);
    inserirNoVazio(g->adj[CA + indice]);
    inserirNoVazio(g->adj[CA + indice]);

}

int calcularEntrosamentoLista(Jogador j1, Jogador j2)
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