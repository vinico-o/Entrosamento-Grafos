#include <stdio.h>
#include <stdlib.h>

void abrirArquivo(char* nomeArquivo)
{
        FILE* arquivo = fopen(nomeArquivo, "r");
        if(arquivo == NULL)
        {
                printf("Erro ao abrir arquivo %s!", nomeArquivo);
                return;
        }
}

void lerArquivo(char* nomeArquivo)
{
    abrirArquivo(nomeArquivo);
    
}
