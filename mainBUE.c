#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query.h"
//CIUDAD AUTONOMA DE BUENOS AIRES
#define CAMPO_COMUNA 3
#define CAMPO_ESPECIE 8
#define CAMPO_DIAM 12

#define BUE 0
#define VAN 1

int main(int argc, char * argv[]) {
  ciudadADT newciudad = nuevaCiudad();
  leeBarrios(argv[2], newciudad);
  ordenarBarrios(newciudad);

  leeArboles(argv[1], newciudad, BUE, CAMPO_COMUNA, CAMPO_ESPECIE, CAMPO_DIAM);

  generarQuery(newciudad,QUERY1);
  generarQuery(newciudad,QUERY2);
  generarQuery(newciudad,QUERY3);

  freeCiudad(newciudad);
  return 0;
}