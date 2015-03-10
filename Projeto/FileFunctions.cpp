/*******************************************************************************
DESCRI��O DO ARQUIVO: Esse arquivo.cpp re�ne as fun��es que utlilizam dos
arquivos do projeto. Em outras palavras, � o conjunto de fun��es relacionadas
a opera��es de main nos arquivos bin�rios.
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
    int cod_cachorro;
    char raca[30];
    char nome[30];
} CACHORRO;

/* Header de AP2 com o c�digo do �ltimo cachorro cadastrado */
int cont; /* Auto-Incremento */

short int root; /* Declara o cabe�alho do arquivo AP1: RRN da P�gina Ra�z */
int btfd; /* Descri��o do Arquivo de �rvore B */ //??
int infd; /* Descri��o do Arquivo de Entrada */ //??

BTIDX btidx; /* Declara �ndice prim�rio de �rvore B */

void InicializaArquivos(FILE **AP1, FILE **BTidx)
{
    rewind(*AP1);
    short int aux = -1; /* -1 indica que o arquivo (AP1) est� vazio */
    fwrite(&aux, sizeof(short int), 1, *AP1);
    
    rewind(*BTidx);
    btidx.keycount = 0; /* Indica que a P�gina tem zero registros */
    fwrite(&btidx.keycount, PAGESIZE, 1, *BTidx);
}

int NumCachorros(FILE **AP2)
{
    int aux = 0;
    CACHORRO reg;
    rewind(*AP2);
    while(fread(&reg, sizeof(CACHORRO), 1, *AP2))
        aux++;
    return aux;
}

void AbreArquivos(FILE **AP1, FILE **AP2, FILE **BTidx)
{
    /* Para AP1 */
    if((*AP1 = fopen("AP1.bin","r+b")) == NULL) /* Se o arquivo n�o existir */
    {
        /* Cria o Arquivo Principal 1 'AP1' */
        if((*AP1 = fopen("AP1.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        
        /* Cria o arquivo de �ndice de �rvore B 'BTidx' */
        if((*BTidx = fopen("BTidx.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em BTidx. Abortando...");
            getch();
            return;
        }
        
        InicializaArquivos(AP1, BTidx);
    }
    else /* Se o arquivo j� existir */
    {
        if((*AP1 = fopen("AP1.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        rewind(*AP1);
        fread(&root, sizeof(short int), 1, *AP1); /* Pega o Header da �rvore B de AP1 */
        
        if((*BTidx = fopen("BTidx.bin","w+b")) == NULL)
        { /* Apenas abre para leitura e escrita */
            printf("Erro em BTidx. Abortando...");
            getch();
            return;
        }
        rewind(*BTidx);
    }
    
    /* Para AP2 */
    if((*AP2 = fopen("AP2.bin","r+b")) == NULL) /* Se o arquivo n�o existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
        printf("\n\nO ARQUIVO NAO EXISTE!\n\n");
        cont = 0;
        printf("\n\n%d\n\n", cont); getch();
    }
    else /* Se o arquivo j� existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
        printf("\n\nO ARQUIVO EXISTE!\n\n");
        cont = NumCachorros(AP2);
        printf("\n\n%d\n\n", cont); getch();
    }
}

void CadastraCachorro(FILE **AP2)
{
	CACHORRO reg;
	system("CLS");

	cont++;
	reg.cod_cachorro = cont;
	printf(" Codigo: %d\n", reg.cod_cachorro);
	fflush(stdin);
	printf(" Raca: ");
	gets(reg.raca);
	printf(" Nome do Cachorro: ");
	gets(reg.nome);

	fseek(*AP2, 0, SEEK_END); /* Seta a posi��o para o fim do arquivo */
	fwrite(&reg, sizeof(CACHORRO), 1, *AP2); /* Escreve no fim do arquivo */
}

int ExisteCachorro(int codigo, FILE **AP2)
{
	CACHORRO reg;
	
	fseek(*AP2, 0, SEEK_SET);
	while (fread(&reg, sizeof(CACHORRO), 1, *AP2))
	{
		if (reg.cod_cachorro == codigo)
		{
			return 1;
			break;
		}	
	}
    return 0;
}
