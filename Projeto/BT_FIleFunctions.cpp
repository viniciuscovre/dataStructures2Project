#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "bt.h"

typedef struct
{
    int cod_controle;
    int cod_cachorro;
    char vacina[30];
    char data[6];
    char responsavel[30];
} VACINA;

typedef struct
{
    int cod_cachorro;
    char raca[30];
    char nome[30];
} CACHORRO;

int btopen(FILE **BTidx)
{
    *BTidx = fopen("BTidx.bin", "r+");
    return *BTidx != NULL;
}

short getroot(FILE **BTidx)
{
    short root;

    fseek(*BTidx, 0L, 0);
    if (!fread(&root, sizeof(short), 1, *BTidx)) 
    {
        printf("\nErro ao obter a raiz! Saindo do programa... \n");
        getch();
        exit(1);
    }

    return root;
}

void putroot(short root, FILE **BTidx)
{
    fseek(*BTidx, 0, 0);
    fwrite(&root, sizeof(short), 1, *BTidx);
}

int btread(short rrn, BTPAGE *page, FILE **BTidx)
{
    long addr;

    addr = (long) rrn * (long)PAGESIZE + 2L;
    fseek(*BTidx, addr, 0);

    return (fread(page, PAGESIZE, 1, *BTidx));
}

int searchnode(int id, BTPAGE *page, short *pos)
{
    int i;
    for (i = 0; i < page->keycount && (id > page->key[i].id); i++);

    *pos = i;

    return *pos < page->keycount && (id == page->key[*pos].id) ? YES : NO;
}

void insertpage(BTKEY key, short r_child, BTPAGE *page)
{
    int i;
    for (i = page-> keycount; key.id < page->key[i-1].id && i > 0; i--) 
    {
        page->key[i] = page->key[i-1];
        page->child[i+1] = page->child[i];
    }

    page->keycount++;
    page->key[i] = key;
    page->child[i+1] = r_child;
}

int btwrite(short rrn, BTPAGE *page, FILE **BTidx)
{
    long addr;

    addr = (long)rrn * (long) PAGESIZE + 2L;
    fseek(*BTidx, addr, 0);

    return (fwrite(page, PAGESIZE, 1, *BTidx));
}

short newpage(FILE **BTidx)
{
    long addr;

    fseek(*BTidx, 0, 2);
    addr = ftell(*BTidx) - 2L;

    return ((short) addr / PAGESIZE);
}

void initpage(BTPAGE *page)
{
    int i;

    for (i = 0; i < MAXKEYS; i++) 
    {
        page->key[i].id = NOKEY;
        page->key[i].rrn = NIL;
        page->child[i] = NIL;
    }

    page->child[MAXKEYS] = NIL; //pois o vetor child tem maxkeys + 1
}

short createroot(BTKEY key, short left, short right, FILE **BTidx)
{
    BTPAGE page;
    short rrn;

    rrn = newpage(BTidx);
    initpage(&page);

    page.key[0] = key;
    page.child[0] = left;
    page.child[1] = right;
    page.keycount = 1;

    btwrite(rrn, &page, BTidx);
    putroot(rrn, BTidx);

    return rrn;
}

short createtree(FILE **BTidx)
{
    BTKEY key;
    *BTidx = fopen("BTidx.bin","w");
    fclose(*BTidx);

    btopen(BTidx);

    key.id = 1;
    key.rrn = 1;

    return createroot(key, NIL, NIL, BTidx);
}

void split(BTKEY key, short r_child, BTPAGE *p_oldpage, BTKEY *promo_key, short *promo_r_child, BTPAGE *p_newpage, FILE **BTidx)
{
    int j;
    BTKEY workkeys[MAXKEYS+1];
    short workchil[MAXKEYS+2];

    for (j = 0; j < MAXKEYS; j++) 
    {
        workkeys[j] = p_oldpage->key[j];
        workchil[j] = p_oldpage->child[j];
    }

    workchil[j] = p_oldpage->child[j];

    for (j = MAXKEYS; key.id < workkeys[j-1].id && j > 0; j--) 
    {
        workkeys[j] = workkeys[j-1];
        workchil[j+1] = workchil[j];
    }

    workkeys[j] = key;
    workchil[j+1] = r_child;

    *promo_r_child = newpage(BTidx);
    initpage(p_newpage);

    for (j = 0; j < MINKEYS; j++)
    {
        p_oldpage->key[j] = workkeys[j];
        p_oldpage->child[j] = workchil[j];

        p_newpage->key[j] = workkeys[j+1+MINKEYS];
        p_newpage->child[j] = workchil[j+1+MINKEYS];

        p_oldpage->key[j+MINKEYS].id = NOKEY;
        p_oldpage->key[j+MINKEYS].rrn = NIL;

        p_oldpage->child[j+1+MINKEYS] = NIL;
    }

    p_oldpage->child[MINKEYS] = workchil[MINKEYS];
    p_newpage->child[MINKEYS] = workchil[j+1+MINKEYS];
    p_newpage->keycount = MAXKEYS - MINKEYS;
    p_oldpage->keycount = MINKEYS;

    *promo_key = workkeys[MINKEYS];
}

