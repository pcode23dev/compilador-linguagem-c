#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"

#define TAM_INICIAL 1000

EntradaTabela* tabela = NULL;
int capacidade = 0;
int pos = 0;

void inicializar_tabela() {
    capacidade = TAM_INICIAL;
    tabela = (EntradaTabela *) malloc(capacidade * sizeof(EntradaTabela));

    if (!tabela) {
        fprintf(stderr, "Erro ao alocar memória para a tabela de símbolos.\n");
        exit(EXIT_FAILURE);
    }
}

void gravar_token_lexema(int tok, const char* lex, int lin, int col) {
    // Aumenta a capacidade da tabela se necessário
    if (pos >= capacidade) {
        capacidade *= 2;
        tabela = (EntradaTabela *) realloc(tabela, capacidade * sizeof(EntradaTabela));
        if (!tabela) {
            fprintf(stderr, "Erro ao realocar memória para a tabela de símbolos.\n");
            exit(EXIT_FAILURE);
        }
    }

    tabela[pos].token = tok;
    tabela[pos].lexema = strdup(lex);  // Aloca e copia
    tabela[pos].linha = lin;
    tabela[pos].coluna = col;
    pos++;
}

void imprimir_tabela_simbolos() {
    printf("\nTABELA DE SÍMBOLOS:\n");
    printf("------------------------------\n");
    int i;
    for (i = 0; i < pos; i++) {
        printf("Token: %d\tLexema: %-10s\tLinha: %d\tColuna: %d\n",
               tabela[i].token,
               tabela[i].lexema,
               tabela[i].linha,
               tabela[i].coluna);
    }
    printf("------------------------------\n");
}

void liberar_tabela() {
     int i;
    for (i = 0; i < pos; i++) {
        free(tabela[i].lexema);
    }
    free(tabela);
}
