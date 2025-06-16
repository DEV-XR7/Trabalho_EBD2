#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

#define MAX 512 // Tamanho máximo da pilha

typedef struct {
    char vetor[MAX]; // Vetor que armazena os elementos da pilha
    int topo; // Índice do topo da pilha
} Pilha;    

void IniciodaPilha(Pilha *P) {
    P->topo = -1; // Inicializa a pilha como vazia
}

int pilhaVazia(Pilha *P) {
    return P->topo == -1;
}

int pilhaCheia(Pilha *P) {
    return P->topo == MAX - 1;
}

void acrescenta(Pilha *P, char c) {
    if (!pilhaCheia(P)) {
        P->topo++;
        P->vetor[P->topo] = c;
    } else {
        printf("Pilha cheia!\n");
    }
}

char retira(Pilha *P) {
    if (!pilhaVazia(P)) {
        char c = P->vetor[P->topo];
        P->topo--;
        return c;
    } else {
        printf("Pilha vazia!\n");
        return '\0'; // Retorna um caractere nulo se a pilha estiver vazia
    }
}

void Parenteses(const char *token, Pilha *pilha, char *saida) {
    if (*token == '(') {
        acrescenta(pilha, *token); // empilha o '('
    } 
    else if (*token == ')') {
        while (!pilhaVazia(pilha) && pilha->vetor[pilha->topo] != '(') {
            char operador = retira(pilha);
            strncat(saida, &operador, 1); // adiciona operador à saída
        }
        if (!pilhaVazia(pilha) && pilha->vetor[pilha->topo] == '(') {
            retira(pilha); // remove o '(' da pilha (descarta)
        } else {
            printf("O parêntese não foi fechado.\n");
        }
    }
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
    const char *funcoes[] = {"log", "raiz", "sen", "cos", "tg"};
    return contem(funcoes, 5, token);
}

int ehNumero(const char *token) {
    if (!token || *token == '\0') return 0;
    char *end;
    strtod(token, &end);
    return (*end == '\0');
}

char *getFormaInFixa(char *Str){} // Retorna a forma inFixa de Str (posFixa) 

char *getFormaPosFixa(char *Str) {
    static char saida[MAX]; // String para armazenar a saída
    Pilha pilha;
    IniciodaPilha(&pilha); // Inicializa a pilha
    saida[0] = '\0'; // Inicializa a string de saída

    // Tokeniza a string de entrada
    char *token = strtok(Str, " ");
    while (token != NULL) {
        if (*token == '(') {
            acrescenta(&pilha, *token); // Adiciona '(' à pilha
        } else if (*token == ')') {
            Parenteses(token, &pilha, saida);
        } else if (ehOperador(token)) {
            acrescenta(&pilha, *token); // Adiciona operador à pilha
        } else if (ehFuncao(token)) {
            acrescenta(&pilha, *token); // Adiciona função à pilha
        } else if (ehNumero(token)) {
            strncat(saida, token, strlen(token)); // Adiciona número à saída
            strncat(saida, " ", 1); // Adiciona espaço após o número
        } else {
            printf("Token inválido: %s\n", token);
        }
        token = strtok(NULL, " ");
    }

    // Verifica se a pilha está vazia e se a saída não está vazia
    if (!pilhaVazia(&pilha)) {
        printf("O parêntese não foi fechado.\n");
    } else if (strlen(saida) == 0) {
        printf("A expressão está vazia.\n");
    } else {
        printf("Expressão em pós-fixa: %s\n", saida);
    }

    return saida; // Retorna a string de saída
}

float getValorPosFixa(char *StrPosFixa); // Calcula o valor de Str (na forma posFixa) 
float getValorInFixa(char *StrInFixa); // Calcula o valor de Str (na forma inFixa) 