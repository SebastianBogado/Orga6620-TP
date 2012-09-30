#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include "line.h"

/**
* @brief ordena un vector de forma ascendente con quicksort
* @param array vector a ordenar
* @param size, tamaño del vector
* @return el vector ordenado, NULL en caso de error.
*/

line** quick_sort (line** array, unsigned size);

#endif // __QUICK_SORT_H__
