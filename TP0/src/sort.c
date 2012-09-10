#include "./sort.h"
#include <stdio.h>

static void sort_file(FILE* inStream, char** (*sort_func)(char**, unsigned )) {	
	printf("Armando buffer... @todo");
	printf("Ordenando... @todo");
	printf("Imprimiendo salida... @todo");
	printf("Liberando memoria del buffer... @todo");
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
				printf("error %s @todo completar con perror\n", files[i]);
		}
	} else
		sort_file(stdin, sort_func);
}
