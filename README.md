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









## Diseño del AFD
El diseño del Autómata Finito Determinista fue realizado en el programa `JFLAP`.
A continuación, se presenta el diagrama de estados:

![DiagramaDeEstados](https://github.com/manueeel202x/Analizador-Lexico-Avanzado/blob/main/AFD.png)

### Tabla de Transiciones 

La siguiente matriz detalla las transiciones de cada estado $(Q)$ con cada símbolo del alfabeto $(\Sigma)$.

![TablaDeTransiciones](https://github.com/manueeel202x/Analizador-Lexico-Avanzado/blob/main/tabla_de_transiciones.png)

### Estados y Alfabeto

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

---

# Lógica del Desafío
# Instrucciones de Uso
# Resultados de Prueba
```
Analizando expresión: "2.5 + -3 * (-10.5) / (5 - 3)"
(NUMERO_DECIMAL, 2.5)
(OP_BINARIO_SUMA, +)
(OP_UNARIO_NEG, -)
(NUMERO_ENTERO, 3)
(OP_MULT, *)
(PAREN_ABRE, ()
(OP_UNARIO_NEG, -)
(NUMERO_DECIMAL, 10.5)
(PAREN_CIERRA, ))
(OP_DIV, /)
(PAREN_ABRE, ()
(NUMERO_ENTERO, 5)
(OP_BINARIO_RESTA, -)
(NUMERO_ENTERO, 3)
(PAREN_CIERRA, ))
(FIN_CADENA, EOF)
```

```
Analizando expresión: "5$ + 1 + 4.1.2"
(NUMERO_ENTERO, 5)
(ERROR_LEXICO, $)
(OP_BINARIO_SUMA, +)
(NUMERO_ENTERO, 1)
(OP_BINARIO_SUMA, +)
(NUMERO_DECIMAL, 4.1)
(ERROR_LEXICO, .)
(NUMERO_ENTERO, 2)
(FIN_CADENA, EOF)
```
## Bibliografia
- https://doi.org/10.37376/asj.vi3.953 Modelo AFD
- https://www.ijariit.com/manuscripts/v8i1/V8I1-1238.pdf Modelo AFD

