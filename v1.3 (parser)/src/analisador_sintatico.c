#include <stdio.h>
#include <stdlib.h>
#include "../bin/analisador_sintatico.h"

// Variável global para o token atual
EntradaTabela *token_atual = NULL;
extern char *nome_arquivo;

// Contador de erros
int total_erros = 0;

// Retorna o token atual
int token_atual_token()
{
    if (token_atual == NULL)
    {
        return TOKEN_EOF;
    }
    return token_atual->token;
}

// Avança para o próximo token
void avancar_token()
{
    if (token_atual != NULL)
        token_atual = token_atual->prox;
}

// Verifica e consome o token esperado, com recuperação de erros
void casa_token(int esperado) {
    int atual = token_atual_token();
    if (atual == esperado) {
        avancar_token();
    } else {
        printf("%s:%d:%d: erro: esperado token %d%s%s, encontrado %d (%s)\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               esperado,
               token_atual && token_atual->token_name ? " (" : "",
               token_atual && token_atual->token_name ? token_atual->token_name : "",
               atual,
               token_atual ? token_atual->lexema : "NULL");
        total_erros++;

        // Modo de pânico: avança até um ponto de sincronização
        while (token_atual != NULL && 
               token_atual_token() != TOKEN_PONTO_VIRGULA && 
               token_atual_token() != TOKEN_FECHA_CHAVES && 
               token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
        if (token_atual != NULL && token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
    }
}

// ------------------ Análise Sintática ----------------------

void programa() {
    lista_de_declaracoes();
    if (token_atual_token() != TOKEN_EOF) {
        printf("%s:%d:%d: Erro sintático: código após o fim do programa, %s não esperado\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               token_atual ? token_atual->token_name : "NULL");
        total_erros++;
    }
    if (total_erros > 0) {
        printf("Análise sintática concluída com %d erro(s) encontrados.\n", total_erros);
    } else {
        printf("Análise sintática concluída sem erros.\n");
    }
}

void lista_de_declaracoes()
{
    int t = token_atual_token();
    if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID || 
        t == TOKEN_IDENTIFICADOR || t == TOKEN_TYPEDEF || t == TOKEN_STRUCT || 
        t == TOKEN_UNION || t == TOKEN_ENUM) {
        declaracao();
        lista_de_declaracoes();
    }
    // epsilon aceita
}

void declaracao()
{
    int t = token_atual_token();
    if (t == TOKEN_TYPEDEF || t == TOKEN_STRUCT || t == TOKEN_UNION || t == TOKEN_ENUM) {
        declaracao_de_tipo();
    }
    else if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID || t == TOKEN_IDENTIFICADOR) {
        EntradaTabela *lookahead = token_atual->prox;
        if (lookahead != NULL && lookahead->token == TOKEN_IDENTIFICADOR) {
            lookahead = lookahead->prox;
            if (lookahead != NULL && lookahead->token == TOKEN_ABRE_PARENTESES) {
                declaracao_de_funcao();
                return;
            }
        }
        declaracao_de_variavel();
    }
    else {
        printf("%s:%d:%d: Erro sintático na declaracao, %s não esperado\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               token_atual ? token_atual->token_name : "NULL");
        total_erros++;
        while (token_atual != NULL && 
               token_atual_token() != TOKEN_PONTO_VIRGULA && 
               token_atual_token() != TOKEN_FECHA_CHAVES && 
               token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
        if (token_atual != NULL && token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
    }
}

void declaracao_de_tipo()
{
    int t = token_atual_token();
    if (t == TOKEN_TYPEDEF) {
        casa_token(TOKEN_TYPEDEF);
        tipo();
        casa_token(TOKEN_IDENTIFICADOR);
        casa_token(TOKEN_PONTO_VIRGULA);
    }
    else if (t == TOKEN_STRUCT) {
        casa_token(TOKEN_STRUCT);
        casa_token(TOKEN_IDENTIFICADOR);
        casa_token(TOKEN_ABRE_CHAVES);
        lista_de_declaracoes_de_campo();
        casa_token(TOKEN_FECHA_CHAVES);
        casa_token(TOKEN_PONTO_VIRGULA);
    }
    else if (t == TOKEN_UNION) {
        casa_token(TOKEN_UNION);
        casa_token(TOKEN_IDENTIFICADOR);
        casa_token(TOKEN_ABRE_CHAVES);
        lista_de_declaracoes_de_campo();
        casa_token(TOKEN_FECHA_CHAVES);
        casa_token(TOKEN_PONTO_VIRGULA);
    }
    else if (t == TOKEN_ENUM) {
        casa_token(TOKEN_ENUM);
        casa_token(TOKEN_IDENTIFICADOR);
        casa_token(TOKEN_ABRE_CHAVES);
        lista_de_valores_enum();
        casa_token(TOKEN_FECHA_CHAVES);
        casa_token(TOKEN_PONTO_VIRGULA);
    }
}

void lista_de_declaracoes_de_campo()
{
    while (token_atual_token() == TOKEN_INT || token_atual_token() == TOKEN_FLOAT ||
           token_atual_token() == TOKEN_CHAR || token_atual_token() == TOKEN_VOID ||
           token_atual_token() == TOKEN_IDENTIFICADOR) {
        declaracao_de_variavel();
    }
}

void lista_de_valores_enum()
{
    casa_token(TOKEN_IDENTIFICADOR);
    if (token_atual_token() == TOKEN_ATRIBUICAO) {
        casa_token(TOKEN_ATRIBUICAO);
        casa_token(TOKEN_CONSTANTE_INT);
    }
    while (token_atual_token() == TOKEN_VIRGULA) {
        casa_token(TOKEN_VIRGULA);
        casa_token(TOKEN_IDENTIFICADOR);
        if (token_atual_token() == TOKEN_ATRIBUICAO) {
            casa_token(TOKEN_ATRIBUICAO);
            casa_token(TOKEN_CONSTANTE_INT);
        }
    }
}

void modificador()
{
    int t = token_atual_token();
    if (t == TOKEN_STATIC || t == TOKEN_EXTERN || t == TOKEN_CONST || t == TOKEN_VOLATILE) {
        casa_token(t);
    }
}

void declaracao_de_variavel()
{
    modificador();
    tipo();
    lista_de_identificadores_com_inicializacao();
    casa_token(TOKEN_PONTO_VIRGULA);
}

void lista_de_identificadores_com_inicializacao()
{
    identificador_com_vetor_e_inicializacao();
    while (token_atual_token() == TOKEN_VIRGULA) {
        casa_token(TOKEN_VIRGULA);
        identificador_com_vetor_e_inicializacao();
    }
}

void identificador_com_vetor_e_inicializacao()
{
    casa_token(TOKEN_IDENTIFICADOR);
    vetor();
    if (token_atual_token() == TOKEN_ATRIBUICAO) {
        casa_token(TOKEN_ATRIBUICAO);
        if (token_atual_token() == TOKEN_ABRE_CHAVES) {
            casa_token(TOKEN_ABRE_CHAVES);
            lista_de_expressoes();
            casa_token(TOKEN_FECHA_CHAVES);
        } else {
            expressao();
        }
    }
}

void lista_de_expressoes()
{
    if (token_atual_token() != TOKEN_FECHA_CHAVES) {
        expressao();
        while (token_atual_token() == TOKEN_VIRGULA) {
            casa_token(TOKEN_VIRGULA);
            expressao();
        }
    }
}

void declaracao_de_funcao()
{
    tipo();
    casa_token(TOKEN_IDENTIFICADOR);
    casa_token(TOKEN_ABRE_PARENTESES);
    parametros();
    casa_token(TOKEN_FECHA_PARENTESES);
    bloco();
}

void parametros()
{
    if (token_atual_token() == TOKEN_FECHA_PARENTESES) {
        return;
    }
    lista_de_parametros();
    if (token_atual_token() == TOKEN_VIRGULA) {
        casa_token(TOKEN_VIRGULA);
        casa_token(TOKEN_VARARG); // Suporte a '...'
    }
}

void lista_de_parametros()
{
    parametro();
    while (token_atual_token() == TOKEN_VIRGULA) {
        casa_token(TOKEN_VIRGULA);
        parametro();
    }
}

void parametro()
{
    tipo();
    while (token_atual_token() == TOKEN_OP_MUL) { // Suporte a múltiplos '*'
        casa_token(TOKEN_OP_MUL);
    }
    casa_token(TOKEN_IDENTIFICADOR);
    vetor();
}

void tipo()
{
    int t = token_atual_token();
    if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID || t == TOKEN_IDENTIFICADOR) {
        casa_token(t);
    } else {
        printf("%s:%d:%d: Erro sintático: tipo esperado, %s não esperado\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               token_atual ? token_atual->token_name : "NULL");
        total_erros++;
        while (token_atual != NULL && 
               token_atual_token() != TOKEN_PONTO_VIRGULA && 
               token_atual_token() != TOKEN_FECHA_CHAVES && 
               token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
        if (token_atual != NULL && token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
    }
}

void bloco()
{
    casa_token(TOKEN_ABRE_CHAVES);
    lista_de_declaracoes_e_comandos();
    casa_token(TOKEN_FECHA_CHAVES);
}

void lista_de_declaracoes_e_comandos()
{
    int t = token_atual_token();
    while (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID ||
           t == TOKEN_IDENTIFICADOR || t == TOKEN_PONTO_VIRGULA || t == TOKEN_IF ||
           t == TOKEN_WHILE || t == TOKEN_FOR || t == TOKEN_DO || t == TOKEN_SWITCH ||
           t == TOKEN_RETURN || t == TOKEN_BREAK || t == TOKEN_CONTINUE || 
           t == TOKEN_ABRE_CHAVES || t == TOKEN_PRE_PROCESSADOR) {
        if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID || t == TOKEN_IDENTIFICADOR) {
            EntradaTabela *lookahead = token_atual->prox;
            if (lookahead != NULL && (lookahead->token == TOKEN_IDENTIFICADOR || lookahead->token == TOKEN_OP_MUL)) {
                declaracao_de_variavel();
            } else {
                comando();
            }
        } else {
            comando();
        }
        t = token_atual_token();
    }
}

void comando()
{
    int t = token_atual_token();
    if (t == TOKEN_IDENTIFICADOR || t == TOKEN_PONTO_VIRGULA) {
        comando_expressao();
    } else if (t == TOKEN_ABRE_CHAVES) {
        comando_composto();
    } else if (t == TOKEN_IF) {
        comando_if();
    } else if (t == TOKEN_WHILE) {
        comando_while();
    } else if (t == TOKEN_FOR) {
        comando_for();
    } else if (t == TOKEN_DO) {
        comando_do_while();
    } else if (t == TOKEN_SWITCH) {
        comando_switch();
    } else if (t == TOKEN_RETURN) {
        comando_return();
    } else if (t == TOKEN_BREAK) {
        comando_break();
    } else if (t == TOKEN_CONTINUE) {
        comando_continue();
    } else if (t == TOKEN_PRE_PROCESSADOR) {
        comando_preprocessador();
    } else {
        printf("%s:%d:%d: Erro sintático do comando, %s não esperado\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               token_atual ? token_atual->token_name : "NULL");
        total_erros++;
        while (token_atual != NULL && 
               token_atual_token() != TOKEN_PONTO_VIRGULA && 
               token_atual_token() != TOKEN_FECHA_CHAVES && 
               token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
        if (token_atual != NULL && token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
    }
}

void comando_expressao()
{
    if (token_atual_token() == TOKEN_PONTO_VIRGULA) {
        casa_token(TOKEN_PONTO_VIRGULA);
    } else {
        expressao();
        casa_token(TOKEN_PONTO_VIRGULA);
    }
}

void comando_composto()
{
    bloco();
}

void comando_if()
{
    casa_token(TOKEN_IF);
    casa_token(TOKEN_ABRE_PARENTESES);
    expressao();
    casa_token(TOKEN_FECHA_PARENTESES);
    comando();
    if (token_atual_token() == TOKEN_ELSE) {
        casa_token(TOKEN_ELSE);
        comando();
    }
}

void comando_while()
{
    casa_token(TOKEN_WHILE);
    casa_token(TOKEN_ABRE_PARENTESES);
    expressao();
    casa_token(TOKEN_FECHA_PARENTESES);
    comando();
}

void comando_for()
{
    casa_token(TOKEN_FOR);
    casa_token(TOKEN_ABRE_PARENTESES);
    if (token_atual_token() != TOKEN_PONTO_VIRGULA) {
        expressao();
    }
    casa_token(TOKEN_PONTO_VIRGULA);
    if (token_atual_token() != TOKEN_PONTO_VIRGULA) {
        expressao();
    }
    casa_token(TOKEN_PONTO_VIRGULA);
    if (token_atual_token() != TOKEN_FECHA_PARENTESES) {
        expressao();
    }
    casa_token(TOKEN_FECHA_PARENTESES);
    comando();
}

void comando_do_while()
{
    casa_token(TOKEN_DO);
    comando();
    casa_token(TOKEN_WHILE);
    casa_token(TOKEN_ABRE_PARENTESES);
    expressao();
    casa_token(TOKEN_FECHA_PARENTESES);
    casa_token(TOKEN_PONTO_VIRGULA);
}

void comando_switch()
{
    casa_token(TOKEN_SWITCH);
    casa_token(TOKEN_ABRE_PARENTESES);
    expressao();
    casa_token(TOKEN_FECHA_PARENTESES);
    casa_token(TOKEN_ABRE_CHAVES);
    lista_de_casos();
    casa_token(TOKEN_FECHA_CHAVES);
}

void lista_de_casos()
{
    while (token_atual_token() == TOKEN_CASE || token_atual_token() == TOKEN_DEFAULT) {
        if (token_atual_token() == TOKEN_CASE) {
            casa_token(TOKEN_CASE);
            if (token_atual_token() == TOKEN_CONSTANTE_INT || 
                token_atual_token() == TOKEN_CONSTANTE_CHAR ||
                token_atual_token() == TOKEN_TRUE || 
                token_atual_token() == TOKEN_FALSE) {
                casa_token(token_atual_token());
            } else {
                printf("%s:%d:%d: Erro sintático: constante esperada em case, %s não esperado\n",
                       nome_arquivo,
                       token_atual ? token_atual->linha : -1,
                       token_atual ? token_atual->coluna : -1,
                       token_atual ? token_atual->token_name : "NULL");
                total_erros++;
            }
            casa_token(TOKEN_DOIS_PONTOS);
        } else {
            casa_token(TOKEN_DEFAULT);
            casa_token(TOKEN_DOIS_PONTOS);
        }
        lista_de_declaracoes_e_comandos();
    }
}

void comando_preprocessador()
{
    casa_token(TOKEN_PRE_PROCESSADOR);
    if (token_atual_token() == TOKEN_STRING_LITERAL) {
        casa_token(TOKEN_STRING_LITERAL); // Para #include <...>
    } else if (token_atual_token() == TOKEN_IDENTIFICADOR) {
        casa_token(TOKEN_IDENTIFICADOR); // Para #define, #ifdef, etc.
        // Avança até o fim da linha
        while (token_atual != NULL && token_atual_token() != TOKEN_NOVA_LINHA && 
               token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
        if (token_atual != NULL && token_atual_token() == TOKEN_NOVA_LINHA) {
            casa_token(TOKEN_NOVA_LINHA);
        }
    }
}

void comando_return()
{
    casa_token(TOKEN_RETURN);
    if (token_atual_token() != TOKEN_PONTO_VIRGULA) {
        expressao();
    }
    casa_token(TOKEN_PONTO_VIRGULA);
}

void comando_break()
{
    casa_token(TOKEN_BREAK);
    casa_token(TOKEN_PONTO_VIRGULA);
}

void comando_continue()
{
    casa_token(TOKEN_CONTINUE);
    casa_token(TOKEN_PONTO_VIRGULA);
}

void expressao()
{
    expressao_atribuicao();
}

void expressao_atribuicao()
{
    if (token_atual_token() == TOKEN_IDENTIFICADOR) {
        EntradaTabela *lookahead = token_atual->prox;
        if (lookahead != NULL && lookahead->token == TOKEN_ATRIBUICAO) {
            casa_token(TOKEN_IDENTIFICADOR);
            casa_token(TOKEN_ATRIBUICAO);
            expressao();
            return;
        }
    }
    expressao_condicional();
}

void expressao_condicional()
{
    expressao_logica_ou();
    if (token_atual_token() == TOKEN_QUESTION) {
        casa_token(TOKEN_QUESTION);
        expressao();
        casa_token(TOKEN_DOIS_PONTOS);
        expressao();
    }
}

void expressao_logica_ou()
{
    expressao_logica_e();
    while (token_atual_token() == TOKEN_OP_OR_LOGICO) {
        casa_token(TOKEN_OP_OR_LOGICO);
        expressao_logica_e();
    }
}

void expressao_logica_e()
{
    expressao_igualdade();
    while (token_atual_token() == TOKEN_OP_AND_LOGICO) {
        casa_token(TOKEN_OP_AND_LOGICO);
        expressao_igualdade();
    }
}

void expressao_igualdade()
{
    expressao_relacional();
    while (token_atual_token() == TOKEN_OP_IGUAL || token_atual_token() == TOKEN_OP_DIFERENTE) {
        casa_token(token_atual_token());
        expressao_relacional();
    }
}

void expressao_relacional()
{
    expressao_bitwise();
    while (token_atual_token() == TOKEN_OP_MENOR || token_atual_token() == TOKEN_OP_MAIOR ||
           token_atual_token() == TOKEN_OP_MENOR_IGUAL || token_atual_token() == TOKEN_OP_MAIOR_IGUAL) {
        casa_token(token_atual_token());
        expressao_bitwise();
    }
}

void expressao_bitwise()
{
    expressao_aditiva();
    while (token_atual_token() == TOKEN_OP_AND_BITWISE || token_atual_token() == TOKEN_OP_OR_BITWISE ||
           token_atual_token() == TOKEN_OP_XOR || token_atual_token() == TOKEN_OP_LSHIFT || 
           token_atual_token() == TOKEN_OP_RSHIFT) {
        casa_token(token_atual_token());
        expressao_aditiva();
    }
}

void expressao_aditiva()
{
    expressao_multiplicativa();
    while (token_atual_token() == TOKEN_OP_SOMA || token_atual_token() == TOKEN_OP_SUB) {
        casa_token(token_atual_token());
        expressao_multiplicativa();
    }
}

void expressao_multiplicativa()
{
    expressao_unaria();
    while (token_atual_token() == TOKEN_OP_MUL || token_atual_token() == TOKEN_OP_DIV ||
           token_atual_token() == TOKEN_OP_MOD) {
        casa_token(token_atual_token());
        expressao_unaria();
    }
}

void expressao_unaria()
{
    int t = token_atual_token();
    if (t == TOKEN_OP_SOMA || t == TOKEN_OP_SUB || t == TOKEN_OP_NOT_LOGICO ||
        t == TOKEN_OP_REF || t == TOKEN_OP_MUL || t == TOKEN_OP_NOT_BITWISE) {
        casa_token(t);
        expressao_unaria();
    } else if (t == TOKEN_OP_INCREMENTO || t == TOKEN_OP_DECREMENTO) {
        casa_token(t);
        unario();
    } else {
        unario();
        t = token_atual_token();
        if (t == TOKEN_OP_INCREMENTO || t == TOKEN_OP_DECREMENTO) {
            casa_token(t);
        }
    }
}

void unario()
{
    int t = token_atual_token();
    if (t == TOKEN_IDENTIFICADOR) {
        casa_token(TOKEN_IDENTIFICADOR);
        if (token_atual_token() == TOKEN_ABRE_PARENTESES) {
            casa_token(TOKEN_ABRE_PARENTESES);
            lista_de_argumentos();
            casa_token(TOKEN_FECHA_PARENTESES);
        } else if (token_atual_token() == TOKEN_ABRE_COLCHETES) {
            casa_token(TOKEN_ABRE_COLCHETES);
            expressao();
            casa_token(TOKEN_FECHA_COLCHETES);
        }
    } else if (t == TOKEN_CONSTANTE_INT || t == TOKEN_CONSTANTE_FLOAT || 
               t == TOKEN_CONSTANTE_CHAR || t == TOKEN_STRING_LITERAL ||
               t == TOKEN_TRUE || t == TOKEN_FALSE) {
        casa_token(t);
    } else if (t == TOKEN_ABRE_PARENTESES) {
        casa_token(TOKEN_ABRE_PARENTESES);
        expressao();
        casa_token(TOKEN_FECHA_PARENTESES);
    } else {
        printf("%s:%d:%d: Erro sintático em unario, token %d (%s) inesperado\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               t,
               token_atual ? token_atual->lexema : "NULL");
        total_erros++;
        while (token_atual != NULL && 
               token_atual_token() != TOKEN_PONTO_VIRGULA && 
               token_atual_token() != TOKEN_FECHA_CHAVES && 
               token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
        if (token_atual != NULL && token_atual_token() != TOKEN_EOF) {
            avancar_token();
        }
    }
}

void lista_de_argumentos()
{
    if (token_atual_token() == TOKEN_FECHA_PARENTESES) {
        return;
    }
    expressao();
    while (token_atual_token() == TOKEN_VIRGULA) {
        casa_token(TOKEN_VIRGULA);
        expressao();
    }
}