#include "./parseManager.h"
#include<stdio.h>
#include<stdlib.h>

unsigned cargarBuffer(char* *buffer, FILE* stream);


unsigned parseLineas(char** *pLinea, unsigned lineas, FILE* stream){
	
	char* buffer = NULL;

	unsigned int bufferLen;
	
	while (!feof(stream)) {
//printf("--- Línea %d\n", lineas); 
		lineas++;
		
		bufferLen = cargarBuffer(&buffer, stream);

		(*pLinea) = (char**)realloc((*pLinea), lineas * sizeof(char*));		
		(*pLinea)[lineas-1] = NULL;	
		(*pLinea)[lineas-1] = (char*)realloc((*pLinea)[lineas-1], bufferLen+1);
//printf("bufferLen = %d\n", bufferLen);
	
//printf("Buffer: %s", buffer);
		strcpy((*pLinea)[lineas-1], buffer);

//printf("Línea:  %s", (*pLinea)[lineas-1]);
	}
	free(buffer);

	return lineas; 

}


unsigned cargarBuffer(char* *buffer, FILE* stream){

	const int len_buffer = 1024;
	const int tam_buffer = len_buffer +1;
	

	// la siguiente variable cuenta la cantidad de veces que fue necesario
	// realocar el buffer + 1 (entonces la capacidad es bufferInc*len_buffer+1)
	unsigned int bufferInc;
	unsigned int bufferCapac;
	unsigned int bufferLen;
	char* resultadoFGetS;

	bufferInc = 0;
		
/* Si el último caracter es un '\n', el fgets no setea el EOF en el archivo,
porque leyó hasta ahí, pero todavía no encontró el final.
Entonces, se llama una vez más a este loop, haciendo que lea una línea de más.
Se verifica que no hay nada para leer porque el puntero que retorna fgets es NULL
*/
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
			((*buffer)[bufferLen-1] != '\n'));

	return bufferLen;
}

