#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "jugador.h"

struct Jugador
{
    int nroJugador;
    int dni;
    char alias[21];
    int puntuacion;
    int respuesta;
};

typedef struct Jugador Jugador;
typedef struct Jugador * JugadorPtr;

///RESERVAR MEMORIA

JugadorPtr crearJugadorVacio();

void mostrarJugador(JugadorPtr j);

///TRABAJAR CON MEMORIA RESERVADA
int seleccionarNumJugadores(int n);
void cargarJugadorTeclado(JugadorPtr jugador);

int contarJugadoresArchivo();
void mostrarJugadoresGuardados(const char* nombreArchivo);

///LIBERAR MEMORIA

void liberarJugador(JugadorPtr jugador);

#endif // JUGADOR_H_INCLUDED
