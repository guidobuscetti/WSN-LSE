/*
 * config.h
 *
 *  Created on: 05/11/2012
 *      Author: joaquin
 */

// 	Aca van los defines caracteristicos de cada nodo

//#define RECEPTOR	1

#define PANID	1
#define ADDR_ENCUEST		1

#define ADDR_LOCAL			10

#define POS_X	2			// Posicion X de nodo fijo
#define POS_Y	0			// Posicion Y de nodo fijo

#if (ADDR_LOCAL<=8)
	#define FIJO
#elif (ADDR_LOCAL >=10)
	#define MOVIL
#endif





/*
#if(RECEPTOR)
	#define ADDR_LOCAL		2
	#define ADDR_REMOTO		1
#else
	#define ADDR_LOCAL		1
	#define ADDR_REMOTO		2
#endif

*/
