#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#define QUERY1 1
#define QUERY2 2
#define QUERY3 3

typedef struct ciudadCDT * ciudadADT;

typedef struct tListaGenerica{ // lista auxiliar para devolver los datos ya procesados
	char * nombre;
	double resultado; // en un caso representa arboles, en otro indice, en otro diametro
	struct tListaGenerica * cola;
}tListaGenerica;

ciudadADT nuevaCiudad(); // crea una nueva ciudad

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion); // recibe el nombre de un barrio y la cantidad de
//habitantes y lo agrega a la ciudad

void ordenarBarrios(ciudadADT ciudad); // ordena alfabeticamente los barrios

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro); // recibe el nombre del barrio,
// la especie y el diametro del arbol y guarda estos datos en la ciudad

tListaGenerica * query(ciudadADT ciudad, size_t numero); // devuelve el puntero al primer nodo de la lista de salida

void freeCiudad(ciudadADT ciudad); // libera todos los recursos utilizados para almacenar los datos de la ciudad

void buscaBarrios(ciudadADT ciudad); // FUNCION DEBUG

void buscaArboles(ciudadADT ciudad); // FUNCION DEBUG
