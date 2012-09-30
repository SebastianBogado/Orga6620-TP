#include "./parseManager.h"
#include "./sort.h"
#include <stdio.h>

void sort(unsigned n, char* files[], char** (*sort_func)(char** , unsigned )) {
	char** pLinea = NULL;
	unsigned lineas = 0;

	if (n) {
		FILE* inStream;
		for (unsigned i = 0; i < n; ++i) {
			inStream = fopen(files[i], "rb");
			
			if (inStream) {
				lineas =+ parseLineas(&pLinea, lineas, inStream);
				fclose(inStream);

			printf("LINEAS %d \n", lineas);


			} else
				perror(files[i]);
		}
	} else
	//No hay archivos por argumento
		lineas =+ parseLineas(&pLinea, lineas, stdin);

	pLinea = sort_func(pLinea, lineas);

	//print salida
	for (int i = 0; i < lineas; ++i)
		printf("%s", pLinea[i]);
	
	//Liberación
	for (int i = 0; i < lineas; ++i)
		free(pLinea[i]);

	free(pLinea);
	
}
