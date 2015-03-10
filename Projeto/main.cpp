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

int main()
{
    FILE *AP1, *AP2, *BTidx;
    AbreArquivos(&AP1, &AP2, &BTidx);
    
    int promoted; /* Booleano: diz se houve promoção da página */
    short int root, /* RRN da página Raíz */
              promo_rrn; /* RRN da página promovida */
    int promo_chave, /* Chave promovida */
        chave; /* Próxima chave a ser inserida na árvore */
         
    int opcao = Menu();
    while (1)
	{
	    switch(opcao)
	    {
	        case 1: CadastraCachorro(&AP2); 
                    break;
	        case 2: CadastraVacina(&AP1, &AP2, &BTidx);
	                /* Inicializa Árvore B */
	                /*if (btopen())
                    {
                        root = getroot();
                    }
                    else
                    {
                        root = create_tree();
                    }
    
                    while ((key = getchar()) != 'q')
                    {
                        promoted = insert(root, key, &promo_rrn, &promo_key);
                        if (promoted)
                            root = create_root(promo_key, root, promo_rrn);
                    }
                    btclose();*/
                    break;
			/*case 3: AlteraCachorro(&AP2);
                    break;
			case 4: AlteraDados(&AP1, &IndPrim, &IndSec1, &IndSec2);
                    break;
            case 5: MenuRemoveVacina(&AP1, &IndPrim, &IndSec1, &IndSec2);                   
                    break;
            case 6: PesquisaCodPrim(&AP1, &AP2);
                    break;
            case 7: PesquisaVacinaSec(&AP1, &AP2, &IndSec2);
                    break;
            case 8: Compacta(&AP1, &IndSec2);
                    break; */
	        case 0: fclose(AP1); 
					fclose(AP2);
					fclose(BTidx);
					DeletarArquivos();
                    return 0;
	        default: printf("\nOpcao invalida!"); 
                     getch();
                     break;
        }
        opcao = Menu();
    }
}
