#include <stdio.h>
#include <stdlib.h>
#include "../bin/analisador_sintatico.h"

EntradaTabela *token_atual = NULL;
extern char *nome_arquivo;

// Nova variável global para contar erros
int total_erros = 0;

int token_atual_token()
{
    if (token_atual == NULL)
    {
        return TOKEN_EOF;
    }
    return token_atual->token;
}

void avancar_token()
{
    if (token_atual != NULL)
        token_atual = token_atual->prox;
}

void casa_token(int esperado) {
    int atual = token_atual_token();
    if (atual == esperado) {
        avancar_token();
    } else {
        // Registra o erro
        // Se token_name estiver preenchido, usa ele; caso contrário, mostra o valor numérico
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

// ------------------ análise sintática  ----------------------

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

    if (t == TOKEN_PRE_PROCESSADOR)
    {
        casa_token(TOKEN_PRE_PROCESSADOR);
        lista_de_declaracoes();
        return;
    }

    if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID || t == TOKEN_TYPEDEF || t == TOKEN_IDENTIFICADOR)
    {
        declaracao();
        lista_de_declaracoes();
    }
    // epsilon aceita
}

void declaracao()
{
    if (token_atual_token() == TOKEN_TYPEDEF)
    {
        declaracao_de_tipo();
    }
    else if (token_atual_token() == TOKEN_INT || token_atual_token() == TOKEN_FLOAT ||
             token_atual_token() == TOKEN_CHAR || token_atual_token() == TOKEN_VOID || token_atual_token() == TOKEN_IDENTIFICADOR)
    {
        EntradaTabela *lookahead = token_atual->prox;
        if (lookahead != NULL && lookahead->token == TOKEN_IDENTIFICADOR)
        {
            lookahead = lookahead->prox;
            if (lookahead != NULL && lookahead->token == TOKEN_ABRE_PARENTESES)
            {
                declaracao_de_funcao();
                return;
            }
        }
        declaracao_de_variavel();
    }
    else
    {
        printf("%s:%d:%d: Erro sintático na declaracao, %s não esperado\n",
               nome_arquivo,
               token_atual ? token_atual->linha : -1,
               token_atual ? token_atual->coluna : -1,
               token_atual ? token_atual->token_name : "NULL");
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

void declaracao_de_tipo()
{
    casa_token(TOKEN_TYPEDEF);
    tipo();
    printf("Antes de casar IDENTIFICADOR 1: token atual = %d (%s)\n", token_atual_token(), token_atual ? token_atual->lexema : "NULL");
    casa_token(TOKEN_IDENTIFICADOR);
    casa_token(TOKEN_PONTO_VIRGULA);
}

void vetor()
{
    if (token_atual_token() == TOKEN_ABRE_COLCHETES)
    {
        casa_token(TOKEN_ABRE_COLCHETES);
        if (token_atual_token() != TOKEN_FECHA_COLCHETES)
        {
            expressao();
        }
        casa_token(TOKEN_FECHA_COLCHETES);
    }
}

void declaracao_de_variavel()
{
    tipo();
    lista_de_identificadores_com_inicializacao();
    casa_token(TOKEN_PONTO_VIRGULA);
}

void lista_de_identificadores_com_inicializacao()
{
    identificador_com_vetor_e_inicializacao();

    while (token_atual_token() == TOKEN_VIRGULA)
    {
        casa_token(TOKEN_VIRGULA);
        identificador_com_vetor_e_inicializacao();
    }
}

void identificador_com_vetor_e_inicializacao()
{
    casa_token(TOKEN_IDENTIFICADOR);
    vetor();

    if (token_atual_token() == TOKEN_ATRIBUICAO)
    {
        casa_token(TOKEN_ATRIBUICAO);
        expressao();
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
    if (token_atual_token() == TOKEN_FECHA_PARENTESES)
    {
        return;
    }
    else
    {
        lista_de_parametros();
    }
}

void lista_de_parametros()
{
    parametro();
    while (token_atual_token() == TOKEN_VIRGULA)
    {
        casa_token(TOKEN_VIRGULA);
        parametro();
    }
}

void parametro()
{
    tipo();

    if (token_atual_token() == TOKEN_OP_MUL)
    {
        casa_token(TOKEN_OP_MUL);
    }

    casa_token(TOKEN_IDENTIFICADOR);
    vetor();
}

void tipo()
{
    int t = token_atual_token();
    if (t == TOKEN_INT)
        casa_token(TOKEN_INT);
    else if (t == TOKEN_FLOAT)
        casa_token(TOKEN_FLOAT);
    else if (t == TOKEN_CHAR)
        casa_token(TOKEN_CHAR);
    else if (t == TOKEN_VOID)
        casa_token(TOKEN_VOID);
    else if (t == TOKEN_IDENTIFICADOR){
        printf("Antes de casar IDENTIFICADOR 5: token atual = %d (%s)\n", token_atual_token(), token_atual ? token_atual->lexema : "NULL");
        casa_token(TOKEN_IDENTIFICADOR);
    }
    else
    {
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

void lista_de_identificadores()
{
    printf("Antes de casar IDENTIFICADOR 6: token atual = %d (%s)\n", token_atual_token(), token_atual ? token_atual->lexema : "NULL");
    casa_token(TOKEN_IDENTIFICADOR);
    while (token_atual_token() == TOKEN_VIRGULA)
    {
        casa_token(TOKEN_VIRGULA);
        printf("Antes de casar IDENTIFICADOR 7: token atual = %d (%s)\n", token_atual_token(), token_atual ? token_atual->lexema : "NULL");
        casa_token(TOKEN_IDENTIFICADOR);
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
           t == TOKEN_WHILE || t == TOKEN_FOR || t == TOKEN_RETURN || t == TOKEN_BREAK ||
           t == TOKEN_CONTINUE || t == TOKEN_ABRE_CHAVES)
    {
        if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID || t == TOKEN_IDENTIFICADOR)
        {
            EntradaTabela *lookahead = token_atual->prox;
            if (lookahead != NULL && (lookahead->token == TOKEN_IDENTIFICADOR || lookahead->token == TOKEN_OP_MUL))
            {
                declaracao_de_variavel();
            }
            else
            {
                comando();
            }
        }
        else
        {
            comando();
        }
        t = token_atual_token();
    }
}

void lista_de_comandos()
{
    int t = token_atual_token();

    while (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID ||
           t == TOKEN_IDENTIFICADOR || t == TOKEN_PONTO_VIRGULA || t == TOKEN_IF ||
           t == TOKEN_WHILE || t == TOKEN_FOR || t == TOKEN_RETURN || t == TOKEN_BREAK ||
           t == TOKEN_CONTINUE || t == TOKEN_ABRE_CHAVES)
    {
        if (t == TOKEN_INT || t == TOKEN_FLOAT || t == TOKEN_CHAR || t == TOKEN_VOID)
        {
            declaracao_de_variavel();
        }
        else if (t == TOKEN_IDENTIFICADOR)
        {
            EntradaTabela *lookahead = token_atual->prox;
            if (lookahead != NULL && (lookahead->token == TOKEN_IDENTIFICADOR || lookahead->token == TOKEN_ATRIBUICAO))
            {
                declaracao_de_variavel();
            }
            else
            {
                comando();
            }
        }
        else
        {
            comando();
        }
        t = token_atual_token();
    }
}

void comando()
{
    int t = token_atual_token();
    if (t == TOKEN_IDENTIFICADOR || t == TOKEN_PONTO_VIRGULA)
        comando_expressao();
    else if (t == TOKEN_ABRE_CHAVES)
        comando_composto();
    else if (t == TOKEN_IF)
        comando_if();
    else if (t == TOKEN_WHILE)
        comando_while();
    else if (t == TOKEN_FOR)
        comando_for();
    else if (t == TOKEN_RETURN)
        comando_return();
    else if (t == TOKEN_BREAK)
        comando_break();
    else if (t == TOKEN_CONTINUE)
        comando_continue();
    else
    {
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
    if (token_atual_token() == TOKEN_PONTO_VIRGULA)
    {
        casa_token(TOKEN_PONTO_VIRGULA);
    }
    else
    {
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
    if (token_atual_token() == TOKEN_ELSE)
    {
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
    if (token_atual_token() != TOKEN_PONTO_VIRGULA)
        expressao();
    casa_token(TOKEN_PONTO_VIRGULA);
    if (token_atual_token() != TOKEN_PONTO_VIRGULA)
        expressao();
    casa_token(TOKEN_PONTO_VIRGULA);
    if (token_atual_token() != TOKEN_FECHA_PARENTESES)
        expressao();
    casa_token(TOKEN_FECHA_PARENTESES);
    comando();
}

void comando_return()
{
    casa_token(TOKEN_RETURN);
    if (token_atual_token() != TOKEN_PONTO_VIRGULA)
        expressao();
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
    if (token_atual_token() == TOKEN_IDENTIFICADOR)
    {
        EntradaTabela *lookahead = token_atual->prox;
        if (lookahead != NULL && lookahead->token == TOKEN_ATRIBUICAO)
        {
            printf("Antes de casar IDENTIFICADOR 8: token atual = %d (%s)\n", token_atual_token(), token_atual ? token_atual->lexema : "NULL");
            casa_token(TOKEN_IDENTIFICADOR);
            casa_token(TOKEN_ATRIBUICAO);
            expressao();
            return;
        }
    }
    expressao_logica_ou();
}

void expressao_logica_ou()
{
    expressao_logica_e();
    while (token_atual_token() == TOKEN_OP_OR_LOGICO)
    {
        casa_token(TOKEN_OP_OR_LOGICO);
        expressao_logica_e();
    }
}

void expressao_logica_e()
{
    expressao_igualdade();
    while (token_atual_token() == TOKEN_OP_AND_LOGICO)
    {
        casa_token(TOKEN_OP_AND_LOGICO);
        expressao_igualdade();
    }
}

void expressao_igualdade()
{
    expressao_relacional();
    while (token_atual_token() == TOKEN_OP_IGUAL || token_atual_token() == TOKEN_OP_DIFERENTE)
    {
        if (token_atual_token() == TOKEN_OP_IGUAL)
            casa_token(TOKEN_OP_IGUAL);
        else
            casa_token(TOKEN_OP_DIFERENTE);
        expressao_relacional();
    }
}

void expressao_relacional()
{
    expressao_aditiva();
    while (token_atual_token() == TOKEN_OP_MENOR || token_atual_token() == TOKEN_OP_MAIOR ||
           token_atual_token() == TOKEN_OP_MENOR_IGUAL || token_atual_token() == TOKEN_OP_MAIOR_IGUAL)
    {
        int t = token_atual_token();
        casa_token(t);
        expressao_aditiva();
    }
}

void expressao_aditiva()
{
    expressao_multiplicativa();
    while (token_atual_token() == TOKEN_OP_SOMA || token_atual_token() == TOKEN_OP_SUB)
    {
        int t = token_atual_token();
        casa_token(t);
        expressao_multiplicativa();
    }
}

void expressao_multiplicativa()
{
    expressao_unaria();
    while (token_atual_token() == TOKEN_OP_MUL || token_atual_token() == TOKEN_OP_DIV ||
           token_atual_token() == TOKEN_OP_MOD)
    {
        int t = token_atual_token();
        casa_token(t);
        expressao_unaria();
    }
}

void expressao_unaria()
{
    int t = token_atual_token();
    if (t == TOKEN_OP_SOMA || t == TOKEN_OP_SUB || t == TOKEN_OP_NOT_LOGICO)
    {
        casa_token(t);
        expressao_unaria();
    }
    else if (t == TOKEN_OP_INCREMENTO || t == TOKEN_OP_DECREMENTO)
    {
        casa_token(t);
        unario();
    }
    else
    {
        unario();
        t = token_atual_token();
        if (t == TOKEN_OP_INCREMENTO || t == TOKEN_OP_DECREMENTO)
        {
            casa_token(t);
        }
    }
}

void unario()
{
    int t = token_atual_token();

    if (t == TOKEN_IDENTIFICADOR)
    {
        printf("Antes de casar IDENTIFICADOR 9: token atual = %d (%s)\n", token_atual_token(), token_atual ? token_atual->lexema : "NULL");
        casa_token(TOKEN_IDENTIFICADOR);
        if (token_atual_token() == TOKEN_ABRE_PARENTESES)
        {
            casa_token(TOKEN_ABRE_PARENTESES);
            lista_de_argumentos();
            casa_token(TOKEN_FECHA_PARENTESES);
        }
    }
    else if (t == TOKEN_CONSTANTE_INT || t == TOKEN_CONSTANTE_FLOAT || t == TOKEN_CONSTANTE_CHAR || t == TOKEN_STRING_LITERAL)
    {
        casa_token(t);
    }
    else if (t == TOKEN_ABRE_PARENTESES)
    {
        casa_token(TOKEN_ABRE_PARENTESES);
        expressao();
        casa_token(TOKEN_FECHA_PARENTESES);
    }
    else
    {
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
    if (token_atual_token() == TOKEN_FECHA_PARENTESES)
        return;

    expressao();

    while (token_atual_token() == TOKEN_VIRGULA)
    {
        casa_token(TOKEN_VIRGULA);
        expressao();
    }
}