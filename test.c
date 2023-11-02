#include <stdio.h>
#include <string.h>

// Função de criptografia simples usando deslocamento
void criptografar(char *texto, int chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] + chave; // Deslocamento da chave
    }
}

// Função de descriptografia
void descriptografar(char *texto, int chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] - chave; // Deslocamento inverso da chave
    }
}

int main() {
    char texto[] = "456789:;<34";
    int chave = 3; // Chave de deslocamento (pode ser qualquer número)

    printf("Texto original: %s\n", texto);

    criptografar(texto, chave);
    printf("Texto criptografado: %s\n", texto);

    descriptografar(texto, chave);
    printf("Texto descriptografado: %s\n", texto);

    return 0;
}
