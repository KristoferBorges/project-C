#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <time.h>
#include <float.h>

// Defina macros para as cores
#define RESET_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"

// Função para imprimir linha centralizada com asteriscos
void imprimirLinhaCentralizada(const char *texto) {
    int larguraTotal = 60; 
    int tamanhoTexto = strlen(texto);
    int margemEsquerda = (larguraTotal - tamanhoTexto) / 2;

    printf("\n");
    for (int i = 0; i < larguraTotal; i++) {
        if (i == margemEsquerda) {
            printf("%s", texto);
            i += tamanhoTexto - 1;
        } else {
            printf("#");
        }
    }
    printf("\n");
    printf("\n");
}

void cifraCesar(char *texto, char chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] ^ chave; 
    }
}

void decifraCesar(char *texto, char chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] ^ chave; 
    }
}


// Estrutura para armazenar informações da indústria
struct Industria {
    char nome[50];
    char nomeFantasia[50];
    char cnpj[15];
    char email[50];
    char regiao[50];
    char telefone[15];
    char dataAbertura[15];
    char cpfResponsavel[50];
    float producao;
    float aporteFinanceiro;

    struct Endereco {
        char rua[50];
        char numero[10];
        char bairro[50];
        char cidade[50];
        char estado[50];
        char cep[15];
    } endereco;

    struct Relatorio{
        char data[15];
        char insumosTratadosM1[100];
        char totalGastoM1[100];
        char insumosTratadosM2[100];
        char totalGastoM2[100];
        char insumosTratadosM3[100];
        char totalGastoM3[100];
        char insumosTratadosM4[100];
        char totalGastoM4[100];
        char insumosTratadosM5[100];
        char totalGastoM5[100];
        char insumosTratadosM6[100];
        char totalGastoM6[100];
        char descricao[100];
    } relatorio;


} industria;

struct Funcionario {
    char nome[50];
    char cpf[15];
    char email[50];
    char telefone[15];
    char dataNascimento[15];
    char cargo[50];
    char setor[50];
    char dataAdmissao[15];
    char dataDemissao[15];
    char salario[15];
    char status[15];
} funcionario;

// Função para realizar o login
int realizarLogin() {
    char login[50];
    char senha[50];
    int sucessoLogin = 0;

    do {
        printf("\n");
        imprimirLinhaCentralizada(GREEN " SISTEMA DE GESTAO AMBIENTAL " RESET_COLOR);

        printf(GREEN "[?] - Usuario: " RESET_COLOR);
        scanf("%s", login);
        printf(GREEN "[?] - Senha: " RESET_COLOR);
        scanf("%s", senha);

        if (strcmp(login, "admin") == 0 && strcmp(senha, "1533") == 0) {
            printf("\n");
            printf(GREEN "[!] - Login realizado com sucesso!\n" RESET_COLOR);
            sucessoLogin = 1;
        } else {
            printf("\n");
            printf(RED "[!] - Login ou senha incorretos. Tente novamente.\n" RESET_COLOR);
        }
    } while (!sucessoLogin);

    return 1;
}

// Função para ler as informações da indústria a partir de um arquivo
void lerIndustrias(const char *nomeArquivo, struct Industria *industrias, int *numIndustrias) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(arquivo, "CNPJ: %s\nNome: %s\nRegiao: %s\nProducao: %f\nAporteFinanceiro: %f\n",
                  industrias[i].cnpj, industrias[i].nome, industrias[i].regiao,
                  &(industrias[i].producao), &(industrias[i].aporteFinanceiro)) == 5) {
        i++;
    }

    *numIndustrias = i;

    fclose(arquivo);
}

// Função para encontrar a indústria que tratou o maior volume de resíduos industriais
void encontrarMaiorProducao(struct Industria *industrias, int numIndustrias, FILE *saida) {
    float maxProducao = -FLT_MAX;
    int idxMaiorProducao = -1;

    for (int i = 0; i < numIndustrias; i++) {
        if (industrias[i].producao > maxProducao) {
            maxProducao = industrias[i].producao;
            idxMaiorProducao = i;
        }
    }

    if (idxMaiorProducao != -1) {
        fprintf(saida,"Industria com maior producao:\n");
        fprintf(saida, " Nome: %s\n Regiao: %s\n Producao: R$ %.2f\n Aporte Financeiro: R$ %.2f\n",
               industrias[idxMaiorProducao].nome, industrias[idxMaiorProducao].regiao,
               industrias[idxMaiorProducao].producao, industrias[idxMaiorProducao].aporteFinanceiro);
    } else {
        fprintf(saida,"[!] - Nenhuma industria encontrada.\n");
    }
}

// Função para encontrar a indústria que menos produziu
void encontrarMenorProducao(struct Industria *industrias, int numIndustrias, FILE *saida) {
    float minProducao = FLT_MAX;
    int idxMenorProducao = -1;

    for (int i = 0; i < numIndustrias; i++) {
        if (industrias[i].producao < minProducao) {
            minProducao = industrias[i].producao;
            idxMenorProducao = i;
        }
    }

    if (idxMenorProducao != -1) {
        fprintf(saida,"Industria com menor producao:\n");
        fprintf(saida, " Nome: %s\n Regiao: %s\n Producao: R$ %.2f\n Aporte Financeiro: R$ %.2f\n",
               industrias[idxMenorProducao].nome, industrias[idxMenorProducao].regiao,
               industrias[idxMenorProducao].producao, industrias[idxMenorProducao].aporteFinanceiro);
    } else {
        fprintf(saida,"[!] - Nenhuma industria encontrada.\n");
    }
}

// Função para calcular o aporte financeiro semestral
void calcularAporteFinanceiroSemestral(struct Industria *industrias, int numIndustrias, FILE *saida) {
    float totalAporteFinanceiro = 0.0;

    for (int i = 0; i < numIndustrias; i++) {
        totalAporteFinanceiro += industrias[i].aporteFinanceiro;
    }

    fprintf(saida,"Aporte financeiro semestral total: R$ %.2f\n", totalAporteFinanceiro);
    printf("\n");
}

