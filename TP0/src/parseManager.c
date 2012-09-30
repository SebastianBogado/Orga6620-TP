#include "./parseManager.h"
#include<stdio.h>
#include<stdlib.h>

unsigned cargarBuffer(char* *buffer, FILE* stream);


unsigned parseLineas(char** *pLinea, unsigned lineas, FILE* stream){

	char* buffer = NULL;
	int quedanLineas;
	unsigned bufferLen;

	while (!feof(stream)) {
	    if (buffer)
            printf("%s", buffer);
		quedanLineas = cargarBuffer(&buffer, stream);

		// si no quedan mas lineas, y la ultima leída es valida, la escribe
		if (quedanLineas ||
		    (strcmp(buffer, (*pLinea)[lineas-1]) != 0)) {

			bufferLen = strlen(buffer);

			++lineas;
			// reserva espacio para una nueva linea
			(*pLinea) = (char**)realloc((*pLinea), lineas * sizeof(char*));
			(*pLinea)[lineas-1] = NULL;
			// reserva espacio para almacenar la linea guardada en el buffer
			(*pLinea)[lineas-1] = (char*)realloc((*pLinea)[lineas-1], bufferLen+1);

			strcpy((*pLinea)[lineas-1], buffer);
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

	do {

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

	}while (resultadoFGetS &&
			((*buffer)[bufferLen-1] != '\n'));

	if (!resultadoFGetS){
		// si el archivo no termina con un salto de linea
		// se lo agrega para normalizar todas las lineas
		if((*buffer)[bufferLen-1] != '\n'){
			(*buffer)[bufferLen] = '\n';

			(*buffer)[bufferLen+1] = '\0';
		}
		//Indica fin del archivo, no hay mas lineas
		bufferLen = 0;
	}

	return bufferLen;
}

