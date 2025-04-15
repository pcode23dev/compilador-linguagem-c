#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"

#define TAM_INICIAL 1000

EntradaTabela* tabela = NULL;
int capacidade = 0;
int indice_tabela = 0;

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
    if (indice_tabela >= capacidade) {
        capacidade *= 2;
        tabela = (EntradaTabela *) realloc(tabela, capacidade * sizeof(EntradaTabela));
        if (!tabela) {
            fprintf(stderr, "Erro ao realocar memória para a tabela de símbolos.\n");
            exit(EXIT_FAILURE);
        }
    }

    tabela[indice_tabela].token = tok;
    tabela[indice_tabela].lexema = strdup(lex);  // Aloca e copia
    tabela[indice_tabela].linha = lin;
    tabela[indice_tabela].coluna = col;
    indice_tabela++;
}

void imprimir_tabela_simbolos() {
    printf("\nTABELA DE SÍMBOLOS:\n");
    printf("------------------------------\n");
    for (int i = 0; i < indice_tabela; i++) {
        printf("Token: %d\tLexema: %-10s\tLinha: %d\tColuna: %d\n",
               tabela[i].token,
               tabela[i].lexema,
               tabela[i].linha,
               tabela[i].coluna);
    }
    printf("------------------------------\n");
}

void liberar_tabela() {
    for (int i = 0; i < indice_tabela; i++) {
        free(tabela[i].lexema);
    }
    free(tabela);
}
