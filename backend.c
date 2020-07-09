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
typedef struct tBarrio { // vamos a usar un vector de structs tBarrio para poder usar busqueda binaria cada vez que insertamos un arbol
	char * nombre;
	unsigned long int cantDeArboles;
	unsigned long int cantDeHabitantes;
}tBarrio;

typedef struct tArbol {
	char * especie;
	float diametroTotal;
	unsigned long int cantArboles;
}tArbol;

/* typedef struct tGeneral{
	char * nombre;
	double param1;
	unsigned long int param2;
}tGeneral; */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////estructuras ordenadas///////////////////////////////////////////////
typedef struct tGenerica{
	char * nombre;
	double resultado; // en un caso representa arboles, en otro indice, en otro diametro
	struct aux * cola;
}tGenerica;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ciudadCDT{
	// datos sin procesar
	tBarrio * barrios;   // vector de structs tBarrio
	size_t dimBarrios;
	tArbol * bosque;     // vector de structs tArbol
	size_t dimBosque;

	tGenerica * primerNodo;
}ciudadCDT;

typedef ciudadCDT * ciudadADT;// va en el .h

///////////////////////////////////////////////Funciones////////////////////////////////////////////////
ciudadADT nuevaCiudad(){
	return calloc(1, sizeof(ciudadADT));
}

static int pertenece(tBarrio * barrio, char * nombre, size_t dim) {
	for(int i = 0; i < dim; i++){
		if(strcmp(barrio[i].nombre, nombre) == 0)
			return 1;
	}
	return 0;
}

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion) {
	if( ! pertenece(ciudad->barrios, nombre, ciudad->dimBarrios)){
		ciudad->barrios = realloc(ciudad->barrios, sizeof(tBarrio) * (ciudad->dimBarrios + 1));
		if( ciudad->barrios == NULL ) {
			return 1;
		}

		strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
		ciudad->barrios[ciudad->dimBarrios].cantDeHabitantes = poblacion;
		ciudad->barrios[ciudad->dimBarrios++].cantdeArb = 0;
		return 0;
	}
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

static int AgregarArbolEnBosque(ciudadADT ciudad, char * especie, double diametro){
	int i;
	for(i = 0; i < ciudad->dimBosque; i++) { // reutilizar pertenece
		if (strcmp(ciudad->bosque[i].especie, especie) == 0) {
			ciudad->bosque[i].diametroTotal += diametro; // REVISAR NO REPETIR CODIGO
			ciudad->bosque[i].cantArboles += 1;
			return 0;
		}
	}
	//si es un bosque vacio o hay una nueva especie
	ciudad->bosque = realloc(ciudad->bosque, (ciudad->dimBosque + 1) * sizeof(tArbol));
	if(ciudad->bosque == NULL ) {
		return 1;
	}
	ciudad->dimBosque += 1;
	strcpy(ciudad->bosque[i].especie, nombre);
	ciudad->bosque[i].diametroTotal += diametro; // REVISAR NO REPETIR CODIGO
	ciudad->bosque[i].cantArboles += 1;
	return 0;
}

int AgregarArbol(ciudadADT ciudad, char *nombre, char * especie, double diametro) {
	AgregarArbolEnBarrio(ciudad, nombre, ciudad->dimBarrios);
	return AgregarArbolEnBosque(ciudad, especie, diametro);
}

//calcula el indice y lo ingresa ordenado en una lista
void query2(ciudadADT ciudad){//llamada cuando se terminan de leer ambos archivos .csv
	// si se llama cuando se terminan de leer ambos archivos no seria mejor pasarle ciudad
	// y dsp por cada indice del vecor de barrios calculas el indice de cant de habitantes y por cada cuenta lo mandas a la lista nueva
	for(int i = 0; i < ciudad->dimBarrios ; i++){
		tGenerica * new = malloc(sizeof(tNodoBarrio));
		new->resultado = ((double)ciudad->barrios[i].cantdeArb)/ciudad->barrios[i].cantDeHabitantes;// casteo a double con 2 cifras signicativas luego de la coma, ver como hacerlo
		strcpy(new->nombre, ciudad->barrios[i].nombre);
		ingresarOrdenadoLista(new, ciudad->primerBarrio);
	}
	return;
}

//calcula el promedio de los diametros y lo ingresa oredenados en una lista
void query3(ciudadADT ciudad){
	for(int i = 0; i < ciudad->dimBosque; i++){
		tGenerica * new = malloc(sizeof(tNodoArbol));
		strcpy(new->nombre, ciudad->bosque[i].nombre);
		new->resultado = ciudad->bosque[i].diametroTotal/(double)(ciudad->bosque[i].cantArboles);
		ingresarOrdenadoLista(new, ciudad->primerArbol);
	}
	return;
}

void query1(ciudadADT ciudad){
	for(int i = 0; i < ciudad->dimBarrios ; i++){
		tGenerica * new = malloc(sizeof(tNodoCuenta));
		new->resultado = ciudad->bosque[i].cantDeArboles;
		strcpy(new->nombre, ciudad->bosque[i].nombre);
		ingresarOrdenadoLista(new, ciudad->primerCuenta);
	}
	return;
}

static void ingresarOrdenadoLista(tGenerica * nodo, tGenerica * lista){
	tGenerica * aux = lista;
	tGenerica * prev = NULL;
	for(; aux != NULL; prev = aux, aux = aux -> cola){
		if(nodo->resultado > aux->resultado || aux->resultado == new->resultado && strcmp(aux->nombre, new->nombre) > 0){
			if(prev == NULL){//tengo que cambiar a donde apunta el primero
				nodo->cola = lista;
				lista = new;
			}
			else{
				prev->cola = nodo;
				nodo->cola = aux;
			}
			return;
		}
	}
	if(prev == NULL){//no hay nodo ingresado
		nodo->cola = NULL;
		lista = new;
	}
	else{//lo pongo a lo ultimo
		prev->cola = nodo;
		nodo->cola = NULL;
	}
	return;
}

static void freeRecindex(tNodeIndex * first){
	if(first == NULL){
		return;
	}
	freeRecindex(first->tail);
	tNodeIndex * aux = first;
	first = first->tail;
	free(aux);
	return;
}

static void freeRecProm(tNodeProm * first){
	if(first == NULL){
		return;
	}
	freeRecindex(first->tail);
	tNodeProm * aux = first;
	first = first->tail;
	free(aux);
	return;
}

void freeCollection(collectionADT collection) { //CAMBIAR NOMBRES
	freeRecindex(collection->firstI);
	freeRecProm(collection->firstP);
	free(collection->vContador);
	free(collection->vDiamProm);
	free(collection);
}
