#include<stdio.h>
#include<stdlib.h>


int main (int argc, char* argv[]){

	int i = 1; // argv[0] = tp0; 
	int input[argc];
	for (i; i<argc; i++){
		input[i] = atoi(argv[i]);
		printf("load %c \n", (*argv[i]));
	}	

	quickSort(input, 1, argc-1); 
	
	for (i=1; i<argc; i++)
		printf("%d \n", input[i]);

	return 0;
}


int swap(int* array, int a, int b){
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

int quickSort (int* array, int izq, int der){

	if(array && (izq<der)){
		int pivot = (izq + der)/2;
		int nuevoPivot = particionar(array, izq, der, pivot);
		
		quickSort(array, izq, nuevoPivot -1);
		quickSort(array, nuevoPivot +1, der);
		
		return 0;	
	}
	return -1;
}	
