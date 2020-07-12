#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define QUERY1 1
#define QUERY2 2
#define QUERY3 3

typedef struct ciudadCDT * ciudadADT;

typedef struct tListaGenerica{ // Lista auxiliar para devolver los datos ya procesados.
	char * nombre;
	double resultado; // En un caso representa arboles, en otro indice, en otro diametro.
	struct tListaGenerica * cola;
}tListaGenerica;

ciudadADT nuevaCiudad(); // Crea una nueva ciudad.

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion); // Recibe el nombre de un barrio y la cantidad de
//habitantes y lo agrega a la ciudad. Devuelve 0 en caso de que fallar al agregar barrio por falta de memoria. Devuelve 1
//si pudo agregarlo.

void ordenarBarrios(ciudadADT ciudad); // Ordena alfabeticamente los barrios para luego poder insertar los arboles
//con mayor facilidad.

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro); // Recibe el nombre del barrio,
// la especie y el diametro del arbol y guarda estos datos en la ciudad.
// IMPORTANTE: Antes de llamar a esta funcion, debe llamarse a ordenarBarrios.
// En caso de fallar al agregar el arbol por falta de memoria devuelve 0. Devuelve 1 si pudo agregarlo.

tListaGenerica * resuelveQuery(ciudadADT ciudad, size_t numero); // Devuelve el puntero al primer nodo de la lista de
// salida. En caso de fallar por insuficiencia de memoria devuelve NULL.

void freeCiudad(ciudadADT ciudad); // Libera todos los recursos utilizados para almacenar los datos de la ciudad.
