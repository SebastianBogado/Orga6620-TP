#ifndef __LINE_H__
#define __LINE_H__

/**
 * TDA línea. Encapsula el manejo de líneas, armado, comparaciones, etc.
 * @example
	line* l createLine(buf, size);
	//hacer lo que sea
	freeLine(&l);
 */


typedef struct line line;

/**
 * inicializa una línea a partir de un manojo de chars
 * @param buf		puntero a chars conteniendo la línea
 * @param size		tamaño del buffer
 * @return puntero a line válido
 *
 * Si se llega al final del buffer sin encontrar un fin de línea, se considera
 * ese como el fin, y se agrega el caracter '\n'
 * size tiene que ser la cantidad de bytes disponibles de memoria alocada.
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
int linecmp(line* a, line* b);


/**
 * función que intercambia la posición entre dos líneas dentro de un vector
 * @param array	puntero al array de líneas
 * @param a, b		posiciones a intercambiar
 */
void swap(line** array, int a, int b);

/**
 * libera toda la memoria asociada a la línea, y pone al puntero *l en NULL
 * @param l	línea a liberar
 */
void freeLine(line** l);

#endif  // __LINE_H__
