/*
 * config.h
 *
 *  Created on: 05/11/2012
 *      Author: joaquin
 */

// 	Aca van los defines caracteristicos de cada nodo

// Cambiar Address Local para cada nodo (menor a 10 es fijo, mayor o igual movil)
#define ADDR_LOCAL			10

// Si es un nodo fijo, setearle la posicion
#define POS_X	13			// Posicion X de nodo fijo
#define POS_Y	23			// Posicion Y de nodo fijo

#define PANID	1
#define ADDR_ENCUEST		1

#if (ADDR_LOCAL<=8)
	#define FIJO
#elif (ADDR_LOCAL >=10)
	#define MOVIL
#endif
