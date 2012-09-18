#include "./stoogesort.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define SIZE 20

int main(int argc, char* argv[]) {
    char** v = (char** )malloc(SIZE * sizeof(char*));
    for (int i = 0; i < SIZE; ++i)
        v[i] = (char* )malloc(20 * sizeof(char));

    strcpy(v[0], "fasdf");
    strcpy(v[1], "qwer");
    strcpy(v[2], "cvbn");
    strcpy(v[3], "asdf");
    strcpy(v[4], "azdfgg");
    strcpy(v[5], "zxcv");
    strcpy(v[6], "fasdf");
    strcpy(v[7], "tyuj");
    strcpy(v[8], "mnbbb");
    strcpy(v[9], "bgfd");
    strcpy(v[10], "erttyuy");
    strcpy(v[11], "poik");
    strcpy(v[12], "lokk");
    strcpy(v[13], "jhgfff");
    strcpy(v[14], "wert");
    strcpy(v[15], "rtyui");
    strcpy(v[16], "iop");
    strcpy(v[17], "iopp");
    strcpy(v[18], "iopz");
    strcpy(v[19], "iopa");

    printf("Entrada antes de ordenar: \n");
    for (int i = 0; i < SIZE; ++i)
        printf("%s\n", v[i]);

    stooge_sort(v, SIZE);

    printf("Entrada después de ordenar: \n");
    for (int i = 0; i < SIZE; ++i)
        printf("%s\n", v[i]);

    for (int i = 0; i < SIZE; ++i)
        free(v[i]);
    free(v);
    return 0;
}
