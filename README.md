# TP-FINAL-PI

Descripcion General:
	El programa consiste en dos ejecutables, los cuales leen dos archivos CSV con informacion de arboles de dos ciudades diferentes (CABA y Vancouver) y otro con la cantidad de habitantes de los barrios de esa ciudad.
	El objetivo de los ejecutables es generar 3 archivos CSV donde cada uno responde a las siguientes queries:

	Query 1: Total de arboles por barrio
	Query 2: Total de arboles por habitante
	Query 3: Diametro promedio por especie de arbol

Geneneracion de ejecutables:

	Para generar los ejecutables se debe ingresar el siguiente comando en la consola de pampero:

		Para generar ambos solo poner: make

		Para el programa de Vancouver: make programaVAN

		Para el programa de CABA: make programaBUE

	Para eliminar los archivos .o: make clean

	Para eliminar los ejecutables: make delexecutables

	Para eliminar los query's: make delquery

Instrucciones para la ejecucion:

Ambos ejecutables se deben invocar de la siguiente forma, asumiendo que los dataset se encuentran en el mismo directorio que los ejecutables:

 ./arbolesADTBUE arbolesBUE.csv barriosBUE.csv

 ./arbolesADTVAN arbolesVAN.csv barriosVAN.csv

Si los dataset no se encuentran en el mismo directorio, se pasan los paths correspondientes.
IMPORTANTE: debe respetarse el orden de los archivos (primero el de arboles, luego el de barrios) para obtener el resultado esperado.
