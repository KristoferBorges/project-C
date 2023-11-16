#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

// Definição da estrutura para armazenar informações da indústria
struct Industria {
    char cnpj[20];
    char nome[50];
    char regiao[20];
    float producao;
    float aporteFinanceiro;
};

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
void encontrarMaiorProducao(struct Industria *industrias, int numIndustrias) {
    float maxProducao = -FLT_MAX;
    int idxMaiorProducao = -1;

    for (int i = 0; i < numIndustrias; i++) {
        if (industrias[i].producao > maxProducao) {
            maxProducao = industrias[i].producao;
            idxMaiorProducao = i;
        }
    }
    if (idxMaiorProducao != -1) {
        printf("\nIndustria com maior producao:\n");
        printf("Nome: %s\nRegiao: %s\nProducao: %.2f\nAporte Financeiro: %.2f\n",
               industrias[idxMaiorProducao].nome, industrias[idxMaiorProducao].regiao,
               industrias[idxMaiorProducao].producao, industrias[idxMaiorProducao].aporteFinanceiro);
    } else {
        printf("Nenhuma industria encontrada.\n");
    }
}

// Função para encontrar a indústria que menos produziu
void encontrarMenorProducao(struct Industria *industrias, int numIndustrias) {
    float minProducao = FLT_MAX;
    int idxMenorProducao = -1;

    for (int i = 0; i < numIndustrias; i++) {
        if (industrias[i].producao < minProducao) {
            minProducao = industrias[i].producao;
            idxMenorProducao = i;
        }
    }

    if (idxMenorProducao != -1) {
        printf("\nIndustria com menor producao:\n");
        printf("Nome: %s\nRegiao: %s\nProducao: %.2f\nAporte Financeiro: %.2f\n",
               industrias[idxMenorProducao].nome, industrias[idxMenorProducao].regiao,
               industrias[idxMenorProducao].producao, industrias[idxMenorProducao].aporteFinanceiro);
    } else {
        printf("Nenhuma industria encontrada.\n");
    }
}

// Função para calcular o aporte financeiro semestral
void calcularAporteFinanceiroSemestral(struct Industria *industrias, int numIndustrias) {
    float totalAporteFinanceiro = 0.0;

    for (int i = 0; i < numIndustrias; i++) {
        totalAporteFinanceiro += industrias[i].aporteFinanceiro;
    }

    printf("\nAporte financeiro semestral total: %.2f\n", totalAporteFinanceiro);
}

int main() {
    const char *nomeArquivo = "../data/industrias/global/industrias_resumo.txt";
    struct Industria industrias[100]; // Assumindo um máximo de 100 indústrias, ajuste conforme necessário
    int numIndustrias = 0;

    lerIndustrias(nomeArquivo, industrias, &numIndustrias);

    encontrarMaiorProducao(industrias, numIndustrias);
    encontrarMenorProducao(industrias, numIndustrias);
    calcularAporteFinanceiroSemestral(industrias, numIndustrias);

    return 0;
}
