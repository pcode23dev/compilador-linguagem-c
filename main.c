#include <stdio.h>
#include "tabela_simbolos.h"

int main(){
    inicializar_tabela();

    // Exemplo de gravação
    gravar_token_lexema(1, "if", 1, 5);
    gravar_token_lexema(10, "x", 2, 1);
    gravar_token_lexema(16, "+", 2, 3);

    imprimir_tabela_simbolos();

    liberar_tabela();

    return 0;
}