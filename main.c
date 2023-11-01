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
}

// Estrutura para armazenar informações da indústria
struct Industria {
    char nome[50];
    char responsavel[50];
    char cnpj[15];
    // Outros campos de informações da indústria
};

// Função para realizar o login
int realizarLogin() {
    char usuario[50];
    char senha[50];

    printf("\n");
    imprimirLinhaCentralizada(GREEN " SISTEMA DE GESTAO AMBIENTAL " RESET_COLOR);
    printf("\n");

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
    struct Industria industria;
    
    imprimirLinhaCentralizada(GREEN " CADASTRO DE INDUSTRIA " RESET_COLOR);
    printf("\n");
    printf(GREEN "[?] - Nome da Industria: " RESET_COLOR);
    scanf("%s", industria.nome);
    printf(GREEN "[?] - Responsavel: " RESET_COLOR);
    scanf("%s", industria.responsavel);
    printf(GREEN "[?] - CNPJ: " RESET_COLOR);
    scanf("%s", industria.cnpj);

    // Salvar informações no arquivo (implementação necessária)
}

// Função para gerar relatórios
void gerarRelatorio() {
    // Gerar relatórios (implementação necessária)
}

int main() {
    if (realizarLogin()) {
        int opcao;
        while (1) {
            imprimirLinhaCentralizada(GREEN " MENU PRINCIPAL " RESET_COLOR);
            printf("\n");
            printf(RED "(1) - " GREEN "Cadastrar Industria\n" RESET_COLOR);
            printf(RED "(2) - " GREEN "Gerar Relatorio\n" RESET_COLOR);
            printf(RED "(3) - " GREEN "Sair\n" RESET_COLOR);
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
