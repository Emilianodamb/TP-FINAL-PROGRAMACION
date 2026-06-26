#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "jugador.h"

struct Juego
{
    JugadorPtr jugadores[4];
};

typedef struct Juego * JuegoPtr;

///RESERVAR MEMORIA
JuegoPtr crearNuevoJuego();
JugadorPtr encontrarJugadorConMayorPuntuacion(JuegoPtr juego, int numJugadores);

///TRABAJAR CON LA MEMORIA RESERVADA
void cargarJugadores(JuegoPtr juego, int cantJugadores);
void mostrarJugadores(JuegoPtr juego, int numJugadores);

void jugar(JuegoPtr partidaActual, int numJugadores);

void menuPrincipal();
void limpiarPantalla();
void pantallaPrincipal();
void systemPauseGenerico();
void imprimirArchivoConFormato(const char* nombreArchivo, const char* formato);

int contarElementosArchivo(const char* nombreArchivo, int tamLinea);

int calcularDiferencia(int a, int b);
void shuffle(int arr[], int n);

int encontrarMaxPuntuacion(JuegoPtr juego, int numJugadores);
void hayEmpate(JuegoPtr juego, JugadorPtr jugadorMayorPuntuacion, int numJugadores);
void determinarGanador(JuegoPtr partidaActual, int numJugadores);
void guardarPuntajesMaximos(const char* nombreArchivo, JuegoPtr partidaActual, int numJugadores);

///LIBERAR MEMORIA
void liberarJugadores(JuegoPtr juego, int cantJugadores);
void liberarJuego(JuegoPtr juego, int cantJugadores);

FILE* abrirArchivo(const char* nombreArchivo, const char* modo);

#endif // JUEGO_H_INCLUDED
