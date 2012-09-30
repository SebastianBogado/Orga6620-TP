#ifndef __SORT__
#define __SORT__

/**
 * Ordena las líneas de los archivos en orden ascendente e imprime por pantalla.
 * @param n la cantidad de archivos
 * @param files los archivos
 * @param sort_func puntero a la función de ordenamiento
 *
 * Si n == 0, se toma como entrada stdin.
 */
void sort(unsigned n, char* files[], line** (*sort_func)(line** , unsigned ));

#endif  // __SORT__
