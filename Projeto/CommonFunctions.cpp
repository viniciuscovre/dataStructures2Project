/*******************************************************************************
DESCRIÇÃO DO ARQUIVO: Esse arquivo.cpp reúne as funções que não utlilizam dos
arquivos do projeto. Em outras palavras, é o conjunto de funções relacionadas
a operações de main que não necessitam dos arquivos binários.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

int Menu()
{
	int opcao;
	system("CLS");
	printf("%c%c%c CL%cNICA VETERIN%cRIA %c%c%c\n", 178, 177, 176, 214, 181, 176, 177, 178);
    printf("\n 1 %c Cadastra Cachorro", 175);
    printf("\n 2 %c Cadastra Vacina", 175);
    printf("\n 3 %c Listar dados de uma Vacina", 175);
    printf("\n 4 %c Listar vacinas", 175);
	printf("\n 0 %c Sair", 175);
	printf("\n\nEscolha a opcao: ");
    scanf("%d", &opcao);
	
	return opcao;
}

/*void DeletarArquivos()
{
    char resp;
    printf("\n\nDeletar Arquivos? (S/N): ");
    resp = getche();
    resp = tolower(resp);
	if (resp == 's')
	{
        remove("AP1.bin");
        remove("AP2.bin");
        remove("BTidx.bin");
        remove("HASHidx.bin");
        printf("\nArquivos deletados!");
    }
    printf("\n\nSaindo do Programa...");
    getch();
}*/

int PerguntaChave()
{
    int cod;
    system("CLS");
    printf("\n Codigo da vacina: ");
    scanf("%d", &cod);
    fflush(stdin);
    return cod;
}

int ListaDados()
{
    int opt = 1;
    printf("\n Metodo de Busca\n  0)Arvore B\n  1)Hash\n\n OPCAO: ");
    scanf("%d", &opt);
    
    while(opt != 0 && opt != 1)
    {
        printf("\n Opcao Invalida! Digite Novamente: ");
        scanf("%d", &opt);
    }
    return opt;
}
