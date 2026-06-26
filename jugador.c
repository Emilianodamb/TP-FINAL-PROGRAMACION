#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "jugador.h"

///RESERVAR MEMORIA

FILE* abrirArchivo(const char* nombreArchivo, const char* modo)
{
    FILE* archivo = fopen(nombreArchivo, modo);

    if (archivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s.\n", nombreArchivo);
        system("PAUSE");
        exit(1);
    }

    return archivo;
}

JugadorPtr crearJugadorVacio()
{
    JugadorPtr nuevoJugador = (JugadorPtr)malloc(sizeof(struct Jugador));

    if (nuevoJugador != NULL)
    {
        nuevoJugador->nroJugador = 0;
        nuevoJugador->dni = 0;
        nuevoJugador->alias[0] = '\0';
        nuevoJugador->puntuacion = 0;
        nuevoJugador->respuesta = 0;
    }
    else
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para un nuevo Jugador\n");
        return NULL;
    }

    return nuevoJugador;
}

///-----TRABAJAR CON MEMORIA RESERVADA


///DEVUELVE UN ENTERO ENTRE 2 Y 4 CON LA CANTIDAD DE JUGADORES PARA LA PARTIDA
int seleccionarNumJugadores(int n)
{
    printf("Ingrese la cantidad de jugadores (de 2 a 4):\n");
    scanf("%d", &n);
    while ( n<2 || n>4 )
    {
        printf("Solo se puede jugar de 2 a 4 jugadores. Vuelva a ingresar un numero entre 2 y 4\n");
        scanf("%d", &n);
    }
    return n;
}

///CUENTA LOS RENGLONES DE UN ARCHIVO Y LOS TRADUCE A NUMERO DE JUGADORES
int contarJugadoresArchivo(const char* archivo)
{
    int cantJugadores = contarElementosArchivo(archivo, 100);

    if (cantJugadores >= 0)
    {
        //printf("Cantidad de jugadores: %d\n", cantJugadores);
    }
    else
    {
        printf("Error al contar los jugadores.\n");
    }

    return cantJugadores;
}

///MUESTRA UN JUGADOR POR PANTALLA
void mostrarJugador(JugadorPtr j)
{
    printf("ALIAS: %s\tDNI: %d\tPUNTAJE: %d\n\n", j->alias, j->dni, j->puntuacion);
}


///MUESTRA A TODOS LOS JUGADORES DEL JUEGO POR PANTALLA
void mostrarJugadores(JuegoPtr juego, int numJugadores)
{
    for(int i = 0; i < numJugadores; i++)
    {
        printf("\n----------------JUGADOR %d----------------\n", juego->jugadores[i]->nroJugador);
        mostrarJugador(juego->jugadores[i]);
    }
}


void ordenarJugadoresArchivo(JugadorPtr* jugadores, int cantidad)
{
    int i, j;
    JugadorPtr temp;
    for (i = 1; i < cantidad; i++)
    {
        temp = jugadores[i];
        j = i - 1;
        while (j >= 0 && jugadores[j]->dni > temp->dni)
        {
            jugadores[j + 1] = jugadores[j];
            j = j - 1;
        }
        jugadores[j + 1] = temp;
    }
}

///PIDE POR PANTALLA ALIAS Y DNI DE UN JUGADOR PARA LA PARTIDA
void cargarJugadorTeclado(JugadorPtr jugador)
{
    printf("Ingrese DNI: ");
    scanf("%d", &(jugador->dni));
    printf("Ingrese alias: ");
    scanf("%20s", jugador->alias);
}

