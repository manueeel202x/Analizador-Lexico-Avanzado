#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_INICIO, 
    NUMERO_ENTERO,
    NUMERO_DECIMAL,
    OP_MULT,
    OP_DIV,
    OP_BINARIO_SUMA,
    OP_BINARIO_RESTA, 
    OP_UNARIO_NEG,    
    PAREN_ABRE,
    PAREN_CIERRA,
    ERROR_LEXICO,
    FIN_CADENA
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
} Token;

typedef enum {
    ESTADO_INICIAL,
    ESTADO_LEYENDO_ENTERO,
    ESTADO_ESPERA_DECIMAL, 
    ESTADO_LEYENDO_DECIMAL,
    ESTADO_LEYENDO_OP
} EstadoAFD;

const char* tipo_a_string(TipoToken tipo) {
    switch (tipo) {
        case NUMERO_ENTERO: return "NUMERO_ENTERO";
        case NUMERO_DECIMAL: return "NUMERO_DECIMAL";
        case OP_MULT: return "OP_MULT";
        case OP_DIV: return "OP_DIV";
        case OP_BINARIO_SUMA: return "OP_BINARIO_SUMA";
        case OP_BINARIO_RESTA: return "OP_BINARIO_RESTA";
        case OP_UNARIO_NEG: return "OP_UNARIO_NEG";
        case PAREN_ABRE: return "PAREN_ABRE";
        case PAREN_CIERRA: return "PAREN_CIERRA";
        case ERROR_LEXICO: return "ERROR_LEXICO";
        case FIN_CADENA: return "FIN_CADENA";
        default: return "DESCONOCIDO";
    }
}

Token getNextToken(const char *expresion, int *indice, TipoToken token_anterior) {
    EstadoAFD estado_actual = ESTADO_INICIAL;
    int inicio_lexema = *indice;
    Token nuevo_token;
    int len = strlen(expresion);

    while (*indice <= len) {
        char c = expresion[*indice];

        if (estado_actual == ESTADO_INICIAL && isspace(c)) {
            (*indice)++;
            inicio_lexema = *indice;
            continue;
        }

        switch (estado_actual) {
            case ESTADO_INICIAL:
                if (isdigit(c)) {
                    estado_actual = ESTADO_LEYENDO_ENTERO;
                    (*indice)++;
                } else if (c == '+') {
                    nuevo_token.tipo = OP_BINARIO_SUMA;
                    (*indice)++;
                    goto token_encontrado; 
                } else if (c == '*' || c == '/') {
                    nuevo_token.tipo = (c == '*') ? OP_MULT : OP_DIV;
                    (*indice)++;
                    goto token_encontrado;
                } else if (c == '(') {
                    nuevo_token.tipo = PAREN_ABRE;
                    (*indice)++;
                    goto token_encontrado;
                } else if (c == ')') {
                    nuevo_token.tipo = PAREN_CIERRA;
                    (*indice)++;
                    goto token_encontrado;
                } else if (c == '-') {
                    if (token_anterior == TOKEN_INICIO || 
                        token_anterior == OP_BINARIO_SUMA || 
                        token_anterior == OP_BINARIO_RESTA || 
                        token_anterior == OP_MULT || 
                        token_anterior == OP_DIV || 
                        token_anterior == PAREN_ABRE) {
                        
                        nuevo_token.tipo = OP_UNARIO_NEG;
                    } else {
                        nuevo_token.tipo = OP_BINARIO_RESTA;
                    }
                    (*indice)++;
                    goto token_encontrado;
                } else if (c == '\0') {
                    nuevo_token.tipo = FIN_CADENA;
                    goto token_encontrado;
                } else {
                    nuevo_token.tipo = ERROR_LEXICO;
                    (*indice)++;
                    goto token_encontrado;
                }
                break;

            case ESTADO_LEYENDO_ENTERO:
                if (isdigit(c)) {
                    (*indice)++;
                } else if (c == '.') {
                    estado_actual = ESTADO_ESPERA_DECIMAL;
                    (*indice)++;
                } else {
                    nuevo_token.tipo = NUMERO_ENTERO;
                    goto token_encontrado;
                }
                break;

            case ESTADO_ESPERA_DECIMAL:
                if (isdigit(c)) {
                    estado_actual = ESTADO_LEYENDO_DECIMAL;
                    (*indice)++;
                } else {
                    nuevo_token.tipo = NUMERO_DECIMAL; 
                    goto token_encontrado;
                }
                break;

            case ESTADO_LEYENDO_DECIMAL:
                if (isdigit(c)) {
                    (*indice)++;
                } else {
                    nuevo_token.tipo = NUMERO_DECIMAL;
                    goto token_encontrado;
                }
                break;
            
        }
    }
    
    if (estado_actual != ESTADO_INICIAL) {
        if (estado_actual == ESTADO_LEYENDO_ENTERO) nuevo_token.tipo = NUMERO_ENTERO;
        else if (estado_actual == ESTADO_LEYENDO_DECIMAL || estado_actual == ESTADO_ESPERA_DECIMAL) nuevo_token.tipo = NUMERO_DECIMAL;
        goto token_encontrado;
    }
    
    nuevo_token.tipo = FIN_CADENA;
    return nuevo_token;

token_encontrado:
    {
        int longitud_lexema = *indice - inicio_lexema;
        if (longitud_lexema > 0 && nuevo_token.tipo != FIN_CADENA) {
            strncpy(nuevo_token.lexema, expresion + inicio_lexema, longitud_lexema);
            nuevo_token.lexema[longitud_lexema] = '\0';
        } else if (nuevo_token.tipo == FIN_CADENA) {
            strcpy(nuevo_token.lexema, "EOF");
        } else {
            nuevo_token.lexema[0] = expresion[inicio_lexema];
            nuevo_token.lexema[1] = '\0';
        }
    }
    return nuevo_token;
}

int main() {

    const char *prueba_completa = "2.5 + -3 * (-10.5) / (5 - 3)";
    printf("Analizando expresión: \"%s\"\n", prueba_completa);

    int indice_actual = 0;
    TipoToken token_anterior = TOKEN_INICIO; 
    Token t;

    do{
        t = getNextToken(prueba_completa, &indice_actual, token_anterior);
        printf("(%s, %s)\n", tipo_a_string(t.tipo), t.lexema);
        token_anterior = t.tipo;

    }while(t.tipo!=FIN_CADENA);
    
    
    const char *prueba_error = "5$ + 1 + 4.1.2";
    printf("\nAnalizando expresión con error: \"%s\"\n", prueba_error);
    
    indice_actual=0;
    token_anterior=TOKEN_INICIO;
    
    do{
        t = getNextToken(prueba_error, &indice_actual, token_anterior);
        printf("(%s, %s)\n", tipo_a_string(t.tipo), t.lexema);
        token_anterior = t.tipo;
    }while (t.tipo!=FIN_CADENA);

    return 0;
}
