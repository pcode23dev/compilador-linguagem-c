#ifndef TOKENS_H
#define TOKENS_H

// ======== PALAVRAS-CHAVE =========
#define TOKEN_AUTO             1
#define TOKEN_BREAK            2
#define TOKEN_CASE             3
#define TOKEN_CHAR             4
#define TOKEN_CONST            5
#define TOKEN_CONTINUE         6
#define TOKEN_DEFAULT          7
#define TOKEN_DO               8
#define TOKEN_DOUBLE           9
#define TOKEN_ELSE             10
#define TOKEN_ENUM             11
#define TOKEN_EXTERN           12
#define TOKEN_FLOAT            13
#define TOKEN_FOR              14
#define TOKEN_GOTO             15
#define TOKEN_IF               16
#define TOKEN_INLINE           17
#define TOKEN_INT              18
#define TOKEN_LONG             19
#define TOKEN_REGISTER         20
#define TOKEN_RESTRICT         21
#define TOKEN_RETURN           22
#define TOKEN_SHORT            23
#define TOKEN_SIGNED           24
#define TOKEN_SIZEOF           25
#define TOKEN_STATIC           26
#define TOKEN_STRUCT           27
#define TOKEN_SWITCH           28
#define TOKEN_TYPEDEF          29
#define TOKEN_UNION            30
#define TOKEN_UNSIGNED         31
#define TOKEN_VOID             32
#define TOKEN_VOLATILE         33
#define TOKEN_WHILE            34
#define TOKEN_ALIGNAS          35
#define TOKEN_ALIGNOF          36
#define TOKEN_ATOMIC           37
#define TOKEN_BOOL             38
#define TOKEN_COMPLEX          39
#define TOKEN_GENERIC          40
#define TOKEN_IMAGINARY        41
#define TOKEN_NORETURN         42
#define TOKEN_STATIC_ASSERT    43
#define TOKEN_THREAD_LOCAL     44

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
#define TOKEN_OP_AND_BIT          230  // &
#define TOKEN_OP_OR_BIT           231  // |
#define TOKEN_OP_XOR_BIT          232  // ^
#define TOKEN_OP_COMPL_BIT        233  // ~
#define TOKEN_OP_SHIFT_ESQ        234  // <<
#define TOKEN_OP_SHIFT_DIR        235  // >>

// ======== OPERADORES DE ATRIBUIÇÃO ========
#define TOKEN_ATRIBUICAO          240  // =
#define TOKEN_ATRIB_SOMA          241  // +=
#define TOKEN_ATRIB_SUB           242  // -=
#define TOKEN_ATRIB_MUL           243  // *=
#define TOKEN_ATRIB_DIV           244  // /=
#define TOKEN_ATRIB_MOD           245  // %=
#define TOKEN_ATRIB_AND           246  // &=
#define TOKEN_ATRIB_OR            247  // |=
#define TOKEN_ATRIB_XOR           248  // ^=
#define TOKEN_ATRIB_SHIFT_ESQ     249  // <<=
#define TOKEN_ATRIB_SHIFT_DIR     250  // >>=

// ======== OUTROS OPERADORES ========
#define TOKEN_OP_CONDICIONAL      260  // ? :
#define TOKEN_OP_SIZEOF           261  // sizeof
#define TOKEN_OP_CAST             262  // (tipo)
#define TOKEN_OP_PONTO            263  // .
#define TOKEN_OP_SETA             264  // ->
#define TOKEN_OP_REFERENCIA       265  // &var
#define TOKEN_OP_DEREFERENCIA     266  // *ptr

// ======== PONTUAÇÃO / DELIMITADORES ========
#define TOKEN_PONTO_VIRGULA       270  // ;
#define TOKEN_VIRGULA             271  // ,
#define TOKEN_ABRE_PARENTESES     272  // (
#define TOKEN_FECHA_PARENTESES    273  // )
#define TOKEN_ABRE_CHAVES         274  // {
#define TOKEN_FECHA_CHAVES        275  // }
#define TOKEN_ABRE_COLCHETES      276  // [
#define TOKEN_FECHA_COLCHETES     277  // ]
#define TOKEN_DOIS_PONTOS         278  // :
#define TOKEN_ASPA_SIMPLES        279  // '
#define TOKEN_ASPA_DUPLA          280  // "
#define TOKEN_BARRA_INVERTIDA     281  // \

// ======== OUTROS ========
#define TOKEN_COMENTARIO          290  // /*...*/ ou //
#define TOKEN_ESPACO_EM_BRANCO    291  // espaço, tab, \n (geralmente ignorado)
#define TOKEN_DESCONHECIDO        292  // símbolo inválido
#define TOKEN_EOF                 999  // fim de arquivo

#endif
