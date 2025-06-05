#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H

#include "../bin/analisador_lexico.h"

// Ponteiro para o token atual no parser
extern EntradaTabela *token_atual;

// Protótipos das funções de análise sintática
void programa();
void lista_de_declaracoes();
void declaracao();
void declaracao_de_variavel();
void declaracao_de_funcao();
void declaracao_de_tipo();
void parametros();
void lista_de_parametros();
void parametro();
void tipo();
void lista_de_identificadores();
void bloco();
void lista_de_comandos();
void comando();
void comando_expressao();
void comando_composto();
void comando_if();
void comando_while();
void comando_for();
void comando_return();
void comando_break();
void comando_continue();
void expressao();
void expressao_atribuicao();
void expressao_logica_ou();
void expressao_logica_e();
void expressao_igualdade();
void expressao_relacional();
void expressao_aditiva();
void expressao_multiplicativa();
void expressao_unaria();
void unario();
void lista_de_argumentos();
void casa_token(int esperado);
int token_atual_token();
void avancar_token();

#endif // ANALISADOR_SINTATICO_H