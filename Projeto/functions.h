/* Declaração das Funções relacionadas à Árvore B */

/*******************************************************************************
DESCRIÇÃO: Verifica se os arquivos já foram criados. Se não, cria-os.
           Válido para os arquivos de Árvore B.
PARÂMETROS: AP1 - Arquivo Principal 1
            AP2 - Arquivo Principal 2
*******************************************************************************/
void AbreArquivos(FILE **AP1, FILE **AP2, FILE **BTidx);

/*******************************************************************************
DESCRIÇÃO: Inicializa o Arquivo Principal 1.
           Inicializa os arquivos de índices de Árvore B e de Hash.
PARÂMETROS: AP1 - Arquivo Principal 1
            BTidx - Arquivo de índice de Árvore B
            Hidx - Arquivo de índice de Hash
*******************************************************************************/
void InicializaArquivos(FILE **AP1, FILE **BTidx);


/* Declaração das Funções que não manipulam arquivos */

/*******************************************************************************
DESCRIÇÃO: Exibe o menu de opções das possíveis operações do programa.
RETORNO: Retorna a opção escolhida pelo usuário.
*******************************************************************************/
int Menu();
