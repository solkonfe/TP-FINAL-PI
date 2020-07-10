<<<<<<< HEAD
#include "backend.h"

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
	struct tListaGenerica * cola;
}tListaGenerica;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ciudadCDT{
	// datos sin procesar
	struct tGeneral * barrios;   // vector de structs tBarrio
	size_t dimBarrios;
	struct tGeneral * bosque;     // vector de structs tArbol
	size_t dimBosque;

	struct tListaGenerica * primerNodo;
}ciudadCDT;


///////////////////////////////////////////////Funciones////////////////////////////////////////////////
//////////////////FALTA CHEQUEAR LOS ERRORES DE MEMORIA CON ERRNO///////////////////////////////////////

ciudadADT nuevaCiudad(){ // FUNCION CHEQUEADA
	return calloc(1, sizeof(ciudadCDT)); // VERIFICACION DE ERRNO
}

static int pertenece(tGeneral * vector, char * nombre, size_t dim, size_t * indice) { // FUNCION CHEQUEADA
	for(int i = 0; i < dim; i++) {
		if(strcmp(vector[i].nombre, nombre) == 0) {
			if(indice != NULL)
				*indice = i;
			return 1;
		}
	}
	return 0;
}

int agregarBarrio(ciudadADT ciudad, char * nombre, int poblacion) { // FUNCION CHEQUEADA
	if( ! pertenece(ciudad->barrios, nombre, ciudad->dimBarrios, NULL)) {
		ciudad->barrios = realloc(ciudad->barrios, sizeof(tGeneral) * (ciudad->dimBarrios + 1));
		if( ciudad->barrios == NULL ) { // ESTA VERIFICACION HAY QUE CORREGIRLA CON ERRNO
			return 0;
		}
		ciudad->barrios[ciudad->dimBarrios].nombre = malloc(strlen(nombre));
		// VERIFICAR MALLOC CON ERRNO
		strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
		ciudad->barrios[ciudad->dimBarrios].param1 = poblacion;
		ciudad->barrios[ciudad->dimBarrios++].param2 = 0;
	}
	return 1;
}

static void intercambioVec(tGeneral * b1, tGeneral * b2) { // FUNCION CHEQUEADA
		tGeneral aux = *b1;
		*b1 = *b2;
		*b2 = aux;
}

void ordenarBarrios(ciudadADT ciudad){ // FUNCION CHEQUEADA
		for(int i = 0; i < ciudad->dimBarrios - 1; i++) {
			for(int j = i + 1; j < ciudad->dimBarrios; j++) {
				if(strcmp(ciudad->barrios[i].nombre, ciudad->barrios[j].nombre) > 0){
					intercambioVec(&(ciudad->barrios[i]), &(ciudad->barrios[j]));
				}
			}
		}
}

static void agregarArbolEnBarrio(ciudadADT ciudad, char * nombre) { // BASADA EN BUSQUEDA BINARIA
	int ultimo = ciudad->dimBarrios - 1; // ultimo = 2
	int medio,c;
	int primero = 0;
	while(primero <= ultimo) {
		medio = (primero + ultimo) / 2; // medio = 1
		if( (c = strcmp(ciudad->barrios[medio].nombre, nombre)) == 0 ) {
			ciudad->barrios[medio].param2++;
			return;
		}
		else if ( c < 0 )
			primero = medio + 1;
		else
			ultimo = medio - 1;
	}
}
//ciudadnombres - nombre > 0 primero = mitad + 1

/*
int bBinaria(int n,int x[],int t)
{
    int mitad,izq,der;
    izq=0;der=n-1;
    while(izq<=der)
    {
        mitad = (izq+der)/2;
        if(t>x[mitad])izq = mitad+1;
        else if(t<x[mitad]) der = mitad-1;
        else return mitad;
    }
    return -1;
}*/

static int agregarArbolEnBosque(ciudadADT ciudad, char * especie, double diametro){
	size_t indice = ciudad->dimBosque;

	if(!pertenece(ciudad->bosque, especie, ciudad->dimBosque, &indice)) {
		ciudad->bosque = realloc(ciudad->bosque, (ciudad->dimBosque + 1) * sizeof(tGeneral)); // VERIFICAR REALLOC
		ciudad->bosque[ciudad->dimBosque].nombre = malloc(strlen(especie)); // VERIFICAR MALLOC
		strcpy(ciudad->bosque[ciudad->dimBosque++].nombre, especie);
	}

	ciudad->bosque[indice].param1 += diametro;
	ciudad->bosque[indice].param2 += 1;
	return 1; // chequear
}

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro) {
	agregarArbolEnBarrio(ciudad, nombre);
	return agregarArbolEnBosque(ciudad, especie, diametro);
}

