#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

#define MAX 512
#define MAX_TOKEN 20
#define MAX_EXPR 1024  // Novo tamanho para expressões compostas


typedef struct {
    char expressao[MAX];
    int prioridade;
} ExpressaoInfo;

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

float absf_manual(float x) {
    return (x < 0) ? -x : x;
}

float fmodf_manual(float x, float y) {
    return x - (int)(x / y) * y;
}

float powf_manual(float base, int expoente) {
    float resultado = 1.0;
    int positivo = (expoente >= 0);
    expoente = positivo ? expoente : -expoente;
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return positivo ? resultado : 1.0 / resultado;
}

float sinf_manual(float x) {
    float termo = x, soma = x;
    for (int i = 1; i < 10; i++) {
        termo *= -1 * x * x / ((2 * i) * (2 * i + 1));
        soma += termo;
    }
    return soma;
}

float cosf_manual(float x) {
    float termo = 1, soma = 1;
    for (int i = 1; i < 10; i++) {
        termo *= -1 * x * x / ((2 * i - 1) * (2 * i));
        soma += termo;
    }
    return soma;
}

float tanf_manual(float x) {
    float cos = cosf_manual(x);
    if (cos == 0) return 0;
    return sinf_manual(x) / cos;
}

float log10f_manual(float x) {
    if (x <= 0) return 0;
    float ln = 0.0, y = (x - 1) / (x + 1);
    float y2 = y * y;
    float termo = y;
    for (int i = 1; i < 20; i += 2) {
        ln += termo / i;
        termo *= y2;
    }
    return 2 * ln / 2.302585093;
}

