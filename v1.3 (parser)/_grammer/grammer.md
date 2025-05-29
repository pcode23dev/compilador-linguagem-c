# Gramática de Linguagem C

> Gramática intermediária da minha linguagem C

___

## Estrutura do Programa

```c
<programa> ::= <lista_de_declaracoes>
```

___

## Declarações

```c
<lista_de_declaracoes> ::= <declaracao> <lista_de_declaracoes> | ε

<declaracao> ::= <declaracao_de_funcao> 
                | <declaracao_de_variavel> 
                | <declaracao_de_tipo>

<declaracao_de_variavel> ::= <tipo> <lista_de_identificadores> [<inicializacao>] ';'

<inicializacao> ::= '=' <expressao> | ε

<lista_de_identificadores> ::= <identificador> 
                            | <identificador> ',' <lista_de_identificadores>

<declaracao_de_funcao> ::= <tipo> <identificador> '(' <parametros> ')' <bloco>

<declaracao_de_tipo> ::= 'typedef' <tipo> <identificador> ';'

<parametros> ::= <lista_de_parametros> | ε

<lista_de_parametros> ::= <parametro> | <parametro> ',' <lista_de_parametros>

<parametro> ::= <tipo> <identificador> | <tipo> '*' <identificador> | <tipo> <identificador> '[' ']'

<tipo> ::= 'int' | 'float' | 'char' | 'void' | <identificador>
```

___

## Blocos e Comandos

```c
<bloco> ::= '{' <lista_de_comandos> '}'

<lista_de_comandos> ::= <comando> <lista_de_comandos> | ε

<comando> ::= <comando-expressao>
            | <comando-composto>
            | <comando-if>
            | <comando-while>
            | <comando-for>
            | <comando-return>
            | <comando-break>
            | <comando-continue>
            | <comando-preprocessador>

<comando_preprocessador> ::= '#' <identificador> <resto_linha>


<comando_expressao> ::= <expressao> ';' | ';'

<comando_composto> ::= <bloco>

<comando_if> ::= 'if' '(' <expressao> ')' <comando> [ 'else' <comando> ]

<comando_while> ::= 'while' '(' <expressao> ')' <comando>

<comando_for> ::= 'for' '(' <expressao_opcional> ';' <expressao_opcional> ';' <expressao_opcional> ')' <comando>

<comando_return> ::= 'return' <expressao_opcional> ';'

<comando_break> ::= 'break' ';'

<comando_continue> ::= 'continue' ';'

<expressao_opcional> ::= <expressao> | ε
```

___

## Expressões

```c
<expressao> ::= <expressao_atribuicao>

<expressao_atribuicao> ::= <unario> '=' <expressao> | <expressao_logica_ou>

<expressao_logica_ou> ::= <expressao_logica_e> { '||' <expressao_logica_e> }

<expressao_logica_e> ::= <expressao_igualdade> { '&&' <expressao_igualdade> }

<expressao_igualdade> ::= <expressao_relacional> { ('==' | '!=') <expressao_relacional> }

<expressao_relacional> ::= <expressao_aditiva> { ('<' | '>' | '<=' | '>=') <expressao_aditiva> }

<expressao_aditiva> ::= <expressao_multiplicativa> { ('+' | '-') <expressao_multiplicativa> }

<expressao_multiplicativa> ::= <expressao_unaria> { ('*' | '/' | '%') <expressao_unaria> }

<expressao_unaria> ::= <operador_unario> <expressao_unaria> | <operador_incremento> <unario> | <unario> <operador_incremento> | <unario>

<operador_unario> ::= '&' | '*' | '+' | '-' | '!' | '~'

<operador_incremento> ::= '++' | '--'

<unario> ::= <primario> | <unario> '[' <expressao> ']' | <unario> '(' <lista_de_argumentos> ')'

<lista_de_argumentos> ::= <expressao> | <expressao> ',' <lista_de_argumentos> | ε

<primario> ::= <identificador> | <constante> | <string> | '(' <expressao> ')'
```

___

## Elementos Léxicos

```c
<identificador> ::= ([a-zA-Z_]) [a-zA-Z0-9_]*

<constante> ::= <inteiro> | <flutuante> | <caractere>

<inteiro> ::= [0-9]+

<flutuante> ::= [0-9]+ '.' [0-9]+

<caractere> ::= '\'' . '\''

<string> ::= '"' { . } '"'

<comentario> ::= '/*' { . } '*/' | '//' { . } '\n'
```

___

## Observações

- Suporte a ponteiros, arrays, typedef, operadores unários, incremento/decremento, comandos for, break e continue.
- Strings e comentários incluídos nos elementos léxicos.
- Tipos definidos pelo usuário permitidos via typedef.
- Funções podem receber ponteiros e arrays como parâmetros.
- Expressões suportam chamadas de função, indexação de arrays e operadores unários.

