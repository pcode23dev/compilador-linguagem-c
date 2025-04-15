#ifndef TOKENS_H
#define TOKENS_H

// Palavras-chave
#define TOKEN_IF              1
#define TOKEN_ELSE            2
#define TOKEN_WHILE           3
#define TOKEN_FOR             4
#define TOKEN_RETURN          5
#define TOKEN_INT             6
#define TOKEN_FLOAT           7
#define TOKEN_CHAR            8
#define TOKEN_VOID            9

// Identificadores e Literais
#define TOKEN_IDENTIFICADOR   10
#define TOKEN_CONSTANTE_INT   11
#define TOKEN_CONSTANTE_FLOAT 12
#define TOKEN_CONSTANTE_CHAR  13
#define TOKEN_STRING_LITERAL  14

// Operadores aritméticos
#define TOKEN_OP_SOMA         20  // +
#define TOKEN_OP_SUB          21  // -
#define TOKEN_OP_MUL          22  // *
#define TOKEN_OP_DIV          23  // /
#define TOKEN_OP_MOD          24  // %

// Operadores relacionais
#define TOKEN_OP_IGUAL        25  // ==
#define TOKEN_OP_DIF          26  // !=
#define TOKEN_OP_MAIOR        27  // >
#define TOKEN_OP_MENOR        28  // <
#define TOKEN_OP_MAIOR_IGUAL  29  // >=
#define TOKEN_OP_MENOR_IGUAL  30  // <=

// Operadores lógicos
#define TOKEN_OP_AND          31  // &&
#define TOKEN_OP_OR           32  // ||
#define TOKEN_OP_NOT          33  // !

// Atribuição
#define TOKEN_ATRIBUICAO      34  // =

// Pontuação
#define TOKEN_PONTO_VIRGULA   40  // ;
#define TOKEN_VIRGULA         41  // ,
#define TOKEN_PONTO           42  // .
#define TOKEN_DOIS_PONTOS     43  // :
#define TOKEN_ASPA_SIMPL      44  // '
#define TOKEN_ASPA_DUPLA      45  // "

// Delimitadores
#define TOKEN_ABRE_PARENTESE  50  // (
#define TOKEN_FECHA_PARENTESE 51  // )
#define TOKEN_ABRE_CHAVE      52  // {
#define TOKEN_FECHA_CHAVE     53  // }
#define TOKEN_ABRE_COLCHETE   54  // [
#define TOKEN_FECHA_COLCHETE  55  // ]

// Fim de arquivo
#define TOKEN_EOF             99

#endif
