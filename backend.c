#include "backend.h"
// tGeneral es la estructura a utilizar para guardar datos, tanto de barrios como de arboles
typedef struct tGeneral{
	char * nombre;
	double param1; // cantDeHabitantes o sumaDiametros
	unsigned long int param2; //cantdeArb
}tGeneral;

typedef struct ciudadCDT{
	struct tGeneral * barrios;
	size_t dimBarrios;
	struct tGeneral * bosque;
	size_t dimBosque;

  // Nodos para las listas de salida
	struct tListaGenerica * primerNodoQ1;
	struct tListaGenerica * primerNodoQ2;
	struct tListaGenerica * primerNodoQ3;
}ciudadCDT;

ciudadADT nuevaCiudad() {
	ciudadADT ciudad;
  ciudad = calloc(1,sizeof(struct ciudadCDT));
	if(ciudad == NULL || errno == ENOMEM)
  	fprintf(stderr, "Errno: %d Error %s \nNo se pudo generar la ciudad\n", errno, strerror(errno));
  return ciudad;
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
		if(ciudad->barrios == NULL || errno == ENOMEM){
			fprintf(stderr, "Errno: %d Error %s \nNo se pudo agregar el barrio\n", errno, strerror(errno));
			return 0;
		}
	}
	ciudad->barrios[ciudad->dimBarrios].nombre = malloc(strlen(nombre) + 1);
	if(ciudad->barrios[ciudad->dimBarrios].nombre == NULL || errno == ENOMEM){
		fprintf(stderr, "Errno: %d Error %s \nNo se pudo guardar el nombre del barrio\n", errno, strerror(errno));
		return 0;
	}
	strcpy(ciudad->barrios[ciudad->dimBarrios].nombre, nombre);
	ciudad->barrios[ciudad->dimBarrios].param1 = poblacion;
	ciudad->barrios[ciudad->dimBarrios++].param2 = 0;
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

//Aprovechando que primero leemos el archivo de barrios, podemos ordenar alfabeticamente los barrios
//para usar busqueda binaria y bajar la complejidad de la insercion de arboles
static void agregarArbolEnBarrio(ciudadADT ciudad, char * nombre) {
	int ultimo = ciudad->dimBarrios - 1;
	int medio,c;
	int primero = 0;
	while(primero <= ultimo) {
		medio = (primero + ultimo) / 2;
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

static int agregarArbolEnBosque(ciudadADT ciudad, char * especie, double diametro){
	size_t indice = ciudad->dimBosque;

	if(!pertenece(ciudad->bosque, especie, ciudad->dimBosque, &indice)) {
		ciudad->bosque = realloc(ciudad->bosque, (ciudad->dimBosque + 1) * sizeof(tGeneral));
		if(ciudad->bosque == NULL || errno == ENOMEM) {
			fprintf(stderr, "Errno: %d Error %s \nNo se pudo agregar el arbol\n", errno, strerror(errno));
			return 0;
		}
		ciudad->bosque[ciudad->dimBosque].nombre = malloc(strlen(especie) +1);
		if(ciudad->bosque[ciudad->dimBosque].nombre == NULL || errno == ENOMEM ){
			fprintf(stderr, "Errno: %d Error %s \nNo se pudo agregar el nombre del arbol\n", errno, strerror(errno));
			return 0;
		}
		strcpy(ciudad->bosque[ciudad->dimBosque].nombre, especie);
		ciudad->bosque[ciudad->dimBosque].param1 = 0;
		ciudad->bosque[ciudad->dimBosque++].param2 = 0;
	}

	ciudad->bosque[indice].param1 += diametro;
	ciudad->bosque[indice].param2 += 1;
	return 1;
}

int agregarArbol(ciudadADT ciudad, char * nombre, char * especie, double diametro) {
	agregarArbolEnBarrio(ciudad, nombre);
	return agregarArbolEnBosque(ciudad, especie, diametro);
}

static tListaGenerica * ingresarRecursiva(tListaGenerica * primero, char * nombre, double resultado) {
	if(primero == NULL || primero->resultado < resultado || (primero->resultado == resultado && strcmp(primero->nombre, nombre)>0 ) ) {
		tListaGenerica * nuevo = malloc(sizeof(tListaGenerica));
		if(nuevo == NULL || errno == ENOMEM){
			fprintf(stderr, "Errno: %d Error %s \nNo se pudo armar la lista de salida\n", errno, strerror(errno));
			return NULL;
		}
		nuevo->resultado = resultado;
		nuevo->nombre = malloc(strlen(nombre) + 1);
		if(nuevo->nombre == NULL || errno == ENOMEM){
			fprintf(stderr, "Errno: %d Error %s \nNo se pudo armar la lista de salida\n", errno, strerror(errno));
			return NULL;
		}
		strcpy(nuevo->nombre, nombre);
		nuevo->cola = primero;
		return nuevo;
	}

	primero->cola = ingresarRecursiva(primero->cola,nombre,resultado);
	return primero;
}

static void trunca(double * valor){
	*valor *= 100;
	int aux = (int) *valor;
	*valor = aux/100.0;
}

static void queryGeneral(ciudadADT ciudad, tGeneral * vector, size_t dim, size_t flag) { //llamada cuando se terminan de leer ambos archivos .csv
	double res;
	for(size_t i = 0; i < dim; i++) {
		if(flag == QUERY1){
			res = vector[i].param2;
			ciudad->primerNodoQ1 = ingresarRecursiva(ciudad->primerNodoQ1, vector[i].nombre, res);
		}
		else if (flag == QUERY2){
		  res = vector[i].param2 / vector[i].param1;
			trunca(&res);
			ciudad->primerNodoQ2 = ingresarRecursiva(ciudad->primerNodoQ2, vector[i].nombre, res);
		}
		else{
			res = vector[i].param1 / vector[i].param2;
			trunca(&res);
			ciudad->primerNodoQ3 = ingresarRecursiva(ciudad->primerNodoQ3, vector[i].nombre, res);
		}
	}
}

struct tListaGenerica * resuelveQuery(ciudadADT ciudad, size_t numero) {
	if( numero == QUERY1) {
		queryGeneral(ciudad, ciudad->barrios, ciudad->dimBarrios, numero);
		return ciudad->primerNodoQ1;
	}
	else if( numero == QUERY2) {
		queryGeneral(ciudad, ciudad->barrios, ciudad->dimBarrios, numero);
		return ciudad->primerNodoQ2;
	}
	else {
		queryGeneral(ciudad, ciudad->bosque, ciudad->dimBosque, numero);
		return ciudad->primerNodoQ3;
	}
}

static void freeRecLista(tListaGenerica * first){
	if( first == NULL)
		return;
	freeRecLista(first->cola);
	free(first->nombre);
	free(first);
}

void freeCiudad(ciudadADT ciudad) {
	freeRecLista(ciudad->primerNodoQ1);
	freeRecLista(ciudad->primerNodoQ2);
	freeRecLista(ciudad->primerNodoQ3);
	for(int i=0; i < ciudad->dimBosque; i++)
		free(ciudad->bosque[i].nombre);
	free(ciudad->bosque);
	for(int j = 0; j < ciudad->dimBarrios; j++)
		free(ciudad->barrios[j].nombre);
	free(ciudad->barrios);
	free(ciudad);
}
