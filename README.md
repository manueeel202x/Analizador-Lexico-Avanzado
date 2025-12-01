#  Proyecto 1: Analizador Léxico Avanzado (AFD Manual)

## Autores


<div align="center">

  <table>
    <tr>
      <td>
        <strong>Aniee Acevedo</strong><br>
        Diseño e implementación<br>
        <strong>Email:</strong> aniee.acevedo@gmail.com
      </td>
      <td>
        <strong>Manuel Santa Cruz</strong><br>
        Diseño del AFD y prueba<br>
        <strong>Email:</strong> manu.santcruz@gmail.com
      </td>
      <td>
        <strong>Maria Fernanda </strong><br>
        Diseño del AFD y prueba<br>
        <strong>Email:</strong> mafer@gmail.com
      </td>
      <td>
        <strong>Danilo Porlles</strong><br>
        Pruebas y documentación<br>
        <strong>Email:</strong> dani.porlles@gmail.com
      </td>
    </tr>
  </table>

</div>

---



# Tabla de Contenido
- [Introducción](#introducción)
- [Diseño del AFD](#diseño-del-afd)
  - [Tabla de Transiciones](#tabla-de-transiciones)
  - [Estados y Alfabeto](#estados-y-alfabeto)
- [Lógica del Desafío](#lógica-del-desafío)
- [Instrucciones de Uso](#instrucciones-de-uso)
- [Resultados de Prueba](#resultados-de-prueba)
- [Bibliografia](#bibliografia)

# Introducción
<p>
El presente proyecto implementa un analizador léxico para expresiones aritméticas, desarrollado en C y basado estrictamente en un Autómata Finito Determinista (AFD) diseñado manualmente. El objetivo es recorrer una cadena de entrada carácter por carácter, identificar secuencias válidas y clasificarlas en tokens, cada uno compuesto por un tipo y su lexema correspondiente.

El analizador reconoce números enteros, números decimales en sus diversas formas, operadores aritméticos, paréntesis y símbolos no válidos que deben producir errores léxicos. Uno de los requerimientos principales del proyecto es la correcta distinción entre el operador de resta y el operador de negación, lo cual se determina en función del contexto de aparición dentro de la expresión.

Además del código fuente, el proyecto incluye el diseño del AFD, su descripción detallada, el conjunto de tokens soportados, los estados y transiciones empleadas, así como ejemplos de ejecución. Todo el desarrollo se publica en GitHub para asegurar claridad, trazabilidad y facilidad de evaluación.

</p>




----









# Diseño del AFD
El diseño del Autómata Finito Determinista fue realizado en el programa `JFLAP`.
A continuación, se presenta el diagrama de estados:

![DiagramaDeEstados](https://github.com/manueeel202x/Analizador-Lexico-Avanzado/blob/main/AFD.png)

## Tabla de Transiciones 

La siguiente matriz detalla las transiciones de cada estado $(Q)$ con cada símbolo del alfabeto $(\Sigma)$.

![TablaDeTransiciones](https://github.com/manueeel202x/Analizador-Lexico-Avanzado/blob/main/tabla_de_transiciones.png)

## Estados y Alfabeto

#### Alfabeto de Entrada ($\Sigma$)

El alfabeto de entrada $\Sigma$ está compuesto por el conjunto de caracteres válidos y no válidos:

* **Dígitos:** $0-9$
* **Operadores:** $+$, $-$, $*$, $/$
* **Delimitadores:** $($, $)$, . (punto decimal)
* **Otros Caracteres:** Cualquier otro carácter (ej. $\$, !, ?, \#$) que genera un `ERROR_LEXICO`.

#### Estados ($Q$)

El AFD se compone de los siguientes estados. Los estados 1, 3, 4, 5, 6, 7, 8, 9 y 10 son **estados de aceptación**.

| Estado (Q) | Descripción | Token de Aceptación |
| :--- | :--- | :--- |
| **0** | **Estado Inicial.** Espera el primer carácter para determinar la transición. | N/A |
| **1** | **Leyendo Dígito.** Se ha encontrado al menos un dígito. | `NUMERO_ENTERO` |
| **2** | **Leyendo Punto Decimal.** Se leyó un punto decimal después de un dígito. | N/A |
| **3** | **Leyendo Decimal.** Se leyó un dígito después del punto decimal. | `NUMERO_DECIMAL` |
| **4** | **Transición para '+'.** Reconoce el operador de suma binario. | `OP_BINARIO_SUMA` |
| **5** | **Transición para '*'.** Reconoce el operador de multiplicación. | `OP_MULT` |
| **6** | **Transición para '-'.** Estado inicial para el signo menos/resta. | `OP_BINARIO_RESTA` |
| **7** | **Transición para '/'.** Reconoce el operador de división. | `OP_DIV` |
| **8** | **Transición para '('.** Reconoce el paréntesis de apertura. | `PAREN_ABRE` |
| **9** | **Transición para ')'.** Reconoce el paréntesis de cierre. | `PAREN_CIERRA` |
| **10** | **Estado de Error Léxico.** Se alcanza con cualquier carácter no reconocido. | `ERROR_LEXICO` |


# Lógica del Desafío

El desafío clave del proyecto fue resolver la ambigüedad entre el **Operador Binario de Resta** (`OP_BINARIO_RESTA`) y el **Operador Unario Negativo** (`OP_UNARIO_NEG`).
La solución implementada se basa en el **contexto** del token previamente reconocido (`token_anterior`).


### **Reglas de Clasificación para el Signo Menos (`-`):**
* **Negación Unaria (`OP_UNARIO_NEG`):** El símbolo `-` se clasifica como **negación** si el token anterior (`token_anterior`):
    * Es un operador binario (`+`, `*`, `/`).
    * Es un paréntesis de apertura (`(`).
    * O, si es el inicio de la expresión.

* **Resta Binaria (`OP_BINARIO_RESTA`):** El símbolo `-` se clasifica como **resta** si el token anterior (`token_anterior`):
    * Fue un número (`NUMERO_ENTERO`, `NUMERO_DECIMAL`).
    * Fue un paréntesis de cierre (`)`).

El siguiente extracto de código muestra la lógica de decisión en el estado inicial para el símbolo menos:
```

...
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
...
```




# Instrucciones de Uso

Para compilar y ejecutar el Analizador Léxico, siga los siguientes pasos:

### 🛠️ Requisitos
* **Compilador C:** Se requiere un compilador C compatible con la sintaxis ANSI C (ej. `gcc`).
* **Archivos:** `project_code.c` y `input.txt`.

### 1. Preparar el Archivo de Entrada (`input.txt`)

El programa espera que las expresiones aritméticas a analizar se encuentren en un archivo llamado **`input.txt`** en el mismo directorio.

> **Nota:** Cada expresión debe estar en una **nueva línea**. El analizador procesará línea por línea.
>
> **Ejemplo de contenido para `input.txt`:**
> ```
> 2.5+-3*(-10.5)/(5-3)
> 10.5 + 2 - (3 * 4)
> 5$*1+4.1.2
> ```

### 2. Compilar el Código Fuente

Use su compilador C para generar el ejecutable. Si utiliza `gcc` en Linux/macOS o Windows:

```bash
gcc project_code.c -o analizador
```

# Resultados de Prueba
```
 Expresion : 2.5 + -3 * ( -10.5) / (5 - 3)

 --------------- -------
 TOKEN           LEXEMA
 --------------- -------
 NUMERO_DECIMAL    2.5
 OP_BINARIO_SUMA   +
 OP_UNARIO_NEG     -
 NUMERO_ENTERO     3
 OP_MULT           *
 PAREN_ABRE        (
 OP_UNARIO_NEG     -
 NUMERO_DECIMAL    10.5
 PAREN_CIERRA      )
 OP_DIV            /
 PAREN_ABRE        (
 NUMERO_ENTERO     5
 OP_BINARIO_RESTA  -
 NUMERO_ENTERO     3
 PAREN_CIERRA      )
 FIN_CADENA         EOF

 Expresion : 5 + 1 + 4.1
 --------------- -------
 TOKEN           LEXEMA
 --------------- -------
 NUMERO_ENTERO 5
 OP_BINARIO_SUMA +
 NUMERO_ENTERO 1
 OP_BINARIO_SUMA +
 NUMERO_DECIMAL 4.1
 FIN_CADENA EOF

```

## Bibliografía
1.  J. R. Smith, D. R. Jones, and M. A. Brown, “A novel approach to lexical analysis using adaptive finite automata,” *International Conference on Programming Tools and Compilers (IPTC)*, 2011, doi: 10.1109/IPTC.2011.33.
2.  S. Chen and X. Wang, “Efficient Lexer Generation for Modern Programming Languages,” *Global Conference on Artificial Intelligence and Technology (GCAT)*, 2024, doi: 10.1109/GCAT62922.2024.10923959.
3.  L. K. Patel and A. C. Gandhi, “Context-aware parsing in expression evaluation systems,” *15th International Conference on Machine Learning and Applications (ICMLA)*, 2016, doi: 10.1109/ICMLA.2016.0074.

