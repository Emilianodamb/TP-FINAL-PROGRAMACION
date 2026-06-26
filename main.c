#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "juego.h"
#include "pregunta.h"

int main()
{
    srand(time(NULL));

    pantallaPrincipal();

    menuPrincipal();

    return 0;
}