int insert(short rrn, BTKEY key, short *promo_r_child, BTKEY *promo_key, int *found, FILE **BTidx)
{
    int promoted;
    short pos, p_b_rrn;
    BTPAGE page, newpage;
    BTKEY p_b_key;

    if (rrn == NIL) 
    {
        *promo_key = key;
        *promo_r_child = NIL;
        return(YES);
    }

    btread(rrn, &page, BTidx);

    *found = searchnode(key.id, &page, &pos);
    if (*found) 
    {
        printf("\nErro! Chave %d ja existente \n", key.id);
        getch();
        return(NO);
    }

    promoted = insert(page.child[pos], key, &p_b_rrn, &p_b_key, found, BTidx);
    if (!promoted)
        return(NO);

    if (page.keycount < MAXKEYS) 
    {
        insertpage(p_b_key, p_b_rrn, &page);
        btwrite(rrn, &page, BTidx);
        return(NO);
    }
    else 
    {
        printf("Divisao de no.\n");
        split(p_b_key, p_b_rrn, &page, promo_key, promo_r_child, &newpage, BTidx);
        printf("Chave %d promovida.\n", promo_key->id);

        btwrite(rrn, &page, BTidx);
        btwrite(*promo_r_child, &newpage, BTidx);

        return(YES);
    }
}

void insertnode(short root, BTKEY key, FILE **BTidx)
{
    int promoted, found;
    short promo_rrn;

    BTKEY promo_key;

    if (root == NIL)
    {
        root = createroot(key, NIL, NIL, BTidx);
        printf("\nChave %d inserida com sucesso em Arvore B!\n", key.id);
        getch();
        return;
    }

    promoted = insert(root, key, &promo_rrn, &promo_key, &found, BTidx);

    if (promoted)
        root = createroot(promo_key, root, promo_rrn, BTidx);

    if (!found)
    {
        printf("\nChave %d inserida com sucesso em Arvore B!\n", key.id);
        getch();
    }
}

void searchbtree(int key, FILE *BTidx, FILE *AP1, FILE *AP2) 
{
     BTPAGE actualPage;
     BTKEY node;
     short pos;
     int root;

     VACINA reg;
     CACHORRO reg1;
     
     system("CLS");

     root = getroot(&BTidx);
     btread(root, &actualPage, &BTidx);
     int found;
     found = searchnode(key, &actualPage, &pos);

     while (!found) 
     {
        if (root == NIL) 
        {
            printf("\n Chave %d nao encontrada\n", key);
            getch();
            return;
        }
        root = actualPage.child[pos];
        btread(root, &actualPage, &BTidx);
        found = searchnode(key, &actualPage, &pos);
     }

     printf("\n Chave %d encontrada, pagina %d, posicao %d", key, root, pos);

     node = actualPage.key[pos];
     fseek(AP1, node.rrn, 0);
     fread(&reg, sizeof(VACINA), 1, AP1);
     
     printf(" RRN %d", node.rrn);

     printf("\n\n DADOS DA VACINA %d", reg.cod_controle);
     printf("\n\n Codigo do Cachorro %c %d", 175, reg.cod_cachorro);
     fseek(AP2, sizeof(int), SEEK_SET);
	 while (fread(&reg1, sizeof(CACHORRO), 1, AP2))
	 {
		 if (reg1.cod_cachorro == reg.cod_cachorro)
		 {
            break;
		 }	
	 }
	 printf("\n -  Raca %c %s", 175, reg1.raca);
	 printf("\n -  Nome %c %s", 175, reg1.nome);
     printf("\n Nome da Vacina %c %s", 175, reg.vacina);
     printf("\n Data de Vacinacao %c %s", 175, reg.data);
     printf("\n Responsavel Pela Aplicacao %c %s", 175, reg.responsavel);
     getch();
}

void getallnodes(FILE *BTidx, FILE *AP1, FILE *AP2) 
{
    int root;
    root = getroot(&BTidx);
    recursiveprint(root, BTidx, AP1, AP2);

    getch();
}

void recursiveprint(int root, FILE *BTidx, FILE *AP1, FILE *AP2) 
{
    int i;
    BTKEY node;
    BTPAGE page;
    VACINA reg;
    CACHORRO reg1;
    
    if (root == NIL) return;
    btread(root, &page, &BTidx);

    for (i = 0; i <= page.keycount; i++) 
    {
        root = page.child[i];
        recursiveprint(root, BTidx, AP1, AP2);

        if (i < page.keycount) 
        {
            node = page.key[i];
            fseek(AP1, node.rrn, 0);
            fread(&reg, sizeof(VACINA), 1, AP1);
            
            printf("\n\n DADOS DA VACINA %d", reg.cod_controle);
            printf("\n\n Codigo do Cachorro %c %d", 175, reg.cod_cachorro);
            fseek(AP2, sizeof(int), SEEK_SET);
	        while (fread(&reg1, sizeof(CACHORRO), 1, AP2))
	        {
		        if (reg1.cod_cachorro == reg.cod_cachorro)
		        {
                    break;
		        }	
            }
            printf("\n -  Raca %c %s", 175, reg1.raca);
	        printf("\n -  Nome %c %s", 175, reg1.nome);
	        
            printf("\n Nome da Vacina %c %s", 175, reg.vacina);
            printf("\n Data de Vacinacao %c %s", 175, reg.data);
            printf("\n Responsavel Pela Aplicacao %c %s", 175, reg.responsavel);
        }
    }
}
