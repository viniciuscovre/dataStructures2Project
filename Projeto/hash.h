/*******************************************************************************
                     Cria a estrutura de dados de Hash.
*******************************************************************************/

#define M 11
//#define TAM_HASH 11
#define TAM_CESTO 2

typedef struct
{
    short int status[TAM_CESTO];
    int chave[TAM_CESTO], rrn[TAM_CESTO];
} HASHIDX;

/*******************************************************************************
                                    Fim.
*******************************************************************************/


/*******************************************************************************
DESCRIÇÃO: Função hashing h(k) que transforma uma chave k em um endereço.
PARÂMETRO: k - chave.
RETORNO: Endereço a partir da chave k.
*******************************************************************************/
int h(int k);


/*******************************************************************************
DESCRIÇÃO: Procura um espaço vazio no cesto.
PARÂMETRO: HASHidx - Arquivo de índice de Hash
RETORNO: Endereço de um espaço livre no cesto (-1 se o cesto está todo ocupado)
*******************************************************************************/
int Hash_VerificaStatus(FILE **HASHidx);


/*******************************************************************************
DESCRIÇÃO: Insere a chave em determinado endereço no arquivo de índice Hash.
PARÂMETRO: HASHidx - Arquivo de índice de Hash
           chave - Chave a ser inserida (cod_controle)
           endereco - Endereço a ser inserida a chave (gerado a partir da chave)
*******************************************************************************/
void Hash_Insere(FILE **HASHidx, int cahve, int endereco);
