/*******************************************************************************
DESCRIÇÃO DA BIBLIOTECA: Essa biblioteca reúne as funções que não utlilizam dos
arquivos do projeto. Em outras palavras, é a biblioteca de funções relacionadas
a operações de main que não necessitam dos arquivos binários.
*******************************************************************************/

/* Declaração das Funções */
int Menu();

/*******************************************************************************
DESCRIÇÃO: Exibe o menu de opções das possíveis operações do programa.
RETORNO: Retorna a opção escolhida pelo usuário.
*******************************************************************************/
int Menu()
{
	int opcao;
	system("CLS");
	printf("%c%c%c CL%cNICA VETERIN%cRIA %c%c%c\n", 178, 177, 176, 214, 181, 176, 177, 178);
    /*printf("\n 1 %c Cadastra Cachorro", 175);
    printf("\n 2 %c Cadastra Vacina", 175);
	printf("\n 3 %c Altera Cachorro", 175);
	printf("\n 4 %c Alterar dados de Vacina", 175);
	printf("\n 5 %c Remove Vacina", 175);
	printf("\n 6 %c Pesquisa por Codigo de Controle", 175);
	printf("\n 7 %c Pesquisa por Nome da Vacina", 175);
	printf("\n 8 %c Compactar o arquivo", 175);*/
	printf("\n 0 %c Sair", 175);
	printf("\n\nEscolha a opcao: ");
    scanf("%d", &opcao);
	
	return opcao;
}
