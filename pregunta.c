#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "jugador.h"
#include "pregunta.h"
#include "respuesta.h"


///CREA UNA PREGUNTA VACIA CON SUS RESPUESTAS VACIAS Y RESERVA MEMORIA
PreguntaPtr crearPreguntaVacia()
{
    PreguntaPtr nuevaPregunta = (PreguntaPtr)malloc(sizeof(struct Pregunta));

    if (nuevaPregunta != NULL)
    {
        nuevaPregunta->nroPregunta = 0;
        strcpy(nuevaPregunta->pregunta, "");

        for (int i = 0; i < 4; i++)
        {
            nuevaPregunta->posibles[i] = crearRespuestaVacia();
        }
    }

    return nuevaPregunta;
}

PreguntaMatematicaPtr crearPreguntaMatematicaVacia()
{
    PreguntaMatematicaPtr nuevaPreguntaMatematica = (PreguntaMatematicaPtr)malloc(sizeof(struct PreguntaMatematica));

    if (nuevaPreguntaMatematica != NULL)
    {
        nuevaPreguntaMatematica->nroPregunta = 0;
        nuevaPreguntaMatematica->nroJugador = 0;
        strcpy(nuevaPreguntaMatematica->pregunta, "");
        nuevaPreguntaMatematica->respuesta = 0;
    }

    return nuevaPreguntaMatematica;
}


///CUENTA LOS RENGLONES DE UN ARCHIVO Y LOS TRADUCE A NUMERO DE PREGUNTAS
int contarPreguntasArchivo(const char* archivo)
{
    int cantPreguntas = contarElementosArchivo(archivo, 200);

    if (cantPreguntas >= 0)
    {
        //printf("Cantidad de preguntas: %d\n", cantPreguntas);
    }
    else
    {
        printf("Error al contar las preguntas.\n");
    }

    return cantPreguntas;
}

///MUESTRA UNA PREGUNTA CON SUS 4 RESPUESTAS
void mostrarPregunta(PreguntaPtr pregunta)
{
    printf("\n%d) %s\n\n", pregunta->nroPregunta, pregunta->pregunta);

    for (int i = 0; i < 4; i++)
    {
        mostrarRespuesta(pregunta->posibles[i], i + 1);
    }
}

void mostrarPreguntaMatematica(PreguntaMatematicaPtr pregunta)
{
    printf("\n%d) %s\n", pregunta->nroPregunta, pregunta->pregunta);
}

///LIBERA LA MEMORIA RESERVADA PARA UNA PREGUNTA CON SUS 4 RESPUESTAS
void liberarPregunta(PreguntaPtr pregunta)
{
    for (int i = 0; i < 4; i++)
    {
        liberarRespuesta(pregunta->posibles[i]);
    }
    free(pregunta);
}

///LIBERA LA MEMORIA RESERVADA PARA UNA PREGUNTA MATEMATICA
void liberarPreguntaMatematica(PreguntaMatematicaPtr pregunta)
{
    free(pregunta);
}


///CARGA TODAS LAS PREGUNTAS DE UN ARCHIVO EN UN VECTOR
PreguntaPtr* cargarPreguntasDesdeArchivo(const char* nombreArchivo, int cantPreguntas)
{
    FILE* archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }

    PreguntaPtr* preguntas = (PreguntaPtr*)malloc(cantPreguntas * sizeof(PreguntaPtr));

    for (int i = 0; i < cantPreguntas; i++)
    {
        preguntas[i] = crearPreguntaVacia();
        fscanf(archivo, "%d,%149[^\n]\n", &(preguntas[i]->nroPregunta), preguntas[i]->pregunta);
    }

    fclose(archivo);
    return preguntas;
}

PreguntaMatematicaPtr* cargarPreguntasMatematicasDesdeArchivo(const char* nombreArchivo, int cantPreguntasMatematicas)
{
    FILE* archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }

    PreguntaMatematicaPtr* preguntasMatematicas = (PreguntaMatematicaPtr*)malloc(cantPreguntasMatematicas * sizeof(PreguntaMatematicaPtr));

    for (int i = 0; i < cantPreguntasMatematicas; i++)
    {
        preguntasMatematicas[i] = crearPreguntaMatematicaVacia();
        fscanf(archivo, "%d,%d,%149[^\n]\n", &(preguntasMatematicas[i]->nroPregunta), &(preguntasMatematicas[i]->respuesta),preguntasMatematicas[i]->pregunta);
    }

    fclose(archivo);
    return preguntasMatematicas;
}



///MUESTRA TODAS LAS PREGUNTAS Y LAS RESPUESTAS DE UN VECTOR
void mostrarPreguntasVector(PreguntaPtr* preguntas, int cantPreguntas)
{
    for (int i = 0; i < cantPreguntas; i++)
    {
        mostrarPregunta(preguntas[i]);
    }
}

void mostrarPreguntasMatematicasVector(PreguntaMatematicaPtr* preguntasMatematicas, int cantPreguntasMatematicas)
{
    for (int i = 0; i < cantPreguntasMatematicas; i++)
    {
        mostrarPreguntaMatematica(preguntasMatematicas[i]);
    }
}