float sqrtf_manual(float x) {
    float guess = x / 2.0;
    for (int i = 0; i < 10; i++) {
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

int ehOperador(const char *token) {
    const char *operadores[] = {"+", "-", "*", "/", "%", "^"};
    return contem(operadores, 6, token);
}

int ehFuncao(const char *token) {
    const char *funcoes[] = {"sen", "cos", "tg", "log", "raiz", "abs"};
    return contem(funcoes, 5, token);
}

int ehNumero(const char *token) {
    if (!token || *token == '\0') return 0;
    char *end;
    strtod(token, &end);
    return (*end == '\0');
}

int ehCaractereFuncao(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int ehOperadores(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

void preparaExpressao(const char *entrada, char *saida) {
    int j = 0;
    char funcBuffer[20];
    int funcIndex = 0;

    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];

        if (c == ',') c = '.';  // <<<<< Substitui vírgula por ponto
        if (c == ' ') continue;

        if (ehCaractereFuncao(c)) {
            funcBuffer[funcIndex++] = c;
        } else {
            if (funcIndex > 0) {
                funcBuffer[funcIndex] = '\0';
                for (int k = 0; funcBuffer[k] != '\0'; k++)
                    saida[j++] = funcBuffer[k];
                saida[j++] = ' ';
                funcIndex = 0;
            }

            if (c == '(' || c == ')' || ehOperadores(c)) {
                saida[j++] = ' ';
                saida[j++] = c;
                saida[j++] = ' ';
            } else {
                saida[j++] = c;
            }
        }
    }

    if (funcIndex > 0) {
        funcBuffer[funcIndex] = '\0';
        for (int k = 0; funcBuffer[k] != '\0'; k++)
            saida[j++] = funcBuffer[k];
        saida[j++] = ' ';
    }

    saida[j] = '\0';
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

char *getFormaInFixa(char *Str) {
    ExpressaoInfo pilha[MAX];
    int topo = -1;

    char copia[MAX];
    strncpy(copia, Str, MAX);
    copia[MAX - 1] = '\0';

    char *token = strtok(copia, " ");
    while (token != NULL) {
        if (ehNumero(token)) {
            ExpressaoInfo info;
            snprintf(info.expressao, sizeof(info.expressao), "%s", token);
            info.prioridade = 10;
            pilha[++topo] = info;
        }
        else if (ehFuncao(token)) {
            if (topo < 0) return strdup("ERRO: Falta operando para função");

            ExpressaoInfo arg = pilha[topo--];
            ExpressaoInfo res;

            if (snprintf(res.expressao, sizeof(res.expressao), "%s(%s)", token, arg.expressao) >= sizeof(res.expressao)) {
                return strdup("ERRO: expressão muito longa");
            }

            res.prioridade = 10;
            pilha[++topo] = res;
        }
        else if (ehOperador(token)) {
            if (topo < 1) return strdup("ERRO: Operação requer dois operandos");

            ExpressaoInfo dir = pilha[topo--];
            ExpressaoInfo esq = pilha[topo--];

            int prec = precedencia(token);
            char esqTemp[MAX_EXPR];
            char dirTemp[MAX_EXPR];

            if (esq.prioridade < prec) {
                if (snprintf(esqTemp, sizeof(esqTemp), "(%s)", esq.expressao) >= sizeof(esqTemp))
                    return strdup("ERRO: expressão muito longa");
            } else {
                strncpy(esqTemp, esq.expressao, sizeof(esqTemp));
                esqTemp[sizeof(esqTemp)-1] = '\0';
            }

            if (dir.prioridade < prec || (dir.prioridade == prec && strcmp(token, "^") != 0)) {
                if (snprintf(dirTemp, sizeof(dirTemp), "(%s)", dir.expressao) >= sizeof(dirTemp))
                    return strdup("ERRO: expressão muito longa");
            } else {
                strncpy(dirTemp, dir.expressao, sizeof(dirTemp));
                dirTemp[sizeof(dirTemp)-1] = '\0';
            }

            ExpressaoInfo res;
            if (snprintf(res.expressao, sizeof(res.expressao), "%s %s %s", esqTemp, token, dirTemp) >= sizeof(res.expressao)) {
                return strdup("ERRO: expressão muito longa");
            }

            res.prioridade = prec;
            pilha[++topo] = res;
        }
        else {
            return strdup("ERRO: Token desconhecido");
        }

        token = strtok(NULL, " ");
    }

    if (topo != 0) {
        return strdup("ERRO: Expressão incompleta");
    }

    return strdup(pilha[topo].expressao);
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

float getValorPosFixa(char *StrPosFixa) {
    Pilha pilha;
    IniciodaPilha(&pilha);

    char expr[MAX];
    strncpy(expr, StrPosFixa, MAX);
    expr[MAX - 1] = '\0';

    char *token = strtok(expr, " ");
    while (token != NULL) {
        if (ehNumero(token)) {
            acrescenta(&pilha, token);
        } else if (ehOperador(token)) {
            if (pilha.topo < 1) {
                printf("Erro: operadores insuficientes para operador binário '%s'\n", token);
                return 0;
            }

            float b = atof(retira(&pilha));
            float a = atof(retira(&pilha));
            float resultado = 0;

            if (strcmp(token, "+") == 0) resultado = a + b;
            else if (strcmp(token, "-") == 0) resultado = a - b;
            else if (strcmp(token, "*") == 0) resultado = a * b;
            else if (strcmp(token, "/") == 0) resultado = a / b;
            else if (strcmp(token, "%") == 0) resultado = fmodf_manual(a, b);
            else if (strcmp(token, "^") == 0) resultado = powf_manual(a, (int)b);
            else {
                printf("Erro: operador '%s' não suportado\n", token);
                return 0;
            }

            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%f", resultado);
            acrescenta(&pilha, buffer);

        } else if (ehFuncao(token)) {
            if (pilha.topo < 0) {
                printf("Erro: operador insuficiente para função '%s'\n", token);
                return 0;
            }

            float x = atof(retira(&pilha));
            float resultado = 0;

            if (strcmp(token, "sen") == 0)
                resultado = sinf_manual(x * 3.14159265 / 180.0); // graus para rad
            else if (strcmp(token, "cos") == 0)
                resultado = cosf_manual(x * 3.14159265 / 180.0);
            else if (strcmp(token, "tg") == 0)
                resultado = tanf_manual(x * 3.14159265 / 180.0);
            else if (strcmp(token, "log") == 0)
                resultado = log10f_manual(x);
            else if (strcmp(token, "raiz") == 0)
                resultado = sqrtf_manual(x);
            else if (strcmp(token, "abs") == 0)
                resultado = absf_manual(x);
            else {
                printf("Erro: função '%s' não suportada\n", token);
                return 0;
            }

            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%f", resultado);
            acrescenta(&pilha, buffer);

        } else {
            printf("Token inválido: %s\n", token);
            return 0;
        }

        token = strtok(NULL, " ");
    }

    if (pilha.topo != 0) {
        printf("Erro: expressão malformada. Itens restantes na pilha.\n");
        return 0;
    }

    return atof(retira(&pilha));
}

float getValorInFixa(char *StrInFixa) {
    char entradaFormatada[MAX * 2];
    preparaExpressao(StrInFixa, entradaFormatada);

    char *posfixa = getFormaPosFixa(entradaFormatada);
    if (posfixa == NULL) {
        printf("Erro ao converter a expressão infixa para pós-fixa.\n");
        return 0.0f;
    }

    return getValorPosFixa(posfixa);
}