#include "./parseManager.h"
#include<stdio.h>
#include<stdlib.h>
unsigned cargarBuffer(char* *buffer, FILE* stream);


unsigned parseLineas(line** *pLinea, unsigned lineas, FILE* stream){

	char* buffer = NULL;
	unsigned bufferLen;
	unsigned lineSize = 0;

	bufferLen = cargarBuffer(&buffer, stream);

	for (int i=0; i<bufferLen; i++){

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

	int bufferSize = 1024;
	unsigned bufferInc = 0;
	unsigned bufferCap = 0;
	unsigned bufferLen = 0;
  	unsigned readBytes = 0;

	do{
		bufferInc++;
		bufferCap = bufferInc * bufferSize +1;

		(*buffer) = (char*)realloc((*buffer), bufferCap*sizeof(char));
		readBytes = (unsigned)fread(
				((*buffer) + bufferCap - (bufferSize +1)),
				 1, (bufferSize ),
				 stream);

		bufferLen += readBytes;

	}while(	!feof(stream) );

//	if(feof(stream)){
		// si el archivo no termina con un salto de linea
		// se lo agrega para normalizar todas las lineas
		if((*buffer)[bufferLen-1] != '\n')
			(*buffer)[bufferLen++] = '\n';
//			(*buffer)[bufferLen+1] = '\0';
//		}
//
//	}
	return bufferLen;
}
