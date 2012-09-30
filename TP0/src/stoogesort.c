#include "./stoogesort.h"
#include <string.h>

line** stooge_sort(line** v, unsigned n) {
    // si el primero es mayor al último, intercambiar
    if (linecmp(v[0], v[n-1]) > 0)
        swapLine(v, 0, n-1);

    if (n >= 3) {
        unsigned tercio = n / 3;
        stooge_sort(v, n - tercio);
        stooge_sort(v + tercio, n - tercio);
        stooge_sort(v, n - tercio);
    }

    return v;
}
