#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#define TAM_LEXEMA 100

typedef struct {
    int token;
    char lexema[TAM_LEXEMA];
    int linha;
    int coluna;
} EntradaTabela;

void inicializar_tabela();
void gravar_token_lexema(int token, const char* lexema, int linha, int coluna);
void imprimir_tabela_simbolos();
void liberar_tabela();

#endif
