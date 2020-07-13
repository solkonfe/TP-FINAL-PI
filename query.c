#include "query.h"
#define LONG_NOMBRE 11

void generarQuery(ciudadADT ciudad, size_t numero) {
  char nombre_archivo[LONG_NOMBRE];
  sprintf(nombre_archivo, "query%zu.csv", numero);
  FILE * archivoQuery = fopen(nombre_archivo, "w");

  tListaGenerica * lista = resuelveQuery(ciudad, numero); // arma la lista ordenada
  tListaGenerica * iterador = lista;

  if(numero == QUERY1)
    fprintf(archivoQuery, "BARRIO;ARBOLES\n");
  else if (numero == QUERY2)
    fprintf(archivoQuery, "BARRIO;ARBOLES_POR_HABITANTE\n");
  else
    fprintf(archivoQuery, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");

  if(numero == QUERY1) { // en la QUERY1  debemos castear resultado a int
    while(iterador != NULL) {
  		fprintf(archivoQuery, "%s;%d\n", iterador->nombre, (int) iterador->resultado);
      iterador = iterador->cola;
    }
  }
  else {
  	while(iterador != NULL) {
      // Se trunca a dos decimales el resultado obtenido. ( diametro || indice ).
      iterador->resultado *= 100;
      int aux = (int) iterador->resultado;
      iterador->resultado = aux / 100.0;
  		fprintf(archivoQuery, "%s;%.2f\n", iterador->nombre, iterador->resultado);
  		iterador = iterador->cola;
    }
	}
  fclose(archivoQuery);
}
