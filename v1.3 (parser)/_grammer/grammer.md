```c
// Programa principal
<programa> ::= <lista_de_declaracoes>

// Lista de declarações globais
<lista_de_declaracoes> ::= <declaracao> <lista_de_declaracoes>
                        | ε

// Tipos de declarações
<declaracao> ::= <declaracao_de_funcao>
              | <declaracao_de_variavel>
              | <declaracao_de_tipo>

// Declaração de variável
<declaracao_de_variavel> ::= <tipo> <lista_de_identificadores_com_vetores> [<inicializacao>] ';'

<inicializacao> ::= '=' <expressao> | ε

// Lista de identificadores com possibilidade de vetores
<lista_de_identificadores_com_vetores> ::= <identificador> [ <vetor>]
                                        | <identificador> [ <vetor>] ',' <lista_de_identificadores_com_vetores>

<vetor> ::= '[' [<expressao_ou_vazio>] ']' | ε

// Declaração de função
<declaracao_de_funcao> ::= <tipo> <identificador> '(' <parametros> ')' <bloco>

// Declaração de novo tipo
<declaracao_de_tipo> ::= 'typedef' <tipo> <identificador> ';'

// Parâmetros de função
<parametros> ::= <lista_de_parametros>
              | ε

// Lista de parâmetros com vetores e ponteiros
<lista_de_parametros> ::= <parametro>
                      | <parametro> ',' <lista_de_parametros>

<parametro> ::= <tipo> <identificador> [ <vetor>]
             | <tipo> '*' <identificador>

// Tipos de dados
<tipo> ::= 'int'
        | 'float'
        | 'char'
        | 'void'
        | <identificador>

// Bloco de comandos e declarações
<bloco> ::= '{' <lista_de_declaracoes_e_comandos> '}'

<lista_de_declaracoes_e_comandos> ::= <declaracao_local> <lista_de_declaracoes_e_comandos>
                                   | <comando> <lista_de_declaracoes_e_comandos>
                                   | ε

<declaracao_local> ::= <declaracao_de_variavel>

// Comandos
<comando> ::= <comando_expressao>
           | <comando_composto>
           | <comando_if>
           | <comando_while>
           | <comando_for>
           | <comando_return>
           | <comando_break>
           | <comando_continue>
           | <comando_preprocessador>

// Comando de preprocessador
<comando_preprocessador> ::= '#' <identificador> <resto_linha>

// Comando de expressão
<comando_expressao> ::= <expressao> ';'
                    | ';'

// Comando composto (bloco)
<comando_composto> ::= <bloco>

// Estruturas de controle
<comando_if> ::= 'if' '(' <expressao> ')' <comando> [ 'else' <comando> ]

<comando_while> ::= 'while' '(' <expressao> ')' <comando>

<comando_for> ::= 'for' '(' [<expressao_ou_vazio>] ';' [<expressao_ou_vazio>] ';' [<expressao_ou_vazio>] ')' <comando>

// Comandos de fluxo
<comando_return> ::= 'return' [<expressao_ou_vazio>] ';'

<comando_break> ::= 'break' ';'

<comando_continue> ::= 'continue' ';'

// Expressões
<expressao_ou_vazio> ::= <expressao>
                      | ε

<expressao> ::= <expressao_atribuicao>

<expressao_atribuicao> ::= <unario> '=' <expressao>
                        | <expressao_logica_ou>

<expressao_logica_ou> ::= <expressao_logica_e> { '||' <expressao_logica_e> }

<expressao_logica_e> ::= <expressao_igualdade> { '&&' <expressao_igualdade> }

<expressao_igualdade> ::= <expressao_relacional> { ('==' | '!=') <expressao_relacional> }

<expressao_relacional> ::= <expressao_aditiva> { ('<' | '>' | '<=' | '>=') <expressao_aditiva> }

<expressao_aditiva> ::= <expressao_multiplicativa> { ('+' | '-') <expressao_multiplicativa> }

<expressao_multiplicativa> ::= <expressao_unaria> { ('*' | '/' | '%') <expressao_unaria> }

<expressao_unaria> ::= <operador_unario> <expressao_unaria>
                    | <operador_incremento> <unario>
                    | <unario> <operador_incremento>
                    | <unario>

// Operadores unários e de incremento
<operador_unario> ::= '&'
                   | '*'
                   | '+'
                   | '-'
                   | '!'
                   | '~'

<operador_incremento> ::= '++'
                       | '--'

// Expressões primárias e chamadas
<unario> ::= <primario>
          | <unario> '[' <expressao> ']'
          | <unario> '(' <lista_de_argumentos> ')'

<lista_de_argumentos> ::= <expressao>
                       | <expressao> ',' <lista_de_argumentos>
                       | ε

<primario> ::= <identificador>
            | <constante>
            | <string>
            | '(' <expressao> ')'

// Identificadores e constantes
<identificador> ::= ([a-zA-Z_]) [a-zA-Z0-9_]*

<constante> ::= <inteiro>
             | <flutuante>
             | <caractere>

<inteiro> ::= [0-9]+

<flutuante> ::= [0-9]+ '.' [0-9]+

<caractere> ::= '\'' . '\''

<string> ::= '"' { . } '"'

// Comentários
<comentario> ::= '/*' { . } '*/'
              | '//' { . } '\n'
```
