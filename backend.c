#include "ciudadADT.h"

/////////////////////////////////////////////////estructura con los datos sin procesar/////////////////////////////
typedef struct tGeneral{
	char * nombre;
	double param1; // cantDeHabitantes o sumaDiametros
	unsigned long int param2; //cantdeArb
}tGeneral;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////estructura ordenada///////////////////////////////////////////////
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
//////////////////FALTA CHEQUEAR LOS ERRORES DE MEMORIA CON ERRNO///////////////////////////////////////
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
	}
	return 0;
}

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion) {
	if( ! pertenece(ciudad->barrios, nombre, ciudad->dimBarrios, NULL)) {
		ciudad->barrios = realloc(ciudad->barrios, sizeof(tBarrio) * (ciudad->dimBarrios + 1));
		if( ciudad->barrios == NULL ) {
			return 0;
		}
		strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
		ciudad->barrios[ciudad->dimBarrios].param1 = poblacion;
		ciudad->barrios[ciudad->dimBarrios++].param2 = 0;
	}
	return 1;
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

static void agregarArbolEnBarrio(ciudadCDT ciudad, char * nombre, int dim) { // BASADA EN BUSQUEDA BINARIA
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

static int agregarArbolEnBosque(ciudadADT ciudad, char * especie, double diametro){
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

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro) {
	AgregarArbolEnBarrio(ciudad, nombre, ciudad->dimBarrios);
	return AgregarArbolEnBosque(ciudad, especie, diametro);
}

static void queryGeneral(ciudadADT ciudad, tGeneral vector, size_t dim, size_t flag) { //llamada cuando se terminan de leer ambos archivos .csv
	double res;
	for(size_t i = 0; i < dim; i++) {
		tGenerica * new = malloc(sizeof(tGenerica)); // chequear error
		if(flag == QUERY1){
			res = vector[i].param2;
		}
		else if (	flag == QUERY2 ){
		  res = vector[i].param2 / vector[i].param1;
		}
		else{
			res = vector[i].param1 / vector[i].param2;
		}
		new->resultado = res; // casteo a double con 2 cifras signicativas luego de la coma, ver como hacerlo
		strcpy(new->nombre, vector[i].nombre);
		ingresarOrdenadoLista(new, ciudad->primerNodo);
	}
}

void query(ciudadADT ciudad, size_t numero){

	if( numero != QUERY3)
		queryGeneral(ciudad, ciudad->barrios, ciudad->dimBarrios, numero);
	else
	  queryGeneral(ciudad, ciudad->bosque, ciudad->dimBosque, QUERY3);
}
//calcula el indice y lo ingresa ordenado en una lista

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

static void freeRecLista(tListaGenerica * first){
	if(first == NULL){
		return;
	}
	freeRecLista(first->cola);
	tListaGenerica * aux = first;
	first = first->cola;
	free(aux);
	return;
}

void freeCiudad(ciudadADT ciudad) {
	freeRecLista(ciudad->primerNodo);
	free(ciudad->bosque);
	free(ciudad->barrios);
	free(collection);
}