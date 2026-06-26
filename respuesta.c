#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pregunta.h"
#include "respuesta.h"
#include "juego.h"


///CREA UNA RESPUESTA VACIA
RespuestaPtr crearRespuestaVacia()
{
    RespuestaPtr nuevaRespuesta = (RespuestaPtr)malloc(sizeof(struct Respuesta));

    if (nuevaRespuesta != NULL)
    {
        nuevaRespuesta->nroRespuesta = 0;
        strcpy(nuevaRespuesta->respuesta, "");
        nuevaRespuesta->nroPreguntaAsociada = 0;
        nuevaRespuesta->correcta = 0;
    }

    return nuevaRespuesta;
}

///CUENTA LOS RENGLONES DE UN ARCHIVO Y LOS TRADUCE A NUMERO DE PREGUNTAS
int contarRespuestasArchivo(const char* archivo)
{
    int cantRespuestas = contarElementosArchivo(archivo, 200);

    if (cantRespuestas >= 0)
    {
        //printf("Cantidad de respuestas: %d\n", cantRespuestas);
    }
    else
    {
        printf("Error al contar las respuestas.\n");
    }
    return cantRespuestas;
}

///MUESTRA UNA RESPUESTA
void mostrarRespuesta(RespuestaPtr respuesta, int numero)
{
    printf("%d. %s\n", numero, respuesta->respuesta);
}

///MUESTRA TODAS LAS RESPUESTAS DE UN VECTOR
void mostrarRespuestasVector(RespuestaPtr* respuestas, int cantRespuestas)
{
    for (int i = 0; i < cantRespuestas; i++)
    {
        mostrarRespuesta(respuestas[i], i + 1);
    }
}

///LIBERA LA MEMORIA RESERVADA PARA UNA RESPUESTA
void liberarRespuesta(RespuestaPtr respuesta)
{
    free(respuesta);
}

/// CARGA TODAS LAS RESPUESTAS DE UN ARCHIVO EN UN VECTOR
RespuestaPtr* cargarRespuestasDesdeArchivo(const char* nombreArchivo, int cantRespuestas, PreguntaPtr* preguntas)
{
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }

    RespuestaPtr* respuestas = (RespuestaPtr*)malloc(cantRespuestas * sizeof(RespuestaPtr));

    for (int i = 0; i < cantRespuestas; i++)
    {
        respuestas[i] = crearRespuestaVacia();
        fscanf(archivo, "%d,%49[^,],%d,%d\n", &(respuestas[i]->nroRespuesta), respuestas[i]->respuesta, &(respuestas[i]->nroPreguntaAsociada), &(respuestas[i]->correcta));

        // Asociamos la respuesta a la pregunta correspondiente
        PreguntaPtr preguntaAsociada = preguntas[respuestas[i]->nroPreguntaAsociada - 1];
        preguntaAsociada->posibles[i % 4] = respuestas[i]; ///Aca me mostraba un error que no pude descifrar cuando quería cargar las respuestas de las preguntas dificiles
    }

    fclose(archivo);
    return respuestas;
}


/// CARGA TODAS LAS RESPUESTAS DE UN ARCHIVO EN UN VECTOR
RespuestaPtr* cargarRespuestasDificilesDesdeArchivo(const char* nombreArchivo, int cantRespuestas, PreguntaPtr* preguntas)
{
    FILE* archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }

    RespuestaPtr* respuestas = (RespuestaPtr*)malloc(cantRespuestas * sizeof(RespuestaPtr));

    for (int i = 0; i < cantRespuestas; i++)
    {
        respuestas[i] = crearRespuestaVacia();
        fscanf(archivo, "%d,%49[^,],%d,%d\n", &(respuestas[i]->nroRespuesta), respuestas[i]->respuesta, &(respuestas[i]->nroPreguntaAsociada), &(respuestas[i]->correcta));

        // Asociamos la respuesta a la pregunta correspondiente
        PreguntaPtr preguntaDificilAsociada = preguntas[respuestas[i]->nroPreguntaAsociada - 1];
        preguntaDificilAsociada->posibles[i % 4] = respuestas[i];
    }

    fclose(archivo);
    return respuestas;
}
