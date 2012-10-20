#include "./parseManager.h"
#include<stdio.h>
#include<stdlib.h>
unsigned cargarBuffer(char* *buffer, FILE* stream);


unsigned parseLineas(char** *pLinea, unsigned lineas, FILE* stream){

	char* buffer = NULL;
	unsigned bufferLen;
	unsigned lineSize = 0;

	bufferLen = cargarBuffer(&buffer, stream);

	for (int i=0; i<=bufferLen; i++){

		lineSize++;

		if (buffer[i] == '\n') {

			char* lineBuff = (char*) malloc(lineSize*sizeof(char));
			memcpy(lineBuff, buffer + i + 1 - lineSize, lineSize);

			++lineas;
			(*pLinea) = (line**)realloc((*pLinea), lineas * sizeof(char*));
			(*pLinea)[lineas-1] = createLine(lineBuff, lineSize);
			lineSize = 0;
		}
	}

    free(buffer);
	return lineas;
}


unsigned cargarBuffer(char* *buffer, FILE* stream){
	const int len_buffer = 1024;
	const int tam_buffer = len_buffer +1;

	// la siguiente variable cuenta la cantidad de veces que fue necesario
	// realocar el buffer + 1 (entonces la capacidad es bufferInc*len_buffer+1)
	unsigned bufferInc = 0;
	unsigned bufferCapac;
	unsigned bufferLen;
	char* resultadoFGetS;

	do{
	 	// prepara el buffer para una nueva lectura, ampliando su capacidad
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
	} while( !feof(stream) );

	// si el archivo NO vacio
	// no termina con un salto de linea
	// se lo agrega para normalizar todas las lineas
	if (bufferLen > 0)
    	if((*buffer)[bufferLen-1] != '\n')
        	(*buffer)[bufferLen] = '\n';

	return bufferLen;
}
