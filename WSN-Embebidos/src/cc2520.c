/*
 * cc2520.c
 * Interfaz con CC2520 conectado a SSP1
 *
 *  Created on: 30/01/2012
 *      Author: pablo
 */

#include "includes.h"

u8 ccCmd(u8 cmd, u16 addr, u8 n, void * data)
{
	uint8_t txdata[n+10];
	uint8_t rxdata[n+10];
	u8 length,j;
	int i;

	if(n>128) return -1;

	txdata[0] = cmd;

	switch(cmd)
	{
		case SFLUSHTX:
		case SFLUSHRX:
		case STXON:
		case STXONCCA:
		case SRXON:
		case SSAMPLECCA:
		case SNOP:
			length = 1;
			break;

		case TXBUF:
			length = n+1;
			for(i=0; i<n; i++) txdata[i+1] = ((u8*)data)[i];
			break;

		case RXBUF:
			for(i=1; i<n+1; i++) txdata[i] = 0;
			length = n+1;
			break;

		case BCLR:
		case BSET:
			if(addr > 0x1F) return -1;
			if(n > 7) return -1;
			txdata[1] = ((addr&0x1F)<<3)|(n&0x7);
			length = 2;
			break;

		case MEMWR:
			txdata[0] |= ((addr&0xFFF)>>8);
			txdata[1] = (u8)(addr&0xFF);
			for(i=0; i<n; i++) txdata[i+2]=((u8*)data)[i];
			length = n+2;
			break;

		case MEMRD:
			txdata[0] |= ((addr&0xFFF)>>8);
			txdata[1] = (u8)(addr&0xFF);
			for(i=2; i<n+2; i++) txdata[i]=0;
			length = n+2;
			break;

		case REGRD:
			txdata[0] |= addr&0x3F;
			for(i=1; i<n+1; i++) txdata[i] = 0;
			length = n+1;
			break;

		case REGWR:
			txdata[0] |= addr&0x3F;
			for(i=0; i<n; i++) txdata[i+1]=((u8*)data)[i];
			length = n+1;
			break;

		default:
			return -1;
	}

	SSP_DATA_SETUP_Type sspData;

	sspData.length = length;
	sspData.rx_data = rxdata;
	sspData.tx_data = txdata;

	SSEL_Clr();

	for(j=0;j<100;j++);
	//pausems(1);

	SSP_ReadWrite(LPC_SSP1, &sspData, SSP_TRANSFER_POLLING);

	for(j=0;j<100;j++);
	//pausems(1);
	SSEL_Set();

	switch(cmd)
	{
		case SFLUSHTX:
		case SFLUSHRX:
		case STXON:
		case STXONCCA:
		case SRXON:
		case SSAMPLECCA:
		case SNOP:
		case TXBUF:
		case BCLR:
		case BSET:
			break;

		case RXBUF:
		case REGRD:
		case REGWR:
			for(i=0; i<n; i++) ((u8*)data)[i] = rxdata[i+1];
			break;

		case MEMWR:
		case MEMRD:
			for(i=0; i<n; i++) ((u8*)data)[i] = rxdata[i+2];
			break;

		default:
			return -1;
	}

	return rxdata[0];
}

u8 ccRegRd(u8 reg, u8 n, void * out)
{
	if(reg < 0x040)
		return ccCmd(REGRD, reg, n, out);
	else
		return ccCmd(MEMRD, reg, n, out);
}

u8 ccRegWr(u8 reg, u8 n, void * in)
{
	if(reg < 0x040)
		return ccCmd(REGWR, reg, n, in);
	else
		return ccCmd(MEMWR, reg, n, in);
}


