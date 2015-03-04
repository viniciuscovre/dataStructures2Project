/*******************************************************************************
DESCRIÇÃO DA BIBLIOTECA: Essa biblioteca reúne as funções que utlilizam dos
arquivos do projeto. Em outras palavras, é a biblioteca de funções relacionadas
a operações de main que operam nos arquivos binários. 
--> Relacionados à Árvores B (funções indicadas por 'BT_').
*******************************************************************************/

/* Declaração das Funções */
void BT_AbreArquivos(FILE **AP1, FILE **AP2);

/*******************************************************************************
DESCRIÇÃO: Verifica se os arquivos já foram criados. Se não, cria-os.
           Válido para os arquivos de Árvore B.
PARÂMETROS: AP1 - Arquivo Principal 1
            AP2 - Arquivo Principal 2
*******************************************************************************/
void BT_AbreArquivos(FILE **AP1, FILE **AP2)
{
    /* Para AP1 */
    if((*AP1 = fopen("AP1.bin","r+b")) == NULL) /* Se o arquivo não existir */
    {
        if((*AP1 = fopen("AP1.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        int aux = -1; /* -1 indica que o arquivo (AP1) está vazio */
        fwrite(&aux, sizeof(int), 1, *AP1);
    }
    else /* Se o arquivo já existir */
    {
        if((*AP1 = fopen("AP1.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP1. Abortando...");
            getch();
            return;
        }
        rewind(*AP1);
        fread(&header, sizeof(short int), 1, *AP1); /* Pega o Header da Árvore B de AP1 */
    }
    
    /* Para AP2 */
    if((*AP2 = fopen("AP2.bin","r+b")) == NULL) /* Se o arquivo não existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Cria o arquivo com w+b */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
    }
    else /* Se o arquivo já existir */
    {
        if((*AP2 = fopen("AP2.bin","w+b")) == NULL) /* Apenas abre para leitura e escrita */
        {
            printf("Erro em AP2. Abortando...");
            getch();
            return;
        }
    }
}
