/*******************************************************************************
DESCRIÇÃO: Inicializa o Arquivo Principal 1.
           Inicializa os arquivos de índices de Árvore B e de Hash.
PARÂMETROS: AP1 - Arquivo Principal 1
            BTidx - Arquivo de índice de Árvore B
            Hidx - Arquivo de índice de Hash
*******************************************************************************/
void InicializaArquivos(FILE **AP1, FILE **BTidx);


/*******************************************************************************
DESCRIÇÃO: Informa o número de cachorros cadastrados.
PARÂMETROS: AP2 - Arquivo Principal 2
RETORNOS: O número de cachorros cadastrados em AP2
*******************************************************************************/
int NumCachorros(FILE **AP2);


/*******************************************************************************
DESCRIÇÃO: Verifica se os arquivos já foram criados. Se não, cria-os.
PARÂMETROS: AP1 - Arquivo Principal 1
            AP2 - Arquivo Principal 2
            BTidx - Arquivo de índice de Árvore B
*******************************************************************************/
void AbreArquivos(FILE **AP1, FILE **AP2, FILE **BTidx);


/*******************************************************************************
DESCRIÇÃO: Cadastra informações de um cachorro no Arquivo Principal 2
PARÂMETROS: AP2 - Arquivo Principal 2
*******************************************************************************/
void CadastraCachorro(FILE **AP2);


/*******************************************************************************
DESCRIÇÃO: Verifica se o código já existe no arquivo.
PARÂMETROS: codigo - Código a ser verificado
            AP2 - Arquivo Principal 2
RETORNOS: 0 - Não existe um cachorro com o código passado por parâmetro
          1 - Existe um cachorro com o código passado por parâmetro
*******************************************************************************/
int ExisteCachorro(int codigo, FILE **AP2);


/*******************************************************************************
DESCRIÇÃO: Exibe o menu de opções das possíveis operações do programa.
RETORNO: Retorna a opção escolhida pelo usuário.
*******************************************************************************/
int Menu();
