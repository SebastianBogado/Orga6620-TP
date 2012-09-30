#include "line.h"
#include <malloc.h>

#define EOL '\n'

struct line {
	char* str;
	size_t size;
};

line* createLine(char* buf, size_t size) {
	/*
	bool found = false;
	size_t i = 0;
	char*
	while (!found || i < size)
		found = buf + i++ == EOL;

	line* l = (line* )malloc(sizeof line);
	l->size = i

	if (i < size) {

	}*/
	line* l = (line* )malloc(sizeof(line));
	l->str = buf;
	l->size = size;
	return l;
}

int linecmp(line* a, line* b) {
	size_t idx_a = 0, idx_b = 0;
	int res = 0;

	// mientras cada char sea igual, y los índices no vayan más allá del tamaño
	// sin contemplar el último char, que es el EOL
	while (!res && idx_a < a->size-1 && idx_b < b->size-1)
		res = *(a->str + idx_a++) - *(b->str + idx_b++);

	// si todos los char son iguales, es menor la línea de menor tamaño
	if (!res)
		return a->size - b->size;
	else
		return res;
}

void swap(line** array, int a, int b) {
	line* aux = array[a];
	array[a] = array[b];
	array[b] = aux;
}

void freeLine(line** l) {
	if (!*l)
		return;

	free((*l)->str);
	free(*l);
	*l = NULL;
}
