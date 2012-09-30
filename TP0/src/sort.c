#include "./parseManager.h"
#include "./sort.h"
#include <stdio.h>

void sort(unsigned n, char* files[], line** (*sort_func)(line** , unsigned )) {
	line** pLinea = NULL;
	unsigned lineas = 0;

	if (n) {
		FILE* inStream;
		for (unsigned i = 0; i < n; ++i) {
			inStream = fopen(files[i], "rb");

			if (inStream) {
				lineas =+ parseLineas(&pLinea, lineas, inStream);
				fclose(inStream);
			} else
				perror(files[i]);
		}
	} else
	//No hay archivos por argumento
		lineas =+ parseLineas(&pLinea, lineas, stdin);

	pLinea = sort_func(pLinea, lineas);

	//print salida
	for (int i = 0; i < lineas; ++i)
		printLine(pLinea[i]);

	//Liberación
	for (int i = 0; i < lineas; ++i)
		freeLine(&pLinea[i]);

	free(pLinea);
}
