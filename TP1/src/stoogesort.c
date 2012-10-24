#include "./stoogesort.h"
#include <string.h>

void swap(char** array, int a, int b){
	char* aux = array[a];
	array[a] = array[b];
	array[b] = aux;
}

void stooge_sort(void* array, unsigned int i, unsigned int j) {
	char** v = (char**) array;
    // si el primero es mayor al último, intercambiar
    if (strcmp(v[i], v[j-1]) > 0)
        swap(v, i, j-1);

    if ( j >= 3 ) {
        unsigned tercio = j / 3;
        stooge_sort(v, 0, j - tercio);
        stooge_sort(v + tercio, 0, j - tercio);
        stooge_sort(v, 0, j - tercio);
    }
}