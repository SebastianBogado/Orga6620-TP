#include "./sort.h"
#include <stdio.h>

static void sort_file(FILE* inStream, char** (*sort_func)(char**, unsigned )) {	
	printf("Armando buffer... @todo\n");
	printf("Ordenando... @todo\n");
	printf("Imprimiendo salida... @todo\n");
	printf("Liberando memoria del buffer... @todo\n");
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
