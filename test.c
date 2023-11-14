#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializa a semente para a função rand()
    srand((unsigned int)time(NULL));

    // Gera dois números aleatórios
    int numero1 = rand() % 10001; // Gera um número entre 0 e 10000
    int numero2 = rand() % 10001; // Gera um número entre 0 e 10000

    // Exibe os números gerados
    printf("Número 1: %d\n", numero1);
    printf("Número 2: %d\n", numero2);

    return 0;
}