/* Actualiza registros del CC2520 siguiendo Tabla 21 de la hoja de datos */
void ccConfig(void)
{
	u8 i;

	//Potencia de salida
	//i=0x32; //0dBm
	i=0xF7; //5dBm
	ccCmd(MEMWR, TXPOWER, 1, &i);
	i=0xF8;
	ccCmd(MEMWR, CCACTRL0, 1, &i);
	i=0x85;
	ccCmd(MEMWR, MDMCTRL0, 1, &i);
	i=0x14;
	ccCmd(MEMWR, MDMCTRL1, 1, &i);
	i=0x3F;
	ccCmd(MEMWR, RXCTRL, 1, &i);
	i=0x5A;
	ccCmd(MEMWR, FSCTRL, 1, &i);
	i=0x2B;
	ccCmd(MEMWR, FSCAL1, 1, &i);
	i=0x11;
	ccCmd(MEMWR, AGCCTRL1, 1, &i);
	i=0x10;
	ccCmd(MEMWR, ADCTEST0, 1, &i);
	i=0x0E;
	ccCmd(MEMWR, ADCTEST1, 1, &i);
	i=0x03;
	ccCmd(MEMWR, ADCTEST2, 1, &i);

	//ch. 1
	i=0x10;
	ccRegWr(FREQCTRL, 1, &i);

}

/* parametros: PANID y direcciones locales */
s8 ccInit(u16 panid, u16 shortAddr, u64 extAddr, u8 autoAck)
{
	SSP_CFG_Type sspCfg;
	PINSEL_CFG_Type pinCfg;
	uint8_t aux;


	//P0.0: RESETn
	LPC_GPIO0->FIODIR |= 1;
	LPC_GPIO0->FIOSET = 1;

	//P0.24: VREG_EN
	LPC_GPIO0->FIODIR |= 1<<24;
	LPC_GPIO0->FIOSET = 1<<24;

	//P0.1: GPIO5 (poner a GND o Vcc)
	LPC_GPIO0->FIODIR |= 1<<1;

	//P0.9: MOSI1
	pinCfg.Portnum = PINSEL_PORT_0;
	pinCfg.Pinnum = PINSEL_PIN_9;
	pinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	pinCfg.Funcnum = PINSEL_FUNC_2;
	pinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pinCfg);

	//P0.8: MISO1
	pinCfg.Pinnum = PINSEL_PIN_8;
	PINSEL_ConfigPin(&pinCfg);

	//P0.7: SCK1
	pinCfg.Pinnum = PINSEL_PIN_7;
	PINSEL_ConfigPin(&pinCfg);

	//P0.6: SSEL1 -> Controlado por software
//	pinCfg.Pinnum = PINSEL_PIN_6;
//	PINSEL_ConfigPin(&pinCfg);
	LPC_GPIO0->FIODIR |= 1<<6;
	SSEL_Set();

	//Parametros del puerto
	sspCfg.CPHA = SSP_CPHA_FIRST;
	sspCfg.CPOL = SSP_CPOL_HI;
	sspCfg.ClockRate = 1000000;
	sspCfg.Databit = SSP_DATABIT_8;
	sspCfg.FrameFormat = SSP_FRAME_SPI;
	sspCfg.Mode = SSP_MASTER_MODE;

	SSP_Init(LPC_SSP1, &sspCfg);
	SSP_Cmd(LPC_SSP1, ENABLE);

	u8 id;
	ccRegRd(CHIPID, 1, &id);
	if(id != 0x84) return -1;

	ccConfig();

	if(autoAck) ccCmd(BSET, FRMCTRL0, 5, 0);

	ccSetLocalExtAddr(extAddr);
	ccSetLocalPANID(panid);
	ccSetLocalShortAddr(shortAddr);

	// Configuro la el pin P0.1 como entrada
	GPIO_SetDir(0,1<<1,0);

	// Configuro el pin 5 para que informe nuevo frame
	aux = 0x09;
	ccRegWr(GPIOCTRL5,1,&aux);

	// Configuro la interrupcion de GPIO
	GPIO_IntCmd(0,1<<1,0);

	// Activo la radio
	ccCmd(SRXON, 0, 0, 0);

	return 0;
}
