#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "juego.h"
#include "jugador.h"
#include "pregunta.h"
#include "respuesta.h"

///RESERVA MEMORIA PARA UN NUEVO JUEGO
JuegoPtr crearNuevoJuego()
{
    JuegoPtr nuevoJuego = (JuegoPtr)malloc(sizeof(struct Juego));
    if (nuevoJuego == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para una nueva partida\n");
        exit(1);
    }
    return nuevoJuego;
}

///CARGA JUGADORES EN LA MEMORIA RESERVADA PARA EL JUEGO
void cargarJugadores(JuegoPtr juego, int cantJugadores)
{
    printf("\n");
    for (int i = 0; i <cantJugadores; i++)
    {
        juego->jugadores[i]= crearJugadorVacio();
        juego->jugadores[i]->nroJugador = i + 1;
        printf("Cargando Jugador %d:\n", juego->jugadores[i]->nroJugador);

        cargarJugadorTeclado(juego->jugadores[i]);
        printf("\n");
    }
    printf("\x1b[32mJugadores cargados con exito.\x1b[0m\n\n");
}

///LIBERA LA MEMORIA RESERVADA PARA LOS JUGADORES DEL JUEGO
void liberarJugadores(JuegoPtr juego, int cantJugadores)
{
    for (int i = 0; i < cantJugadores; i++)
    {
        liberarJugador(juego->jugadores[i]);
    }
}

///LIBERA LA MEMORIA RESERVADA PARA EL JUEGO
void liberarJuego(JuegoPtr juego, int cantJugadores)
{
    liberarJugadores(juego, cantJugadores);
    free(juego);
}

///MUESTRA LA PANTALLA DE BIENVENIDA
void pantallaPrincipal()
{
    imprimirArchivoConFormato("bienvenida.txt", "%s");
    systemPauseGenerico();

    imprimirArchivoConFormato("instrucciones.txt", "%s");
    printf("QUE SE DIVIERTAN!\n");
    systemPauseGenerico();
}

///LIMPIA LA CONSOLA
void limpiarPantalla()
{
    printf("\033[2J\033[H");
}

///PAUSA LA PANTALLA PARA PODER LEER (GENERICO PARA DISTINTOS S.O.)
void systemPauseGenerico()
{
    printf("\nPresiona Enter para continuar...");
    fflush(stdin);
    getchar();
    limpiarPantalla();
}

///ACCEDE AL MENU PRINCIPAL
void menuPrincipal()
{
    int opcion;
    do
    {
        printf("--- MENU PRINCIPAL ---\n\n");
        imprimirArchivoConFormato("menu.txt", "%s");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 1:

            limpiarPantalla();

            printf("Seleccionaste la Opcion 1.\n");
            printf("\nNUEVA PARTIDA\n\n");
            systemPauseGenerico();

            int numJugadores = 0;

            numJugadores = seleccionarNumJugadores(numJugadores);

            JuegoPtr partida = crearNuevoJuego();

            cargarJugadores(partida, numJugadores);

            jugar(partida, numJugadores);

            liberarJuego(partida, numJugadores);

            systemPauseGenerico();
            menuPrincipal();
            break;

        case 2:

            mostrarJugadoresGuardados("jugadores.txt");

            systemPauseGenerico();
            menuPrincipal();
            break;

        case 3:

            printf("Gracias por jugar! Hasta la proxima!\n");

            systemPauseGenerico();
            break;
        }
    }
    while ((opcion < 1 || opcion > 3) && opcion != 3);
}

///DEVUELVE UN ENTERO ALEATORIO
int numeroAleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

///DEVUELVE UN ENTERO ENTRE 1 Y 4 CON LA OPCION SELECCIONADA PARA LA RESPUESTA
int seleccionarRespuesta(int n)
{
    printf("\nElige una respuesta: ");
    scanf("%d", &n);
    while ( n<1 || n>4 )
    {
        printf("La opcion ingresada no existe. Elija una respuesta valida entre 1 y 4\n");
        scanf("%d", &n);
    }
    return n;
}

