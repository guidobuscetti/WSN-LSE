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

	// Inicio la tarea del nodo fijo
	rutina_fijo();

	// En teoria nunca debe llegar a esta instancia
	for(;;);
}
#endif
