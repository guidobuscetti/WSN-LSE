/*
 * rssi.c
 *
 *  Created on: 29/10/2012
 *      Author: Joaquin
 */

#include "rssi.h"

//	Pasar RSSI a distancia usando metodo probabilistico
float64_t RSSI_to_dist_1 (int8_t * RSSI_vec , uint8_t size)
{
	float32_t suma[cols_tabla];
	uint8_t i,dist,rssi_index;

	// Inicializo el vector suma
	for(i=0;i<cols_tabla;i++)
	{suma[i]=0;}

	// Inicio el loop sobre el vector de RSSI
	for(i=0;i<size;i++)
	{

		rssi_index = (uint8_t) ((int8_t)rssi_max - RSSI_vec[i]);

		// Sumo las probabilidades para ese RSSI
		if (rssi_index>=0 && rssi_index<filas_tabla)
		{
			sumar_vectores(suma,tabla+((uint32_t)rssi_index)*cols_tabla,cols_tabla);
		}
	}

	// Busco el máximo
	dist = buscar_max(suma,dist_max);
	dist++;

	return (float64_t)dist;

}

// Pasar RSSI a distancia ajustando la curva
float64_t RSSI_to_dist_2 (int8_t * RSSI_vec, uint8_t size)
{
	float64_t dist,prom,exponente;

	// Hago un promedio de todos los RSSI
	prom = promediar (RSSI_vec,size);

	// Ajusto con la curva
	exponente = -(prom+AJUSTE_A)/(10*AJUSTE_N);
	dist = pow((float64_t)10,exponente);

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

float64_t promediar (int8_t * vec, uint8_t size)
{
	float64_t prom=0.0;
	uint8_t i;

	for(i=0;i<size;i++)
	{
		prom += (float64_t)vec[i]/size;
	}

	return prom;
}

void calc_tabla (float32_t * tabla)
{
	uint8_t i,j;
	float32_t pi = 3.14159265358979;
	float32_t expon,mod;

	// Inicializo la tabla de ajustes:
	float32_t tabla_ajuste_u[] = {1,1,1,1,1,1.06700000000000,1.45500000000000,1.77600000000000,1.89300000000000,1.80900000000000,1.69100000000000,1.62100000000000,2.67767767767768,3.08700000000000,3.14014014014014,3.31868131868132,3.91000000000000,4.22700000000000,5.69469469469470,6.94405594405594,6.91800000000000,7.54200000000000,7.87587587587588,9.01803607214429,9.85900000000000,10.3020000000000,11.4430000000000,11.4335664335664,11.8968968968969,11.8578578578579,11.9280000000000,11.6840000000000,11.7210000000000,12.0640640640641,11.5674325674326,12.1868131868132,11.1770000000000,11.7840000000000,11.2720000000000,11.9220000000000,12.0139860139860,11.4830000000000,11.7310000000000,12.1710000000000,10.5310000000000,15,12.6640000000000,11.5615615615616,10.4470000000000,14.7260000000000,15,10.1660000000000,6,0,10};
	float32_t tabla_ajuste_s[filas_tabla] = {0.0100000000000000,0.0100000000000000,0.0100000000000000,0.0100000000000000,0.0100000000000000,0.250147103868051,0.498220055019085,0.417130672569152,0.309267920493940,0.393285740491160,0.462312375707959,0.643251718048831,0.958148375164232,0.748325457933238,0.817138796046543,1.00764113618919,0.956459520740322,0.828346037086656,1.78444680017286,1.63855641735862,1.82060171113580,2.22557614769506,2.21504434526977,2.76488863758309,2.80945048221391,3.10426036801562,2.72216111961820,2.62522992666019,2.72308846752807,2.56025890627297,2.21443440176488,2.51365519959730,2.38261113819182,2.46455837745662,2.24848800345884,2.65331225717322,2.66848117696037,2.73071433892320,2.12097018237281,2.89452833710333,2.83157274245326,2.43796116758547,2.73681002795757,3.07428206419162,2.54352285393870,0.0100000000000000,1.97256051744808,2.18346031836803,2.33680372553016,0.446232140396813,0.0100000000000000,2.88318517559256,0.0100000000000000,0.0100000000000000,0.0100000000000000};

	// Calculo cada elemento de la tabla
	for(j=0;j<filas_tabla;j++)
	{
		for(i=0;i<cols_tabla;i++)
		{
			expon = (i+1 - tabla_ajuste_u[j])/tabla_ajuste_s[j];
			expon = -0.5*expon*expon;
			mod =(float32_t) sqrt(2*pi)*tabla_ajuste_s[j];
			tabla[j*cols_tabla+i] = (float32_t) (exp((float64_t)expon)/mod);
		}

	}

}