///INICIA EL JUEGO
void jugar(JuegoPtr partidaActual, int numJugadores)
{
    printf("Que comience el juego!\n");
    systemPauseGenerico();

    int cantPreguntas = contarPreguntasArchivo("preguntas.txt");
    int cantRespuestas = contarRespuestasArchivo("respuestas.txt");

    int cantPreguntasDificiles = contarPreguntasArchivo("preguntasDificiles.txt");
    int cantRespuestasDificiles = contarRespuestasArchivo("respuestasDificiles.txt");

    PreguntaPtr* preguntas = cargarPreguntasDesdeArchivo("preguntas.txt", cantPreguntas);
    RespuestaPtr* respuestas = cargarRespuestasDesdeArchivo("respuestas.txt", cantRespuestas, preguntas);

    PreguntaPtr* preguntasDificiles = cargarPreguntasDesdeArchivo("preguntasDificiles.txt", cantPreguntasDificiles);
    RespuestaPtr* respuestasDificiles = cargarRespuestasDesdeArchivo("respuestasDificiles.txt", cantRespuestasDificiles, preguntasDificiles);
    ///NECESITO QUE EN LA DEVOLUCION ME EXPLIQUE QUE ES LO QUE PASA EN LA LINEA ANTERIOR CUANDO INTENTO ASIGNAR MEMORIA
    ///EL ERROR ME SALE SOLAMENTE SI CARGO MAS RESPUESTAS EN EL ARCHIVO respuestasDificiles.txt. EN ESTE MOMENTO NO ESTA DANDO ERROR
    ///(VERIFICAR CARGANDO MANUALMENTE UNA RESPUESTA MAS EN EL ARCHIVO respuestasDificiles.txt y las respectivas respuestas en el archivo respuestasDificiles.txt)

    int* indices = malloc(sizeof(int) * cantPreguntas);
    for (int i = 0; i < cantPreguntas; i++)
    {
        indices[i] = i;
    }
    int* indicesDificiles = malloc(sizeof(int) * cantPreguntasDificiles);
    for (int i = 0; i < cantPreguntasDificiles; i++)
    {
        indicesDificiles[i] = i;
    }

    int contadorPreguntas = 1;
    int contadorPreguntasDificiles = 1;

    for(int i=0; i<numJugadores; i++)
    {
        printf("\n----------------TURNO DEL JUGADOR %d----------------\n", i+1);
        mostrarJugador(partidaActual->jugadores[i]);
        systemPauseGenerico();

        shuffle(indices, cantPreguntas);
        shuffle(indicesDificiles, cantPreguntasDificiles);

        int respuestaIncorrecta=0;
        contadorPreguntas = 1;
        contadorPreguntasDificiles = 1;

        while (respuestaIncorrecta!=1)
        {
            int indicePregunta = indices[contadorPreguntas-1];

            if(contadorPreguntas % 5 == 0 && contadorPreguntas != 0)
            {
                int indicePreguntasDificiles = indicesDificiles[contadorPreguntasDificiles-1];


                printf("Jugador %d (%s)--> Pregunta Numero %d:\n", i+1, partidaActual->jugadores[i]->alias, contadorPreguntas);
                printf("\x1b[32m\nVAS MUY BIEN! A CONTINUACION VIENE PREGUNTA DIFICIL (SI RESPONDES BIEN SUMAS 3 PUNTOS)\n");


                mostrarPregunta(preguntasDificiles[indicePreguntasDificiles]);

                int respuestaElegida = 0;
                respuestaElegida = seleccionarRespuesta(respuestaElegida);

                for (int k=0; k<cantRespuestasDificiles; k++)
                {
                    if(preguntasDificiles[indicePreguntasDificiles]->nroPregunta == respuestasDificiles[k]->nroPreguntaAsociada)
                    {
                        if(respuestaElegida == respuestasDificiles[k]->nroRespuesta)
                        {
                            if(respuestasDificiles[k]->correcta==1)
                            {
                                printf("\x1b[32m\nBIEN HECHO!   +3 puntos\n");
                                partidaActual->jugadores[i]->puntuacion++;
                                partidaActual->jugadores[i]->puntuacion++;
                                partidaActual->jugadores[i]->puntuacion++;
                            }
                            else
                            {
                                printf("\x1b[31m\nRESPUESTA INCORRECTA :( \n\nTERMINO EL TURNO\n");
                                respuestaIncorrecta++;
                            }
                        }
                    }
                }
                contadorPreguntasDificiles++;
                contadorPreguntas++;
            }
            else
            {
                printf("Jugador %d (%s)--> Pregunta Numero %d:\n", i+1, partidaActual->jugadores[i]->alias, contadorPreguntas);
                mostrarPregunta(preguntas[indicePregunta]);

                int respuestaElegida = 0;
                respuestaElegida = seleccionarRespuesta(respuestaElegida);


                for (int k=0; k<cantRespuestas; k++)
                {
                    if(preguntas[indicePregunta]->nroPregunta == respuestas[k]->nroPreguntaAsociada)
                    {
                        if(respuestaElegida == respuestas[k]->nroRespuesta)
                        {
                            if(respuestas[k]->correcta==1)
                            {
                                printf("\x1b[32m\nRESPUESTA CORRECTA!   +1 punto\n");
                                partidaActual->jugadores[i]->puntuacion++;
                            }
                            else
                            {
                                printf("\x1b[31m\nRESPUESTA INCORRECTA :( \n\nTERMINO EL TURNO\n");
                                respuestaIncorrecta++;
                            }
                        }
                    }
                }
                contadorPreguntas++;
            }
            systemPauseGenerico();
        }
    }

    free(preguntas);
    free(respuestas);
    free(indices);
    free(preguntasDificiles);
    free(respuestasDificiles);
    free(indicesDificiles);

    mostrarJugadores(partidaActual, numJugadores);
    determinarGanador(partidaActual, numJugadores);
    guardarPuntajesMaximos("jugadores.txt", partidaActual, numJugadores);


}

