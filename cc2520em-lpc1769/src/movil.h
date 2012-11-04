/*
 * movil.h
 *
 *  Created on: 03/11/2012
 *      Author: joaquin
 */
#include "includes.h"
#include "arm_math.h"
#include "math.h"

#define MAX_RSSI	20

struct{
		uint8_t numero;
		float32_t	posicion[2];
		s8		rssi[MAX_RSSI];
		uint8_t	last_rssi;
		float32_t prom_rssi;
		float32_t dist;
		} typedef nodo_fijo_t;

void rutina_movil (void);
void trilateracion (nodo_fijo_t * nodo_vec, uint8_t cant_nodos, float32_t * posicion);
void enviar_posicion (uint8_t * payload,uint8_t size,uint16_t dst_address);
float32_t dist2d (float32_t * r1, float32_t * r2);
