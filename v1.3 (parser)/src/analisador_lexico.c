#include "../bin/analisador_lexico.h"

EntradaTabela *tabelaSimbolos = NULL;
FILE *arquivo;
int linha = 1;
int coluna = 1;

char ler_caractere() 
{
    char c = fgetc(arquivo);
    if (c == '\n')
    {
        linha++;
        coluna = 1;
    }
    else
    {
        coluna++;
    }
    return c;
}

void volta_caractere(char c)
{
    if (c != EOF)
    {
        ungetc(c, arquivo);
        coluna--;
        if (c == '\n')
            linha--;
    }
}

void gravar_token_no_fim_da_lista(int token, const char *lexema, const char *token_name, int linha, int coluna)
{
    EntradaTabela *novo = (EntradaTabela *)malloc(sizeof(EntradaTabela));
    novo->token = token;
    strcpy(novo->lexema, lexema);
    strcpy(novo->token_name, token_name);
    novo->linha = linha;
    novo->coluna = coluna;   // grava coluna atual
    novo->prox = NULL;

    if (tabelaSimbolos == NULL)
    {
        tabelaSimbolos = novo;
    }
    else
    {
        EntradaTabela *atual = tabelaSimbolos;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

int e_palavra_reservada(const char *lexema, char *token_name)
{
    struct
    {
        const char *palavra;
        const char *token_name;
        int token_val;
    } palavras[] = {
        {"auto", "TOKEN_AUTO", TOKEN_AUTO},
        {"break", "TOKEN_BREAK", TOKEN_BREAK},
        {"case", "TOKEN_CASE", TOKEN_CASE},
        {"char", "TOKEN_CHAR", TOKEN_CHAR},
        {"const", "TOKEN_CONST", TOKEN_CONST},
        {"continue", "TOKEN_CONTINUE", TOKEN_CONTINUE},
        {"default", "TOKEN_DEFAULT", TOKEN_DEFAULT},
        {"do", "TOKEN_DO", TOKEN_DO},
        {"double", "TOKEN_DOUBLE", TOKEN_DOUBLE},
        {"else", "TOKEN_ELSE", TOKEN_ELSE},
        {"enum", "TOKEN_ENUM", TOKEN_ENUM},
        {"extern", "TOKEN_EXTERN", TOKEN_EXTERN},
        {"float", "TOKEN_FLOAT", TOKEN_FLOAT},
        {"for", "TOKEN_FOR", TOKEN_FOR},
        {"goto", "TOKEN_GOTO", TOKEN_GOTO},
        {"if", "TOKEN_IF", TOKEN_IF},
        {"inline", "TOKEN_INLINE", TOKEN_INLINE},
        {"int", "TOKEN_INT", TOKEN_INT},
        {"long", "TOKEN_LONG", TOKEN_LONG},
        {"register", "TOKEN_REGISTER", TOKEN_REGISTER},
        {"restrict", "TOKEN_RESTRICT", TOKEN_RESTRICT},
        {"return", "TOKEN_RETURN", TOKEN_RETURN},
        {"short", "TOKEN_SHORT", TOKEN_SHORT},
        {"signed", "TOKEN_SIGNED", TOKEN_SIGNED},
        {"sizeof", "TOKEN_SIZEOF", TOKEN_SIZEOF},
        {"static", "TOKEN_STATIC", TOKEN_STATIC},
        {"struct", "TOKEN_STRUCT", TOKEN_STRUCT},
        {"switch", "TOKEN_SWITCH", TOKEN_SWITCH},
        {"typedef", "TOKEN_TYPEDEF", TOKEN_TYPEDEF},
        {"typeof", "TOKEN_TYPEOF", TOKEN_TYPEOF},
        {"union", "TOKEN_UNION", TOKEN_UNION},
        {"unsigned", "TOKEN_UNSIGNED", TOKEN_UNSIGNED},
        {"void", "TOKEN_VOID", TOKEN_VOID},
        {"volatile", "TOKEN_VOLATILE", TOKEN_VOLATILE},
        {"while", "TOKEN_WHILE", TOKEN_WHILE},
        {"_Alignas", "TOKEN_ALIGNAS", TOKEN_ALIGNAS},
        {"_Alignof", "TOKEN_ALIGNOF", TOKEN_ALIGNOF},
        {"_Atomic", "TOKEN_ATOMIC", TOKEN_ATOMIC},
        {"_Bool", "TOKEN_BOOL", TOKEN_BOOL},
        {"_Complex", "TOKEN_COMPLEX", TOKEN_COMPLEX},
        {"_Generic", "TOKEN_GENERIC", TOKEN_GENERIC},
        {"_Imaginary", "TOKEN_IMAGINARY", TOKEN_IMAGINARY},
        {"_Noreturn", "TOKEN_NORETURN", TOKEN_NORETURN},
        {"_Static_assert", "TOKEN_STATIC_ASSERT", TOKEN_STATIC_ASSERT},
        {"_Thread_local", "TOKEN_THREAD_LOCAL", TOKEN_THREAD_LOCAL},
        {NULL, NULL, 0}
    };

    for (int i = 0; palavras[i].palavra != NULL; i++)
    {
        if (strcmp(lexema, palavras[i].palavra) == 0)
        {
            strcpy(token_name, palavras[i].token_name);
            return palavras[i].token_val;
        }
    }
    return TOKEN_IDENTIFICADOR;
}

void imprimir_tabela_simbolos()
{
    printf("Tabela de Símbolos:\n");
    printf("Token\t\t\t\t | Lexema\t\t\t\t | Linha:Coluna\n");
    printf("----------------------------------------------------------------------------------------\n");
    EntradaTabela *atual = tabelaSimbolos;
    while (atual)
    {
        printf("%s\t\t\t %s\t\t\t %d:%d\n", atual->token_name, atual->lexema, atual->linha, atual->coluna);
        atual = atual->prox;
    }
}

void liberar_tabela_simbolos()
{
    EntradaTabela *atual = tabelaSimbolos;
    while (atual)
    {
        EntradaTabela *tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    tabelaSimbolos = NULL;
}

int analex()
{
    char c, lexema[MAX_LEXEMA];
    int pos = 0, coluna_inicial = coluna;
    char token_name[MAX_TOKEN_NAME]; 

    while (1)
    {
        coluna_inicial = coluna;
        c = ler_caractere();

        if (c == EOF)
        {
            gravar_token_no_fim_da_lista(TOKEN_EOF, "EOF", "TOKEN_EOF", linha, coluna_inicial);
            return TOKEN_EOF;
        }

        if (isspace(c))
            continue;

        // Identificadores e palavras-chave
        if (isalpha(c) || c == '_')
        {
            lexema[pos++] = c;
            while (isalnum(c = ler_caractere()) || c == '_')
            {
            lexema[pos++] = c;
            }
            volta_caractere(c);
            lexema[pos] = '\0';
            pos = 0;
            int gotTokenVal = e_palavra_reservada(lexema, token_name);
            if (gotTokenVal < TOKEN_IDENTIFICADOR) // Se for uma palavra reservada
            {
            gravar_token_no_fim_da_lista(gotTokenVal, lexema, token_name, linha, coluna_inicial); // PALAVRA_RESERVADA
            }
            else
            {
            gravar_token_no_fim_da_lista(gotTokenVal, lexema, "TOKEN_IDENTIFIER", linha, coluna_inicial); // IDENTIFICADOR
            }
            return gotTokenVal;
        }

        // Números inteiros ou ponto flutuante
        if (isdigit(c))
        {
            lexema[pos++] = c;
            int ponto = 0;
            while (isdigit(c = ler_caractere()) || (c == '.' && !ponto))
            {
            if (c == '.')
                ponto = 1;
            lexema[pos++] = c;
            }
            volta_caractere(c);
            lexema[pos] = '\0';
            pos = 0;

            if (ponto)
            {
            gravar_token_no_fim_da_lista(TOKEN_CONSTANTE_FLOAT, lexema, "TOKEN_CONSTANTE_FLOAT", linha, coluna_inicial);
            return TOKEN_CONSTANTE_FLOAT;
            }
            else
            {
            gravar_token_no_fim_da_lista(TOKEN_CONSTANTE_INT, lexema, "TOKEN_CONSTANTE_INT", linha, coluna_inicial);
            return TOKEN_CONSTANTE_INT;
            }
        }

        // Literais de caractere
        if (c == '\'')
        {
            lexema[pos++] = c;
            c = ler_caractere();
            lexema[pos++] = c;
            c = ler_caractere();
            if (c == '\'')
            {
            lexema[pos++] = c;
            lexema[pos] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_CONSTANTE_CHAR, lexema, "TOKEN_CONSTANTE_CHAR", linha, coluna_inicial);
            return TOKEN_CONSTANTE_CHAR;
            }
        }

        // Literais de string
        if (c == '"')
        {
            lexema[pos++] = c;
            while ((c = ler_caractere()) != '"' && c != EOF)
            {
            lexema[pos++] = c;
            }
            lexema[pos++] = '"';
            lexema[pos] = '\0';
            pos = 0;
            gravar_token_no_fim_da_lista(TOKEN_STRING_LITERAL, lexema, "TOKEN_STRING_LITERAL", linha, coluna_inicial);
            return TOKEN_STRING_LITERAL;
        }

        // DIV E Comentários
        if (c == '/')
        {
            lexema[pos++] = c;
            char next = ler_caractere();
            lexema[pos++] = next;
            if (next == '/')
            {
            // comentário de uma linha
            while ((c = ler_caractere()) != '\n' && c != EOF)
            {
                lexema[pos++] = c;
            };
            lexema[pos] = '\0';
            pos = 0;
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_COMENTARIO, lexema, "TOKEN_COMENTARIO", linha, coluna_inicial);
            continue;
            }
            else if (next == '*')
            {
            // comentário de múltiplas linhas
            char prev = 0;
            while ((c = ler_caractere()) != EOF)
            {
                lexema[pos++] = c;
                if (prev == '*' && c == '/')
                break;
                prev = c;
            }
            lexema[pos] = '\0';
            pos = 0;
            gravar_token_no_fim_da_lista(TOKEN_COMENTARIO, lexema, "TOKEN_COMENTARIO", linha, coluna_inicial);
            continue;
            }
            else
            {
            // operador de divisão
            volta_caractere(next);
            gravar_token_no_fim_da_lista(TOKEN_OP_DIV, "/", "TOKEN_OP_DIV", linha, coluna_inicial);
            return TOKEN_OP_DIV;
            }
        }

        // Operadores relacionais e lógicos
        switch (c)
        {
        case '+':
            if ((c = ler_caractere()) == '+')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_INCREMENTO, "++", "TOKEN_INCREMENTO", linha, coluna_inicial);
            return TOKEN_OP_INCREMENTO;
            }
            else if (c == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_ATRIB_SOMA, "+=", "TOKEN_ATRIBUICAO_SOMA", linha, coluna_inicial);
            return TOKEN_ATRIB_SOMA;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_SOMA, "+", "TOKEN_OP_SOMA", linha, coluna_inicial);
            return TOKEN_OP_SOMA;
            }

        case '-':
            if ((c = ler_caractere()) == '-')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_DECREMENTO, "--", "TOKEN_OP_DECREMENTO", linha, coluna_inicial);
            return TOKEN_OP_DECREMENTO;
            }
            else if (c == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_ATRIB_SUB, "-=", "TOKEN_ATRIB_SUB", linha, coluna_inicial);
            return TOKEN_ATRIB_SUB;
            }
            else if (c == '>')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_SETA, "->", "TOKEN_OP_SETA", linha, coluna_inicial);
            return TOKEN_OP_SETA;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_SUB, "-", "TOKEN_OP_SUB", linha, coluna_inicial);
            return TOKEN_OP_SUB;
            }

        case '*':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_ATRIB_MUL, "*=", "TOKEN_ATRIB_MUL", linha, coluna_inicial);
            return TOKEN_ATRIB_MUL;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_MUL, "*", "TOKEN_OP_MUL", linha, coluna_inicial);
            return TOKEN_OP_MUL;
            }

        case '%':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_ATRIB_MOD, "%=", "TOKEN_ATRIB_MOD", linha, coluna_inicial);
            return TOKEN_ATRIB_MOD;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_MOD, "%", "TOKEN_OP_MOD", linha, coluna_inicial);
            return TOKEN_OP_MOD;
            }

        case '=':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_IGUAL, "==", "TOKEN_OP_IGUAL", linha, coluna_inicial);
            return TOKEN_OP_IGUAL;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_ATRIBUICAO, "=", "TOKEN_ATRIBUICAO", linha, coluna_inicial);
            return TOKEN_ATRIBUICAO;
            }

        case '!':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_DIFERENTE, "!=", "TOKEN_OP_DIFERENTE", linha, coluna_inicial);
            return TOKEN_OP_DIFERENTE;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_NOT_LOGICO, "!", "TOKEN_OP_NOT_LOGICO", linha, coluna_inicial);
            return TOKEN_OP_NOT_LOGICO;
            }

        case '<':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_MENOR_IGUAL, "<=", "TOKEN_OP_MENOR_IGUAL", linha, coluna_inicial);
            return TOKEN_OP_MENOR_IGUAL;
            }
            else if (c == '<')
            {
            if ((c = ler_caractere()) == '=')
            {
                gravar_token_no_fim_da_lista(TOKEN_ATRIB_SHIFT_ESQ, "<<=", "TOKEN_ATRIB_SHIFT_ESQ", linha, coluna_inicial);
                return TOKEN_ATRIB_SHIFT_ESQ;
            }
            else
            {
                volta_caractere(c);
                gravar_token_no_fim_da_lista(TOKEN_OP_SHIFT_ESQ, "<<", "TOKEN_OP_SHIFT_ESQ", linha, coluna_inicial);
                return TOKEN_OP_SHIFT_ESQ;
            }
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_MENOR, "<", "TOKEN_OP_MENOR", linha, coluna_inicial);
            return TOKEN_OP_MENOR;
            }

        case '>':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_MAIOR_IGUAL, ">=", "TOKEN_OP_MAIOR_IGUAL", linha, coluna_inicial);
            return TOKEN_OP_MAIOR_IGUAL;
            }
            else if (c == '>')
            {
            if ((c = ler_caractere()) == '=')
            {
                gravar_token_no_fim_da_lista(TOKEN_ATRIB_SHIFT_DIR, ">>=", "TOKEN_ATRIB_SHIFT_DIR", linha, coluna_inicial);
                return TOKEN_ATRIB_SHIFT_DIR;
            }
            else
            {
                volta_caractere(c);
                gravar_token_no_fim_da_lista(TOKEN_OP_SHIFT_DIR, ">>", "TOKEN_OP_SHIFT_DIR", linha, coluna_inicial);
                return TOKEN_OP_SHIFT_DIR;
            }
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_MAIOR, ">", "TOKEN_OP_MAIOR", linha, coluna_inicial);
            return TOKEN_OP_MAIOR;
            }

        case '&':
            if ((c = ler_caractere()) == '&')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_AND_LOGICO, "&&", "TOKEN_OP_AND_LOGICO", linha, coluna_inicial);
            return TOKEN_OP_AND_LOGICO;
            } else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_AND_BIT, "&", "TOKEN_OP_AND_BIT", linha, coluna_inicial);
            return TOKEN_OP_AND_BIT;
            }

        case '|':
            if ((c = ler_caractere()) == '|')
            {
            gravar_token_no_fim_da_lista(TOKEN_OP_OR_LOGICO, "||", "TOKEN_OP_OR_LOGICO", linha, coluna_inicial);
            return TOKEN_OP_OR_LOGICO;
            }
            else if (c == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_ATRIB_OR, "|=","TOKEN_ATRIB_OR", linha, coluna_inicial);
            return TOKEN_ATRIB_OR;
            } else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_OR_BIT, "|", "TOKEN_OP_OR_BIT", linha, coluna_inicial);
            return TOKEN_OP_OR_BIT;
            }
        case '^':
            if ((c = ler_caractere()) == '=')
            {
            gravar_token_no_fim_da_lista(TOKEN_ATRIB_XOR, "^=", "TOKEN_ATRIB_XOR", linha, coluna_inicial);
            return TOKEN_ATRIB_XOR;
            }
            else
            {
            volta_caractere(c);
            gravar_token_no_fim_da_lista(TOKEN_OP_XOR_BIT, "^", "TOKEN_OP_XOR_BIT", linha, coluna_inicial);
            return TOKEN_OP_XOR_BIT;
            }
        case '~':
            // Complemento bit a bit
            gravar_token_no_fim_da_lista(TOKEN_OP_COMPL_BIT, "~", "TOKEN_OP_COMPL_BIT", linha, coluna_inicial);
            return TOKEN_OP_COMPL_BIT;
        case '?':
            // Operador condicional ternário
            lexema[pos++] = c;
            c = ler_caractere();
            if (c == ':')
            {
            lexema[pos++] = c;
            lexema[pos] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_OP_CONDICIONAL, lexema, "TOKEN_OP_CONDICIONAL", linha, coluna_inicial);
            return TOKEN_OP_CONDICIONAL;
            }
            else
            {
            volta_caractere(c);
            lexema[pos] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_DESCONHECIDO, lexema, "TOKEN_DESCONHECIDO", linha, coluna_inicial);
            return TOKEN_DESCONHECIDO;
            }
        case '\\':
            // Caractere de escape
            lexema[pos++] = c;
            c = ler_caractere();
            if (c == '\n')
            {
            // Linha continuada
            lexema[pos++] = c;
            lexema[pos] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_BARRA_INVERTIDA, lexema, "TOKEN_BARRA_INVERTIDA", linha, coluna_inicial);
            return TOKEN_BARRA_INVERTIDA;
            }
            else
            {
            volta_caractere(c);
            lexema[pos] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_DESCONHECIDO, lexema, "TOKEN_DESCONHECIDO", linha, coluna_inicial);
            return TOKEN_DESCONHECIDO;
            }
            
        // Delimitadores e separadores
        case ';':
            gravar_token_no_fim_da_lista(TOKEN_PONTO_VIRGULA, ";", "TOKEN_PONTO_VIRGULA", linha, coluna_inicial);
            return TOKEN_PONTO_VIRGULA;
        case ',':
            gravar_token_no_fim_da_lista(TOKEN_VIRGULA, ",", "TOKEN_VIRGULA", linha, coluna_inicial);
            return TOKEN_VIRGULA;
        case '.':
            gravar_token_no_fim_da_lista(TOKEN_OP_PONTO, ".", "TOKEN_OP_PONTO", linha, coluna_inicial);
            return TOKEN_OP_PONTO;
        case ':':
            gravar_token_no_fim_da_lista(TOKEN_DOIS_PONTOS, ":", "TOKEN_DOIS_PONTOS", linha, coluna_inicial);
            return TOKEN_DOIS_PONTOS;
        case '(':
            gravar_token_no_fim_da_lista(TOKEN_ABRE_PARENTESES, "(", "TOKEN_ABRE_PARENTESES", linha, coluna_inicial);
            return TOKEN_ABRE_PARENTESES;
        case ')':
            gravar_token_no_fim_da_lista(TOKEN_FECHA_PARENTESES, ")", "TOKEN_FECHA_PARENTESES", linha, coluna_inicial);
            return TOKEN_FECHA_PARENTESES;
        case '{':
            gravar_token_no_fim_da_lista(TOKEN_ABRE_CHAVES, "{", "TOKEN_ABRE_CHAVES", linha, coluna_inicial);
            return TOKEN_ABRE_CHAVES;
        case '}':
            gravar_token_no_fim_da_lista(TOKEN_FECHA_CHAVES, "}", "TOKEN_FECHA_CHAVES", linha, coluna_inicial);
            return TOKEN_FECHA_CHAVES;
        case '[':
            gravar_token_no_fim_da_lista(TOKEN_ABRE_COLCHETES, "[", "TOKEN_ABRE_COLCHETES", linha, coluna_inicial);
            return TOKEN_ABRE_COLCHETES;
        case ']':
            gravar_token_no_fim_da_lista(TOKEN_FECHA_COLCHETES, "]", "TOKEN_FECHA_COLCHETES", linha, coluna_inicial);
            return TOKEN_FECHA_COLCHETES;

        // Pre-processadores
        case '#':
            lexema[pos++] = c;
            while (isalnum(c = ler_caractere()) || c == '_')
            {
            lexema[pos++] = c;
            }
            volta_caractere(c);
            lexema[pos] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_PRE_PROCESSADOR, lexema, "TOKEN_PRE_PROCESSADOR", linha, coluna_inicial);
            return TOKEN_PRE_PROCESSADOR;

        default:
            // caractere não reconhecido
            lexema[0] = c;
            lexema[1] = '\0';
            gravar_token_no_fim_da_lista(TOKEN_DESCONHECIDO, lexema, "TOKEN_DESCONHECIDO", linha, coluna_inicial);
            return TOKEN_DESCONHECIDO;
        }
    }
}
