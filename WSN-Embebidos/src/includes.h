/*
 * includes.h
 *
 *  Created on: 31/01/2012
 *      Author: pablo
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Incluyo configuracion de la RED
#include "config.h"

// Incluyo defines (de hardware y software)
#define LED_PORT	0
#define LED_BIT		(1<<22)

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef int64_t s64;
typedef uint64_t u64;
typedef char ascii;

// Incluyo drivers del micro
#include "lpc17xx_ssp.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"

// Incluyo definiciones matematicas
#include "math.h"
#include "arm_math.h"

// Incluyo headers de funciones
#include "cc2520.h"
#include "cc2520-mac.h"
#include "rssi.h"

#include "movil.h"
#include "fijo.h"

void pausems(int t);

// Defino variables globales
uint8_t mje_nuevo,mje_simulado,enviando,numero_mje,OutReport,InReport[33];
float32_t posicion_x,posicion_y;


//Includes si se trata del nodo conectado a PC
#if (ADDR_LOCAL==1)
#include "lpc_types.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"

#include "USBapp.h"
#include "hid.h"

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_nvic.h"
#endif


#endif /* INCLUDES_H_ */

