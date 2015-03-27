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
    int key, opcao;
    
    FILE *AP1, *AP2, *BTidx, *HASHidx;
    AbreArquivos(&AP1, &AP2, &BTidx, &HASHidx);
         
    opcao = Menu();
    while (1)
	{
	    switch(opcao)
	    {
	        case 1: CadastraCachorro(&AP2); 
                    break;
	        case 2: CadastraVacina(&AP1, &AP2, &BTidx, &HASHidx);
                    break;
			case 3: key = PerguntaChave();
                    if(ListaDados()) /* Busca em Hash */
                    {
                        int aux = h(key);
                        Hash_Pesquisa(key, aux, 1, HASHidx, AP1);
                    }
                    else /* Busca em Árvore B */
                    {
                        searchbtree(key, BTidx, AP1);
                    }
			        break;
            case 4: getallnodes(BTidx, AP1);
                    break;
	        case 0: fclose(AP1); 
					fclose(AP2);
					fclose(BTidx);
					fclose(HASHidx);
					//DeletarArquivos();
                    return 0;
	        default: printf("\nOpcao invalida!"); 
                     getch();
                     break;
        }
        opcao = Menu();
    }
}