// Função para cadastrar uma indústria
void cadastrarIndustria() {
    int chave = 3;
    char caminhoArquivoPasta[100];
    char caminhoArquivo[100];
    char caminhoArquivoPastaRelatorio[100];
    char caminhoArquivoRelatorio[100];
    char caminhoArquivoRelatorioBackup[100];

    imprimirLinhaCentralizada(GREEN " CADASTRO DE INDUSTRIA " RESET_COLOR);

    // Dados da empresa
    printf(GREEN "[?] - CNPJ: " RESET_COLOR);
    scanf("%s", industria.cnpj);

    printf(GREEN "[?] - Nome da Empresa: " RESET_COLOR);
    scanf("%s", industria.nome);
    
    printf(GREEN "[?] - Nome Fantasia: " RESET_COLOR);
    scanf("%s", industria.nomeFantasia);

    printf(GREEN "[?] - Data de Abertura: " RESET_COLOR);
    scanf("%s", industria.dataAbertura);

    printf(GREEN "[?] - Telefone: " RESET_COLOR);
    scanf("%s", industria.telefone);

    printf(GREEN "[?] - Email: " RESET_COLOR);
    scanf("%s", industria.email);

    printf(GREEN "[?] - Regiao: " RESET_COLOR);
    scanf("%s", industria.regiao);

    imprimirLinhaCentralizada(GREEN " ENDERECO DA EMPRESA " RESET_COLOR);

    // Dados da empresa (Endereço)
    printf(GREEN "[?] - Rua: " RESET_COLOR);
    scanf("%s", industria.endereco.rua);

    printf(GREEN "[?] - Numero: " RESET_COLOR);
    scanf("%s", industria.endereco.numero);

    printf(GREEN "[?] - Bairro: " RESET_COLOR);
    scanf("%s", industria.endereco.bairro);

    printf(GREEN "[?] - Cidade: " RESET_COLOR);
    scanf("%s", industria.endereco.cidade);

    printf(GREEN "[?] - Estado: " RESET_COLOR);
    scanf("%s", industria.endereco.estado);

    printf(GREEN "[?] - CEP: " RESET_COLOR);
    scanf("%s", industria.endereco.cep);

    printf("\n");
    imprimirLinhaCentralizada(GREEN " DADOS DO RESPONSAVEL " RESET_COLOR);

    // Dados do responsável
    printf(GREEN "[?] - CPF do Responsavel: " RESET_COLOR);
    scanf("%s", industria.cpfResponsavel);

    // Cria uma pasta para o Industria
    sprintf(caminhoArquivoPasta, "../data/industrias/industria_%s", industria.cnpj);
    sprintf(caminhoArquivoPastaRelatorio, "../data/industrias/industria_%s/relatorio", industria.cnpj);
    sprintf(caminhoArquivoRelatorioBackup, "../data/industrias/industria_%s/relatoriobackup", industria.cnpj);

    if (mkdir(caminhoArquivoPasta) == 0) {
        sprintf(caminhoArquivo, "../data/industrias/industria_%s/industria_%s.txt", industria.cnpj, industria.cnpj);

            if (mkdir(caminhoArquivoRelatorioBackup) == 0){
                if (mkdir(caminhoArquivoPastaRelatorio) == 0) {
                    sprintf(caminhoArquivoRelatorio, "../data/industrias/industria_%s/relatorio/relatorio_%s.txt", industria.cnpj, industria.cnpj);
                    printf(GREEN "[!] - Industria cadastrada com sucesso!\n" RESET_COLOR);

                } else {
                    printf(RED "[!] - Erro ao criar pasta para o relatorio.\n" RESET_COLOR);
                }
            }
        
    } else {
        printf(RED "[!] - Erro cadastrar Industria.\n" RESET_COLOR);
    }

    

    // Salvando os dados da empresa em um arquivo (A empresa)
    cifraCesar(industria.cnpj, chave);
    cifraCesar(industria.nome, chave);
    cifraCesar(industria.nomeFantasia, chave);
    cifraCesar(industria.email, chave);
    cifraCesar(industria.regiao, chave);
    cifraCesar(industria.telefone, chave);
    cifraCesar(industria.dataAbertura, chave);
    cifraCesar(industria.cpfResponsavel, chave);
    cifraCesar(industria.endereco.rua, chave);
    cifraCesar(industria.endereco.numero, chave);
    cifraCesar(industria.endereco.bairro, chave);
    cifraCesar(industria.endereco.cidade, chave);
    cifraCesar(industria.endereco.estado, chave);
    cifraCesar(industria.endereco.cep, chave);

    FILE *arquivo = fopen(caminhoArquivo, "a");
    fprintf(arquivo, "%s\n", industria.cnpj);
    fprintf(arquivo, "%s\n", industria.nome);
    fprintf(arquivo, "%s\n", industria.nomeFantasia);
    fprintf(arquivo, "%s\n", industria.email);
    fprintf(arquivo, "%s\n", industria.regiao);
    fprintf(arquivo, "%s\n", industria.telefone);
    fprintf(arquivo, "%s\n", industria.dataAbertura);
    fprintf(arquivo, "%s\n", industria.endereco.rua);
    fprintf(arquivo, "%s\n", industria.endereco.numero);
    fprintf(arquivo, "%s\n", industria.endereco.bairro);
    fprintf(arquivo, "%s\n", industria.endereco.cidade);
    fprintf(arquivo, "%s\n", industria.endereco.estado);
    fprintf(arquivo, "%s\n", industria.endereco.cep);
    fprintf(arquivo, "%s\n", industria.cpfResponsavel);
    fclose(arquivo);
    printf("\n");

    // Gerando primeiro relatório pelo sistema
    time_t t;
    struct tm *dataHoraAtual;

    time(&t);
    dataHoraAtual = localtime(&t);

    char dataAtual[11];
    strftime(dataAtual, sizeof(dataAtual), "%d-%m-%Y", dataHoraAtual);

    // Geração de informações para Insumos Tratados e Total Gasto Mensal
    srand((unsigned int)time(NULL));

    int mes1 = rand() % 10001; // Gera um número entre 0 e 10000
    int gastoM1 = rand() % 10001; // Gera um número entre 0 e 10000
    int mes2 = rand() % 10001; // Gera um número entre 0 e 10000
    int gastoM2 = rand() % 10001; // Gera um número entre 0 e 10000
    int mes3 = rand() % 10001; // Gera um número entre 0 e 10000
    int gastoM3 = rand() % 10001; // Gera um número entre 0 e 10000
    int mes4 = rand() % 10001; // Gera um número entre 0 e 10000
    int gastoM4 = rand() % 10001; // Gera um número entre 0 e 10000
    int mes5 = rand() % 10001; // Gera um número entre 0 e 10000
    int gastoM5 = rand() % 10001; // Gera um número entre 0 e 10000
    int mes6 = rand() % 10001; // Gera um número entre 0 e 10000
    int gastoM6 = rand() % 10001; // Gera um número entre 0 e 10000
    

    // Salvando os dados da empresa em um arquivo (Relatorio)
    FILE *arquivoRelatorio = fopen(caminhoArquivoRelatorio, "a");
    fprintf(arquivoRelatorio, "%s\n", dataAtual);
    fprintf(arquivoRelatorio, "%d\n", mes1);
    fprintf(arquivoRelatorio, "%d\n", gastoM1);
    fprintf(arquivoRelatorio, "%d\n", mes2);
    fprintf(arquivoRelatorio, "%d\n", gastoM2);
    fprintf(arquivoRelatorio, "%d\n", mes3);
    fprintf(arquivoRelatorio, "%d\n", gastoM3);
    fprintf(arquivoRelatorio, "%d\n", mes4);
    fprintf(arquivoRelatorio, "%d\n", gastoM4);
    fprintf(arquivoRelatorio, "%d\n", mes5);
    fprintf(arquivoRelatorio, "%d\n", gastoM5);
    fprintf(arquivoRelatorio, "%d\n", mes6);
    fprintf(arquivoRelatorio, "%d\n", gastoM6);
    fprintf(arquivoRelatorio, "%s\n", "Relatorio_gerado_pelo_sistema.");
    fclose(arquivoRelatorio);

    // Importando informações para o relatório global (formatação)
    double producaoTotal = (gastoM1 + gastoM2 + gastoM3 + gastoM4 + gastoM5 + gastoM6);
    double aporteFinanceiro = (mes1 + mes2 + mes3 + mes4 + mes5 + mes6);

    // Importando informações para o relatório global
    char caminhoArquivoGlobal[100];
    sprintf(caminhoArquivoGlobal, "../data/industrias/global/industrias_resumo.txt");

    FILE *arquivoGlobal = fopen(caminhoArquivoGlobal, "a");
    decifraCesar(industria.cnpj, chave);
    decifraCesar(industria.nome, chave);
    decifraCesar(industria.regiao, chave);
    fprintf(arquivoGlobal, "CNPJ: %s\n", industria.cnpj);
    fprintf(arquivoGlobal, "Nome: %s\n", industria.nome);
    fprintf(arquivoGlobal, "Regiao: %s\n", industria.regiao);
    fprintf(arquivoGlobal, "Producao: %.2f\n", producaoTotal);
    fprintf(arquivoGlobal, "AporteFinanceiro: %.2f\n", aporteFinanceiro);
    fclose(arquivoGlobal);

}

