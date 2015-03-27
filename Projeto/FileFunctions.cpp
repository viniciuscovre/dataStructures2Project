/*******************************************************************************
DESCRIÇÃO DO ARQUIVO: Esse arquivo reúne as funções que utlilizam dos arquivos 
do projeto. Em outras palavras, é o conjunto de funções relacionadas a operações
de main nos arquivos binários, mas não nas estruturas Hash e Árvore B.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "bt.h"
#include "hash.h"

/* Define um tipo para o cadastro de vacinas (AP1) */
typedef struct
{
    int cod_controle;
    int cod_cachorro;
    char vacina[30];
    char data[6];
    char responsavel[30];
} VACINA;

/* Define um tipo para o cadastro de cachorros (AP2) */
typedef struct
{
    int cod_cachorro;
    char raca[30];
    char nome[30];
} CACHORRO;

int header;
int cont; /* Auto-Incremento */

void InicializaArquivos(FILE **AP1, FILE **AP2, FILE **BTidx, FILE **HASHidx)
{
    rewind(*AP1);
    int aux = -1; /* -1 indica que o arquivo (AP1) está vazio */
    fwrite(&aux, sizeof(int), 1, *AP1);
    
    rewind(*AP2); /* lê o header de AP2, que é o codigo de cachorro (auto-incremento)*/
    fwrite(&aux, sizeof(int), 1, *AP2);
    
    short root = NIL;
    putroot(root, BTidx);
    
    HASHIDX reg;
    reg.cont = 0;
    rewind(*HASHidx);
    for(int i=0; i<M; i++)
      fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);
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

void AbreArquivos(FILE **AP1, FILE **AP2, FILE **BTidx, FILE **HASHidx)
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
        
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP2. Abortando...");
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
        
        /* Cria o arquivo de índice de Hash 'HASHidx' */
        if((*HASHidx = fopen("HASHidx.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em HASHidx. Abortando...");
            getch();
            return;
        }

        InicializaArquivos(AP1, AP2, BTidx, HASHidx);
    }
    else /* Se o arquivo já existir */
    {
        if((*AP1 = fopen("AP1.bin","r+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        rewind(*AP1);
        fread(&header, sizeof(int), 1, *AP1); /* Pega o Header de AP1 */
        
        if((*AP2 = fopen("AP2.bin","r+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
        
        if((*BTidx = fopen("BTidx.bin","r+b")) == NULL)
        { /* Apenas abre para leitura e escrita */
            printf("Erro em BTidx. Abortando...");
            getch();
            return;
        }
        rewind(*BTidx);
        
        if((*HASHidx = fopen("HASHidx.bin","r+b")) == NULL)
        { /* Apenas abre para leitura e escrita */
            printf("Erro em HASHidx. Abortando...");
            getch();
            return;
        }
        rewind(*HASHidx);
    }
}

void CadastraCachorro(FILE **AP2)
{
	CACHORRO reg;
	system("CLS");
    
    rewind(*AP2);
    fread(&cont, sizeof(int), 1, *AP2);
	cont++;
	
	reg.cod_cachorro = cont;
	printf("\n Codigo: %d\n", reg.cod_cachorro);
	fflush(stdin);
	printf(" Raca: ");
	gets(reg.raca);
	printf(" Nome do Cachorro: ");
	gets(reg.nome);

	fseek(*AP2, 0, SEEK_END); /* Seta a posição para o fim do arquivo */
	fwrite(&reg, sizeof(CACHORRO), 1, *AP2); /* Escreve no fim do arquivo */
	
	rewind(*AP2);
	fwrite(&cont, sizeof(int), 1, *AP2);
	
	printf("\n Cachorro cadastrado com sucesso!");
	getch();
}

int ExisteCachorro(int codigo, FILE **AP2)
{
    if(cont == -1)
        return 0;
        
	CACHORRO reg;
	
	fseek(*AP2, sizeof(int), SEEK_SET);
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

int PerguntaCodigo(FILE **AP2)
{
    int cod, aux = 0;
    system("CLS");
    printf("\n Digite o codigo do cachorro <-1 para cadastrar um cachorro>: ");
    scanf("%d", &cod);
    if(cod == -1)
    {   
        CadastraCachorro(AP2);
        aux = 1;
    }
    while (!ExisteCachorro(cod, AP2))
    {
        if (!aux)
            printf("\n Cachorro inexistente. Digite novamente!");
        else
        {
            printf("\n Nova busca..." );
            aux = 0;
        }
        getch(); 
        system("CLS");  
        printf("\n Digite o codigo do cachorro <-1 para cadastrar um cachorro>: ");
        scanf("%d", &cod);
        if (cod == -1)
        {
            CadastraCachorro(AP2);
            aux = 1;
        }
    }
    return cod;
}

void CadastraVacina(FILE **AP1, FILE **AP2, FILE **BTidx, FILE **HASHidx)
{
    VACINA reg;
    
    system("CLS");
    printf("\n Codigo de controle: ");
    scanf("%d", &reg.cod_controle);
    fflush(stdin);
    
    reg.cod_cachorro = PerguntaCodigo(AP2);
    system("CLS");
    printf("\n Codigo de controle: %d", reg.cod_controle);
    printf("\n Codigo do cachorro: %d", reg.cod_cachorro);
    fflush(stdin);
    printf("\n Nome da vacina: ");
    gets(reg.vacina);
    fflush(stdin);
    printf(" Data de vacinacao <MM/AA>: ");
    gets(reg.data);
    printf(" Responsavel pela aplicacao: ");
    gets(reg.responsavel);
    
    fseek(*AP1, 0, SEEK_END); /* Vai para o final de AP1 para escrever reg */
    int offset = ftell(*AP1);
    fwrite(&reg, sizeof(VACINA), 1, *AP1);
    
    /* Insere na Hash */
    int rrn = h(reg.cod_controle); 
    Hash_Insere(HASHidx, reg.cod_controle, rrn, offset, 1);
    
    /* Insere em Árvore B */
    BTKEY BTreg;
    BTreg.id = reg.cod_controle;
    BTreg.rrn = offset;
    insertnode(getroot(BTidx), BTreg, BTidx);
}
