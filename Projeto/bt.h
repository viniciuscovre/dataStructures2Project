/*******************************************************************************
DESCRIÇÃO DA BIBLIOTECA: Essa biblioteca cria a estrutura de dados de Árvores B.
*******************************************************************************/

/* Definições de constantes para a Árvore B */
#define MAXKEYS 4 /* Árvore B de ordem M (onde M = MAXKEYS + 1) */
#define MINKEYS ceil((MAXKEYS+1)/2) /* Mínimo de nós em uma página (exceto para a raíz) */
//#define NIL (-1)
#define NOKEY '@'
#define NO 0
#define YES 1

/* Define um tipo para a página de uma Árvore B */
typedef struct
{
    short int keycount; /* Número de chaves em uma página */
    int chave[MAXKEYS]; /* Página Atual. */
    short int child[MAXKEYS+1]; /* Ponteiros para os filhos */
} BTIDX;

#define PAGESIZE sizeof(BTIDX)
