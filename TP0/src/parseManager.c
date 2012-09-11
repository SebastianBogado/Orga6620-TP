#include "./parseManager.h"
#include<stdio.h>
#include<stdlib.h>

unsigned cargarBuffer(char* *buffer, FILE* stream);


unsigned parseLineas(char** *pLinea, unsigned lineas, FILE* stream){
	
	char* buffer = NULL;

	unsigned int bufferLen;

	while (!feof(stream)) {
		lineas++;
		
		(*pLinea) = (char**)realloc((*pLinea), lineas * sizeof(char*));		
		(*pLinea)[lineas-1] = NULL;	

		bufferLen = cargarBuffer(&buffer, stream);
		(*pLinea)[lineas-1] = (char*)realloc((*pLinea)[lineas-1], bufferLen);

		memcpy((*pLinea)[lineas-1], buffer, bufferLen);

	}
	free(buffer);

	return lineas; 

}


unsigned cargarBuffer(char* *buffer, FILE* stream){

	int len_buffer = 128;
	int tam_buffer = len_buffer +1;
	

	// la siguiente variable cuenta la cantidad de veces que fue necesario
	// realocar el buffer + 1 (entonces la capacidad es bufferInc*len_buffer+1)
	unsigned int bufferInc;
	unsigned int bufferCapac;
	unsigned int bufferLen;

	char* resultadoFGetS;

	bufferInc = 0;
		
	do {
		bufferInc++;
		bufferCapac = bufferInc*len_buffer + 1;
		(*buffer) = (char*)realloc((*buffer), bufferCapac*sizeof(char));

		// buffer + bufferCapac - (tam_buffer) pone al puntero en la
		// posición inicial de la porción nueva de memoria

		resultadoFGetS = fgets((*buffer) + bufferCapac - (tam_buffer),
							  tam_buffer, stream);
		bufferLen = strlen(*buffer);
		// Mientras que fgets no devuelva un puntero nulo y
		// que el último char no sea un fin de línea, repetir
	}while (resultadoFGetS &&
			(*buffer)[bufferLen-1] != '\n');

	return bufferLen;
}