void guardarPuntajesMaximos(const char* nombreArchivo, JuegoPtr partidaActual, int numJugadores)
{
    int tam = contarJugadoresArchivo("jugadores.txt");
    FILE * archivo = abrirArchivo(nombreArchivo, "r");

    JugadorPtr* jugadoresEnArchivo = (JugadorPtr*) malloc(tam * sizeof(JugadorPtr));
    int pos = 0;

    while (!feof(archivo))
    {
        JugadorPtr nuevoJugador = (JugadorPtr) malloc(sizeof(struct Jugador));
        if (nuevoJugador == NULL)
        {
            printf("Error: No se pudo asignar memoria para un nuevo Jugador\n");
            for (int i = 0; i < pos; i++)
            {
                free(jugadoresEnArchivo[i]);
            }
            free(jugadoresEnArchivo);
            fclose(archivo);
            exit(EXIT_FAILURE);
        }

        fscanf(archivo, "%d,%20[^,],%d\n", &(nuevoJugador->dni), nuevoJugador->alias, &(nuevoJugador->puntuacion));
        jugadoresEnArchivo[pos] = nuevoJugador;
        (pos)++;
    }

    int yaEsta = 0;
    for(int i=0; i<tam ; i++)
    {
        for(int j=0; j<numJugadores; j++)
        {
            if(jugadoresEnArchivo[i]->dni == partidaActual->jugadores[j]->dni)
            {
                yaEsta++;

                if(jugadoresEnArchivo[i]->puntuacion < partidaActual->jugadores[j]->puntuacion)
                {
                    jugadoresEnArchivo[i]->puntuacion = partidaActual->jugadores[j]->puntuacion;
                    strcpy(jugadoresEnArchivo[i]->alias, partidaActual->jugadores[j]->alias);
                }
            }
        }
    }

    int nuevoTam = tam + numJugadores - yaEsta;
    JugadorPtr* jugadoresParaNuevoArchivo = (JugadorPtr*) malloc(nuevoTam * sizeof(JugadorPtr));

    int indiceNuevo = 0;
    for(int i = 0; i < tam; i++)
    {
        jugadoresParaNuevoArchivo[indiceNuevo++] = jugadoresEnArchivo[i];
    }

    for(int j = 0; j < numJugadores; j++)
    {
        int dniActual = partidaActual->jugadores[j]->dni;
        int encontrado = 0;

        for(int i = 0; i < tam; i++)
        {
            if(jugadoresEnArchivo[i]->dni == dniActual)
            {
                encontrado = 1;
                break;
            }
        }

        if(!encontrado)
        {
            jugadoresParaNuevoArchivo[indiceNuevo++] = partidaActual->jugadores[j];
        }
    }

    FILE* nuevoArchivo = abrirArchivo(nombreArchivo, "w");

    for(int i = 0; i < nuevoTam; i++)
    {
        fprintf(nuevoArchivo, "%d,%s,%d\n", jugadoresParaNuevoArchivo[i]->dni, jugadoresParaNuevoArchivo[i]->alias, jugadoresParaNuevoArchivo[i]->puntuacion);
    }

    fclose(nuevoArchivo);

    for(int i = 0; i < tam; i++)
    {
        free(jugadoresEnArchivo[i]);
    }

    free(jugadoresEnArchivo);
    free(jugadoresParaNuevoArchivo);
}

void mostrarJugadoresGuardados(const char* nombreArchivo)
{
    FILE* archivo = abrirArchivo(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    Jugador jugador;

    while (fscanf(archivo, "%d,%20[^,],%d\n", &(jugador.dni), jugador.alias, &(jugador.puntuacion)) == 3)
    {
        if(jugador.dni>9)
        {
            printf("DNI:  %d\tALIAS:  %s\tPUNTUACION MAXIMA:  %d\n", jugador.dni, jugador.alias, jugador.puntuacion);
        }
        else
        {
            printf("DNI:  %d\t\tALIAS:  %s\tPUNTUACION MAXIMA:  %d\n", jugador.dni, jugador.alias, jugador.puntuacion);
        }
    }

    fclose(archivo);
}

///LIBERAR MEMORIA

///LIBERA LA MEMORIA RESERVADA PARA UN JUGADOR
void liberarJugador(JugadorPtr jugador)
{
    free(jugador);
}


