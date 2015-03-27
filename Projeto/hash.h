/* Cria a estrutura de dados de Hash. */

#define M 11
#define TAM_CESTO 2

typedef struct
{
    int chave, offset;
} CESTO;

typedef struct
{
    int cont;
    CESTO cesto[TAM_CESTO];
} HASHIDX;


/*******************************************************************************
DESCRIÇÃO: Função hashing h(k) que transforma uma chave k em um endereço.
PARÂMETRO: k - chave.
RETORNO: RRN a partir da chave k.
*******************************************************************************/
int h(int k);


/*******************************************************************************
DESCRIÇÃO: Insere a chave em determinado endereço no arquivo de índice Hash.
PARÂMETRO: HASHidx - Arquivo de índice de Hash
           chave - Chave a ser inserida (cod_controle)
           rrn - Endereço no índice Hash (gerado a partir da chave)
           offset - Endereço do registro no arquivo AP1
           tentativa - Número de tentativas de inserção até dar certo
*******************************************************************************/
void Hash_Insere(FILE **HASHidx, int chave, int rrn, int offset, int tentativa);


/*******************************************************************************
DESCRIÇÃO: Imprime os dados de uma vacinação.
PARÂMETRO: AP1 - Arquivo Principal 1
           AP2 - Arquivo Principal 2
           offset - Byteoffset de uma chave no arquivo AP1
*******************************************************************************/
void Hash_Imprime(FILE *AP1, FILE *AP2, int offset);


/*******************************************************************************
DESCRIÇÃO: Busca uma dada vacina e exibe seus dados (inclusive do cachorro).
PARÂMETRO: chave - Chave a ser pesquisada (código de controle)
           rrn - Endereço no índice Hash (gerado a partir da chave)
           acessos - Número de acessos para encontrar a chave.
           HASHidx - Arquivo de índice de Hash
           AP1 - Arquivo Principal 1
           AP2 - Arquivo Principal 2
*******************************************************************************/
void Hash_Pesquisa(int chave, int rrn, int acessos, FILE *HASHidx, FILE *AP1, FILE *AP2);
