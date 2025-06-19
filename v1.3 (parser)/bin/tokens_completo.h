#ifndef TOKENS_H
#define TOKENS_H

// ======== PALAVRAS-CHAVE =========
#define TOKEN_BREAK            2
#define TOKEN_CASE             3
#define TOKEN_CHAR             4
#define TOKEN_CONST            5
#define TOKEN_CONTINUE         6
#define TOKEN_DEFAULT          7
#define TOKEN_DO               8
#define TOKEN_ELSE             10
#define TOKEN_ENUM             11
#define TOKEN_EXTERN           12
#define TOKEN_FLOAT            13
#define TOKEN_FOR              14
#define TOKEN_IF               16
#define TOKEN_INT              18
#define TOKEN_RETURN           22
#define TOKEN_STATIC           26
#define TOKEN_STRUCT           27
#define TOKEN_SWITCH           28
#define TOKEN_TYPEDEF          29
#define TOKEN_UNION            30
#define TOKEN_VOID             32
#define TOKEN_VOLATILE         33
#define TOKEN_WHILE            34
#define TOKEN_TRUE             38
#define TOKEN_FALSE            39

// ======== IDENTIFICADORES E LITERAIS ========
#define TOKEN_IDENTIFICADOR       100
#define TOKEN_CONSTANTE_INT       101
#define TOKEN_CONSTANTE_FLOAT     102
#define TOKEN_CONSTANTE_CHAR      103
#define TOKEN_STRING_LITERAL      104

// ======== OPERADORES ARITMÉTICOS ========
#define TOKEN_OP_SOMA             200  // +
#define TOKEN_OP_SUB              201  // -
#define TOKEN_OP_MUL              202  // *
#define TOKEN_OP_DIV              203  // /
#define TOKEN_OP_MOD              204  // %
#define TOKEN_OP_INCREMENTO       205  // ++
#define TOKEN_OP_DECREMENTO       206  // --

// ======== OPERADORES RELACIONAIS ========
#define TOKEN_OP_IGUAL            210  // ==
#define TOKEN_OP_DIFERENTE        211  // !=
#define TOKEN_OP_MAIOR            212  // >
#define TOKEN_OP_MENOR            213  // <
#define TOKEN_OP_MAIOR_IGUAL      214  // >=
#define TOKEN_OP_MENOR_IGUAL      215  // <=

// ======== OPERADORES LÓGICOS ========
#define TOKEN_OP_AND_LOGICO       220  // &&
#define TOKEN_OP_OR_LOGICO        221  // ||    
#define TOKEN_OP_NOT_LOGICO       222  // !

// ======== OPERADORES BIT A BIT ========
#define TOKEN_OP_AND_BITWISE      230  // &
#define TOKEN_OP_OR_BITWISE       231  // |
#define TOKEN_OP_XOR              232  // ^
#define TOKEN_OP_NOT_BITWISE      233  // ~
#define TOKEN_OP_LSHIFT           234  // <<
#define TOKEN_OP_RSHIFT           235  // >>

// ======== OPERADORES DE ATRIBUIÇÃO ========
#define TOKEN_ATRIBUICAO          240  // =

// ======== OUTROS OPERADORES ========
#define TOKEN_QUESTION            260  // ?
#define TOKEN_DOIS_PONTOS         261  // :
#define TOKEN_OP_REF              262  // & (referência)
#define TOKEN_OP_DEREF            263  // * (dereferência)

// ======== PONTUAÇÃO / DELIMITADORES ========
#define TOKEN_PONTO_VIRGULA       270  // ;
#define TOKEN_VIRGULA             271  // ,
#define TOKEN_ABRE_PARENTESES     272  // (
#define TOKEN_FECHA_PARENTESES    273  // )
#define TOKEN_ABRE_CHAVES         274  // {
#define TOKEN_FECHA_CHAVES        275  // }
#define TOKEN_ABRE_COLCHETES      276  // [
#define TOKEN_FECHA_COLCHETES     277  // ]
#define TOKEN_DOIS_PONTOS         278  // : (redefinido, mantido para compatibilidade)

// ======== OUTROS ========
#define TOKEN_PRE_PROCESSADOR     300  // #define, #include, etc.
#define TOKEN_VARARG              301  // ...
#define TOKEN_COMENTARIO          290  // /*...*/ ou //
#define TOKEN_ESPACO_EM_BRANCO    291  // espaço, tab, \n (geralmente ignorado)
#define TOKEN_NOVA_LINHA          292  // \n (especificamente para diretivas de pré-processador)
#define TOKEN_DESCONHECIDO        666  // caractere inválido 
#define TOKEN_EOF                 999  // fim de arquivo

#endif // TOKENS_H