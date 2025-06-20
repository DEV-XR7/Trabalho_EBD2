#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

#define MAX 512

void preparaExpressao(const char *entrada, char *saida);

int main() {
    char entrada[MAX];
    char entradaFormatada[MAX * 2] = {0}; // espaço extra para adicionar espaços

    printf("Digite a expressão: ");
    fgets(entrada, MAX, stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    preparaExpressao(entrada, entradaFormatada);

    printf("entrada formatada: %s\n", entradaFormatada);

    char *posfixa = getFormaPosFixa(entradaFormatada);
    if (posfixa != NULL)
        printf("Expressao posfixa: %s\n", posfixa);
    else
        printf("Erro ao converter a expressão.\n");

    return 0;
}