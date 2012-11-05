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

// COMO USO EL 1769 INCLUYO SUS LIBRERIAS

#include "lpc17xx_ssp.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

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




void pausems(int t);

//#include "math.h"
#include "arm_math.h"

#include "cc2520.h"
#include "cc2520-mac.h"
#include "rssi.h"
//#include "movil.h"



#endif /* INCLUDES_H_ */
