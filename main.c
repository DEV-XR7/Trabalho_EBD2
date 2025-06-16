#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

int main() {
    char entrada[MAX];
    printf("Digite a expressão: ");
    fgets(entrada, MAX, stdin); // Lê a expressão do usuário
    // Remove nova linha do final da string
    entrada[strcspn(entrada, "\n")] = 0;
    // Chama a função para obter a forma pós-fixa
    getFormaPosFixa(entrada);
    return 0;
}