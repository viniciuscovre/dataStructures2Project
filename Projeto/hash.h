/* Cria a estrutura de dados de Hash. */
#define M 11
//#define TAM_HASH 11
#define TAM_CESTO 2

typedef struct
{
    int chave, offset;
} CESTO;

typedef struct
{
    short int cont;
    CESTO cesto[TAM_CESTO];
} HASHIDX;


/*******************************************************************************
DESCRIÇÃO: Função hashing h(k) que transforma uma chave k em um endereço.
PARÂMETRO: k - chave.
RETORNO: Endereço a partir da chave k.
*******************************************************************************/
int h(int k);


/*******************************************************************************
DESCRIÇÃO: Insere a chave em determinado endereço no arquivo de índice Hash.
PARÂMETRO: HASHidx - Arquivo de índice de Hash
           chave - Chave a ser inserida (cod_controle)
           rrn - Endereço no índice Hash (gerado a partir da chave)
           endereco - Endereço do registro no arquivo AP1
*******************************************************************************/
void Hash_Insere(FILE **HASHidx, int cahve, int rrn, int endereco);


/*******************************************************************************
DESCRIÇÃO: Busca uma dada vacina e exibe seus dados (inclusive do cachorro).
PARÂMETRO: chave - Chave a ser pesquisada (código de controle)
           HASHidx - Arquivo de índice de Hash
           AP2 - Arquivo Principal 2
*******************************************************************************/
void Hash_Pesquisa(int chave, FILE *HASHidx, FILE *AP2);
