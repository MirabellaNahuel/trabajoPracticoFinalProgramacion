#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "CLIENTES.h"
#include "CONSUMOS.h"
#include "MENU.h"
#include "gotoxy.h"
#include "windows.h"
#include "ARBOLCLIENTES.h"

#define ESC 27
#define DIM_CONSUMOS 500
#define DIM_CLIENTES 100
#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_CONSUMOS "consumos.bin"

int main()
{
    muestraMenu();

    return 0;
}
