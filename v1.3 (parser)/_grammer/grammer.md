```c
// Programa Principal
<programa> ::= <lista_de_declaracoes>

Lista de Declarações Globais
<lista_de_declaracoes> ::= <declaracao> <lista_de_declaracoes> | ε

// Tipos de Declarações
<declaracao> ::= <declaracao_de_funcao>
              | <declaracao_de_variavel>
              | <declaracao_de_tipo>

// Declaração de Variável
<declaracao_de_variavel> ::= [<modificador>] <tipo> <lista_de_identificadores_com_vetores> [<inicializacao>] ';'
<modificador> ::= 'static' | 'extern' | 'const' | 'volatile'
<inicializacao> ::= '=' <expressao> | '=' '{' <lista_de_expressoes> '}' | ε
<lista_de_expressoes> ::= <expressao> (',' <expressao>)* | ε

Lista de Identificadores com Vetores
<lista_de_identificadores_com_vetores> ::= <identificador> [<vetor>] | <identificador> [<vetor>] ',' <lista_de_identificadores_com_vetores>
<vetor> ::= '[' [<expressao_ou_vazio>] ']' | ε

// Declaração de Função
<declaracao_de_funcao> ::= <tipo> <identificador> '(' <parametros> ')' <bloco>

// Declaração de Tipo
<declaracao_de_tipo> ::= 'typedef' <tipo> <identificador> ';'
                      | 'struct' <identificador> '{' <lista_de_declaracoes_de_campo> '}' ';'
                      | 'union' <identificador> '{' <lista_de_declaracoes_de_campo> '}' ';'
                      | 'enum' <identificador> '{' <lista_de_valores_enum> '}' ';'
<lista_de_declaracoes_de_campo> ::= <declaracao_de_variavel> <lista_de_declaracoes_de_campo> | ε
<lista_de_valores_enum> ::= <identificador> ['=' <inteiro>] (',' <identificador> ['=' <inteiro>])*

// Parâmetros de Função
<parametros> ::= <lista_de_parametros> [',' '...'] | ε
<lista_de_parametros> ::= <parametro> | <parametro> ',' <lista_de_parametros>
<parametro> ::= <tipo> <ponteiros> <identificador> [<vetor>]
<ponteiros> ::= '*' <ponteiros> | ε

// Tipos de Dados
<tipo> ::= 'int' | 'float' | 'char' | 'void' | <identificador>

// Bloco de Comandos e Declarações
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
           | <comando_do_while>
           | <comando_switch>
           | <comando_return>
           | <comando_break>
           | <comando_continue>
           | <comando_preprocessador>

// Comando de Pré-processador
<comando_preprocessador> ::= '#include' <string>
                          | '#define' <identificador> <resto_linha>
                          | '#ifdef' <identificador> <lista_de_declaracoes_e_comandos> '#endif'
                          | '#' <identificador> <resto_linha>

// Comandos de Controle
<comando_expressao> ::= <expressao> ';' | ';'
<comando_composto> ::= <bloco>
<comando_if> ::= 'if' '(' <expressao> ')' <comando> ['else' <comando>]
<comando_while> ::= 'while' '(' <expressao> ')' <comando>
<comando_do_while> ::= 'do' <comando> 'while' '(' <expressao> ')' ';'
<comando_for> ::= 'for' '(' [<expressao_ou_vazio>] ';' [<expressao_ou_vazio>] ';' [<expressao_ou_vazio>] ')' <comando>
<comando_switch> ::= 'switch' '(' <expressao> ')' '{' <lista_de_casos> '}'
<lista_de_casos> ::= 'case' <constante> ':' <lista_de_declaracoes_e_comandos> <lista_de_casos>
                  | 'default' ':' <lista_de_declaracoes_e_comandos>
                  | ε
<comando_return> ::= 'return' [<expressao_ou_vazio>] ';'
<comando_break> ::= 'break' ';'
<comando_continue> ::= 'continue' ';'

// Expressões
<expressao_ou_vazio> ::= <expressao> | ε
<expressao> ::= <expressao_atribuicao>
<expressao_atribuicao> ::= <unario> '=' <expressao> | <expressao_condicional>
<expressao_condicional> ::= <expressao_logica_ou> '?' <expressao> ':' <expressao> | <expressao_logica_ou>
<expressao_logica_ou> ::= <expressao_logica_e> { '||' <expressao_logica_e> }
<expressao_logica_e> ::= <expressao_igualdade> { '&&' <expressao_igualdade> }
<expressao_igualdade> ::= <expressao_relacional> { ('==' | '!=') <expressao_relacional> }
<expressao_relacional> ::= <expressao_bitwise> { ('<' | '>' | '<=' | '>=') <expressao_bitwise> }
<expressao_bitwise> ::= <expressao_aditiva> { ('&' | '|' | '^' | '<<' | '>>') <expressao_aditiva> }
<expressao_aditiva> ::= <expressao_multiplicativa> { ('+' | '-') <expressao_multiplicativa> }
<expressao_multiplicativa> ::= <expressao_unaria> { ('*' | '/' | '%') <expressao_unaria> }
<expressao_unaria> ::= <operador_unario> <expressao_unaria>
                    | <operador_incremento> <unario>
                    | <unario> <operador_incremento>
                    | <unario>

// Operadores Unários e de Incremento
<operador_unario> ::= '&' | '*' | '+' | '-' | '!' | '~'
<operador_incremento> ::= '++' | '--'

// Expressões Primárias e Chamadas
<unario> ::= <primario>
          | <unario> '[' <expressao> ']'
          | <unario> '(' <lista_de_argumentos> ')'
<lista_de_argumentos> ::= <expressao> | <expressao> ',' <lista_de_argumentos> | ε
<primario> ::= <identificador> | <constante> | <string> | '(' <expressao> ')'

// Identificadores e Constantes
<identificador> ::= ([a-zA-Z_]) [a-zA-Z0-9_]*
<constante> ::= <inteiro> | <flutuante> | <caractere> | 'true' | 'false'
<inteiro> ::= [0-9]+
<flutuante> ::= [0-9]+ '.' [0-9]+
<caractere> ::= '\'' . '\''
<string> ::= '"' { . } '"'

// Comentários
<comentario> ::= '/*' { . } '*/' | '//' { . } '\n'


```
