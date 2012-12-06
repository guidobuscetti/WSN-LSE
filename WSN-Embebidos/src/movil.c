#include "movil.h"

void rutina_movil (void)
{
	// Verificaiones y declaraciones
	frameData data;				// Data que leo
	nodo_fijo_t nodo_vec[20];	// Defino nodos fijos
	uint8_t i,cant_nodos=0;		// Cantidad de nodos fijos
	float32_t posicion[2];		// Posicion del nodo movil
	uint8_t j,listo,k;
	uint32_t aux;

	while(1)
	{
		if (mje_nuevo)
		{
			mje_nuevo = 0;
			data = ccFrameRx();		// Leo data del receptor

			// Prendo led por breve tiempo
			GPIO_SetValue(LED_PORT,LED_BIT);
			for(aux=0;aux<10000;aux++);
			GPIO_ClearValue(LED_PORT,LED_BIT);


			// Verifico que sean datos utiles
			if(macFCFGetFrameType(data.fcf)==MAC_FRAME_TYPE_DATA)
			{
				// Busco nodo que envio mensaje

				i=0;
				listo=0;

				// Si el RSSI es malo lo descarto
				if(data.rssi != 0)
				{
					//printf("%d\n",data.rssi);

					while(i<=cant_nodos && !listo)
					{
						// Si se encuentra, se guarda el RSSI
						if (data.src.shortAddr.addr == nodo_vec[i].numero)
						{
							k = i; // Guardo el numero del nodo
							nodo_vec[i].rssi[nodo_vec[i].last_rssi] = data.rssi;
							nodo_vec[i].last_rssi++;
							if (nodo_vec[i].last_rssi == RSSI_MAX) nodo_vec[i].last_rssi=0;
							listo=1;
						}
						i++;
					}

					// Si no encontro el nodo, defino uno nuevo
					if (!listo)
					{
						nodo_vec[cant_nodos].numero = (data.src).shortAddr.addr;		// Guardo numero
						nodo_vec[cant_nodos].posicion[0] = (float32_t)data.payload[0];	// Guardo posicion X
						nodo_vec[cant_nodos].posicion[1] = (float32_t)data.payload[1];	// Guardo posicion Y
						nodo_vec[cant_nodos].last_rssi = 0;								// Inicio last_rssi
						nodo_vec[cant_nodos].rssi[nodo_vec[cant_nodos].last_rssi] = data.rssi;		// Guardo rssi
						nodo_vec[cant_nodos].last_rssi++;
						for(j=0;j<RSSI_MAX;j++) nodo_vec[cant_nodos].rssi[j] = 0;		// Inicilizo rssi en 0
						k = cant_nodos; 												// Guardo el numero de nodo
						cant_nodos++;													// Aumento cantidad de nodos
					}

					// Calculo las distancias a cada nodo (si recibo de 3)

					if (k==2)
					{
						i=0;
						for(i=0;i<cant_nodos;i++)
						{
							nodo_vec[i].dist = (float32_t) RSSI_to_dist_1(nodo_vec[i].rssi,RSSI_MAX);	// Calculo distancia
							printf("Distancia a nodo %d : %.2fm. Ultimo RSSI:%d\n",i+1,nodo_vec[i].dist,nodo_vec[i].rssi[nodo_vec[i].last_rssi-1]);
						}
						nodo_vec[k].prom_rssi = (float32_t) promediar(nodo_vec[k].rssi,RSSI_MAX);	// Calculo promedio rssi
					}

					// Pregunto si hago trilateración

					// Caso simple : con 3 nodos fijos UNICAMETE, hago trilateracion

					if (cant_nodos >= 3 && k==2)
					{
						trilateracion(nodo_vec,cant_nodos,posicion);
						printf("Posicion (%.2f,%.2f)\n",posicion[0],posicion[1]);
					}

					// Mando la posicion
					enviar_posicion((uint8_t*)posicion,sizeof(float32_t)*2,ADDR_ENCUEST);
					}
				}
			}

			// Deshabilita el systick para que no despierte al sleep
			SYSTICK_Cmd(DISABLE);

			// Entra en modo Deep-Sleep
			CLKPWR_DeepSleep();

			// Aqui se reanuda el programa

			// Habilita nuevamente el systick
			SYSTICK_Cmd(ENABLE);
	}

}


