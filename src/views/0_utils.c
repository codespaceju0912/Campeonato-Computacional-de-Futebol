#ifndef VIEW_UTILS_C
#define VIEW_UTILS_C 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER 100

// -------------------------------------------
// Lê um caractere (ex: para menus)
// -------------------------------------------
char readChar(const char *msg) {
    char buffer[INPUT_BUFFER];

    while (1) {
        printf("%s", msg);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro de leitura. Tente novamente.\n");
            continue;
        }

        // Ignora apenas ENTER
        if (buffer[0] == '\n') {
            printf("Nenhum caractere digitado. Tente novamente.\n");
            continue;
        }

        // Pega primeiro caractere válido
        return buffer[0];
    }
}

// -------------------------------------------
// Lê uma string com limite de tamanho
// -------------------------------------------
void readString(const char *msg, char *dest, size_t maxLen) {
    char buffer[INPUT_BUFFER];

    while (1) {
        printf("%s", msg);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro de leitura. Tente novamente.\n");
            continue;
        }

        // Remove newline se existir
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        if (strlen(buffer) >= maxLen) {
            printf("Entrada muito longa! Máximo permitido: %zu caracteres.\n", maxLen - 1);
            continue;
        }

        strcpy(dest, buffer);
        return;
    }
}

// -------------------------------------------
// Lê um inteiro com validação
// -------------------------------------------
int readInt(const char *msg) {
    char buffer[INPUT_BUFFER];
    char *endptr;
    long value;

    while (1) {
        printf("%s", msg);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro de leitura. Tente novamente.\n");
            continue;
        }

        // Remove newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        // Converte para inteiro usando strtol
        value = strtol(buffer, &endptr, 10);

        // Verifica erro
        if (endptr == buffer || *endptr != '\0') {
            printf("Valor inválido! Digite um número inteiro.\n");
            continue;
        }

        return (int)value;
    }
}

#endif