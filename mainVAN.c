#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query.h"
///*VANCOUVER
#define CAMPO_COMUNA 13
#define CAMPO_ESPECIE 7
#define CAMPO_DIAM 16

#define BUE 0
#define VAN 1

int main(int argc, char * argv[]) {
  ciudadADT newciudad = nuevaCiudad();
  leeBarrios(argv[2], newciudad);
  ordenarBarrios(newciudad);

  leeArboles(argv[1], newciudad, VAN,CAMPO_COMUNA, CAMPO_ESPECIE, CAMPO_DIAM);

  generarQuery(newciudad,QUERY1);
  generarQuery(newciudad,QUERY2);
  generarQuery(newciudad,QUERY3);

  freeCiudad(newciudad);
  return 0;
}