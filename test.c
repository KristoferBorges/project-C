void decifraCesar(char *texto, int chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        // Verifica se o caractere é uma letra maiúscula
        if (isalpha(texto[i]) && isupper(texto[i])) {
            texto[i] = ((texto[i] - 'A' - chave + 26) % 26) + 'A';
        }
        // Verifica se o caractere é uma letra minúscula
        else if (isalpha(texto[i]) && islower(texto[i])) {
            texto[i] = ((texto[i] - 'a' - chave + 26) % 26) + 'a';
        }
        // Caso não seja uma letra, não realiza alteração
    }
}

void decifraCesar(char *texto, int chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        // Verifica se o caractere é uma letra maiúscula
        if (isalpha(texto[i]) && isupper(texto[i])) {
            texto[i] = (((texto[i] - 'A' - chave) % 26) + 26) % 26 + 'A';
        }
        // Verifica se o caractere é uma letra minúscula
        else if (isalpha(texto[i]) && islower(texto[i])) {
            texto[i] = (((texto[i] - 'a' - chave) % 26) + 26) % 26 + 'a';
        }
        // Não realiza alteração se não for uma letra
    }
}




