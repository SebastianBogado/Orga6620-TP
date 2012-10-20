#include "./parseManager.h"
#include "./sort.h"
#include "./stoogesort.h"
#include <stdio.h>

void sort(unsigned n, char* files[]) {
	char** pLinea = NULL;
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

	stooge_sort(pLinea, 0, lineas);

	//print salida
	for (int i = 0; i < lineas; ++i)
		printf("%s", pLinea[i]);

	//Liberación
	for (int i = 0; i < lineas; ++i)
		free(pLinea[i]);

	free(pLinea);
}
