/*
 * rssi.h
 *
 *  Created on: 29/10/2012
 *      Author: Joaquin
 */

#include "includes.h"
//#include "math.h"

#define dist_max 100
#define dist_min 1

#define rssi_max -54
#define rssi_min -88
#define filas_tabla (rssi_max-rssi_min+1)
#define cols_tabla (dist_max-dist_min+1)

#define AJUSTE_A	45
#define AJUSTE_N	2.3224

float64_t RSSI_to_dist_1 (int8_t * RSSI_vec , uint8_t size);
float64_t RSSI_to_dist_2 (int8_t * RSSI_vec, uint8_t size);
void sumar_vectores (float32_t * a, float32_t * b, uint8_t size);
uint8_t buscar_max (float32_t * vec, uint8_t size);
float64_t promediar (int8_t * vec, uint8_t size);
void calc_tabla (float32_t * tabla);

float32_t tabla[filas_tabla*cols_tabla];


