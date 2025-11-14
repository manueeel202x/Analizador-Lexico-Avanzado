
#  Proyecto 1: Analizador Léxico Avanzado (AFD Manual)


## 3. Diseño del AFD
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

