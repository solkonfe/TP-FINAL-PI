/*PASO 1: leer archivo barriosBUE.csv // esto es front
guardando los barrios de una
barrio1 barrio8 barrio20 barrio3 barrio6
PASO 2: ordenar los barrios (INEFICIENTE) (PERO ESTO SE EJECUTA 1 SOLA VEZ)
barrio1 barrio3 barrio6 barrio8 barrio20
PASO 3: leer archivo arbolesBUE.csv // esto es front
for(final del vector) (INEFICIENTE) orden n^2 (n = 370 mil)
	cuando lo encuentra: suma un arbol y se va
busqueda binaria (eficiente) orden log2 n (n = 370 mil)
PASO 4: ordenar el mismo vector de barrios pero ahora por total de arboles O hacer una lista
PASO 5: ordenar el mismo vector de barrios pero ahora por indice O hacer una lista
PASO 6: armar la lista con especies ordenadas por diametro promedio
PASO 7: (no sabemos si es back o front) armar los archivos csv de salida
*/

/*
BACKEND.C
Arreglar ordenarBarrios para que elimine barrios repetidos. HECHO
Retornar 1 o 0 cada vez que hagamos una funcion que use malloc/calloc/realloc. (agregar barrios, y agregar arbol en bosque)
Revisar las funciones de lautaro y arreglar los errores si es que los hay.
Nuevo free.


lectura.c
Armarlo con el nuevo formato y borrar el int main
Decidir si abortamos cuando hay errores en la reserva de memoria


main.c
hacerlo


query.c
hacerlo completo

}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CollectionADT.h"

/////////////////////////////////////////////////estructuras con los datos sin procesar/////////////////////////////
typedef struct tGeneral{
	char * nombre;
	double param1; // cantDeHabitantes o sumaDiametros
	unsigned long int param2; //cantdeArb
}tGeneral;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////estructuras ordenadas///////////////////////////////////////////////
typedef struct tListaGenerica{
	char * nombre;
	double resultado; // en un caso representa arboles, en otro indice, en otro diametro
	struct aux * cola;
}tListaGenerica;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ciudadCDT{
	// datos sin procesar
	tGeneral * barrios;   // vector de structs tBarrio
	size_t dimBarrios;
	tGeneral * bosque;     // vector de structs tArbol
	size_t dimBosque;

	tListaGenerica * primerNodo;
}ciudadCDT;


///////////////////////////////////////////////Funciones////////////////////////////////////////////////
ciudadADT nuevaCiudad(){
	return calloc(1, sizeof(ciudadADT));
}

static int pertenece(tGeneral * vector, char * nombre, size_t dim, size_t * indice) {
	for(int i = 0; i < dim; i++) {
		if(strcmp(vector[i].nombre, nombre) == 0) {
			if(indice != NULL)
				*indice = i;
			return 1;
	}
	return 0;
}

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion) {
	if( ! pertenece(ciudad->barrios, nombre, ciudad->dimBarrios, NULL)) {
		ciudad->barrios = realloc(ciudad->barrios, sizeof(tBarrio) * (ciudad->dimBarrios + 1));
		if( ciudad->barrios == NULL ) {
			return 1;
		}
		strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
		ciudad->barrios[ciudad->dimBarrios].param1 = poblacion;
		ciudad->barrios[ciudad->dimBarrios++].param2 = 0;
	}
	return 0;
}

static void intercambioVec(tGeneral * b1, tGeneral * b2) {
		tGeneral aux = * b1;
		*b1 = *b2;
		*b2 = aux;
}

void ordenarBarrios(ciudadADT ciudad){
		for(int i = 0; i < ciudad->dimBarrios - 1; i++) {
			for(int j = i + 1; j < ciudad->dimBarrios; j++) {
				if(strcmp(ciudad->barrios[i].nombre, ciudad->barrios[j].nombre) > 0){
					intercambioVec(ciudad->barrios[i], ciudad->barrios[j]);
				}
			}
		}
}

static void AgregarArbolEnBarrio(ciudadCDT ciudad, char * nombre, int dim) { // BASADA EN BUSQUEDA BINARIA
	int ultimo = dim -1;
	int medio, c;
	int primero = 0;
	while(ultimo >= primero) {
		medio = (primero + ultimo) / 2;
		if( (c = strcmp(ciudad->barrios[medio].nombre,nombre)) == 0 )
			ciudad->barrios[medio].param2++;
		else if ( c < 0 )
			ultimo = medio - 1;
		else
			primero = medio + 1;
	}
}

static int AgregarArbolEnBosque(ciudadADT ciudad, char * especie, double diametro){
	size_t indice;
	if(!pertenece(ciudad->bosque, especie, ciudad->dimBosque, &indice)) {
		ciudad->bosque = realloc(ciudad->bosque, (ciudad->dimBosque + 1) * sizeof(tArbol));
		if(ciudad->bosque == NULL ) {
			return 1;
		}
		ciudad->dimBosque += 1;
	}
	strcpy(ciudad->bosque[indice].especie, nombre);
	ciudad->bosque[indice].param1 += diametro;
	ciudad->bosque[indice].param2 += 1;
	return 0;
}