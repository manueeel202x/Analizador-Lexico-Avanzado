#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    NUMERO_ENTERO,
    OP_MULT,
    OP_DIV,
    OP_BINARIO_SUMA,
    OP_BINARIO_RESTA,
    PAREN_ABRE,
    PAREN_CIERRA,
    ERROR_LEXICO,
    FIN_CADENA
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
} Token;

const char* tipo_a_cadena(TipoToken tipo) {
    switch (tipo) {
        case NUMERO_ENTERO: return "NUMERO_ENTERO";
        case OP_MULT: return "OP_MULT";
        case OP_DIV: return "OP_DIV";
        case OP_BINARIO_SUMA: return "OP_BINARIO_SUMA";
        case OP_BINARIO_RESTA: return "OP_BINARIO_RESTA";
        case PAREN_ABRE: return "PAREN_ABRE";
        case PAREN_CIERRA: return "PAREN_CIERRA";
        case ERROR_LEXICO: return "ERROR_LEXICO";
        case FIN_CADENA: return "FIN_CADENA";
        default: return "DESCONOCIDO";
    }
}

Token ObtenerToken(const char *expresion, int *indice) {
    int inicio_lexema = *indice;
    Token nuevo_token;
    int len = strlen(expresion);

    while (*indice < len && isspace(expresion[*indice])) {
        (*indice)++;
        inicio_lexema = *indice; 
    }

    if (*indice >= len) {
        nuevo_token.tipo = FIN_CADENA;
        goto token_encontrado;
    }

    char c = expresion[*indice];
    
    if (isdigit(c)) {
        nuevo_token.tipo = NUMERO_ENTERO;
    } else if (c == '+') {
        nuevo_token.tipo = OP_BINARIO_SUMA;
    } else if (c == '-') {
        nuevo_token.tipo = OP_BINARIO_RESTA;
    } else if (c == '*') {
        nuevo_token.tipo = OP_MULT;
    } else if (c == '/') {
        nuevo_token.tipo = OP_DIV;
    } else if (c == '(') {
        nuevo_token.tipo = PAREN_ABRE;
    } else if (c == ')') {
        nuevo_token.tipo = PAREN_CIERRA;
    } else if (c == '\0') {
        nuevo_token.tipo = FIN_CADENA;
        goto token_encontrado; 
        
    } else {
        nuevo_token.tipo = ERROR_LEXICO;
    }
    
    (*indice)++;
    
    token_encontrado:
    {
        int longitud_lexema = *indice - inicio_lexema;
        
        if (nuevo_token.tipo == FIN_CADENA) {
            strcpy(nuevo_token.lexema, "EOF");
        } else if (longitud_lexema > 0) {
            strncpy(nuevo_token.lexema, expresion + inicio_lexema, longitud_lexema);
            nuevo_token.lexema[longitud_lexema] = '\0';
        } else {
            nuevo_token.lexema[0] = expresion[inicio_lexema];
            nuevo_token.lexema[1] = '\0';
        }
    }
    return nuevo_token;
}

int main() {
    // Cadena de prueba
    const char *prueba_simple = "456 + 10"; 
    printf("Expresión: \"%s\"\n", prueba_simple);

    int indice_actual = 0;
    Token t;

    do {
        t = ObtenerToken(prueba_simple, &indice_actual);
        printf("Tipo: %-20s | Lexema: %s\n", tipo_a_cadena(t.tipo), t.lexema);
        
    } while (t.tipo != FIN_CADENA && t.tipo != ERROR_LEXICO);
    

    return 0;
}