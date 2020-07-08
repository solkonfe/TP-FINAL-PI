#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LONG 1024
#define CAMPO_COMUNA 13
#define CAMPO_ESPECIE 5
#define CAMPO_DIAM 16
/*
////////////DEFINE DEL MAIN/////
#define MAX_LONG 1024
#define CAMPO_COMUNA 3
#define CAMPO_ESPECIE 8
#define CAMPO_DIAM 12
///////////////////////////////
*/
#define CANT_CAMPOS 3
// ejemplo de valores elegidos para BUE, en el caso de VAN el main lo llamara con
//otros valores.
void leeArboles(char * campos[], char * linea, const char delim[], size_t c1, size_t c2, size_t c3) {
	strtok(linea,delim);
	for(int i = 1, j = 0; j < CANT_CAMPOS; i++) {
		if(i == c1 - 1|| i == c2 - 1 || i == c3 - 1)
		//para acceder al campo c tiene que hacer c - 1 saltos
			campos[j++] = strtok(NULL, delim);
		else
			strtok(NULL, delim);
		}
}

void leeBarrios(char * campos[], char * linea, const char delim[]){
	campos[0] = strtok(linea,delim);
	campos[1] = strtok(NULL, delim);
}

//////////////DEBUG////////////////
void imprimirCampos(char * campos[], int dim){
	for(int i = 0; i < dim ; i++){
			printf("%s\t",campos[i]);
	}
	printf("\n");
}
//////////////////////////////////

int main( int argc, char *argv[] ) {

	if( argc < 3 ) {
		printf("Se esperaban dos argumentos\n");
		return 1;
	}

	FILE * flujo = fopen(argv[1], "r"); // apertura del archivo de arboles
	if( flujo == NULL ) {
		printf("Error en la apertura del archivo\n");
		return 2;
	}

	char aux[MAX_LONG];
	const char delim[2] = ";";
  	char * campos[CANT_CAMPOS];
	int diametro, habitantes;
	while(!feof(flujo)) {
			fgets(aux, MAX_LONG,flujo);
			if (!feof(flujo)){
				leeArboles(campos, aux, delim, CAMPO_COMUNA, CAMPO_ESPECIE, CAMPO_DIAM); // aca se leen los 3 campos y quedan guardados en aux
				diametro = atoi(campos[2]);
				//llamar 3 funciones distintas
				// guardarComuna(aux[0]);
				// conversion y despues mandar diametro
			  imprimirCampos(campos,3);
		}
	}

	fclose(flujo); // cierre del archivo de arboles

	printf("Impresion de barrios\n");

	flujo = fopen(argv[2], "r"); // apertura del archivo de barrios

	if( flujo == NULL ) {
		printf("Error en la apertura del archivo\n");
		return 2;
	}

	while(!feof(flujo)) {
		fgets(aux, MAX_LONG, flujo);
		if(!feof(flujo)){
			leeBarrios(campos,aux,delim);
			habitantes = atoi(campos[1]);
	  		imprimirCampos(campos,2);
		}
	}
	fclose(flujo);
	return 0;
}
