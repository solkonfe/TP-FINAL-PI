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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CollectionADT.h"

/////////////////////////////////////////////////estructuras con los datos sin procesar/////////////////////////////
typedef struct tBarrio { // vamos a usar un vector de structs tBarrio para poder usar busqueda binaria cada vez que insertamos un arbol
	char * nombre;
	unsigned long int cantDeArboles;
	unsigned long int cantDeHabitantes;
}tBarrio;

typedef struct tArbol {
	char * nombre;
	float diametroTotal;
	unsigned long int cantArboles;
}tArbol;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////estructuras ordenadas///////////////////////////////////////////////
typedef struct tNodoBarrio { // o usar esta struct para el query 1 o ordenar devuelta el * barrios
	char * nombre;
	double indice; // arboles por cantDeHabitantes
	int cantdeArb;
	struct tNodoBarrio * cola;
}tNodoBarrio;

typedef struct tNodoArbol{
	char * especie;
	double diamPromedio;
	struct tNodoArbol * cola;
}tNodoArbol;

typedef struct tNodoCuenta{// posible creacion de una lista nueva(opcion2)
	int cantdeArb;
	char * nombre;
	struct tNodoCuenta * cola;
}tNodoCuenta;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ciudadCDT{
	// datos sin procesar
	tBarrio * barrios;   // vector de structs tBarrio
	size_t dimBarrios;
	tArbol * bosque;     // vector de structs tArbol
	size_t dimBosque;

	// listas que contendran los datos ordenados solicitados en las queries
	tNodoBarrio * primerBarrio; // primer nodo de la lista que contiene los indices por barrio (query 2)
	tNodoArbol * primerArbol;// primer tipo de arbol con su diametro promedio(query 3)
	tNodoCuenta * primerCuenta;

}ciudadCDT;

///////////////////////////////////////////////Funciones////////////////////////////////////////////////
ciudadADT nuevaCiudad(){
	return calloc(1, sizeof(ciudadADT));
}

void agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion) {
	ciudad->barrios = realloc(ciudad->barrios, sizeof(tBarrio) * (ciudad->dimBarrios + 1));

	if( ciudad->barrios == NULL ) { //// REVISAR
		printf("No hay espacio en memoria \n", );
		exit(1);
	}

	strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
	ciudad->barrios[ciudad->dimBarrios].cantDeHabitantes = poblacion;
	ciudad->barrios[ciudad->dimBarrios++].cantdeArb = 0;
}

static void intercambioBarrios(tBarrio * b1, tBarrio * b2) {
		tBarrio aux = * b1;
		*b1 = *b2;
		*b2 = aux;
}

void ordenarBarrios(ciudadADT ciudad){
		for(int i = 0; i < ciudad->dimBarrios - 1; i++) {
			for(int j = i + 1; j < ciudad->dimBarrios; j++) {
				if(strcmp(ciudad->barrios[i].nombre, ciudad->barrios[j].nombre) > 0){
					intercambioBarrios(ciudad->barrios[i], ciudad->barrios[j]);
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
			ciudad->barrios[medio].cantdeArb++;
		else if ( c < 0 )
			ultimo = medio - 1;
		else
			primero = medio + 1;
	}
}

static void AgregarArbolesEnBosque(ciudadADT ciudad, char * especie, double diametro){
	int i;
	for(i = 0; i < ciudad->dimBosque; i++) {
		if (strcmp(ciudad->bosque[i].especie, especie) == 0) {
			ciudad->bosque[i].diametroTotal += diametro; // REVISAR NO REPETIR CODIGO
			ciudad->bosque[i].cantArboles += 1;
			return;
		}
	}
	//si es un bosque vacio o hay una nueva especie
	ciudad->bosque = realloc(ciudad->bosque, (ciudad->dimBosque + 1) * sizeof(tArbol)); // FALTA VERIFICAR REALLOC
	ciudad->dimBosque += 1;
	strcpy(ciudad->bosque[i].especie, nombre);
	ciudad->bosque[i].diametroTotal += diametro; // REVISAR NO REPETIR CODIGO
	ciudad->bosque[i].cantArboles += 1;
	return;
}

void AgregarArbol(ciudadADT ciudad, char *nombre, char * especie, double diametro) {
	AgregarArbolsEnBarrio(ciudad, nombre, dim);
	AgregarArbolesEnBosque(ciudad, especie, diametro);
}
