#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

#define MAX 512

void preparaExpressao(const char *entrada, char *saida);

int main() {
    char entrada[MAX * 2] = {0};

    printf("Escolha a operação:\n");
    printf("1 - Converter expressão infixa para pós-fixa\n");
    printf("2 - Calcular valor de expressão pós-fixa\n");
    printf("3 - Calcular valor de expressão infixa\n");
    printf("4 - Converter expressão pós-fixa para infixa\n");
    printf("Opcao: ");
    int opcao;
    scanf("%d", &opcao);
    getchar(); // limpa '\n' do buffer

    if (opcao == 1) {
        printf("Digite a expressão infixa: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0;

        char entradaFormatada[MAX * 2] = {0};
        preparaExpressao(entrada, entradaFormatada);

        char *posfixa = getFormaPosFixa(entradaFormatada);
        if (posfixa == NULL) {
            printf("Erro ao converter a expressão.\n");
            return 1;
        }
        printf("Expressão pós-fixa: %s\n", posfixa);

    } else if (opcao == 2) {
        printf("Digite a expressão pós-fixa: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0;

        float resultado = getValorPosFixa(entrada);
        printf("Resultado: %f\n", resultado);

    } else if (opcao == 3) {
        printf("Digite a expressão infixa: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0;

        float resultado = getValorInFixa(entrada);
        printf("Resultado: %f\n", resultado);

    } else if (opcao == 4) {
        printf("Digite a expressão pós-fixa: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0;

        char *infixa = getFormaInFixa(entrada);
        printf("Expressão infixa: %s\n", infixa);
        free(infixa); // libera memória alocada por strdup

    } else {
        printf("Opção inválida.\n");
    }

    return 0;
}
