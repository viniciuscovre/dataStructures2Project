/******************************************************************************* 
PROJETO 2 - Estrutura de Dados II - Ciência da Computação (noturno)
Grupo: Vinicius Covre de Assis e Webster Lima.
Professora: Verônica Carvalho.
Data de entrega: 26/03/2015.
UNESP - Rio Claro.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "functions.h"
#include "bt.h"
#include "hash.h"

int main()
{
    FILE *AP1, *AP2, *BTidx, *HASHidx;
    AbreArquivos(&AP1, &AP2, &BTidx, &HASHidx);
    
    int promoted; /* Booleano: diz se houve promoção da página */
    short int root, /* RRN da página Raíz */
              promo_rrn; /* RRN da página promovida */
    int promo_chave, /* Chave promovida */
        chave; /* Próxima chave a ser inserida na árvore */
         
    int key, opcao = Menu();
    while (1)
	{
	    switch(opcao)
	    {
	        case 1: CadastraCachorro(&AP2); 
                    break;
	        case 2: CadastraVacina(&AP1, &AP2, &BTidx, &HASHidx);
                    break;
			case 3: key = PerguntaChave();
                    if(ListaDados())/* Busca em Hash */
                        Hash_Pesquisa(key, HASHidx, AP2);
                    //else /* Busca em Árvore B */
			        break;
	        case 0: fclose(AP1); 
					fclose(AP2);
					fclose(BTidx);
					fclose(HASHidx);
					DeletarArquivos();
                    return 0;
	        default: printf("\nOpcao invalida!"); 
                     getch();
                     break;
        }
        opcao = Menu();
    }
}
