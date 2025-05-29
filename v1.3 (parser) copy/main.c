#include "bin/analisador_lexico.h"
#include "bin/analisador_sintatico.h"

char *nome_arquivo = NULL;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo-fonte>\n", argv[0]);
        return 1;
    }
    nome_arquivo = argv[1];

    arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    linha = 1;
    tabelaSimbolos = NULL;


    // Executa análise léxica para preencher a tabela
    while (analex() != TOKEN_EOF);

    // Imprime a tabela de símbolos
    imprimir_tabela_simbolos();

    // Inicializa o ponteiro do parser para o começo da tabela
    token_atual = tabelaSimbolos;

    printf("Iniciando análise sintática...\n");
    programa();
    printf("Análise sintática concluída com sucesso!\n");

    liberar_tabela_simbolos();
    fclose(arquivo);

    return 0;
}