static void ingresarOrdenadoLista(tListaGenerica * nodo, tListaGenerica * lista) {
	tListaGenerica * aux = lista;
	tListaGenerica * prev = NULL;
	for(; aux != NULL; prev = aux, aux = aux -> cola){
		if( (nodo->resultado > aux->resultado) || ((aux->resultado == nodo->resultado) && strcmp(aux->nombre, nodo->nombre) > 0)){
			if(prev == NULL){//tengo que cambiar a donde apunta el primero
				nodo->cola = lista;
				lista = nodo;
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
		lista = nodo;
	}
	else{//lo pongo a lo ultimo
		prev->cola = nodo;
		nodo->cola = NULL;
	}
	return;
}

static void queryGeneral(ciudadADT ciudad, tGeneral * vector, size_t dim, size_t flag) { //llamada cuando se terminan de leer ambos archivos .csv
	double res;
	for(size_t i = 0; i < dim; i++) {
		tListaGenerica * new = malloc(sizeof(tListaGenerica)); // chequear error
		if(flag == QUERY1){
			res = vector[i].param2;
		}
		else if (	flag == QUERY2 ){
		  res = vector[i].param2 / vector[i].param1;
		}
		else{
			res = vector[i].param1 / vector[i].param2;
		}
		new->resultado = res;
		new->nombre = malloc(strlen(vector[i].nombre)); // VERIFICAR MALLOC
		strcpy(new->nombre, vector[i].nombre);
		ingresarOrdenadoLista(new, ciudad->primerNodo);
	}
}

void query(ciudadADT ciudad, size_t numero){

	if( numero != QUERY3)
		queryGeneral(ciudad, ciudad->barrios, ciudad->dimBarrios, numero);
	else
		queryGeneral(ciudad, ciudad->bosque, ciudad->dimBosque, numero);
}
//calcula el indice y lo ingresa ordenado en una lista

void buscaBarrios(ciudadADT ciudad) { // FUNCION PARA DEBUG
	for(int i = 0; i< ciudad->dimBarrios; i++) {
			printf("%s\t",ciudad->barrios[i].nombre);
			printf("%d\t", (int) ciudad->barrios[i].param1);
			printf("%lu \n", ciudad->barrios[i].param2);
	}
	printf("%zu \n",ciudad->dimBarrios);
}

void buscaArboles(ciudadADT ciudad) { // fUNCION PARA DEBUG
	for(int i = 0; i<ciudad->dimBosque; i++) {
		printf("%s\t", ciudad->bosque[i].nombre);
		printf("%.2f\t", ciudad->bosque[i].param1);
		printf("%lu \n", ciudad->bosque[i].param2);
	}
	printf("%zu \n",ciudad->dimBosque);
}

static void freeRecLista(tListaGenerica * first){
	if(first == NULL) {
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
	free(ciudad);
}
=======
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
	struct tListaGenerica * cola;
}tListaGenerica;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ciudadCDT{
	// datos sin procesar
	struct tGeneral * barrios;   // vector de structs tBarrio
	size_t dimBarrios;
	struct tGeneral * bosque;     // vector de structs tArbol
	size_t dimBosque;

	struct tListaGenerica * primerNodo;
}ciudadCDT;


///////////////////////////////////////////////Funciones////////////////////////////////////////////////
//////////////////FALTA CHEQUEAR LOS ERRORES DE MEMORIA CON ERRNO///////////////////////////////////////
ciudadADT nuevaCiudad(){
	return calloc(1, sizeof(ciudadCDT)); // VERIFICACION DE ERRNO
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
		ciudad->barrios = realloc(ciudad->barrios, sizeof(tGeneral) * (ciudad->dimBarrios + 1));
		if( ciudad->barrios == NULL ) { // ESTA VERIFICACION HAY QUE CORREGIRLA CON ERRNO
			return 0;
		}
		ciudad->barrios[ciudad->dimBarrios].nombre = malloc(strlen(nombre));
		// VERIFICAR MALLOC CON ERRNO
		strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
		ciudad->barrios[ciudad->dimBarrios].param1 = poblacion;
		ciudad->barrios[ciudad->dimBarrios++].param2 = 0;
	}
	return 1;
}

static void intercambioVec(tGeneral * b1, tGeneral * b2) {
		tGeneral aux = *b1;
		*b1 = *b2;
		*b2 = aux;
}

void ordenarBarrios(ciudadADT ciudad){
		for(int i = 0; i < ciudad->dimBarrios - 1; i++) {
			for(int j = i + 1; j < ciudad->dimBarrios; j++) {
				if(strcmp(ciudad->barrios[i].nombre, ciudad->barrios[j].nombre) > 0){
					intercambioVec(&(ciudad->barrios[i]), &(ciudad->barrios[j]));
				}
			}
		}
}

static void agregarArbolEnBarrio(ciudadADT ciudad, char * nombre) { // BASADA EN BUSQUEDA BINARIA
	int ultimo = ciudad->dimBarrios - 1;
	int medio,c;
	int primero = 0;
	while(ultimo >= primero) {
		medio = (primero + ultimo) / 2;
		if( (c = strcmp(ciudad->barrios[medio].nombre,nombre)) == 0 ){
			ciudad->barrios[medio].param2++;
		}
		else if ( c < 0 )
			ultimo = medio - 1;
		else
			primero = medio + 1;
	}
}

static int agregarArbolEnBosque(ciudadADT ciudad, char * especie, double diametro){
	size_t indice = ciudad->dimBosque;

	if(!pertenece(ciudad->bosque, especie, ciudad->dimBosque, &indice)) {
		ciudad->bosque = realloc(ciudad->bosque, (ciudad->dimBosque + 1) * sizeof(tGeneral)); // VERIFICAR REALLOC
		ciudad->bosque[ciudad->dimBosque].nombre = malloc(strlen(especie)); // VERIFICAR MALLOC
		strcpy(ciudad->bosque[ciudad->dimBosque++].nombre, especie);
	}

	ciudad->bosque[indice].param1 += diametro;
	ciudad->bosque[indice].param2 += 1;
	return 0;
}

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro) {
	agregarArbolEnBarrio(ciudad, nombre);
	return agregarArbolEnBosque(ciudad, especie, diametro);
}

