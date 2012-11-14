/*
 * fijo.c
 *
 *  Created on: 14/11/2012
 *      Author: joaquin
 */
#include "fijo.h"


void rutina_fijo (void)
{

	frameData d_rx,d_tx;
	uint16_t addr_aux;
	uint8_t reg_nodos[10];
	uint8_t i;

	// Inicializo el registro
	for(i=0;i<10;i++)
	{
		reg_nodos[i] = 0;
	}

	// Configuro mensajes que mando

	d_tx.dst.shortAddr.panid = d_tx.src.shortAddr.panid = PANID;
	d_tx.src.shortAddr.addr = ADDR_LOCAL;

	d_tx.fcf = ccWrapperFCF(MAC_FRAME_TYPE_DATA, 0, 0, 1, 0,
	MAC_ADDR_MODE_SHORT, 0, MAC_ADDR_MODE_SHORT);

	// Comienzo rutina infinita
	while(1)
	{
		// Leo el tranceiver
		d_rx = ccFrameRx();

		// Veo si es mensaje util
		if(macFCFGetFrameType(d_rx.fcf)==MAC_FRAME_TYPE_DATA)
		{

			// Veo si es mensaje del nodo anterior
			if (d_rx.src.shortAddr.addr == ADDR_LOCAL -1 )
			{
				// Si es mensaje, envio posicion del nodo a todos

				d_tx.dst.shortAddr.addr = 0xFFFF;
				d_tx.payload[0] = POS_X; 	// Mando posicion X
				d_tx.payload[1] = POS_Y;	// Mando posicion Y
				d_tx.pl_length = 2;
				ccFrameTx(d_tx);
			}
			else if (d_rx.src.shortAddr.addr == ADDR_LOCAL +1 )
			{
				// Verifico si es mensaje de retorno
				if (d_rx.pl_length > 2)
				{
					// Veo si ya reenvie esa secuencia
					memcpy(&addr_aux,d_rx.payload,2);
					if (d_rx.payload[2] != reg_nodos[addr_aux - 10])
					{
						// Si no la reenvie, la mando al anterior

						// Copio el payload
						memcpy(d_tx.payload,d_rx.payload,d_rx.pl_length);

						// Reenvio al anterior
						d_tx.dst.shortAddr.addr = ADDR_LOCAL -1;
						ccFrameTx(d_tx);

						// Registro el envio
						reg_nodos[addr_aux - 10] = d_rx.payload[2];
					}
				}
			}
			else if (d_rx.src.shortAddr.addr >=10 )
			{
				// Si es mensaje de nodo movil, adapto el mensaje

				// Copio direccion del nodo a 2 primeros bytes
				memcpy(d_tx.payload, &(d_rx.src.shortAddr.addr), 2);
				// Copio el numero de secuencia del payload
				memcpy((d_tx.payload)+2, d_rx.payload, 1);
				// Luego copio el payload con la posicion del movil
				memcpy((d_tx.payload)+3, (d_rx.payload)+1, sizeof(float32_t)*2);

				d_tx.pl_length = sizeof(float32_t)*2 + 3;

				// Reenvio
				d_tx.dst.shortAddr.addr = ADDR_LOCAL -1;
				ccFrameTx(d_tx);

				// Registro el envio
				reg_nodos[d_rx.src.shortAddr.addr - 10] = d_rx.payload[0];

			}

		}

	}

}
