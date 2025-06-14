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

void IniciodaPilha(Pilha *P) { //Cria uma pilha vazia
    P->topo = -1; //Vazio real
}

int pilhaVazia(Pilha *P) { //Verifica se a pilha está vazia
    return P->topo == -1;
}

int pilhaCheia(Pilha *P) { //Verifica se a pilha está cheia
    return P->topo == MAX - 1; //MAX é o tamanho máximo da pilha
}

void acrescenta(Pilha *P, char c) { //Coloca um elemento na pilha
    if (!pilhaCheia(P)) {
        P->topo++;
        P->vetor[P->topo] = c;
    } else {
        printf("Pilha cheia!\n");
    }
}

char retira(Pilha *P) { //Retira um elemento da pilha
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
        while (!pilhaVazia(pilha) && pilha -> vetor[pilha->topo] != '(') {
            char operador = retira(pilha);
            strncat(saida, &operador, 1); // adiciona operador à saída
        }
        if (!pilhaVazia(pilha) && pilha -> vetor[pilha->topo] == '(') {
            retira(pilha); // remove o '(' da pilha (descarta)
        }
    }
}

char *getFormaInFixa(char *Str); // Retorna a forma inFixa de Str (posFixa) 
char *getFormaPosFixa(char *Str); // Retorna a forma posFixa de Str (inFixa) 

    int contem(const char *lista[], int tamanho, const char *token) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(lista[i], token) == 0)
                return 1;
        return 0;
    }

    int ehParenteses(const char *token) {
        if (*token == '(' || *token == ')') {
            Parenteses(token, pilha, saida);
        }
        
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

float getValorPosFixa(char *StrPosFixa); // Calcula o valor de Str (na forma posFixa) 
float getValorInFixa(char *StrInFixa); // Calcula o valor de Str (na forma inFixa) 