void realizarBackup(char caminhoArquivoRelatorioBackup[100], char caminhoRelatorio[100]){
    struct Industria relatorioIndustriaBackup;

    printf("\n");
    imprimirLinhaCentralizada(GREEN " SALVANDO RELATORIO " RESET_COLOR);

    // Pegando informações e armazenando temporariamente
    FILE *arquivoRelatorio = fopen(caminhoRelatorio, "r");
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.data);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.insumosTratadosM1);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.totalGastoM1);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.insumosTratadosM2);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.totalGastoM2);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.insumosTratadosM3);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.totalGastoM3);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.insumosTratadosM4);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.totalGastoM4);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.insumosTratadosM5);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.totalGastoM5);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.insumosTratadosM6);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.totalGastoM6);
    fscanf(arquivoRelatorio, "%s", relatorioIndustriaBackup.relatorio.descricao);

    // Fechando o arquivo
    fclose(arquivoRelatorio);

    // Formatação dos dados antes do Backup

    // Inserindo informações no arquivo de backup
    FILE *arquivoRelatorioBackup = fopen(caminhoArquivoRelatorioBackup, "a");
    fprintf(arquivoRelatorioBackup, "[%s]\n", relatorioIndustriaBackup.relatorio.data);
    fprintf(arquivoRelatorioBackup, "Mês 1: R$ %s\n", relatorioIndustriaBackup.relatorio.insumosTratadosM1);
    fprintf(arquivoRelatorioBackup, "Valor Gasto: R$ %s\n", relatorioIndustriaBackup.relatorio.totalGastoM1);
    fprintf(arquivoRelatorioBackup, "Mês 2: R$ %s\n", relatorioIndustriaBackup.relatorio.insumosTratadosM2);
    fprintf(arquivoRelatorioBackup, "Valor Gasto: R$ %s\n", relatorioIndustriaBackup.relatorio.totalGastoM2);
    fprintf(arquivoRelatorioBackup, "Mês 3: R$ %s\n", relatorioIndustriaBackup.relatorio.insumosTratadosM3);
    fprintf(arquivoRelatorioBackup, "Valor Gasto: R$ %s\n", relatorioIndustriaBackup.relatorio.totalGastoM3);
    fprintf(arquivoRelatorioBackup, "Mês 4: R$ %s\n", relatorioIndustriaBackup.relatorio.insumosTratadosM4);
    fprintf(arquivoRelatorioBackup, "Valor Gasto: R$ %s\n", relatorioIndustriaBackup.relatorio.totalGastoM4);
    fprintf(arquivoRelatorioBackup, "Mês 5: R$ %s\n", relatorioIndustriaBackup.relatorio.insumosTratadosM5);
    fprintf(arquivoRelatorioBackup, "Valor Gasto: R$ %s\n", relatorioIndustriaBackup.relatorio.totalGastoM5);
    fprintf(arquivoRelatorioBackup, "Mês 6: R$ %s\n", relatorioIndustriaBackup.relatorio.insumosTratadosM6);
    fprintf(arquivoRelatorioBackup, "Valor Gasto: R$ %s\n", relatorioIndustriaBackup.relatorio.totalGastoM6);
    fprintf(arquivoRelatorioBackup, "Descricao: %s\n", relatorioIndustriaBackup.relatorio.descricao);

    // Fechando o arquivo
    fclose(arquivoRelatorioBackup);

    // Mensagem de finalização
    printf(GREEN "[!] - Relatorio salvo com sucesso!\n" RESET_COLOR);
    printf("\n");

    return;
}

