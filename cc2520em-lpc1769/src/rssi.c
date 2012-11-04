/*
 * rssi.c
 *
 *  Created on: 29/10/2012
 *      Author: Joaquin
 */

#include "rssi.h"

//	Pasar RSSI a distancia usando metodo probabilistico
double RSSI_to_dist_1 (s8 * RSSI_vec , uint8_t size)
{
	float32_t suma[cols_tabla];
	uint8_t i,dist,rssi_index;
	s8 aux;

	// Inicializo el vector suma
	for(i=0;i<cols_tabla;i++)
	{suma[i]=0;}

	// Inicio el loop sobre el vector de RSSI
	for(i=0;i<size;i++)
	{

		rssi_index = (uint8_t) ((s8)rssi_max - RSSI_vec[i]);

		// Sumo las probabilidades para ese RSSI
		if (rssi_index>=0 && rssi_index<filas_tabla)
		{
			sumar_vectores(suma,tabla+((uint32_t)rssi_index)*cols_tabla,cols_tabla);
		}
	}

	// Busco el máximo
	dist = buscar_max(suma,dist_max);
	dist++;

	return (double)dist;

}

// Pasar RSSI a distancia ajustando la curva
double RSSI_to_dist_2 (s8 * RSSI_vec, uint8_t size)
{
	double dist,prom,exponente;

	// Hago un promedio de todos los RSSI
	prom = promediar (RSSI_vec,size);

	// Ajusto con la curva
	exponente = -(prom+AJUSTE_A)/(10*AJUSTE_N);
	dist = pow((double)10,exponente);

	return dist;

}


void sumar_vectores(float32_t * a, float32_t * b, uint8_t size)
{
	uint8_t i;

	for(i=0;i<size;i++)
	{
		a[i]+=b[i];
	}
}

uint8_t buscar_max (float32_t * vec, uint8_t size)
{
	uint8_t i,index;
	index=0;

	for(i=0;i<size;i++)
	{
		if (vec[index]<vec[i])
			index=i;
	}

	return index;
}

double promediar (s8 * vec, uint8_t size)
{
	double prom=0.0;
	uint8_t i;

	for(i=0;i<size;i++)
	{
		prom += (double)vec[i]/size;
	}

	return prom;
}

void calc_tabla (float32_t * tabla)
{
	uint8_t i,j;
	float32_t pi = 3.14159265358979;
	float32_t expon,mod;

	// Inicializo la tabla de ajustes:
	float32_t tabla_ajuste_u[] = {1.32600000000000,1.97100000000000,1.87300000000000,1.86600000000000,2.30969030969031,4.44200000000000,4.61800000000000,4.60639360639361,4.66633366633367,4.82000000000000,5.53846153846154,4.94300000000000,6.10900000000000,7.87187187187187,8.23823823823824,9.76600000000000,12.4570000000000,13.1060000000000,14.2710000000000,17.8677354709419,20.7504990019960,22.2955911823647,24.0189620758483,25.9540000000000,28.3126873126873,31.7967967967968,32.2887112887113,33.9459459459459,36.4519038076152,36.6460000000000,34.8078078078078,33.3153692614770,29.2700000000000,30.5135135135135,35.3930000000000};
	float32_t tabla_ajuste_s[filas_tabla] = {(float32_t)0.468981816218861,(float32_t)0.167890402308138,(float32_t)0.333139583331053,(float32_t)0.340822769427394,(float32_t)1.30076746730382,(float32_t)1.28697019868072,(float32_t)1.37766976230663,(float32_t)1.22348644492658,(float32_t)1.39232016596594,(float32_t)1.79354866586240,(float32_t)1.71545015397395,(float32_t)2.21825870260247,(float32_t)3.19206959640738,(float32_t)2.95822612442085,(float32_t)2.63613309502553,(float32_t)3.03487305409211,(float32_t)3.58091803508180,(float32_t)3.43490357398321,(float32_t)4.13287304905917,(float32_t)4.50125816381780,(float32_t)5.97092729630174,(float32_t)5.50369626878694,(float32_t)6.03259873297444,(float32_t)5.16939131877307,(float32_t)6.55035333941069,(float32_t)5.15158494102146,(float32_t)5.23063690553669,(float32_t)5.61249331790856,(float32_t)4.73820039802037,(float32_t)3.37817940555204,(float32_t)3.84560482265187,(float32_t)6.44459544912412,(float32_t)13.4181648203898,(float32_t)12.7839127193673,(float32_t)3.18852908371836};

	// Calculo cada elemento de la tabla
	for(j=0;j<filas_tabla;j++)
	{
		for(i=0;i<cols_tabla;i++)
		{
			expon = (i+1 - tabla_ajuste_u[j])/tabla_ajuste_s[j];
			expon = -0.5*expon*expon;
			mod =(float32_t) sqrt(2*pi)*tabla_ajuste_s[j];
			tabla[j*cols_tabla+i] = (float32_t) (exp((double)expon)/mod);
		}

	}

}
