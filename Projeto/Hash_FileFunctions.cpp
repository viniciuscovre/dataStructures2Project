/* Hash_FIleFunctions.cpp */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "hash.h"

int h(int k)
{
    return k % M;
}

void Hash_Insere(FILE **HASHidx, int chave, int rrn, int endereco)
{
    HASHIDX reg;
    
    if(fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET))/* Se der erro em fseek */
        printf("\nERRO ao dar Seeking no arquivo de indice!\nInicializacao incorreta...\n");
    
    short int qtd; /* Pega a quantidade de cadastros em um cesto */
    fread(&qtd, sizeof(short int), 1, *HASHidx);
        
    if(qtd == 0 || qtd == 1)
    {
        fseek(*HASHidx, sizeof(HASHIDX)*(rrn) , SEEK_SET);
        /* fseek(*HASHidx, -sizeof(short int), SEEK_CUR); */
        reg.cesto[qtd].chave = chave;
        reg.cesto[qtd].offset = endereco;
        qtd++;
        reg.cont = qtd;
        fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);
        printf("\nEndereco: %d", rrn);
        printf("\nChave %d inserida com sucesso!\n", reg.cesto[qtd-1].chave);
        getch();
    }
    else
    {
        int tentativa = 0;
        while(qtd == 2 || tentativa <= M-1)
        {
            tentativa++;
            printf("\nColisao!\nTentativa %d", tentativa);
            getch();
            rrn = rrn+1;
            fseek(*HASHidx, sizeof(HASHIDX)*(rrn), SEEK_SET);
            fread(&qtd, sizeof(short int), 1, *HASHidx);
            if(qtd < 2)
            {
                Hash_Insere(HASHidx, chave, rrn, endereco);
                break;
            }
        }
        if(tentativa == M-1)
            printf("\n\nHASH OVERFLOW!");
        getch();
    }
}

void Hash_Pesquisa(int chave, FILE *HASHidx, FILE *AP2)
{
    int rrn, acessos = 1;
    HASHIDX reg;
    
    system("CLS");
    rrn = h(chave);
    
    rewind(HASHidx);
    fread(&reg, sizeof(HASHIDX), rrn, HASHidx); /* Carrega o cesto em reg */
    printf("ERRO1");getch();
    while((chave != reg.cesto[0].chave && chave != reg.cesto[1].chave) && acessos == M)
    {
        printf("ERRO2");getch();
        rrn++;
        rewind(HASHidx);
        fread(&reg, sizeof(HASHIDX), rrn, HASHidx); /* Carrega o cesto em reg */
        acessos++;
    }
    if(acessos == M)
        printf("\n Chave %d nao encontrada", chave);
    else
        printf("\n Chave %d encontrada, endereco %d, %d acesso(s)", chave, rrn, acessos);
    getch();
}
