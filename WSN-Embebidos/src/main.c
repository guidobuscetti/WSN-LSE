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

// MAIN PARA NODO MOVIL:

#ifdef MOVIL

int main (void)
{
	int8_t init = -1;
	// Configuro el tick del sistema
	SysTick_Config(SystemCoreClock/1000);

	// Seteo el LED
	GPIO_SetDir(LED_PORT, LED_BIT, 1);
	GPIO_ClearValue(LED_PORT, LED_BIT);

	// Inicializo direcciones del tranceiver
	GPIO_SetValue(LED_PORT, LED_BIT);
	while(init<0)
	{
		init = ccInit(PANID, ADDR_LOCAL, ADDR_LOCAL, 0);
	}
	GPIO_ClearValue(LED_PORT, LED_BIT);

	// Calculo la tabla para el ajuste probabilistico
	calc_tabla(tabla);

	// Inicio la interrupcion
	NVIC_EnableIRQ(EINT3_IRQn);

	// Inicio la tarea del nodo movil
	rutina_movil();

	// En teoria nunca debe llegar a esta instancia
	for(;;);
}
#endif

#ifdef FIJO
// Main para nodo FIJO
int main (void)
{
	int8_t init=-1;

	// Configuro el tick del sistema
	SysTick_Config(SystemCoreClock/1000);

	// Seteo el LED
	GPIO_SetDir(LED_PORT, LED_BIT, 1);
	GPIO_ClearValue(LED_PORT, LED_BIT);

	GPIO_SetValue(LED_PORT, LED_BIT);
	// Inicializo direcciones del tranceiver
	while(init<0)
	{
		init = ccInit(PANID, ADDR_LOCAL, ADDR_LOCAL, 0);
	}
	GPIO_ClearValue(LED_PORT, LED_BIT);

	// Inicio la interrupcion externa
	NVIC_EnableIRQ(EINT3_IRQn);

#if (ADDR_LOCAL == 2)
	// Si es el primer nodo, seteo el timer que sincroniza red
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct;

	// Seteo escala de timer en 1 milosegundo
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue = 1000;

	// Uso Timer 0
	TIM_MatchConfigStruct.MatchChannel = 0;
	// Habilito la interrupcion
	TIM_MatchConfigStruct.IntOnMatch = TRUE;
	// Habilito el Reset
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	TIM_MatchConfigStruct.StopOnMatch = FALSE;
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	// Seteo valor final 10 segundos
	TIM_MatchConfigStruct.MatchValue = 3000;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);

	// Inicio la interrupcion
	NVIC_EnableIRQ(TIMER0_IRQn);

#endif
	// Inicio la tarea del nodo fijo
	rutina_fijo();

	// En teoria nunca debe llegar a esta instancia
	for(;;);
}
#endif


void EINT3_IRQHandler( void )
{
	// Limpio la interrupción
	GPIO_ClearInt(0,(1<<1));

	// Limpio el flag en cc2520
	ccCmd(BCLR, EXCFLAG1, 0, 0);

	// Seteo flag de mensaje nuevo
	mje_nuevo = 1;
}

void TIMER0_IRQHandler (void)
{
	// Verifico que haya sido la interrupcion
	if (TIM_GetIntStatus(LPC_TIM0,TIM_MR0_INT) == SET)
	{
		// "Creo" un mensaje recibido
		d_rx.fcf = MAC_FRAME_TYPE_DATA;
		d_rx.dst.shortAddr.panid = PANID;
		d_rx.dst.shortAddr.addr = ADDR_LOCAL;
		d_rx.payload[0] = (uint8_t)0;
		d_rx.pl_length = 1;
		d_rx.src.shortAddr.panid = PANID;
		d_rx.src.shortAddr.addr = ADDR_LOCAL-1;
		mje_nuevo = 1;
		mje_simulado = 1;

	}

	// Limpio el flag de interrupcion
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
}