void trilateracion (nodo_fijo_t * nodo_vec, uint8_t cant_nodos, float32_t * posicion)
{

	uint8_t i,i1,i2,i3;

	float32_t Adata[2*2];
	float32_t Atdata[2*2];
	float32_t bdata[2*1];
	float32_t distref[2];

	arm_status s;

	// Seleccion de nodos para trilaterar
	i1=0;
	i2=0;
	i3=0;

	// Busco los tres nodos con mejor RSSI.

	for(i=0;i<cant_nodos;i++)
	{
		if (nodo_vec[i].prom_rssi>nodo_vec[i3].prom_rssi)
		{	if (nodo_vec[i].prom_rssi>nodo_vec[i2].prom_rssi)
			{
				if (nodo_vec[i].prom_rssi>nodo_vec[i1].prom_rssi)
				{
					i3=i2;
					i2=i1;
					i1=i;
				}
				else
				{
					i3=i2;
					i2=i;
				}
			}
			else
			{
				i3=i;
			}
		}
	}


	// ALGORITMO DE TRILATERACION

	// Trilatero con i1,i2,i3

	// Calculo las distancias entre nodos
	distref[0] = dist2d(nodo_vec[i2].posicion,nodo_vec[i1].posicion);
	distref[1] = dist2d(nodo_vec[i3].posicion,nodo_vec[i1].posicion);

	// Creo la Matriz A
	Adata[0] = nodo_vec[i2].posicion[0] - nodo_vec[i1].posicion[0];
	Adata[1] = nodo_vec[i2].posicion[1] - nodo_vec[i1].posicion[1];
	Adata[2] = nodo_vec[i3].posicion[0] - nodo_vec[i1].posicion[0];
	Adata[3] = nodo_vec[i3].posicion[1] - nodo_vec[i1].posicion[1];

	// Creo el vector b
	bdata[0] = (nodo_vec[i1].dist*nodo_vec[i1].dist - nodo_vec[i2].dist*nodo_vec[i2].dist + distref[0]*distref[0])/2;
	bdata[1] = (nodo_vec[i1].dist*nodo_vec[i1].dist - nodo_vec[i3].dist*nodo_vec[i3].dist + distref[1]*distref[1])/2;

	arm_matrix_instance_f32 matA = {2,2,Adata};
	arm_matrix_instance_f32 matAt = {2,2,Atdata};
	arm_matrix_instance_f32 matB = {2,1,bdata};

	// Calculo A transpuesta
	s = arm_mat_trans_f32(&matA,&matAt);

	// Matriz Auxiliar 1
	float32_t aux1data[3*3];
	arm_matrix_instance_f32 mataux1 =  {3,3,aux1data};

	// Aux 1 = At*A
	s = arm_mat_mult_f32(&matAt,&matA,&mataux1);

	// Invierto la matriz auxiliar
	float32_t auxinvdata[3*3];
	arm_matrix_instance_f32 matauxinv =  {3,3,auxinvdata};

	s = arm_mat_inverse_f32(&mataux1,&matauxinv);

	// Matriz auxiliar 2
	float32_t aux2data[3*3];
	arm_matrix_instance_f32 mataux2 =  {3,3,aux2data};

	// Aux 2 = AuxInv * At
	s = arm_mat_mult_f32(&matauxinv,&matAt,&mataux2);

	// Aux1 = Aux2 * b
	s = arm_mat_mult_f32(&mataux2,&matB,&mataux1);

	// Lo guardo en posicion
	posicion[0] = aux1data[0] + nodo_vec[i1].posicion[0];
	posicion[1] = aux1data[1] + nodo_vec[i1].posicion[1];

}


void enviar_posicion (uint8_t * payload,uint8_t size,uint16_t dst_address)
{

	frameData d;

	d.dst.shortAddr.panid = PANID;
	d.src.shortAddr.panid = PANID;
	d.dst.shortAddr.addr = dst_address;
	d.src.shortAddr.addr = ADDR_LOCAL;

	d.fcf = ccWrapperFCF(MAC_FRAME_TYPE_DATA, 0, 0, 1, 0,
					MAC_ADDR_MODE_SHORT, 0, MAC_ADDR_MODE_SHORT);

	// Mando el numero de secuencia
	d.payload[0] = sec_num;
	// Incremento el numero de secuencia
	sec_num++;

	memcpy((d.payload)+1, payload, size);
	d.pl_length = size+1;

	ccFrameTx(d);

}

float32_t dist2d (float32_t * r1, float32_t * r2)
{
	float32_t x = r1[0] - r2[0];
	float32_t y = r1[1] - r2[1];

	x *= x;
	y *= y;

	x += y;

	arm_sqrt_f32(x,&x);

	return x;
}
