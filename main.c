#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

#define MAX 512

void preparaExpressao(const char *entrada, char *saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] == '(' || entrada[i] == ')') {
            saida[j++] = ' ';
            saida[j++] = entrada[i];
            saida[j++] = ' ';
        } else {
            saida[j++] = entrada[i];
        }
    }
    saida[j] = '\0';
}

int main() {
    char entrada[MAX];
    char entradaFormatada[MAX*2]; // espaço extra para adicionar espaços
    printf("Digite a expressão: ");
    fgets(entrada, MAX, stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    preparaExpressao(entrada, entradaFormatada);

    char *posfixa = getFormaPosFixa(entradaFormatada);
    if (posfixa != NULL)
        printf("Expressao posfixa: %s\n", posfixa);
    else
        printf("Erro ao converter a expressão.\n");

    return 0;
}