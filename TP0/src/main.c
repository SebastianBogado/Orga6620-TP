#include <stdio.h>
#include <string.h>

#define ERROR 	-1
#define HELP	0
#define VERSION	1
#define QUICK	2
#define STOOGE	3

int check_param(char* param);
void print_help();
void print_version();

int main(int argc, char* argv[]) {
	int opcion;
	
	if (argc == 1 )
		opcion = HELP;
	else if (argc == 2) { //no se reciben archivos, leer stdin
		opcion = check_param(argv[1]);
		printf("Leer buffer de stdin... @todo\n");
	}
	else { // argc >= 3, se aplica a uno o mas archivos
		opcion = check_param(argv[1]);
		
		//Se puede unificar esto con el manejo del stdin 
		//hay que hacer la lectura por fread con el buffer variable
		//pero despues hay que convertirlo todo a ints par evitar
		//el error de "FFFFFF"
			
		
		// verificar archivo, etc...
	}
	
	switch(opcion) {
		case HELP: print_help(); break;
		case VERSION: printf("Mostrar versión... @todo\n"); break;
		case QUICK: printf("Ordenar con quicksort... @todo\n"); break;
		case STOOGE: printf("Ordenar con stoogesort... @todo\n"); break;
		default: break;		
	}
	return 0;
}


int check_param(char* param) {

	if (!strcmp(param, "-q") || !strcmp(param, "--quick"))
		return QUICK;
	else 
	if (!strcmp(param, "-s") || !strcmp(param, "--stooge"))
		return STOOGE;
	else
	// en el enunciado dice v mayúscula, importará?
	if (!strcmp(param, "-v") || !strcmp(param, "--version"))
		return VERSION;
	else
		return HELP;
}

void print_help() {
	printf(
	"tp0 [OPTIONS] [file...]\n"
	"-h, --help\t""display this help and exit.\n"
	"-v, --version\t""display version information and exit.\n"
	"-q, --quick\t""use the quicksort algorithm.\n"
	"-s, --stooge\t""use the stoogesort algorithm.\n"
	);
}
/** main de un TP que leía entradas "infinitas" de stdin
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "./Parser.h"
#include "./BaseDeDatos.h"

#define LEN_BUFFER 128
#define TAM_BUFFER LEN_BUFFER+1

int main(int argc, char* argv[]) {
	if (argc > 1)
		return 1;

	char* buffer = NULL;
	// la siguiente variable cuenta la cantidad de veces que fue necesario
	// realocar el buffer + 1 (entonces la capacidad es bufferInc*LEN_BUFFER+1)
	unsigned int bufferInc;
	unsigned int bufferCapac;
	unsigned int bufferLen;
	char* resultadoFGetS;

	while (!feof(stdin)) {
		bufferInc = 0;
		do {
			bufferInc++;
			bufferCapac = bufferInc*LEN_BUFFER + 1;
			buffer = (char*)realloc(buffer, bufferCapac*sizeof(char));
			// buffer + bufferCapac - (TAM_BUFFER) pone al puntero en la
			// posición inicial de la porción nueva de memoria
			resultadoFGetS = fgets(buffer + bufferCapac - (TAM_BUFFER),
								   TAM_BUFFER, stdin);
			bufferLen = strlen(buffer);
			// Mientras que fgets no devuelva un puntero nulo y
			// que el último char no sea un fin de línea, repetir
		}while (resultadoFGetS &&
				buffer[bufferLen-1] != '\n');

		if (resultadoFGetS) {
			// chomp, con la seguridad de que hay un '\n' en esa posición
			buffer[bufferLen - 1] = '\0';
			parsear(buffer, bufferLen-1);
		}
	}

	free(buffer);
	eliminarBaseDeDatos();
	return 0;
}
*/