void alterarInformacoes(const char *cnpjAlvo, const double novoValorProducao, const double novoValorAporte) {
    FILE *arquivoEntrada, *arquivoSaida;
    char linha[1000];
    char arquivoEntradaNome[100] = "../data/industrias/global/industrias_resumo.txt";
    char arquivoSaidaNome[100] = "temp.txt"; // Nome temporário para o arquivo de saída

    arquivoEntrada = fopen(arquivoEntradaNome, "r");
    arquivoSaida = fopen(arquivoSaidaNome, "w");

    if (arquivoEntrada == NULL) {
        printf(RED "[!] - Erro ao abrir o arquivo de entrada\n" RESET_COLOR);
        return;
    }

    if (arquivoSaida == NULL) {
        printf(RED "[!] - Erro ao criar o arquivo de saída\n" RESET_COLOR);
        fclose(arquivoEntrada);
        return;
    }

    int cnpjEncontrado = 0; // Flag para indicar se o CNPJ alvo foi encontrado
    int ignorarLinhas = 0; // Flag para indicar se as próximas linhas devem ser ignoradas

    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        // Se as próximas linhas devem ser ignoradas, pula para a próxima iteração
        if (ignorarLinhas) {
            ignorarLinhas = 0;
            continue;
        }

        // Procura por CNPJ no formato desejado
        if (strstr(linha, "CNPJ: ") == linha) {
            char cnpj[20];
            sscanf(linha, "CNPJ: %s", cnpj);

            if (strcmp(cnpj, cnpjAlvo) == 0) {
                // Encontrou o CNPJ desejado, faz as alterações nas linhas seguintes
                fprintf(arquivoSaida, "CNPJ: %s\n", cnpj);

                fgets(linha, sizeof(linha), arquivoEntrada); // Pula a linha "Nome: ..."
                fprintf(arquivoSaida, "%s", linha);

                fgets(linha, sizeof(linha), arquivoEntrada); // Pula a linha "Regiao: ..."
                fprintf(arquivoSaida, "%s", linha);

                // Altera a linha "Producao: ..."
                fprintf(arquivoSaida, "Producao: %.2f\n", novoValorProducao);

                // Altera a linha "AporteFinanceiro: ..."
                fgets(linha, sizeof(linha), arquivoEntrada); // Pula a linha original
                fprintf(arquivoSaida, "AporteFinanceiro: %.2f\n", novoValorAporte);

                cnpjEncontrado = 1; // Indica que o CNPJ alvo foi encontrado

                // Marca as próximas 2 linhas para serem ignoradas
                ignorarLinhas = 1;
            } else {
                // Se não é o CNPJ alvo, apenas copia a linha para o arquivo de saída
                fputs(linha, arquivoSaida);
            }
        } else {
            // Se a linha não começa com "CNPJ: ", apenas copia para o arquivo de saída
            fputs(linha, arquivoSaida);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    // Se o CNPJ alvo não foi encontrado, remove o arquivo de saída
    if (!cnpjEncontrado) {
        remove(arquivoSaidaNome);
    } else {
        // Renomeia o arquivo temporário para o nome original
        remove(arquivoEntradaNome);
        rename(arquivoSaidaNome, arquivoEntradaNome);
    }
}


void atualizarRelatorio(char procurarCNPJ[20], char caminhoArquivoRelatorio[100], char dataFormatada[15]){
    printf("\n");
    imprimirLinhaCentralizada(GREEN " ATUALIZAR RELATORIO " RESET_COLOR);
    printf("\n");

    // Criando uma instância da estrutura para armazenar os dados
    struct Industria relatorioIndustria;

    // Verificando a existência do arquivo
    FILE *arquivoRelatorio = fopen(caminhoArquivoRelatorio, "r");
    if (arquivoRelatorio == NULL) {
        printf(RED "[!] - Relatorio nao foi encontrado.\n" RESET_COLOR);
        return;
    }

    // Solicitando dados para alteração (relatorio principal)
    printf(RED "[!] - Caso nao queira alterar o dado, digite o mesmo.\n" RESET_COLOR);
    printf(RED "[!] - Certifique-se de gerar um backup da opcao de Exportar relatorio\n" RESET_COLOR);
    printf(GREEN "[!] - Informe dos dados para atualizacao do relatorio.\n" RESET_COLOR);

    printf(GREEN "[?] - Insumos Tratados 1 Mes: " RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.insumosTratadosM1);
    printf(GREEN "[?] - Total Gasto Mensal: " RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.totalGastoM1);
    printf("\n");
    printf(GREEN"[?] - Insumos Tratados 2 Mes: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.insumosTratadosM2);
    printf(GREEN "[?] - Total Gasto Mensal: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.totalGastoM2);
    printf("\n");
    printf(GREEN "[?] - Insumos Tratados 3 Mes: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.insumosTratadosM3);
    printf(GREEN "[?] - Total Gasto Mensal: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.totalGastoM3);
    printf("\n");
    printf(GREEN "[?] - Insumos Tratados 4 Mes: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.insumosTratadosM4);
    printf(GREEN "[?] - Total Gasto Mensal: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.totalGastoM4);
    printf("\n");
    printf(GREEN "[?] - Insumos Tratados 5 Mes: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.insumosTratadosM5);
    printf(GREEN "[?] - Total Gasto Mensal: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.totalGastoM5);
    printf("\n");
    printf(GREEN "[?] - Insumos Tratados 6 Mes: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.insumosTratadosM6);
    printf(GREEN "[?] - Total Gasto Mensal: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.totalGastoM6);
    printf("\n");
    printf(GREEN "[?] - Descricao: "RESET_COLOR);
    scanf("%s", relatorioIndustria.relatorio.descricao);
    printf("\n");

    // Somar os valores obtidos
    double procucaoTotal = atof(relatorioIndustria.relatorio.insumosTratadosM1) + atof(relatorioIndustria.relatorio.insumosTratadosM2) + atof(relatorioIndustria.relatorio.insumosTratadosM3) + atof(relatorioIndustria.relatorio.insumosTratadosM4) + atof(relatorioIndustria.relatorio.insumosTratadosM5) + atof(relatorioIndustria.relatorio.insumosTratadosM6);
    double gastoTotal = atof(relatorioIndustria.relatorio.totalGastoM1) + atof(relatorioIndustria.relatorio.totalGastoM2) + atof(relatorioIndustria.relatorio.totalGastoM3) + atof(relatorioIndustria.relatorio.totalGastoM4) + atof(relatorioIndustria.relatorio.totalGastoM5) + atof(relatorioIndustria.relatorio.totalGastoM6);

    // Salvando os dados no arquivo (relatorio principal)
    FILE *arquivoRelatorioAtualizado = fopen(caminhoArquivoRelatorio, "w");
    fprintf(arquivoRelatorioAtualizado, "%s\n", dataFormatada);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.insumosTratadosM1);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.totalGastoM1);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.insumosTratadosM2);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.totalGastoM2);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.insumosTratadosM3);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.totalGastoM3);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.insumosTratadosM4);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.totalGastoM4);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.insumosTratadosM5);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.totalGastoM5);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.insumosTratadosM6);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.totalGastoM6);
    fprintf(arquivoRelatorioAtualizado, "%s\n", relatorioIndustria.relatorio.descricao);
    fclose(arquivoRelatorioAtualizado);

    // Passando como parâmetro as informações para alteração (relatorio global)
    alterarInformacoes(procurarCNPJ, procucaoTotal, gastoTotal);

}

