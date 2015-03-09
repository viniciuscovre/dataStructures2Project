/*******************************************************************************
DESCRIÇÃO DO ARQUIVO: Esse arquivo.cpp reúne as funções que utlilizam dos
arquivos do projeto. Em outras palavras, é o conjunto de funções relacionadas
a operações de main nos arquivos binários.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "bt.h"

short int header; /* Declara o cabeçalho do arquivo AP1: RRN da Página Raíz */
BTIDX btidx; /* Declara índice primário de Árvore B */

void InicializaArquivos(FILE **AP1, FILE **BTidx)
{
    rewind(*AP1);
    int aux = -1; /* -1 indica que o arquivo (AP1) está vazio */
    fwrite(&aux, sizeof(int), 1, *AP1);
    
    rewind(*BTidx);
    btidx.keycount = 0; /* Indica que a Página tem zero registros */
    fwrite(&btidx.keycount, PAGESIZE, 1, *BTidx);
}

void AbreArquivos(FILE **AP1, FILE **AP2, FILE **BTidx)
{
    /* Para AP1 */
    if((*AP1 = fopen("AP1.bin","r+b")) == NULL) /* Se o arquivo não existir */
    {
        /* Cria o Arquivo Principal 1 'AP1' */
        if((*AP1 = fopen("AP1.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        
        /* Cria o arquivo de índice de Árvore B 'BTidx' */
        if((*BTidx = fopen("BTidx.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em BTidx. Abortando...");
            getch();
            return;
        }
        
        InicializaArquivos(AP1, BTidx);
    }
    else /* Se o arquivo já existir */
    {
        if((*AP1 = fopen("AP1.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        rewind(*AP1);
        fread(&header, sizeof(short int), 1, *AP1); /* Pega o Header da Árvore B de AP1 */
        
        if((*BTidx = fopen("BTidx.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em BTidx. Abortando...");
            getch();
            return;
        }
        rewind(*BTidx);
    }
    
    /* Para AP2 */
    if((*AP2 = fopen("AP2.bin","r+b")) == NULL) /* Se o arquivo não existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
    }
    else /* Se o arquivo já existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
    }
}