///CUENTA LOS RENGLONES DE UN ARCHIVO Y DEVUELVE UN ENTERO
int contarElementosArchivo(const char* nombreArchivo, int tamLinea)
{
    int cantidad = 0;
    char linea[tamLinea];

    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        cantidad++;
    }

    fclose(archivo);
    return cantidad;
}

///IMPRIME UN ARCHIVO .TXT POR PANTALLA
void imprimirArchivoConFormato(const char* nombreArchivo, const char* formato)
{
    FILE* archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        fprintf(stderr, "Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char linea[300];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        printf(formato, linea);
    }

    fclose(archivo);
}

///MEZCLA UN ARREGLO UNIDIMENSIONAL
void shuffle(int arr[], int n)
{
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


///ITERA SOBRE LOS JUGADORES Y DEVUELVE LA PUNTUACION MAS ALTA
int encontrarMaxPuntuacion(JuegoPtr juego, int numJugadores)
{
    int maxPuntuacion = 0;

    for (int i = 0; i<numJugadores; i++)
    {
        if(juego->jugadores[i]->puntuacion > maxPuntuacion)
        {
            maxPuntuacion = juego->jugadores[i]->puntuacion;
        }
    }

    return maxPuntuacion;
}

int calcularDiferencia(int a, int b)
{
    int diferencia;
    diferencia = a - b;

    if (diferencia < 0)
    {
        diferencia = -diferencia;
    }

    return diferencia;
}

void determinarGanador(JuegoPtr partidaActual, int numJugadores)
{
    int maxPuntuacion = encontrarMaxPuntuacion(partidaActual, numJugadores);
    int* desempate = NULL;
    int jugadoresEmpatados = 0;

    for (int i = 0; i<numJugadores; i++)
    {
        if(partidaActual->jugadores[i]->puntuacion == maxPuntuacion)
        {
            jugadoresEmpatados++;
            desempate = (int*)realloc(desempate, jugadoresEmpatados * sizeof(int));
            desempate[jugadoresEmpatados-1] = partidaActual->jugadores[i]->nroJugador;
        }
    }

    int cantPreguntasMatematicas = contarPreguntasArchivo("preguntasMatematicas.txt");

    PreguntaMatematicaPtr* preguntasMatematicas = cargarPreguntasMatematicasDesdeArchivo("preguntasMatematicas.txt", cantPreguntasMatematicas);

    while (jugadoresEmpatados > 1)
    {

        printf("\nHay %d jugadores empatados:\n\n", jugadoresEmpatados);
        for (int i = 0; i < jugadoresEmpatados; i++)
        {
            printf("Jugador %d\n", desempate[i]);
        }

        jugadoresEmpatados=0;

        systemPauseGenerico();
        limpiarPantalla();

        int* indicesMatematicas = malloc(sizeof(int) * cantPreguntasMatematicas);
        for (int i = 0; i < cantPreguntasMatematicas; i++)
        {
            indicesMatematicas[i] = i;
        }

        shuffle(indicesMatematicas, cantPreguntasMatematicas);

        int contadorPreguntasMatematicas=0;
        int diferenciaMinima = 0;
        int respuestaCorrecta = 0;
        int contadorJugador = 0;

        for (int i = 0; i < numJugadores; i++)
        {
            if(partidaActual->jugadores[i]->puntuacion == maxPuntuacion)
            {
                contadorJugador++;

                printf("\nDESEMPATE! Responde la siguiente pregunta con un numero entero:\n\n");
                printf("\n----------------TURNO DEL JUGADOR %d----------------\n", partidaActual->jugadores[i]->nroJugador);

                mostrarPreguntaMatematica(preguntasMatematicas[indicesMatematicas[contadorPreguntasMatematicas]]);

                respuestaCorrecta = preguntasMatematicas[indicesMatematicas[contadorPreguntasMatematicas]]->respuesta;

                scanf("%d", &partidaActual->jugadores[i]->respuesta);
                printf("\n");

                int diferencia = calcularDiferencia(respuestaCorrecta, partidaActual->jugadores[i]->respuesta);

                if (contadorJugador == 1)
                {
                    diferenciaMinima = diferencia;
                }

                if(diferencia < diferenciaMinima)
                {
                    diferenciaMinima = diferencia;
                }
            }
        }

        printf("\n");
        printf("La respuesta correcta es: %d\n\n", preguntasMatematicas[indicesMatematicas[contadorPreguntasMatematicas]]->respuesta);

        for (int i = 0; i < numJugadores; i++)
        {
            if (partidaActual->jugadores[i]->respuesta + diferenciaMinima == respuestaCorrecta || partidaActual->jugadores[i]->respuesta - diferenciaMinima == respuestaCorrecta)
            {
                partidaActual->jugadores[i]->puntuacion++;
                printf("Jugador %d   +1 PUNTO!\n", partidaActual->jugadores[i]->nroJugador);
            }
        }

        printf("\n");
        maxPuntuacion = encontrarMaxPuntuacion(partidaActual, numJugadores);

        ///CUENTA CUANTOS JUGADORES HAY CON LA POSICION MAS ALTA Y LOS CARGA EN UN PUNTERO int* desempate;
        for (int i = 0; i<numJugadores; i++)
        {
            if(partidaActual->jugadores[i]->puntuacion == maxPuntuacion)
            {
                jugadoresEmpatados++;
                desempate = (int*)realloc(desempate, jugadoresEmpatados * sizeof(int));
                desempate[jugadoresEmpatados-1] = partidaActual->jugadores[i]->nroJugador;
            }
        }

        contadorPreguntasMatematicas++;
        contadorJugador = 0;
        diferenciaMinima=0;

        free(indicesMatematicas);
    }

    free(preguntasMatematicas);

    printf("\nEl ganador es el Jugador %d  FELICITACIONES!!\n\n", desempate[0]);

    free(desempate);
}





