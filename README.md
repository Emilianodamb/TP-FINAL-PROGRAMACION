# TP-FINAL-PROGRAMACION
# Juego Multijugador de Preguntas y Respuestas (C)

## Resumen

Trabajo Práctico Final desarrollado en **2023** para la materia **Introducción a la Programación** de la universidad.

El proyecto consiste en un **juego multijugador de preguntas y respuestas por consola**, desarrollado íntegramente en **lenguaje C**, con el objetivo de aplicar los principales conceptos adquiridos durante la cursada.

### Conceptos aplicados

* Sintaxis y fundamentos del lenguaje C.
* Variables y tipos de datos.
* Operadores aritméticos, relacionales y lógicos.
* Estructuras de control (`if`, `else`, `switch`, `for`, `while` y `do-while`).
* Arreglos unidimensionales y bidimensionales (vectores y matrices).
* Estructuras de datos (`struct`).
* Funciones y procedimientos.
* Paso de parámetros y argumentos.
* Manejo dinámico de memoria mediante punteros (`malloc` y `free`).
* Implementación de nodos y listas enlazadas dinámicas.
* Persistencia de datos utilizando archivos.
* Creación y utilización de librerías propias.
* Implementación de Tipos de Datos Abstractos (TDA) y encapsulamiento.

## Consigna del trabajo

El objetivo del trabajo práctico consistía en desarrollar un juego de preguntas y respuestas con soporte para múltiples jugadores.

### Requisitos funcionales

* Permitir partidas de **2 a 4 jugadores**.
* Solicitar los datos de cada participante (alias y DNI), utilizando el DNI como identificador de jugadores previamente registrados.
* Presentar preguntas de forma aleatoria, cada una con **cuatro opciones de respuesta**.
* Asignar puntajes según la dificultad de cada pregunta.
* Permitir que un jugador continúe jugando mientras responda correctamente; al fallar, el turno pasa al siguiente jugador.
* Finalizar la partida cuando todos los jugadores hayan perdido y mostrar el puntaje obtenido por cada uno, indicando el ganador.
* Almacenar las preguntas y sus respuestas en archivos externos.
* Persistir el ranking de puntajes máximos en archivos y permitir su consulta desde el menú principal.
* Resolver empates mediante una pregunta matemática, donde el jugador cuya respuesta sea la más cercana obtiene un punto adicional.
* Implementar el paradigma de **Tipos de Datos Abstractos (TDA)** en la mayor parte del código fuente.
