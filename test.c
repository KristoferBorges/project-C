#include <stdio.h>
#include <string.h>

// Defina macros para as cores
#define RESET_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"

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

int main() {

    printf(GREEN "[?] - Nome da Empresa: " RESET_COLOR);
    scanf("%s", industria.nome);
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "../data/industria_%s.txt", industria.nome);

    FILE *arquivo = fopen(caminhoArquivo, "a");
    fprintf(arquivo, "%s\n", industria.nome);
    fclose(arquivo);
    printf("\n");
    printf(GREEN "[!] - Industria cadastrada com sucesso!\n" RESET_COLOR);
    
    return 0;
}
