#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

#define MAX 512
#define MAX_TOKEN 20

typedef struct {
    char itens[MAX][MAX_TOKEN];
    int topo;
} Pilha;

void IniciodaPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

void acrescenta(Pilha *p, const char *str) {
    if (!pilhaCheia(p)) {
        p->topo++;
        strncpy(p->itens[p->topo], str, MAX_TOKEN);
        p->itens[p->topo][MAX_TOKEN-1] = '\0';
    } else {
        printf("Pilha cheia!\n");
    }
}

char *retira(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->itens[p->topo--];
    } else {
        printf("Pilha vazia!\n");
        return NULL;
    }
}

char *topo(Pilha *p) {
    if (!pilhaVazia(p))
        return p->itens[p->topo];
    return NULL;
}

int contem(const char *lista[], int tamanho, const char *token) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(lista[i], token) == 0)
            return 1;
    }
    return 0;
}

int ehOperador(const char *token) {
    const char *operadores[] = {"+", "-", "*", "/", "%", "^"};
    return contem(operadores, 6, token);
}

int ehFuncao(const char *token) {
    const char *funcoes[] = {"sen", "cos", "tg", "log", "raiz"};
    return contem(funcoes, 5, token);
}

int ehNumero(const char *token) {
    if (!token || *token == '\0') return 0;
    char *end;
    strtod(token, &end);
    return (*end == '\0');
}

int precedencia(const char *token) {
    if (strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
        strcmp(token, "tg") == 0 || strcmp(token, "log") == 0)
        return 4;
    else if (strcmp(token, "raiz") == 0 || strcmp(token, "^") == 0)
        return 3;
    else if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0)
        return 2;
    else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
        return 1;
    else if (strcmp(token, "(") == 0 || strcmp(token, ")") == 0)
        return 5;
    return 0;
}

int ehParentese(const char *token) {
    return (strcmp(token, "(") == 0 || strcmp(token, ")") == 0);
}

char *getFormaPosFixa(char *str) {
    static char saida[MAX*MAX_TOKEN];
    saida[0] = '\0';

    Pilha pilha;
    IniciodaPilha(&pilha);

    char *token = strtok(str, " ");
    while (token != NULL) {

        if (ehNumero(token)) {
            strcat(saida, token);
            strcat(saida, " ");
        }
        else if (ehFuncao(token)) {
            acrescenta(&pilha, token);
        }
        else if (ehOperador(token)) {
            while (!pilhaVazia(&pilha) && !ehParentese(topo(&pilha)) &&
                   precedencia(topo(&pilha)) >= precedencia(token)) {
                strcat(saida, retira(&pilha));
                strcat(saida, " ");
            }
            acrescenta(&pilha, token);
        }
        else if (strcmp(token, "(") == 0) {
            acrescenta(&pilha, token);
        }
        else if (strcmp(token, ")") == 0) {
            while (!pilhaVazia(&pilha) && strcmp(topo(&pilha), "(") != 0) {
                strcat(saida, retira(&pilha));
                strcat(saida, " ");
            }
            if (!pilhaVazia(&pilha) && strcmp(topo(&pilha), "(") == 0) {
                retira(&pilha);
            } else {
                printf("Erro: Parêntese não fechado\n");
                return NULL;
            }
            if (!pilhaVazia(&pilha) && ehFuncao(topo(&pilha))) {
                strcat(saida, retira(&pilha));
                strcat(saida, " ");
            }
        }
        else {
            printf("Token inválido: %s\n", token);
            return NULL;
        }

        token = strtok(NULL, " ");
    }

    while (!pilhaVazia(&pilha)) {
        if (strcmp(topo(&pilha), "(") == 0 || strcmp(topo(&pilha), ")") == 0) {
            printf("Erro: Parêntese não fechado\n");
            return NULL;
        }
        strcat(saida, retira(&pilha));
        strcat(saida, " ");
    }

    return saida;
}