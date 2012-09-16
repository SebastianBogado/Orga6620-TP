#include "./parseManager.h"
#include "./sort.h"
#include <stdio.h>

void sort(unsigned n, char* files[], char** (*sort_func)(char** , unsigned )) {
	char** pLinea = NULL;
	unsigned lineas = 0;
	unsigned int size = 0;

	
	if (n) {
		FILE* inStream;
		for (unsigned i = 0; i < n; ++i) {
			inStream = fopen(files[i], "rb");
			
	
			fseek(inStream, 0, SEEK_END);
			size=ftell(inStream);
			fseek(inStream, 0, SEEK_SET);	
			
			if (inStream) {
				lineas =+ parseLineas(&pLinea, lineas, inStream);
				fclose(inStream);
			} else
				perror(files[i]);
		}
	} else
		lineas =+ parseLineas(&pLinea, lineas, stdin);
	
	pLinea = sort_func(pLinea, lineas);

//print salida
	for (int i = 0; i < lineas; ++i)
		printf("%s", pLinea[i]);
	
// liberación

	for (int i = 0; i < lineas; ++i)
		free(pLinea[i]);

	free(pLinea);

//	printf("%d", size);
	
}
