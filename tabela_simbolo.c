#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"

#define TAM_INICIAL 1000

EntradaTabela* tabela = NULL;
int capacidade = 0;
int index = 0;

void inicializar_tabela() {
    capacidade = TAM_INICIAL;
    tabela = (EntradaTabela *) malloc(capacidade * sizeof(EntradaTabela));

    if (!tabela) {
        fprintf(stderr, "Erro ao alocar memória para a tabela de símbolos.\n");
        exit(EXIT_FAILURE);
    }
}

void gravar_token_lexema(int tok, char* lex, int lin, int col) {
    // Aumenta a capacidade da tabela se necessário
    if (index >= capacidade) {
        capacidade *= 2;
        tabela = (EntradaTabela *) realloc(tabela, capacidade * sizeof(EntradaTabela));
        if (!tabela) {
            fprintf(stderr, "Erro ao realocar memória para a tabela de símbolos.\n");
            exit(EXIT_FAILURE);
        }
    }

    tabela[index].token = tok;
    tabela[index].lexema = strdup(lex);  // Aloca e copia
    tabela[index].linha = lin;
    tabela[index].coluna = col;
    index++;
}

void imprimir_tabela_simbolos() {
    printf("\nTABELA DE SÍMBOLOS:\n");
    printf("------------------------------\n");
    for (int i = 0; i < index; i++) {
        printf("Token: %d\tLexema: %-10s\tLinha: %d\tColuna: %d\n",
               tabela[i].token,
               tabela[i].lexema,
               tabela[i].linha,
               tabela[i].coluna);
    }
    printf("------------------------------\n");
}

void liberar_tabela() {
    for (int i = 0; i < index; i++) {
        free(tabela[i].lexema);
    }
    free(tabela);
}
