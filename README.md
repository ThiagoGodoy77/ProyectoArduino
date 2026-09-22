# Proyecto Arduino: Juego del Ahorcado

## Descripción del Proyecto
Aplicación desarrollada en Arduino Uno que implementa una versión simplificada del clásico juego del ahorcado, enfocada en la adivinanza de vocales para una serie de palabras con niveles de dificultad.

* **Materia**: Organización y Arquitectura.
* **Año**: 2021.
* **Autores**: Juarez Lucas y Godoy Thiago.

---

## Arquitectura y Componentes
El sistema hardware y software está integrado por los siguientes elementos:

* **Display LCD**: Utilizado para presentar las reglas del juego, las opciones, los mensajes de acierto/error y la palabra oculta.
* **Teclado matricial**: Permite al usuario interactuar seleccionando tanto la dificultad de las palabras como las vocales a arriesgar.
* **Parlante**: Emite melodías de notificación ante los estados finales de victoria ("Never Gonna Give You Up") o derrota (Super Mario Bros Death Song).
* **Led RGB**: Utiliza específicamente el canal rojo para señalizar de manera visual los errores cometidos durante las partidas.

---

## Niveles de Dificultad y Palabras
El sistema cuenta con un menú inicial operado desde el teclado numérico con tres niveles:
1. **Fácil**: `hilo` (mostrado inicialmente como `h_l_`)
2. **Medio**: `caduco` (mostrado inicialmente como `c_d_c_`)
3. **Difícil**: `vislumbrando` (mostrado inicialmente como `v_sl_mbr_nd_`)

---

## Lógica y Funcionamiento
* El sistema evalúa el ingreso de vocales mediante estructuras de control condicionales (`switch` y `if`).
* Si el usuario acierta, la vocal se revela en la posición correspondiente del display LCD.
* Si el usuario se equivoca, se descuenta una vida y el LED rojo parpadea tres veces.
* El juego finaliza con éxito si la palabra se completa en su totalidad, o en derrota si las vidas llegan a cero.
