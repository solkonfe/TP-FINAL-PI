#include "backend.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LONG 1024
#define CAMPOS_BARRIOS 2
#define CAMPOS_ARBOLES 3

void leeBarrios(const char * archivo, ciudadADT ciudad);
void leeArboles(const char * archivo, ciudadADT ciudad, size_t flag, size_t c1, size_t c2, size_t c3);
