#include "./stoogesort.h"
#include <string.h>

void swap(char** array, int a, int b){
	char* aux = array[a];
	array[a] = array[b];
	array[b] = aux;
}

void stoogesort(void* array, unsigned int i, unsigned int j) {
	char** v = (char**) array;
    // si el primero es mayor al último, intercambiar
    if (strcmp(v[i], v[j-1]) > 0)
        swap(v, i, j-1);

	unsigned n = j - i;
    if ( n >= 3 ) {
        unsigned tercio = n / 3;
        stoogesort(v, i, j - tercio);
        stoogesort(v, i + tercio, j);
        stoogesort(v, i, j - tercio);
    }
}
