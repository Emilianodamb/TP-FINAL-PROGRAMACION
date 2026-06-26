#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include "respuesta.h"

struct Pregunta
{
    int nroPregunta;
    char pregunta[200];
    RespuestaPtr posibles[4];
};

struct PreguntaMatematica
{
    int nroPregunta;
    int nroJugador;
    char pregunta[200];
    int respuesta;
};

typedef struct Pregunta * PreguntaPtr;
typedef struct PreguntaMatematica * PreguntaMatematicaPtr;

PreguntaPtr crearPreguntaVacia();
PreguntaMatematicaPtr crearPreguntaMatematicaVacia();

int contarPreguntasArchivo(const char* archivo);

void mostrarPregunta(PreguntaPtr pregunta);
void mostrarPreguntaMatematica(PreguntaMatematicaPtr pregunta);

PreguntaPtr* cargarPreguntasDesdeArchivo(const char* nombreArchivo, int cantPreguntas);
RespuestaPtr* cargarRespuestasDesdeArchivo(const char* nombreArchivo, int cantRespuestas, PreguntaPtr* preguntas);
RespuestaPtr* cargarRespuestasDificilesDesdeArchivo(const char* nombreArchivo, int cantRespuestas, PreguntaPtr* preguntas);
PreguntaMatematicaPtr* cargarPreguntasMatematicasDesdeArchivo(const char* nombreArchivo, int cantPreguntasMatematicas);

void mostrarPreguntasVector(PreguntaPtr* preguntas, int cantPreguntas);
void mostrarPreguntasMatematicasVector(PreguntaMatematicaPtr* preguntasMatematicas, int cantPreguntasMatematicas);

void liberarPregunta(PreguntaPtr pregunta);
void liberarPreguntaMatematica(PreguntaMatematicaPtr pregunta);

#endif // PREGUNTA_H_INCLUDED