// Função para gerar relatórios
void gerarRelatorio() {
    int opcao;
    char procurarCNPJ[20];
    char caminhoPastaRelatorio[100];
    char caminhoArquivoRelatorio[100];
    char caminhoArquivoRelatorioBackup[100];

    // Pegando a data e hora atuais
    time_t t;
    struct tm *dataHoraAtual;

    time(&t);
    dataHoraAtual = localtime(&t);
    char dataFormatada[20];
    strftime(dataFormatada, sizeof(dataFormatada), "%d-%m-%Y %H-%M-%S", dataHoraAtual);


    // Criando uma instância da estrutura para armazenar os dados
    struct Industria relatorioIndustria;

    imprimirLinhaCentralizada(GREEN " GERAR RELATORIO " RESET_COLOR);
    printf("\n");
    printf(GREEN "[?] - Qual o CNPJ da empresa: " RESET_COLOR);
    scanf("%s", procurarCNPJ);
    sprintf(caminhoPastaRelatorio, "../data/industrias/industria_%s", procurarCNPJ);
    sprintf(caminhoArquivoRelatorio, "../data/industrias/industria_%s/relatorio/relatorio_%s.txt", procurarCNPJ, procurarCNPJ);
    sprintf(caminhoArquivoRelatorioBackup, "../data/industrias/industria_%s/relatoriobackup/relatorio_semestre_%s.txt", procurarCNPJ, dataFormatada);

    FILE *arquivoRelatorio = fopen(caminhoArquivoRelatorio, "r");
    if (arquivoRelatorio == NULL) {
        // O arquivo não foi encontrado
        printf(RED "[!] - Relatorio para o CNPJ [%s] nao foi encontrado.\n" RESET_COLOR, procurarCNPJ);
        return;
    } else {
        // O arquivo foi encontrado
        printf(GREEN "[!] - Arquivo encontrado.\n" RESET_COLOR);
        printf("\n");
    }

    // Lendo os dados do arquivo e armazenando temporariamente
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.data);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.insumosTratadosM1);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.totalGastoM1);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.insumosTratadosM2);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.totalGastoM2);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.insumosTratadosM3);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.totalGastoM3);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.insumosTratadosM4);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.totalGastoM4);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.insumosTratadosM5);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.totalGastoM5);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.insumosTratadosM6);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.totalGastoM6);
    fscanf(arquivoRelatorio, "%s", relatorioIndustria.relatorio.descricao);

    // Imprimindo os dados
    printf("Data: %s\n", relatorioIndustria.relatorio.data);
    printf("Insumos Tratados 1 Mes: R$ %s\n", relatorioIndustria.relatorio.insumosTratadosM1);
    printf("Total Gasto Mensal: R$ %s\n\n", relatorioIndustria.relatorio.totalGastoM1);
    printf("Insumos Tratados 2 Mes: R$ %s\n", relatorioIndustria.relatorio.insumosTratadosM2);
    printf("Total Gasto Mensal: R$ %s\n\n", relatorioIndustria.relatorio.totalGastoM2);
    printf("Insumos Tratados 3 Mes: R$ %s\n", relatorioIndustria.relatorio.insumosTratadosM3);
    printf("Total Gasto Mensal: R$ %s\n\n", relatorioIndustria.relatorio.totalGastoM3);
    printf("Insumos Tratados 4 Mes: R$ %s\n", relatorioIndustria.relatorio.insumosTratadosM4);
    printf("Total Gasto Mensal: R$ %s\n\n", relatorioIndustria.relatorio.totalGastoM4);
    printf("Insumos Tratados 5 Mes: R$ %s\n", relatorioIndustria.relatorio.insumosTratadosM5);
    printf("Total Gasto Mensal: R$ %s\n\n", relatorioIndustria.relatorio.totalGastoM5);
    printf("Insumos Tratados 6 Mes: R$ %s\n", relatorioIndustria.relatorio.insumosTratadosM6);
    printf("Total Gasto Mensal: R$ %s\n\n", relatorioIndustria.relatorio.totalGastoM6);
    printf("Descricao: %s\n", relatorioIndustria.relatorio.descricao);
    printf("\n");

    // Fechando o arquivo
    fclose(arquivoRelatorio);

    // Menu de opções
    while(1){
        imprimirLinhaCentralizada(GREEN " MENU DE OPCOES EMPRESA " RESET_COLOR);
        printf(RED "(1) - " GREEN "Criar novo relatorio\n" RESET_COLOR);
        printf(RED "(2) - " GREEN "Exportar relatorio em TxT\n" RESET_COLOR);
        printf(RED "(3) - " GREEN "Voltar\n" RESET_COLOR);
        printf("\n");
        printf(GREEN "[?] - Escolha uma opcao: " RESET_COLOR);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atualizarRelatorio(procurarCNPJ, caminhoArquivoRelatorio, dataFormatada);
                break;
            case 2:
                realizarBackup(caminhoArquivoRelatorioBackup, caminhoArquivoRelatorio);
                break;
            case 3:
                return;
            default:
                printf(RED "[!] - Opcao invalida.\n" RESET_COLOR);
                break;
        }
    }
}

