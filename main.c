#include <stdio.h>
#include <string.h>

// Defina macros para as cores
#define RESET_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
char login[50];
char senha[50];

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
        texto[i] = texto[i] ^ chave; // Operação XOR para criptografia
    }
}

void decifraCesar(char *texto, char chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] ^ chave; // Operação XOR para descriptografia
    }
}


// Estrutura para armazenar informações da indústria
struct Industria {
    char nome[50];
    char nomeFantasia[50];
    char cnpj[15];
    char email[50];
    char telefone[15];
    char dataAbertura[15];
    char cpfResponsavel[50];

    struct Endereco {
        char rua[50];
        char numero[10];
        char bairro[50];
        char cidade[50];
        char estado[50];
        char cep[15];
    } endereco;

    // Outros campos de informações da indústria
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
    printf("\n");
    imprimirLinhaCentralizada(GREEN " SISTEMA DE GESTAO AMBIENTAL " RESET_COLOR);

    printf(GREEN "[?] - Usuario: " RESET_COLOR);
    scanf("%s", login);
    printf(GREEN "[?] - Senha: " RESET_COLOR);
    scanf("%s", senha);

    if (strcmp(login, "admin") == 0 && strcmp(senha, "1533") == 0) {
        printf("\n");
        printf(GREEN "[!] - Login realizado com sucesso!\n" RESET_COLOR);
        return 1;
    } else {
        printf("\n");
        printf(RED "[!] - Login ou senha incorretos. Tente novamente.\n" RESET_COLOR);
        return 0;
    }
}

// Função para cadastrar uma indústria
void cadastrarIndustria() {
    int chave = 3;
    char caminhoArquivo[100];

    imprimirLinhaCentralizada(GREEN " CADASTRO DE INDUSTRIA " RESET_COLOR);

    // Dados da empresa
    printf(GREEN "[?] - CNPJ: " RESET_COLOR);
    scanf("%s", industria.cnpj);
    sprintf(caminhoArquivo, "../data/industrias/industria_%s.txt", industria.cnpj);

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

    // Salvando os dados da empresa em um arquivo (A empresa)
    cifraCesar(industria.cnpj, chave);
    cifraCesar(industria.nome, chave);
    cifraCesar(industria.nomeFantasia, chave);
    cifraCesar(industria.email, chave);
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
    printf(GREEN "[!] - Industria cadastrada com sucesso!\n" RESET_COLOR);
}

// Função para gerar relatórios
void gerarRelatorio() {
    // Gerar relatórios (implementação necessária)
}

void cadastrarFuncionario() {
    char caminhoArquivo[100];
    int chave = 3;

    imprimirLinhaCentralizada(GREEN " CADASTRO DE FUNCIONARIO " RESET_COLOR);

    // Dados do funcionario
    printf(GREEN "[?] - Nome: " RESET_COLOR);
    scanf("%s", funcionario.nome);
    sprintf(caminhoArquivo, "../data/funcionarios/funcionario_%s.txt", funcionario.nome);

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

    printf(GREEN "[!] - Funcionario cadastrado com sucesso!\n" RESET_COLOR);
}

void consultarFuncionario(){
    char procurarNome[50];
    char nomeArquivo[100];
    int chave = 3;
    
    imprimirLinhaCentralizada(GREEN " CONSULTA DE FUNCIONARIO " RESET_COLOR);

    printf(GREEN "[?] - Nome do Funcionario: " RESET_COLOR);
    scanf("%s", procurarNome);

    // Construindo o nome do arquivo com base no nome
    sprintf(nomeArquivo, "../data/funcionarios/funcionario_%s.txt", procurarNome);

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
        printf("Nome: %s\n", meuFuncionario.nome);
        printf("CPF: %s\n", meuFuncionario.cpf);
        printf("Data de Nascimento: %s\n", meuFuncionario.dataNascimento);
        printf("Telefone: %s\n", meuFuncionario.telefone);
        printf("Email: %s\n", meuFuncionario.email);
        printf("Cargo: %s\n", meuFuncionario.cargo);
        printf("Data de Admissao: %s\n", meuFuncionario.dataAdmissao);
        printf("Data de Demissao: %s\n", meuFuncionario.dataDemissao);
        printf("Salario: %s\n", meuFuncionario.salario);
        printf("Status: %s\n", meuFuncionario.status);

        printf("\n");
    
    // Fechando o arquivo
    fclose(arquivo);
    
};

void consultarEmpresa() {
    char procurarCNPJ[15];
    char nomeArquivo[100];
    int chave = 3;
    
    imprimirLinhaCentralizada(GREEN " CONSULTA DE EMPRESA " RESET_COLOR);

    printf(GREEN "[?] - CNPJ da Empresa: " RESET_COLOR);
    scanf("%s", procurarCNPJ);

    // Construindo o nome do arquivo com base no CNPJ
    sprintf(nomeArquivo, "../data/industrias/industria_%s.txt", procurarCNPJ);

    // Abrindo o arquivo para leitura
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
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
        printf("CNPJ: %s\n", minhaIndustria.cnpj);
        printf("Nome: %s\n", minhaIndustria.nome);
        printf("Nome Fantasia: %s\n", minhaIndustria.nomeFantasia);
        printf("Email: %s\n", minhaIndustria.email);
        printf("Telefone: %s\n", minhaIndustria.telefone);
        printf("Data de Abertura: %s\n", minhaIndustria.dataAbertura);
        printf("Rua: %s\n", minhaIndustria.endereco.rua);
        printf("Numero: %s\n", minhaIndustria.endereco.numero);
        printf("Bairro: %s\n", minhaIndustria.endereco.bairro);
        printf("Cidade: %s\n", minhaIndustria.endereco.cidade);
        printf("Estado: %s\n", minhaIndustria.endereco.estado);
        printf("CEP: %s\n", minhaIndustria.endereco.cep);
        printf("CPF do Responsavel: %s\n", minhaIndustria.cpfResponsavel);

        printf("\n");
    }

    // Fechando o arquivo
    fclose(arquivo);
    
};


int main() {
    if (realizarLogin()) {
        int opcao;
        while (1) {
            imprimirLinhaCentralizada(GREEN " MENU PRINCIPAL " RESET_COLOR);
            printf("\n");
            printf(RED "(1) - " GREEN "Cadastrar Industria\n" RESET_COLOR);
            printf(RED "(2) - " GREEN "Gerar Relatorio\n" RESET_COLOR);
            printf(RED "(3) - " GREEN "Cadastrar Funcionario\n" RESET_COLOR);
            printf(RED "(4) - " GREEN "Consultar Funcionario\n" RESET_COLOR);
            printf(RED "(5) - " GREEN "Consultar Empresa\n" RESET_COLOR);
            printf(RED "(6) - " GREEN "Sair\n" RESET_COLOR);
            printf(GREEN "[?] - Escolha uma opcao: " RESET_COLOR);
            scanf("%d", &opcao);
            printf("\n");

            switch (opcao) {
                case 1:
                    cadastrarIndustria();
                    break;
                case 2:
                    gerarRelatorio();
                    break;
                case 3:
                    cadastrarFuncionario();
                    break;
                case 4:
                    consultarFuncionario();
                    break;
                case 5:
                    consultarEmpresa();
                    break;
                case 6:
                    printf(RED "[!] - SISTEMA ENCERRADO!\n" RESET_COLOR);
                    return 0;
                default:
                    printf(RED "[!] - Opção invalida. Tente novamente.\n" RESET_COLOR);
            }
        }
    } else {
        printf("Login falhou. Encerrando o sistema.\n");
    }

    return 0;
}
