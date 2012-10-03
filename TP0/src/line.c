#include "line.h"
#include <malloc.h>
#include <stdio.h>

struct line {
	char* str;
	size_t size;
};

unsigned getSize(line* l) {return l->size;}

line* createLine(char* buf, size_t size) {
	line* l = (line* )malloc(sizeof(line));
	l->str = buf;
	l->size = size;
	return l;
}

int linecmp(const line* a, const line* b) {
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

void printLine(const line* l) {
	fwrite(l->str, sizeof(char), l->size, stdout);
}

void swapLine(line** array, int a, int b) {
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
