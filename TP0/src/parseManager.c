#include "./parseManager.h"
#include<stdio.h>
#include<stdlib.h>

unsigned cargarBuffer(char* *buffer, FILE* stream);


unsigned parseLineas(char** *pLinea, unsigned lineas, FILE* stream){
	
	char* buffer = NULL;

	unsigned int bufferLen;
	int i = 0;

	while (!feof(stream)) {
		i++;		
		bufferLen = cargarBuffer(&buffer, stream);

		//Evita guardar dos veces el buffer ante un eof
		lineas++;
		(*pLinea) = (char**)realloc((*pLinea), lineas * sizeof(char*));		
		(*pLinea)[lineas-1] = NULL;	
		//bufferLen+1 contempla el \n a ser leido por el strcpy
		(*pLinea)[lineas-1] = (char*)realloc((*pLinea)[lineas-1], bufferLen+1);
		strcpy((*pLinea)[lineas-1], buffer);
	}
	free(buffer);
	
	
//PARCHE para la lectura extra al final del archivo


	return lineas; 

}


unsigned cargarBuffer(char* *buffer, FILE* stream){

	const int len_buffer = 1024;
	const int tam_buffer = len_buffer +1;
	

	// la siguiente variable cuenta la cantidad de veces que fue necesario
	// realocar el buffer + 1 (entonces la capacidad es bufferInc*len_buffer+1)
	unsigned int bufferInc = 0;
	unsigned int bufferCapac;
	unsigned int bufferLen;
//	char* resultadoFGetS;
	int endOfLine = 0;
		
/* Si el último caracter es un '\n', el fgets no setea el EOF en el archivo,
porque leyó hasta ahí, pero todavía no encontró el final.
Entonces, se llama una vez más a este loop, haciendo que lea una línea de más.
Se verifica que no hay nada para leer porque el puntero que retorna fgets es NULL
*/
	/*
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
	*/

	
	bufferInc++;
	bufferCapac = bufferInc*len_buffer + 1;
	(*buffer) = (char*)realloc((*buffer), bufferCapac*sizeof(char));

	while( fgets((*buffer) + bufferCapac - (tam_buffer),tam_buffer,stream) 
		&& !endOfLine){
		
		bufferLen = strlen(*buffer);
		
		endOfLine = ((*buffer)[bufferLen-1] == '\n');
		
		bufferInc++;
		bufferCapac = bufferInc*len_buffer + 1;
		(*buffer) = (char*)realloc((*buffer), bufferCapac*sizeof(char));


	}






	return bufferLen;
}