void cadastrarFuncionario() {
    char caminhoArquivoPasta[100];
    char caminhoArquivo[100];
    int chave = 3;

    imprimirLinhaCentralizada(GREEN " CADASTRO DE FUNCIONARIO " RESET_COLOR);

    // Dados do funcionario
    printf(GREEN "[?] - Nome: " RESET_COLOR);
    scanf("%s", funcionario.nome);

    printf(GREEN "[?] - CPF: " RESET_COLOR);
    scanf("%s", funcionario.cpf);

    printf(GREEN "[?] - Data de Nascimento: " RESET_COLOR);
    scanf("%s", funcionario.dataNascimento);

    printf(GREEN "[?] - Telefone: " RESET_COLOR);
    scanf("%s", funcionario.telefone);

    printf(GREEN "[?] - Email: " RESET_COLOR);
    scanf("%s", funcionario.email);

    printf(GREEN "[?] - Cargo: " RESET_COLOR);
    scanf("%s", funcionario.cargo);

    printf(GREEN "[?] - Data de Admissao: " RESET_COLOR);
    scanf("%s", funcionario.dataAdmissao);

    printf(GREEN "[?] - Data de Demissao: " RESET_COLOR);
    scanf("%s", funcionario.dataDemissao);

    printf(GREEN "[?] - Salario: " RESET_COLOR);
    scanf("%s", funcionario.salario);

    printf(GREEN "[?] - Status: " RESET_COLOR);
    scanf("%s", funcionario.status);

    // Cria uma pasta para o funcionário
    sprintf(caminhoArquivoPasta, "../data/funcionarios/funcionario_%s", funcionario.cpf);

    if (mkdir(caminhoArquivoPasta) == 0) {
        sprintf(caminhoArquivo, "../data/funcionarios/funcionario_%s/funcionario_%s.txt", funcionario.cpf, funcionario.cpf);
        printf(GREEN "[!] - Funcionario cadastrado com sucesso!\n" RESET_COLOR);
    } else {
        printf(RED "[!] - Erro ao cadastrar Funcionario.\n" RESET_COLOR);
    }

    // Cripitografando os dados do funcionario
    cifraCesar(funcionario.nome, chave);
    cifraCesar(funcionario.cpf, chave);
    cifraCesar(funcionario.dataNascimento, chave);
    cifraCesar(funcionario.telefone, chave);
    cifraCesar(funcionario.email, chave);
    cifraCesar(funcionario.cargo, chave);
    cifraCesar(funcionario.dataAdmissao, chave);
    cifraCesar(funcionario.dataDemissao, chave);
    cifraCesar(funcionario.salario, chave);
    cifraCesar(funcionario.status, chave);
    
    // Salvando os dados do funcionario em um arquivo (A empresa)
    FILE *arquivo = fopen(caminhoArquivo, "a");
    fprintf(arquivo, "%s\n", funcionario.nome);
    fprintf(arquivo, "%s\n", funcionario.cpf);
    fprintf(arquivo, "%s\n", funcionario.dataNascimento);
    fprintf(arquivo, "%s\n", funcionario.telefone);
    fprintf(arquivo, "%s\n", funcionario.email);
    fprintf(arquivo, "%s\n", funcionario.cargo);
    fprintf(arquivo, "%s\n", funcionario.dataAdmissao);
    fprintf(arquivo, "%s\n", funcionario.dataDemissao);
    fprintf(arquivo, "%s\n", funcionario.salario);
    fprintf(arquivo, "%s\n", funcionario.status);
    fclose(arquivo);
    printf("\n");
}

void consultarFuncionario(){
    char procurarNome[50];
    char nomeArquivo[100];
    int chave = 3;
    
    imprimirLinhaCentralizada(GREEN " CONSULTA DE FUNCIONARIO " RESET_COLOR);

    printf(GREEN "[?] - CPF do Funcionario: " RESET_COLOR);
    scanf("%s", procurarNome);

    // Construindo o nome do arquivo com base no nome
    sprintf(nomeArquivo, "../data/funcionarios/funcionario_%s/funcionario_%s.txt", procurarNome, procurarNome);

    // Abrindo o arquivo para leitura
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("\n");
        printf(RED "[!] - Erro ao abrir o arquivo ou o funcionario nao foi encontrado.\n" RESET_COLOR);
        return;
    }

    // Criando uma instância da estrutura para armazenar os dados
    struct Funcionario meuFuncionario;

    // Lendo os dados do arquivo e armazenando temporariamente
    while (fscanf(arquivo, "%s", meuFuncionario.nome) != EOF) {
        decifraCesar(meuFuncionario.nome, chave);

        fscanf(arquivo, "%s", meuFuncionario.cpf);
        decifraCesar(meuFuncionario.cpf, chave);

        fscanf(arquivo, "%s", meuFuncionario.dataNascimento);
        decifraCesar(meuFuncionario.dataNascimento, chave);

        fscanf(arquivo, "%s", meuFuncionario.telefone);
        decifraCesar(meuFuncionario.telefone, chave);

        fscanf(arquivo, "%s", meuFuncionario.email);
        decifraCesar(meuFuncionario.email, chave);

        fscanf(arquivo, "%s", meuFuncionario.cargo);
        decifraCesar(meuFuncionario.cargo, chave);

        fscanf(arquivo, "%s", meuFuncionario.dataAdmissao);
        decifraCesar(meuFuncionario.dataAdmissao, chave);

        fscanf(arquivo, "%s", meuFuncionario.dataDemissao);
        decifraCesar(meuFuncionario.dataDemissao, chave);

        fscanf(arquivo, "%s", meuFuncionario.salario);
        decifraCesar(meuFuncionario.salario, chave);

        fscanf(arquivo, "%s", meuFuncionario.status);   
        decifraCesar(meuFuncionario.status, chave);
}

        // Imprimindo os dados
        printf("\n");
        printf(BLUE "Nome: " RESET_COLOR "%s\n", meuFuncionario.nome);
        printf(BLUE "CPF: " RESET_COLOR "%s\n", meuFuncionario.cpf);
        printf(BLUE "Data de Nascimento: " RESET_COLOR "%s\n", meuFuncionario.dataNascimento);
        printf(BLUE "Telefone: " RESET_COLOR "%s\n", meuFuncionario.telefone);
        printf(BLUE "Email: " RESET_COLOR "%s\n", meuFuncionario.email);
        printf(BLUE "Cargo: " RESET_COLOR "%s\n", meuFuncionario.cargo);
        printf(BLUE "Data de Admissao: " RESET_COLOR "%s\n", meuFuncionario.dataAdmissao);
        printf(BLUE "Data de Demissao: " RESET_COLOR "%s\n", meuFuncionario.dataDemissao);
        printf(BLUE "Salario: " RESET_COLOR "%s\n", meuFuncionario.salario);
        printf(BLUE "Status: " RESET_COLOR "%s\n", meuFuncionario.status);

        printf("\n");
    
    // Fechando o arquivo
    fclose(arquivo);
    
};

