#include "backend.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LONG 1024
#define CAMPOS_BARRIOS 2
#define CAMPOS_ARBOLES 3

// Esta funcion lee las lineas del archivo de barrios y prepara los datos para su posterior procesamiento.
void leeBarrios(const char * archivo, ciudadADT ciudad);

// Esta funcion lee las lineas del archivo de arboles y prepara los datos para su posterior procesamiento.
void leeArboles(const char * archivo, ciudadADT ciudad, size_t flag, size_t c1, size_t c2, size_t c3);
