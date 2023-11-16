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
        fprintf(saida, "Indústria com maior produção:\n");
        fprintf(saida, "Nome: %s\nRegião: %s\nProdução: %.2f\nAporte Financeiro: %.2f\n",
               industrias[idxMaiorProducao].nome, industrias[idxMaiorProducao].regiao,
               industrias[idxMaiorProducao].producao, industrias[idxMaiorProducao].aporteFinanceiro);
    } else {
        fprintf(saida, "Nenhuma indústria encontrada.\n");
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
        fprintf(saida, "Indústria com menor produção:\n");
        fprintf(saida, "Nome: %s\nRegião: %s\nProdução: %.2f\nAporte Financeiro: %.2f\n",
               industrias[idxMenorProducao].nome, industrias[idxMenorProducao].regiao,
               industrias[idxMenorProducao].producao, industrias[idxMenorProducao].aporteFinanceiro);
    } else {
        fprintf(saida, "Nenhuma indústria encontrada.\n");
    }
}

// Função para calcular o aporte financeiro semestral
void calcularAporteFinanceiroSemestral(struct Industria *industrias, int numIndustrias, FILE *saida) {
    float totalAporteFinanceiro = 0.0;

    for (int i = 0; i < numIndustrias; i++) {
        totalAporteFinanceiro += industrias[i].aporteFinanceiro;
    }

    fprintf(saida, "Aporte financeiro semestral total: %.2f\n", totalAporteFinanceiro);
}

int main() {
    const char *nomeArquivo = "industrias.txt";
    const char *nomeArquivoSaida = "resultados.txt";
    struct Industria industrias[100]; // Assumindo um máximo de 100 indústrias, ajuste conforme necessário
    int numIndustrias = 0;

    FILE *saida = fopen(nomeArquivoSaida, "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    lerIndustrias(nomeArquivo, industrias, &numIndustrias);

    encontrarMaiorProducao(industrias, numIndustrias, saida);
    encontrarMenorProducao(industrias, numIndustrias, saida);
    calcularAporteFinanceiroSemestral(industrias, numIndustrias, saida);

    fclose(saida);

    return 0;
}
