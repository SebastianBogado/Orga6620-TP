#include<stdio.h>
#include<stdlib.h>

void swap(int* array, int a, int b){
	int aux = array[a]; 
	array[a] = array[b];
	array[b] = aux;

}


int particionar (int* array, int izq, int der, int pivotIndex){

	int pivot = array[pivotIndex];
	int prevIndex = izq; 
	swap(array, pivotIndex, der);
	int i = 0;
	for(i = izq; i<der; i++){
		if(array[i] < pivot){
			swap(array, i, prevIndex);
			prevIndex ++;
		}
	}
	swap(array, prevIndex, der);
	return prevIndex;
}

int quickSort (int* array, unsigned izq, unsigned der){

	if(array && (izq<der)){
		int pivot = (izq + der)/2;
		int nuevoPivot = particionar(array, izq, der, pivot);
		
		quickSort(array, izq, nuevoPivot -1);
		quickSort(array, nuevoPivot +1, der);
		
		return 0;	
	}
	return -1;
}	
