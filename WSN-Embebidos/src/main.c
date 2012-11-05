#include "config.h"
#include "includes.h"

int ledcont, pausecont;

void SysTick_Handler(void)
{
	if(ledcont)
	{
		ledcont--;
		if(ledcont==0)
			GPIO_ClearValue(LED_PORT, LED_BIT);
	}
	if(pausecont) pausecont--;
}

void pausems(int t)
{
	pausecont = t;
	while(pausecont);
}

void ledFlash(int t)
{
	GPIO_SetValue(LED_PORT, LED_BIT);
	ledcont = t;
}

int main(void)
{
	frameData d;
#if (RECEPTOR)
	double dist,dist1;
	uint8_t i=0;
	s8 RSSI_vec[20];
	calc_tabla(tabla);
#endif

	SysTick_Config(SystemCoreClock/1000);


	GPIO_SetDir(LED_PORT, LED_BIT, 1);
	GPIO_ClearValue(LED_PORT, LED_BIT);

	if(ccInit(PANID, ADDR_LOCAL, ADDR_LOCAL, 0)<0)
	{
		GPIO_SetValue(LED_PORT, LED_BIT);
		while(1);
	}



	while(1)
	{
#if(RECEPTOR)
		d = ccFrameRx();
		if(macFCFGetFrameType(d.fcf)==MAC_FRAME_TYPE_DATA)
		{
			ledFlash(50);
			RSSI_vec[i] = d.rssi;
			i++;
			if (i==20) i=0;
			dist = RSSI_to_dist_1(RSSI_vec,20);
			dist1 = RSSI_to_dist_2(RSSI_vec,20);
			printf("Prob:%.2fm Ajus:%.2fm\n",dist,dist1);
		}


#else
		d.dst.shortAddr.panid = d.src.shortAddr.panid = PANID;
		d.dst.shortAddr.addr = ADDR_REMOTO;
		d.src.shortAddr.addr = ADDR_LOCAL;

		d.fcf = ccWrapperFCF(MAC_FRAME_TYPE_DATA, 0, 0, 1, 0,
				MAC_ADDR_MODE_SHORT, 0, MAC_ADDR_MODE_SHORT);

		memcpy(d.payload, "hola", 5);
		d.pl_length = 5;

		if(ccFrameTx(d) < 0) GPIO_SetValue(LED_PORT, LED_BIT);
		else ledFlash(20);

		//recibo ACK
//		frameData e = ccFrameRx();
//		if(macFCFGetFrameType(e.fcf)==MAC_FRAME_TYPE_ACK)
//			ledFlash(20);

		pausems(1000);
#endif
	}
	return 0;
}

// MAIN PARA NODO MOVIL:

#ifdef NODOMOVIL

#define PANID	1
#define ADDR_LOCAL 10

void main (void)
{
	// Seteo el LED
	GPIO_SetDir(LED_PORT, LED_BIT, 1);
	GPIO_ClearValue(LED_PORT, LED_BIT);

	// Inicializo direcciones del tranceiver
	if(ccInit(PANID, ADDR_LOCAL, ADDR_LOCAL, 0)<0)
	{
		// Si no se inicializa correctamente se cuelga
		GPIO_SetValue(LED_PORT, LED_BIT);
		while(1);
	}

	// Calculo la tabla para el ajuste probabilistico
	calc_tabla(tabla);

	// Inicio la tarea del nodo movil

	rutina_movil();

	// En teoria nunca debe llegar a esta instancia
	for(;;);
}
#endif



void mainTRUCHO (void)
{
	double dist,dist1;

	s8 RSSI_vec[20]={-70,-71,-70,-70,-72,-73,-70,-72,-69,-72,-71,-70,-70,-70,-70,-72,-73,-73,-72,-71};
	calc_tabla(tabla);
	dist = RSSI_to_dist_1(RSSI_vec,20);
	dist1 = RSSI_to_dist_2(RSSI_vec,20);
	while(1);
}
