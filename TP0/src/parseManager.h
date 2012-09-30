#ifndef __PARSE_MANAGER_H__
#define __PARSE_MANAGER_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./line.h"

/**
 * @brief Toma un inStream, lo separa en lineas y las guarda en pLinea 
 * @param pLinea referencia a un vector de lineas vacio
 * @param stream flujo de entrada de datos a ser separados
 * @param lineas tamaño inicial del vector pLineas (lineas ya leidas)
 * @return cantidad de lineas leidas (tamaño del vector pLinea)
 */
unsigned parseLineas(line** *pLinea, unsigned lineas, FILE* stream);


#endif // __PARSE_MANAGER_H___

