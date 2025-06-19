#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

#define MAX 512 // Tamanho máximo da pilha

void preparaExpressao(const char *entrada, char *saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] == '(' || entrada[i] == ')') {
            // Adiciona espaço antes do parêntese
            saida[j++] = ' ';
            saida[j++] = entrada[i];
            saida[j++] = ' ';
        } else {
            saida[j++] = entrada[i];
        }
    }
    saida[j] = '\0'; // Finaliza string
}

int main() {
    char entrada[MAX];
    char entradaFormatada[MAX];
    printf("Digite a expressão: ");
    fgets(entrada, MAX, stdin); // Lê a expressão do usuário
    // Remove nova linha do final da string
    entrada[strcspn(entrada, "\n")] = 0;
    // Chama a função para obter a forma pós-fixa
    preparaExpressao(entrada, entradaFormatada);

    getFormaPosFixa(entradaFormatada);
    return 0;
}