static void ingresarOrdenadoLista(tListaGenerica * nodo, tListaGenerica * lista){
	tListaGenerica * aux = lista;
	tListaGenerica * prev = NULL;
	for(; aux != NULL; prev = aux, aux = aux -> cola){
		if(nodo->resultado > aux->resultado || (aux->resultado == nodo->resultado && strcmp(aux->nombre, nodo->nombre) > 0)){
			if(prev == NULL){//tengo que cambiar a donde apunta el primero
				nodo->cola = lista;
				lista = nodo;
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
		lista = nodo;
	}
	else{//lo pongo a lo ultimo
		prev->cola = nodo;
		nodo->cola = NULL;
	}
	return;
}

static void queryGeneral(ciudadADT ciudad, tGeneral * vector, size_t dim, size_t flag) { //llamada cuando se terminan de leer ambos archivos .csv
	double res;
	for(size_t i = 0; i < dim; i++) {
		tListaGenerica * new = malloc(sizeof(tListaGenerica)); // chequear error
		if(flag == QUERY1){
			res = vector[i].param2;
		}
		else if (	flag == QUERY2 ){
		  res = vector[i].param2 / vector[i].param1;
		}
		else{
			res = vector[i].param1 / vector[i].param2;
		}
		new->resultado = res;
		new->nombre = malloc(strlen(vector[i].nombre)); // VERIFICAR MALLOC
		strcpy(new->nombre, vector[i].nombre);
		ingresarOrdenadoLista(new, ciudad->primerNodo);
	}
}

void query(ciudadADT ciudad, size_t numero){

	if( numero != QUERY3)
		queryGeneral(ciudad, ciudad->barrios, ciudad->dimBarrios, numero);
	else
		queryGeneral(ciudad, ciudad->bosque, ciudad->dimBosque, numero);
}
//calcula el indice y lo ingresa ordenado en una lista



static void freeRecLista(tListaGenerica * first){
	if(first == NULL) {
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
	free(ciudad);
}
>>>>>>> fe12ca604bce73d91cb318e7e7ed451410c37de9
