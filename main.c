
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* VANCOUVER
#define CAMPO_COMUNA 13
#define CAMPO_ESPECIE 5
#define CAMPO_DIAM 16
*/
#define CAMPO_COMUNA 3
#define CAMPO_ESPECIE 8
#define CAMPO_DIAM 12

#include "backend.h"
#include "lectura.h"

int main(int argc, char * argv[]) {
  ciudadADT newciudad = nuevaCiudad();
  leeBarrios(argv[2], newciudad);
  ordenarBarrios(newciudad);

  leeArboles(argv[1], newciudad, 0,CAMPO_COMUNA, CAMPO_ESPECIE, CAMPO_DIAM);
  buscaArboles(newciudad);
  buscaBarrios(newciudad);
  return 0;
}
