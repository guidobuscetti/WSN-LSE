/*----------------------------------------------------------------------------
 *      Name:    DEMO.C
 *      Purpose: USB HID Demo
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC family microcontroller devices only. Nothing
 *      else gives you the right to use this software.
 *
 *      Copyright (c) 2005-2009 Keil Software.
 *---------------------------------------------------------------------------*/

#include "LPC17xx.h"                        /* LPC17xx definitions */

#include "lpc_types.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"

#include "demo.h"
#include "hid.h"

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_nvic.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup USBDEV_USBHID	USBHID
 * @ingroup USBDEV_Examples
 * @{
 */


uint8_t InReport[33];                              /* HID Input Report    */
                                            /*   Bit0   : Buttons  */
                                            /*   Bit1..7: Reserved */

uint8_t OutReport;                             /* HID Out Report      */
                                            /*   Bit0..7: LEDs     */
uint8_t enviando,numero_mje;
float32_t posicion_x,posicion_y;

extern uint8_t  EP0Buf[USB_MAX_PACKET0];
/*
 *  Get HID Input Report -> InReport
 */

void GetInReport (void) {
	uint8_t i;


	if (enviando){
		if(numero_mje)
		{
			InReport[0] = POS_Y;
			memcpy(InReport+1,&posicion_y,sizeof(float32_t));
			numero_mje = 0;
		}
		else
		{
			InReport[0] = POS_X;
			memcpy(InReport+1,&posicion_x,sizeof(float32_t));
			numero_mje = 1;
		}

	}
	else
		for(i=0;i<33;i++) InReport[i] = 0x00;

}


/*
 *  Set HID Output Report <- OutReport
 */

void SetOutReport (void) {

	if (OutReport == 'S')
		enviando = 1;

}


/* Main Program */

int main (void) {
	numero_mje = 0;
	enviando = 0;
	posicion_x = 33.2;
	posicion_y = 64.7;

	USB_Init();                               /* USB Initialization */
	USB_Connect(TRUE);                        /* USB Connect */

	while (1);                                /* Loop forever */
}

void memcpy (void *dst, void *src, uint8_t cnt)
{
	uint8_t *destino, *fuente;
	uint8_t i;

	destino = (uint8_t *) dst;
	fuente = (uint8_t *) src;
	for(i=0;i<cnt;i++) destino[i] = fuente[i];

}