void consultarIndustria() {
    char procurarCNPJ[15];
    char nomeArquivo[100];
    char nomeArquivoRelatorio[100];
    int chave = 3;
    
    imprimirLinhaCentralizada(GREEN " CONSULTA DE EMPRESA " RESET_COLOR);

    printf(GREEN "[?] - CNPJ da Empresa: " RESET_COLOR);
    scanf("%s", procurarCNPJ);

    // Construindo o nome do arquivo com base no CNPJ
    sprintf(nomeArquivo, "../data/industrias/industria_%s/industria_%s.txt", procurarCNPJ, procurarCNPJ);
    sprintf(nomeArquivoRelatorio, "../data/industrias/industria_%s/relatorio/relatorio_%s.txt", procurarCNPJ, procurarCNPJ);
    // Abrindo o arquivo para leitura
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("\n");
        printf(RED "[!] - Erro ao abrir o arquivo ou a empresa nao foi encontrada.\n" RESET_COLOR);
        return;
    }

    // Abrindo o arquivo para leitura
    FILE *arquivoRelatorio = fopen(nomeArquivoRelatorio, "r");

    if (arquivoRelatorio == NULL) {
        printf("\n");
        printf(RED "[!] - Erro ao abrir o arquivo ou a empresa nao foi encontrada.\n" RESET_COLOR);
        return;
    }

    // Criando uma instância da estrutura para armazenar os dados
    struct Industria minhaIndustria;

    // Lendo os dados do arquivo e armazenando temporariamente
    while (fscanf(arquivo, "%s", minhaIndustria.cnpj) != EOF) {
        decifraCesar(minhaIndustria.cnpj, chave);

        fscanf(arquivo, "%s", minhaIndustria.nome);
        decifraCesar(minhaIndustria.nome, chave);

        fscanf(arquivo, "%s", minhaIndustria.nomeFantasia);
        decifraCesar(minhaIndustria.nomeFantasia, chave);

        fscanf(arquivo, "%s", minhaIndustria.email);
        decifraCesar(minhaIndustria.email, chave);

        fscanf(arquivo, "%s", minhaIndustria.regiao);
        decifraCesar(minhaIndustria.regiao, chave);

        fscanf(arquivo, "%s", minhaIndustria.telefone);
        decifraCesar(minhaIndustria.telefone, chave);

        fscanf(arquivo, "%s", minhaIndustria.dataAbertura);
        decifraCesar(minhaIndustria.dataAbertura, chave);

        fscanf(arquivo, "%s", minhaIndustria.endereco.rua);
        decifraCesar(minhaIndustria.endereco.rua, chave);

        fscanf(arquivo, "%s", minhaIndustria.endereco.numero);
        decifraCesar(minhaIndustria.endereco.numero, chave);

        fscanf(arquivo, "%s", minhaIndustria.endereco.bairro);
        decifraCesar(minhaIndustria.endereco.bairro, chave);

        fscanf(arquivo, "%s", minhaIndustria.endereco.cidade);
        decifraCesar(minhaIndustria.endereco.cidade, chave);

        fscanf(arquivo, "%s", minhaIndustria.endereco.estado);
        decifraCesar(minhaIndustria.endereco.estado, chave);

        fscanf(arquivo, "%s", minhaIndustria.endereco.cep);
        decifraCesar(minhaIndustria.endereco.cep, chave);

        fscanf(arquivo, "%s", minhaIndustria.cpfResponsavel);
        decifraCesar(minhaIndustria.cpfResponsavel, chave);

        // Imprimindo os dados
        printf("\n");
        printf(BLUE "CNPJ: " RESET_COLOR "%s\n", minhaIndustria.cnpj);
        printf(BLUE "Nome: " RESET_COLOR "%s\n", minhaIndustria.nome);
        printf(BLUE "Nome Fantasia: " RESET_COLOR "%s\n", minhaIndustria.nomeFantasia);
        printf(BLUE "Email: " RESET_COLOR "%s\n", minhaIndustria.email);
        printf(BLUE "Regiao: " RESET_COLOR "%s\n", minhaIndustria.regiao);
        printf(BLUE "Telefone: " RESET_COLOR "%s\n", minhaIndustria.telefone);
        printf(BLUE "Data de Abertura: " RESET_COLOR "%s\n", minhaIndustria.dataAbertura);
        printf(BLUE "Rua: " RESET_COLOR "%s\n", minhaIndustria.endereco.rua);
        printf(BLUE "Numero: " RESET_COLOR "%s\n", minhaIndustria.endereco.numero);
        printf(BLUE "Bairro: " RESET_COLOR "%s\n", minhaIndustria.endereco.bairro);
        printf(BLUE "Cidade: " RESET_COLOR "%s\n", minhaIndustria.endereco.cidade);
        printf(BLUE "Estado: " RESET_COLOR "%s\n", minhaIndustria.endereco.estado);
        printf(BLUE "CEP: " RESET_COLOR "%s\n", minhaIndustria.endereco.cep);
        printf(BLUE "CPF do Responsavel: " RESET_COLOR "%s\n", minhaIndustria.cpfResponsavel);

        printf("\n");
        imprimirLinhaCentralizada(GREEN " RELATORIO ATUAL " RESET_COLOR);
        printf("\n");
    }

    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.data);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.insumosTratadosM1);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.totalGastoM1);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.insumosTratadosM2);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.totalGastoM2);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.insumosTratadosM3);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.totalGastoM3);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.insumosTratadosM4);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.totalGastoM4);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.insumosTratadosM5);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.totalGastoM5);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.insumosTratadosM6);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.totalGastoM6);
    fscanf(arquivoRelatorio, "%s", minhaIndustria.relatorio.descricao);

    // Imprimindo os dados
    printf(BLUE "Data: %s\n", minhaIndustria.relatorio.data);
    printf(BLUE "Insumos Tratados 1 Mes: " RESET_COLOR "R$ %s\n", minhaIndustria.relatorio.insumosTratadosM1);
    printf(BLUE "Total Gasto Mensal: " RESET_COLOR "R$ %s\n\n", minhaIndustria.relatorio.totalGastoM1);
    printf(BLUE "Insumos Tratados 2 Mes: " RESET_COLOR "R$ %s\n", minhaIndustria.relatorio.insumosTratadosM2);
    printf(BLUE "Total Gasto Mensal: " RESET_COLOR "R$ %s\n\n", minhaIndustria.relatorio.totalGastoM2);
    printf(BLUE "Insumos Tratados 3 Mes: " RESET_COLOR "R$ %s\n", minhaIndustria.relatorio.insumosTratadosM3);
    printf(BLUE "Total Gasto Mensal: " RESET_COLOR "R$ %s\n\n", minhaIndustria.relatorio.totalGastoM3);
    printf(BLUE "Insumos Tratados 4 Mes: " RESET_COLOR "R$ %s\n", minhaIndustria.relatorio.insumosTratadosM4);
    printf(BLUE "Total Gasto Mensal: " RESET_COLOR "R$ %s\n\n", minhaIndustria.relatorio.totalGastoM4);
    printf(BLUE "Insumos Tratados 5 Mes: " RESET_COLOR "R$ %s\n", minhaIndustria.relatorio.insumosTratadosM5);
    printf(BLUE "Total Gasto Mensal: " RESET_COLOR "R$ %s\n\n", minhaIndustria.relatorio.totalGastoM5);
    printf(BLUE "Insumos Tratados 6 Mes: " RESET_COLOR "R$ %s\n", minhaIndustria.relatorio.insumosTratadosM6);
    printf(BLUE "Total Gasto Mensal: " RESET_COLOR "R$ %s\n\n", minhaIndustria.relatorio.totalGastoM6);
    
    printf(BLUE "Descricao: " RESET_COLOR "%s\n", minhaIndustria.relatorio.descricao);
    
    // Fechando o arquivo
    fclose(arquivo);
    fclose(arquivoRelatorio);
};

