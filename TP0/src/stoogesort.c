#include "./stoogesort.h"
#include <string.h>

static void swap(char** str1, char** str2) {
    char* aux = *str1;
    *str1 = *str2;
    *str2 = aux;
}

char** stooge_sort(char** v, unsigned n) {
    // si el primero es mayor al último, intercambiar
    if (strcmp(v[0], v[n-1]) > 0)
        swap(&v[0], &v[n-1]);

    if (n >= 3) {
        unsigned tercio = n / 3;
        stooge_sort(v, n - tercio);
        stooge_sort(v + tercio, n - tercio);
        stooge_sort(v, n - tercio);
    }

    return v;
}
