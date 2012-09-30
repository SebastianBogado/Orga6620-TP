#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "quicksort.h"

int particionar (line** array, int izq, int der, int pivotIndex){

	line* pivot = array[pivotIndex];
	int prevIndex = izq;
	swapLine(array, pivotIndex, der);
	int i = 0;

	for(i = izq; i<der; i++){
		// si [i] es menor que el pivot lo deja a antes del mismo
		// si [i] es igual o mayor lo deja despues
		if(linecmp(array[i] ,pivot) < 0){
			swapLine(array, i, prevIndex);
			prevIndex++;
		}
	}

	swapLine(array, prevIndex, der);
	// prevIndex contiene la posicion final del pivot
	return prevIndex;
}

line** quickSort_r (line** array, int izq, int der){

	if(array && (izq<der)){
		// seleccion arbitraria de Pivot
		int pivot = (izq + der)/2;
		int nuevoPivot = particionar(array, izq, der, pivot);

		quickSort_r(array, izq, nuevoPivot -1);
		quickSort_r(array, nuevoPivot +1, der);

		return array;
	}
	return array;
}

line** quick_sort(line** array, unsigned size){

	return quickSort_r(array, 0, size-1);
}