void gerarRelatorioGlobal(){
    // Pega a data atual
    time_t t;
    struct tm *dataHoraAtual;

    time(&t);
    dataHoraAtual = localtime(&t);
    char dataFormatada[20];
    strftime(dataFormatada, sizeof(dataFormatada), "%Y/%m/%d", dataHoraAtual);

    const char *nomeArquivo = "../data/industrias/global/industrias_resumo.txt";
    char nomeArquivoSaida[50];
    sprintf(nomeArquivoSaida, "../data/industrias/global/resultados/relatorio_global.txt");

    struct Industria industrias[100];
    int numIndustrias = 0;

    FILE *saida = fopen(nomeArquivoSaida, "w");
    if (saida == NULL) {
        printf(RED "[!] - Erro ao criar o arquivo de saida.\n" RESET_COLOR);
        exit(EXIT_FAILURE);
    } else {
        printf(GREEN "[!] - Relatorio global criado com sucesso.\n" RESET_COLOR);
        printf(GREEN "[!] - Arquivo armazenado para Consulta!\n" RESET_COLOR);
    }

    lerIndustrias(nomeArquivo, industrias, &numIndustrias);

    encontrarMaiorProducao(industrias, numIndustrias, saida);
    encontrarMenorProducao(industrias, numIndustrias, saida);
    calcularAporteFinanceiroSemestral(industrias, numIndustrias, saida);

    fclose(saida);

    // Impressão dos resultados
    printf("\n");
    imprimirLinhaCentralizada(GREEN " RESULTADO " RESET_COLOR);
    printf("\n");
    FILE *arquivoSaida = fopen(nomeArquivoSaida, "r");
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivoSaida)) {
        printf("%s", linha);
    }
    return;
}

int main() {
    if (realizarLogin()) {
        int opcao;
        while (1) {
            imprimirLinhaCentralizada(GREEN " MENU PRINCIPAL " RESET_COLOR);
            printf("\n");
            printf(RED "(1) - " GREEN "Cadastrar Industria\n" RESET_COLOR);
            printf(RED "(2) - " GREEN "Cadastrar Funcionario\n" RESET_COLOR);
            printf(RED "(3) - " GREEN "Consultar Industria\n" RESET_COLOR);
            printf(RED "(4) - " GREEN "Consultar Funcionario\n" RESET_COLOR);
            printf(RED "(5) - " GREEN "Atualizar Relatorio " RED "(Industria)\n" RESET_COLOR);
            printf(RED "(6) - " GREEN "Gerar Relatorio Global " RED "(Dados estatisticos)\n" RESET_COLOR);
            printf(RED "(7) - " GREEN "Sair\n" RESET_COLOR);
            printf(GREEN "[?] - Escolha uma opcao: " RESET_COLOR);
            scanf("%d", &opcao);
            printf("\n");

            switch (opcao) {
                case 1:
                    cadastrarIndustria();
                    break;
                case 2:
                    cadastrarFuncionario();
                    break;
                case 3:
                    consultarIndustria();
                    break;
                case 4:
                    consultarFuncionario();
                    break;
                case 5:
                    gerarRelatorio();
                    break;
                case 6:
                    gerarRelatorioGlobal();
                    break;
                case 7:
                    printf(RED "[!] - SISTEMA ENCERRADO!\n" RESET_COLOR);
                    return 0;
                default:
                    printf(RED "[!] - Opcao invalida. Tente novamente.\n" RESET_COLOR);
            }
        }
    } else {
        printf(RED "[!] - Login falhou. Encerrando o sistema.\n" RESET_COLOR);
    }

    return 0;
}
