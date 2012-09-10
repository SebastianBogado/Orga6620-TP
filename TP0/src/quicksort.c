#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(char** array, int a, int b){
	char* aux = array[a]; 
	array[a] = array[b];
	array[b] = aux;

}


int particionar (char** array, int izq, int der, int pivotIndex){

	char* pivot = array[pivotIndex];
	int prevIndex = izq; 
	swap(array, pivotIndex, der);
	int i = 0;

	for(i = izq; i<der; i++){

		if(strcmp(array[i] ,pivot) < 0){
			swap(array, i, prevIndex);
			prevIndex ++;
		}
	}
	swap(array, prevIndex, der);
	return prevIndex;
}

char** quickSort_r (char** array, int izq, int der){

	if(array && (izq<der)){
		int pivot = (izq + der)/2;
		int nuevoPivot = particionar(array, izq, der, pivot);
		
		quickSort_r(array, izq, nuevoPivot -1);
		quickSort_r(array, nuevoPivot +1, der);
		
		return array;	
	}
	return NULL;
}	

char** quick_sort(char** array, unsigned size){

	return quickSort_r(array, 0, size-1);
}
