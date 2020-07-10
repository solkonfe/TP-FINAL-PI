#include "lectura.h"

void leeBarrios(const char * archivo, ciudadADT ciudad) {
	char aux[MAX_LONG];
	const char delim[2] = ";";
	char * campos[CAMPOS_BARRIOS];

	FILE * flujo = fopen(archivo, "r"); // apertura del archivo de barrios
	if( flujo == NULL ) {
		printf("Error en la apertura del archivo\n");
		exit(1);
	}

	while(!feof(flujo)) {
		fgets(aux, MAX_LONG, flujo);
		if(!feof(flujo)){
			campos[0] = strtok(aux,delim);
			campos[1] = strtok(NULL, delim);
			if(!agregarBarrio(ciudad,campos[0],atof(campos[1])) {
				printf("No se pudo agregar el barrio por insuficiencia de memoria\n");
				exit(2);
			}
		}
	}

	fclose(flujo);
}

void leeArboles(const char * archivo, ciudadADT ciudad, size_t flag) {
	char aux[MAX_LONG];
	const char delim[2] = ";";
	char * campos[CAMPOS_ARBOLES];

	FILE * flujo = fopen(archivo, "r"); // apertura del archivo de barrios
	if( flujo == NULL ) {
		printf("Error en la apertura del archivo\n");
		exit(1);
	}

	strtok(aux,delim);
	for(int i = 1, j = 0; j < CANT_CAMPOS; i++) {
		if(i == c1 - 1 || i == c2 - 1 || i == c3 - 1)
			campos[j++] = strtok(NULL, delim);
		else
			strtok(NULL, delim);
	}

	if( flag ) { // en el caso de los arboles VAN debemos intercambiar los campos
		char * swap;
		strcpy(swap,campos[0]);
		strcpy(campos[0],campos[1]);
		strcpy(campos[1],swap);
	}

	if(!AgregarArbol(ciudad, campo[0], campo[1], atof(campo[2]))) {
		printf("Error al agregar el arbol por insuficiencia de memoria\n");
		exit(2);
	}

	fclose(flujo);
}
