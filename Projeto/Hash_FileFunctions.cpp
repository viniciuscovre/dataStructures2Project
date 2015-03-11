/* Hash_FIleFunctions.cpp */

#include <stdio.h>
#include "hash.h"

int h(int k)
{
    return k % M;
}

void Hash_Insere(FILE **HASHidx, int chave, int endereco)
{
    int status = 1; /* Indica que já existe registro no endereço dado */
    
    /* Pula o header de HASHidx (sizeof(int)) e vai ao endereço correto */
    fseek(*HASHidx, sizeof(int) + sizeof(HASHIDX)*endereco , SEEK_SET);
    
    fwrite(&status, sizeof(int), 1, *HASHidx);
    fwrite(&chave, sizeof(int), 1, *HASHidx);
    fwrite(&endereco, sizeof(int), 1, *HASHidx);
}
