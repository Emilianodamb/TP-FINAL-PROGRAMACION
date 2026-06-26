#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED

#include "pregunta.h"

struct Respuesta
{
    int nroRespuesta;
    char respuesta[50];
    int nroPreguntaAsociada;
    int correcta; //0 o 1
};

typedef struct Respuesta* RespuestaPtr;

RespuestaPtr crearRespuestaVacia();

int contarRespuestasArchivo();

void mostrarRespuesta(RespuestaPtr respuesta, int numero);

void liberarRespuesta(RespuestaPtr respuesta);

/// MUESTRA TODAS LAS RESPUESTAS DE UN VECTOR
void mostrarRespuestasVector(RespuestaPtr* respuestas, int cantRespuestas);

#endif // RESPUESTA_H_INCLUDED
