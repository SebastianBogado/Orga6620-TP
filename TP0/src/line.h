#ifndef __LINE_H__
#define __LINE_H__

#include <malloc.h>

/**
 * TDA línea. Encapsula el manejo de líneas, armado, comparaciones, etc.
 * @example
	line* l createLine(buf, size);
	//hacer lo que sea
	freeLine(&l);
 */

typedef struct line line;

unsigned getSize(line* l);
/**
 * inicializa una línea a partir de un manojo de chars que termina en '\n'
 * @param buf		puntero a chars conteniendo la línea
 * @param size		tamaño del buffer
 * @return puntero a line válido
 */
line* createLine(char* buf, size_t size);


/**
 * función que compara dos líneas
 * @param a	puntero a la primera línea
 * @param b	puntero a la segunda línea
 * @return	<0 si *a < *b
			 0 si *a = *b
			>0 si *a > *b
 */
int linecmp(const line* a, const line* b);

/**
 * función que imprime por salida estándar la línea
 * @param l	línea a imprimir
 */
void printLine(const line* l);

/**
 * función que intercambia la posición entre dos líneas dentro de un vector
 * @param array	puntero al array de líneas
 * @param a, b		posiciones a intercambiar
 */
void swapLine(line** array, int a, int b);

/**
 * libera toda la memoria asociada a la línea, y pone al puntero *l en NULL
 * @param l	línea a liberar
 */
void freeLine(line** l);

#endif  // __LINE_H__
