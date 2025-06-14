#include <stdio.h>
#include "expressao.h"

int main() {
    char posfixa[] = "3 4 + 2 *"; // Exemplo de expressão posfixa
    char *infixa = getFormaInFixa(posfixa);
    printf("Expressão infixa: %s\n", infixa);
    return 0;
}