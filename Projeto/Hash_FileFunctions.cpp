/* Hash_FIleFunctions.cpp */

#include <stdio.h>
#include <conio.h>
#include "hash.h"

int h(int k)
{
    return k % M;
}

void Hash_Insere(FILE **HASHidx, int chave, int endereco)
{
    HASHIDX reg;
    
    /* Pula o header de HASHidx (sizeof(int)) e vai ao endereço correto */
    if(fseek(*HASHidx, sizeof(HASHIDX)*(endereco) , SEEK_SET))
        printf("\nERRO!\n"); /* Se der erro em fseek */
    
    short int qtd; /* Pega a quantidade de cadastros em um cesto */
    fread(&qtd, sizeof(short int), 1, *HASHidx);
        
    if(qtd == 0 || qtd == 1)
    {
        fseek(*HASHidx, sizeof(HASHIDX)*(endereco) , SEEK_SET);
        /* fseek(*HASHidx, -sizeof(short int), SEEK_CUR); */
        reg.cesto[qtd].chave = chave;
        reg.cesto[qtd].rrn = endereco;
        qtd++;
        reg.cont = qtd;
        fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);
        printf("\nEndereco: %d", reg.cesto[qtd-1].rrn);
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
            endereco = endereco+1;
            fseek(*HASHidx, sizeof(HASHIDX)*(endereco), SEEK_SET);
            fread(&qtd, sizeof(short int), 1, *HASHidx);
            if(qtd < 2)
            {
                Hash_Insere(HASHidx, chave, endereco);
                break;
            }
        }
        if(tentativa == M-1)
            printf("\n\nHASH OVERFLOW!");
        getch();
    }
}
