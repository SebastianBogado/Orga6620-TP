#include "./sort.h"
#include <stdio.h>

static void sort_file(FILE* inStream, char** (*sort_func)(char**, unsigned )) {	
	printf("Armando buffer... @todo\n");
	printf("Ordenando... @todo\n");
	/* suponiendo que hay una variable "lineas" con la cantidad de líneas, pLinea, el vector mismo, y que mantienen el "\n" al final, el ordenamiento es: 

	sort_func(pLinea, lineas);
	
	*/
	printf("Imprimiendo salida... @todo\n");
	/* la impresión es:

	for (int i = 0; i < lineas, ++i)
		printf("%s", pLinea[i]);
	
	*/
	printf("Liberando memoria del buffer... @todo\n");
	/* la liberación, que podría hacerse después de imprimir cada línea en el for de arriba, es:

	for (int i = 0; i < lineas, ++i)
		free(pLinea[i]);

	free(pLinea);
	*/	
}

void sort(unsigned n, char* files[], char** (*sort_func)(char** , unsigned )) {
	if (n) {
		FILE* inStream;
		for (unsigned i = 0; i < n; ++i) {
			inStream = fopen(files[i], "rb");
			if (inStream) {
				sort_file(inStream, sort_func);
				fclose(inStream);
			} else
				perror(files[i]);
		}
	} else
		sort_file(stdin, sort_func);
}
