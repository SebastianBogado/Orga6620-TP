#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sort.h"
#include "./quicksort.h"
#include "./stoogesort.h"

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
	else 
		opcion = check_param(argv[1]);
	
	switch(opcion) {
		case HELP:	print_help(); break;
		case VERSION:	print_version(); break;
		case QUICK:	sort(argc - 2, argv + 2, quick_sort); break;
		case STOOGE: 	sort(argc - 2, argv + 2, stooge_sort); break;
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
	if (!strcmp(param, "-V") || !strcmp(param, "--version"))
		return VERSION;
	else
		return HELP;
}

void print_help() {
	printf(
	"tp0 [OPTIONS] [file...]\n"
	"-h, --help\t""display this help and exit.\n"
	"-V, --version\t""display version information and exit.\n"
	"-q, --quick\t""use the quicksort algorithm.\n"
	"-s, --stooge\t""use the stoogesort algorithm.\n"
	);
}

void print_version() {
	printf("Organizacion de Computadoras [6620] - TP0 \n");	
	printf("Version: 1.0");
	printf("Alumnos: Bogado, Sebastian \n");
	printf("         Garcia Marra, Alejandro\n");
}

