#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct
{
    int cod_controle;
    int cod_cachorro;
    char vacina[30];
    char data[6];
    char responsavel[30];
} VACINA;

typedef struct
{
    int cod_cachorro;
    char raca[30];
    char nome[30];
} CACHORRO;

int h(int k)
{
    return k % M;
}

void Hash_Insere(FILE **HASHidx, int chave, int rrn, int offset, int tentativa)
{
    HASHIDX reg;
    
    fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET);
    fread(&reg, sizeof(HASHIDX), 1, *HASHidx);
    
    if(reg.cont < TAM_CESTO)
    {   
        reg.cesto[reg.cont].chave = chave;
        reg.cesto[reg.cont].offset = offset;
        reg.cont = reg.cont + 1;
        
        fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET);
        fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);
        
        printf("\nEndereco: %d. ByteOffset: %d", rrn, reg.cesto[reg.cont-1].offset);
        printf("\nChave %d inserida na Hash com sucesso!\n", reg.cesto[reg.cont-1].chave);
        getch();
    }
    else /* reg.cont == 2 */
    {
        printf("\nColisao!\nTentativa %d", tentativa);
        getch();
        Hash_Insere(HASHidx, chave, ++rrn, offset, ++tentativa);
    }
}

void Hash_Imprime(FILE *AP1, FILE *AP2, int offset)
{
    VACINA reg;
    CACHORRO reg1;
    
    fseek(AP1, offset, SEEK_SET);
    fread(&reg, sizeof(VACINA), 1,  AP1);
    
    printf(" RRN %d", offset);
    
    printf("\n\n DADOS DA VACINA %d", reg.cod_controle);
    printf("\n\n Codigo do Cachorro %c %d", 175, reg.cod_cachorro);
    
    fseek(AP2, sizeof(int), SEEK_SET);
	while (fread(&reg1, sizeof(CACHORRO), 1, AP2))
	{
		if (reg1.cod_cachorro == reg.cod_cachorro)
		{
			break;
		}	
	}
	printf("\n -  Raca %c %s", 175, reg1.raca);
	printf("\n -  Nome %c %s", 175, reg1.nome);
	
    printf("\n Nome da Vacina %c %s", 175, reg.vacina);
    printf("\n Data de Vacinacao %c %s", 175, reg.data);
    printf("\n Responsavel Pela Aplicacao %c %s", 175, reg.responsavel);   
}

void Hash_Pesquisa(int chave, int rrn, int acessos, FILE *HASHidx, FILE *AP1, FILE *AP2)
{   
    HASHIDX reg;
    
    system("CLS");
    fseek(HASHidx, sizeof(HASHIDX)*(rrn), SEEK_SET);
    fread(&reg, sizeof(HASHIDX), 1, HASHidx);

    if(reg.cont == 0)
    {
        printf("\n Chave %d nao encontrada!", chave);
        getch();
        return;
    }
    
    if (reg.cont == 1)
    {
        if(reg.cesto[reg.cont-1].chave == chave)
        {
            printf("\n Chave %d encontrada, endereco %d,", reg.cesto[reg.cont-1].chave, rrn);
            printf(" %d acesso(s)", acessos);
            Hash_Imprime(AP1, AP2, reg.cesto[reg.cont-1].offset);
            getch();
            return;
        }
        else
        {
            printf("\n Chave %d nao encontrada!", chave);
            getch();
            return;
        }
    }
    
    if (reg.cont == 2)
    {
        for(int i=0; i<TAM_CESTO; i++)
        {
            if(reg.cesto[i].chave == chave)
            {
                printf("\n Chave %d encontrada, endereco %d,", reg.cesto[i].chave, rrn);
                printf(" %d acesso(s)", acessos);
                Hash_Imprime(AP1, AP2, reg.cesto[i].offset);
                getch();
                return;
            }
        }
        rrn++;
        if (rrn > M)
        {
            rrn = 0;
            Hash_Pesquisa(chave, rrn, ++acessos, HASHidx, AP1, AP2);
        }
        else
            Hash_Pesquisa(chave, rrn, ++acessos, HASHidx, AP1, AP2);
    }
}
