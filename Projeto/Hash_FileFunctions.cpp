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
    fseek(*HASHidx, sizeof(HASHIDX)*(endereco) , SEEK_SET);
    
    short int qtd;
    fread(&qtd, sizeof(short int), 1, *HASHidx);
    
    reg.cont = qtd;
    reg.cesto[qtd-1].chave = chave;
    reg.cesto[qtd-1].rrn = endereco;
        
    if(qtd == 0 || qtd == 1)
    {
        fseek(*HASHidx, -sizeof(short int), SEEK_CUR);
        reg.cont++;
        fwrite(&reg, sizeof(HASHIDX), 1, *HASHidx);
        printf("Endereco: %d", reg.cesto[qtd].rrn);
        printf("\nChave %d inserida com sucesso!", reg.cesto[qtd].chave);
    }
    else
    {
        int tentativa = 0;
        while(qtd == 2)
        {
            tentativa++;
            printf("\nColisao!\nTentativa %d", tentativa);
            endereco = endereco+1;
            fseek(*HASHidx, sizeof(HASHIDX)*(endereco), SEEK_SET);
            fread(&qtd, sizeof(short int), 1, *HASHidx);
            if(qtd < 2)
                Hash_Insere(HASHidx, chave, endereco);
        }
    }
}
