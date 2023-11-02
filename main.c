#include <stdio.h>
#include <string.h>

// Defina macros para as cores
#define RESET_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"

// Função para imprimir linha centralizada com asteriscos
void imprimirLinhaCentralizada(const char *texto) {
    int larguraTotal = 50; // Largura total da linha (ajuste conforme necessário)
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

void criptografar(char *texto, int chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] + chave; // Deslocamento da chave
    }
}

// Estrutura para armazenar informações da indústria
struct Industria {
    char nome[50];
    char nomeFantasia[50];
    char cnpj[15];
    char email[50];
    char telefone[15];
    char dataAbertura[10];
    char cpfResponsavel[50];

    struct Endereco {
        char rua[50];
        char numero[10];
        char bairro[50];
        char cidade[50];
        char estado[50];
        char cep[10];
    } endereco;

    // Outros campos de informações da indústria
} industria;

struct Funcionario {
    char nome[50];
    char cpf[15];
    char email[50];
    char telefone[15];
    char dataNascimento[10];
    char cargo[50];
    char setor[50];
    char dataAdmissao[10];
    char dataDemissao[10];
    char salario[10];
    char status[10];
} funcionario;

// Função para realizar o login
int realizarLogin() {
    char usuario[50];
    char senha[50];

    printf("\n");
    imprimirLinhaCentralizada(GREEN " SISTEMA DE GESTAO AMBIENTAL " RESET_COLOR);

    printf(GREEN "[?] - Usuario: " RESET_COLOR);
    scanf("%s", usuario);
    printf(GREEN "[?] - Senha: " RESET_COLOR);
    scanf("%s", senha);

    // Verificar o login e senha no sistema (implementação necessária)
    // Se login for bem-sucedido, retorne 1; caso contrário, retorne 0
    return 1; // Simulando login bem-sucedido
}

// Função para cadastrar uma indústria
void cadastrarIndustria() {
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
    int chave = 3;
    criptografar(industria.cpfResponsavel, chave);
    
    FILE *arquivo = fopen("../data/industrias.txt", "a");
    fprintf(arquivo, "*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    fprintf(arquivo, "Nome: %s\n", industria.nome);
    fprintf(arquivo, "Nome Fantasia: %s\n", industria.nomeFantasia);
    fprintf(arquivo, "CNPJ: %s\n", industria.cnpj);
    fprintf(arquivo, "Email: %s\n", industria.email);
    fprintf(arquivo, "Telefone: %s\n", industria.telefone);
    fprintf(arquivo, "Data de Abertura: %s\n", industria.dataAbertura);
    fprintf(arquivo, "Rua: %s\n", industria.endereco.rua);
    fprintf(arquivo, "Numero: %s\n", industria.endereco.numero);
    fprintf(arquivo, "Bairro: %s\n", industria.endereco.bairro);
    fprintf(arquivo, "Cidade: %s\n", industria.endereco.cidade);
    fprintf(arquivo, "Estado: %s\n", industria.endereco.estado);
    fprintf(arquivo, "CEP: %s\n", industria.endereco.cep);
    fprintf(arquivo, "CPF do Responsavel: %s\n", industria.cpfResponsavel);
    fclose(arquivo);
}

// Função para gerar relatórios
void gerarRelatorio() {
    // Gerar relatórios (implementação necessária)
}

void cadastrarFuncionario() {
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

    printf(GREEN "[?] - Setor: " RESET_COLOR);
    scanf("%s", funcionario.setor);

    printf(GREEN "[?] - Data de Admissao: " RESET_COLOR);
    scanf("%s", funcionario.dataAdmissao);

    printf(GREEN "[?] - Data de Demissao: " RESET_COLOR);
    scanf("%s", funcionario.dataDemissao);

    printf(GREEN "[?] - Salario: " RESET_COLOR);
    scanf("%s", funcionario.salario);

    printf(GREEN "[?] - Status: " RESET_COLOR);
    scanf("%s", funcionario.status);

}

void consultarEmpresa() {
    // Consultar empresa (implementação necessária)
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
            printf(RED "(4) - " GREEN "Consultar Empresa\n" RESET_COLOR);
            printf(RED "(5) - " GREEN "Sair\n" RESET_COLOR);
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
                    consultarEmpresa();
                    break;
                case 5:
                    printf("SISTEMA ENCERRADO!\n");
                    return 0;
                default:
                    printf("Opção invalida. Tente novamente.\n");
            }
        }
    } else {
        printf("Login falhou. Encerrando o sistema.\n");
    }

    return 0;
}
