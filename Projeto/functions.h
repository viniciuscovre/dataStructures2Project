/*******************************************************************************
DESCRIÇÃO: Inicializa o Arquivo Principal 1.
           Inicializa os arquivos de índices de Árvore B e de Hash.
PARÂMETROS: AP1 - Arquivo Principal 1
            BTidx - Arquivo de índice de Árvore B
            HASHidx - Arquivo de índice de Hash
*******************************************************************************/
void InicializaArquivos(FILE **AP1, FILE **BTidx, FILE **HASHidx);


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
            HASHidx - Arquivo de índice de Hash
*******************************************************************************/
void AbreArquivos(FILE **AP1, FILE **AP2, FILE **BTidx, FILE **HASHidx);


/*******************************************************************************
DESCRIÇÃO: Cadastra informações de um cachorro no Arquivo Principal 2.
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
DESCRIÇÃO: Pergunta o código do cachorro para posteriormente fazer uma operação.
PARÂMETROS: AP2 - Arquivo Principal 2
RETORNO: Código do cachorro
*******************************************************************************/
int PerguntaCodigo(FILE **AP2);


/*******************************************************************************
DESCRIÇÃO: Realiza o cadastro de vacinas.
PARÂMETROS: AP1 - Arquivo principal 1
            AP2 - Arquivo principal 2
            BTidx - Arquivo de índice de Árvore B
            HASHidx - Arquivo de índice de Hash
*******************************************************************************/
void CadastraVacina(FILE **AP1, FILE **AP2, FILE **BTidx, FILE **HASHidx);


/*******************************************************************************
DESCRIÇÃO: Exibe o menu de opções das possíveis operações do programa.
RETORNO: Retorna a opção escolhida pelo usuário.
*******************************************************************************/
int Menu();


/*******************************************************************************
DESCRIÇÃO: Pergunta se o usuário quer deletar os arquivos do projeto. Se a
resposta for 's', os arquivos são deletados da memória; caso contrário, não.
*******************************************************************************/
void DeletarArquivos();


/*******************************************************************************
DESCRIÇÃO: Pergunta a chave a ser procurada (e exibidos seus dados).
RETORNO: Retorna a chave que o usuário quer que os dados sejam listados.
*******************************************************************************/
int PerguntaChave();


/*******************************************************************************
DESCRIÇÃO: Pergunta o método de busca e exibição dos dados de uma dada chave 
(por Hash ou Árvore B).
RETORNOS: 1 - Hash
          0 - Árvore B
*******************************************************************************/
int ListaDados();
