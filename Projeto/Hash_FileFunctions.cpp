#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "hash.h"

/* Define um tipo para o cadastro de vacinas (AP1) */
typedef struct
{
    int cod_controle;
    int cod_cachorro;
    char vacina[30];
    char data[5];
    char responsavel[30];
} VACINA;

int h(int k)
{
    return k % M;
}

void Hash_Insere(FILE **HASHidx, int chave, int rrn, int offset, int tentativa)
{
    HASHIDX reg;
    
    if(fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET))/* Se der erro em fseek */
        printf("\nERRO ao dar Seeking no arquivo de indice!\nInicializacao incorreta...\n");
    
    short int qtd; /* Pega a quantidade de cadastros em um cesto */
    fread(&qtd, sizeof(short int), 1, *HASHidx);
        
    if(qtd < TAM_CESTO)
    {
        fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET);
        /* fseek(*HASHidx, -sizeof(short int), SEEK_CUR); */
        
        reg.cesto[qtd].chave = chave;
        reg.cesto[qtd].offset = offset;
        reg.cont = ++qtd;
        
        fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);
        printf("\nEndereco: %d", rrn);
        printf("\nChave %d inserida com sucesso!\n", reg.cesto[qtd-1].chave);
        getch();
    }
    else /* qtd == 2 */
    {
        printf("\nColisao!\nTentativa %d", tentativa);
        getch();
        Hash_Insere(HASHidx, chave, ++rrn, offset, ++tentativa);
        /*if(qtd == 2)
        {
            printf("\nColisao!\nTentativa %d", tentativa);
            getch();
            Hash_Insere(HASHidx, chave, ++rrn, offset, ++tentativa);
            fseek(*HASHidx, sizeof(HASHIDX)*(++rrn) , SEEK_SET);
            fread(&qtd, sizeof(short int), 1, *HASHidx);
        }
        fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET);
        fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);*/
    }
}

void Hash_Imprime(FILE *AP1, int offset)
{
    VACINA reg;
    
    fseek(AP1, offset, SEEK_SET);
    fread(&reg, sizeof(VACINA), 1,  AP1);
    
    printf("\n\n DADOS DA VACINA %d", reg.cod_controle);
    printf("\n\n Codigo do Cachorro %c %d", 175, reg.cod_cachorro);
    printf("\n Nome da Vacina %c %s", 175, reg.vacina);
    printf("\n Data de Vacinacao %c %s", 175, reg.data);
    printf("\n Responsavel Pela Aplicacao %c %s", 175, reg.responsavel);
    
}

void Hash_Pesquisa(int chave, int rrn, int acessos, FILE *HASHidx, FILE *AP1)
{   
    int cont;
    HASHIDX reg;
    
    system("CLS");
    fseek(HASHidx, sizeof(HASHIDX)*(rrn), SEEK_SET);
    
    fread(&cont, sizeof(short int), 1, HASHidx);
    
    if(cont == 0)
    {
        printf("\n Chave %d nao encontrada!", chave);
        getch();
        return;
    }

    else /* Carrega o cesto e faz as comparações */
    {
        fseek(HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET);
        /* fseek(*HASHidx, -sizeof(short int), SEEK_CUR); */
        fread(&reg, sizeof(HASHIDX), 1, HASHidx);
        
        for(int i=0; i<TAM_CESTO; i++)
        {
            if(reg.cesto[i].chave == chave);
            {
                printf("\n Chave %d encontrada, endereco %d,", reg.cesto[i].chave, rrn);
                printf(" %d acesso(s)", acessos);
                Hash_Imprime(AP1, reg.cesto[i].offset);
                getch();
                return;
            }
        }
        Hash_Pesquisa(chave, ++rrn, ++acessos, HASHidx, AP1);
    }
}
