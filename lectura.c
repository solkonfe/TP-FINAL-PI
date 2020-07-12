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
  if ( !feof ( flujo) )
		fgets(aux, MAX_LONG, flujo); // Descartamos la primer linea

	while(!feof(flujo)) {
		fgets(aux, MAX_LONG, flujo);
		if(!feof(flujo)){
			campos[0] = strtok(aux,delim);
			campos[1] = strtok(NULL, delim);
			if(!agregarBarrio(ciudad,campos[0],atof(campos[1])))
				exit(2);
		}
	}

	fclose(flujo);
}

void leeArboles(const char * archivo, ciudadADT ciudad, size_t flag, size_t c1, size_t c2, size_t c3) {
	char aux[MAX_LONG];
	const char delim[2] = ";";
	char * campos[CAMPOS_ARBOLES];

	FILE * flujo = fopen(archivo, "r"); // apertura del archivo de arboles
	if( flujo == NULL ) {
		printf("Error en la apertura del archivo\n");
		exit(1);
	}
	if ( !feof ( flujo) )
		fgets(aux, MAX_LONG, flujo); // Descartamos la primer linea

	while(!feof(flujo)) {
		fgets(aux, MAX_LONG, flujo);
		if(!feof(flujo)) {
			strtok(aux,delim);
			for(int i = 1, j = 0; j < CAMPOS_ARBOLES; i++) {
				if(i == c1 - 1 || i == c2 - 1 || i == c3 - 1)
					campos[j++] = strtok(NULL, delim);
				else
					strtok(NULL, delim);
			}
			if( flag ) { // en el caso de los arboles VAN debemos intercambiar los campos
				if(agregarArbol(ciudad, campos[1], campos[0], atof(campos[2])) != 1 )
					exit(2);
			}
			else {
			 	if (agregarArbol(ciudad, campos[0], campos[1], atof(campos[2])) != 1 )
					exit(2);
			}
		}
	}
	fclose(flujo);
}
