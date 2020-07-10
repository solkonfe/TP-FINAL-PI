#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#define QUERY1 1
#define QUERY2 2
#define QUERY3 3
typedef struct ciudadCDT * ciudadADT;

ciudadADT nuevaCiudad();

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion);

void ordenarBarrios(ciudadADT ciudad);

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro);

void query(ciudadADT ciudad, size_t numero);

void freeCiudad(ciudadADT ciudad);

void buscaBarrios(ciudadADT ciudad);

void buscaArboles(ciudadADT ciudad);
