/* Hash_FIleFunctions.cpp */

#include <stdio.h>
#include <conio.h>
#include "hash.h"

int h(int k)
{
    return k % M;
}

int Hash_VerificaStatus(FILE **HASHidx)
{
    int i = 0, status[TAM_CESTO];
    while(i < TAM_CESTO) /* Verifica se tem espaço livre em algum dos nós do cesto */
    {
        /* Lê os status dos nós de um cesto */
        fread(&status[i], sizeof(short int), 1, *HASHidx);
        
        if(status[i] == 0) /* Se um item do cesto estiver livre */
        {
            /* Volta para a posição correta da inserção */
            fseek(*HASHidx, -sizeof(short int), SEEK_CUR);
            return i;
        }
        i++;
    }
    return -1;
}

void Hash_Insere(FILE **HASHidx, int chave, int endereco)
{
    int status[TAM_CESTO];
    int novo_status = 1; /* Indica que o novo item foi inserido */
    
    /* Pula o header de HASHidx (sizeof(int)) e vai ao endereço correto */
    fseek(*HASHidx, sizeof(HASHIDX)*(endereco) , SEEK_SET);
    
    int pos_cesto = Hash_VerificaStatus(HASHidx);
    
    if(pos_cesto == -1 || pos_cesto == 0)
    {
        fwrite(&novo_status, sizeof(short int), 1, *HASHidx);
        fseek(*HASHidx, sizeof(short int), SEEK_CUR);
        fwrite(&chave, sizeof(int), 1, *HASHidx);
        fseek(*HASHidx, sizeof(int), SEEK_CUR);
        fwrite(&endereco, sizeof(int), 1, *HASHidx);
        fseek(*HASHidx, sizeof(int), SEEK_CUR);
    }
    else /* if(pos_cesto == 1); */
    {
        fwrite(&novo_status, sizeof(short int), 1, *HASHidx);
        fseek(*HASHidx, sizeof(int), SEEK_CUR);
        fwrite(&chave, sizeof(int), 1, *HASHidx);
        fseek(*HASHidx, sizeof(int), SEEK_CUR);
        fwrite(&endereco, sizeof(int), 1, *HASHidx);
    }
}
