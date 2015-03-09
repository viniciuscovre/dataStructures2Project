/*******************************************************************************
DESCRIÇÃO DO ARQUIVO: Esse arquivo.cpp reúne as funções que utlilizam dos
arquivos do projeto. Em outras palavras, é o conjunto de funções relacionadas
a operações de main nos arquivos binários.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "bt.h"

/* Define um tipo para o cadastro de vacinas (AP1) */
typedef struct
{
    int cod_controle;
    int cod_cachorro;
    char vacina[30];
    char data[5];
    char responsavel[30];
} VACINA;

/* Define um tipo para o cadastro de cachorros (AP2) */
typedef struct
{
    char raca[30];
    char nome[30];
} CACHORRO;

/* Header de AP2 com o código do último cachorro cadastrado */
short int cod_cachorro; /* Auto-Incremento */

short int root; /* Declara o cabeçalho do arquivo AP1: RRN da Página Raíz */
int btfd; /* Descrição do Arquivo de Árvore B */ //??
int infd; /* Descrição do Arquivo de Entrada */ //??

BTIDX btidx; /* Declara índice primário de Árvore B */

void InicializaArquivos(FILE **AP1, FILE **BTidx)
{
    rewind(*AP1);
    short int aux = -1; /* -1 indica que o arquivo (AP1) está vazio */
    fwrite(&aux, sizeof(short int), 1, *AP1);
    
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
        fread(&root, sizeof(short int), 1, *AP1); /* Pega o Header da Árvore B de AP1 */
        
        if((*BTidx = fopen("BTidx.bin","w+b")) == NULL)
        { /* Apenas abre para leitura e escrita */
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
        printf("\n\nO ARQUIVO NAO EXISTE!\n\n");getch();
        rewind(*AP2);
        short int aux = 0;
        fwrite(&aux, sizeof(short int), 1, *AP2);
        cod_cachorro = aux;
    }
    else /* Se o arquivo já existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
        printf("\n\nO ARQUIVO EXISTE!\n\n");getch();
        rewind(*AP2);
        fread(&cod_cachorro, sizeof(short int), 1, *AP2);
    }
}

void CadastraCachorro(FILE **AP2)
{
	CACHORRO reg;
	
	system("CLS");
	
	cod_cachorro++;
	rewind(*AP2);
	fwrite(&cod_cachorro, sizeof(short int), 1, *AP2); /* Atualiza header de AP2 */
	printf(" Codigo: %d\n", cod_cachorro);
	
	fflush(stdin);
	printf(" Raca: ");
	gets(reg.raca);
	printf(" Nome do Cachorro: ");
	gets(reg.nome);

	fseek(*AP2, 0, SEEK_END); /* Seta a posição para o fim do arquivo */
	fwrite(&reg, sizeof(CACHORRO), 1, *AP2); /* Escreve no fim do arquivo */
}

int ExisteCachorro(int codigo, FILE **AP2)
{
	if(codigo <= cod_cachorro)
	   return 1;
	else
	   return 0;	
}
