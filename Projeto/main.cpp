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
#include "bt.h"
#include "functions.h"

/* Define um tipo para o cadastro de vacinas (AP1) */
typedef struct
{
    int cod_controle;
    int cod_cachorro;
    char vacina[30];
    char data[5];
    char responsavel[30];
} VACINA;

/* Define um tipo para o cadastro de cachorros (AP2) */
typedef struct
{
    int cod_cachorro; /* Auto-Incremento */
    char raca[30];
    char nome[30];
} CACHORRO;

int main()
{
    FILE *AP1, *AP2, *BTidx;
    AbreArquivos(&AP1, &AP2, &BTidx);
    
    int opcao = Menu();
    while (1)
	{
	    switch(opcao)
	    {
	        /*case 1: CadastraCachorro(&AP2); 
                    break;
	        case 2: CadastraVacina(&AP1, &AP2, &IndPrim, &IndSec1, &IndSec2); 
                    break;
			case 3: AlteraCachorro(&AP2);
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
	        case 0: printf("\nSaindo do Programa...");
					/* Fecha arquivos principais */ 
        	        fclose(AP1); 
					fclose(AP2);
					fclose(BTidx);
                    getch(); 
                    return 0;
	        default: printf("\nOpcao invalida!"); 
                     getch();
                     break;
        }
        opcao = Menu();
    }
}
