#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "c_computacional.h"

const funcion FUNCIONES[] = {LOG, NxLogN, Nexp_x};

/*
* Funciones de Utilidad
*/
double microsegundos(){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void leerTiempo_v(algoritmo alg, situacion sit, tempos tiempos[], int *tamV){
	double ta, tb, t, ti;
	int k, n, i;
	int *v;

	typeSituationFunction ini = sit.func;
	typeAlgorithemFunction ord = alg.func;

	int inicio = alg.ini;
	int fin = alg.fin;
	int mult = alg.mult;

	i = 0;
	printf("ALGORITMO > %s\n",alg.alg_name);
	printf("\tSITUATION > %s\n",sit.sit_name);

	for (n = inicio; n <= fin; n = n * mult) {
		tamV[i]=n;
		v = malloc(sizeof(int) * n);
		ini(v, n);
		ta = microsegundos();
		ord(v, n);
		tb = microsegundos();
		t = tb - ta;

		if (t < 500) {
			ta = microsegundos();
			for (k = 0; k < 1000; k++) {
				ini(v, n);
				ord(v, n);
			}
			tb = microsegundos();
			t = tb - ta;

			ta = microsegundos();
			for (k = 0; k < 1000; k++) {
				ini(v, n);
			}
			tb = microsegundos();

			ti = tb - ta;
			t = (t - ti) / k;

			tiempos[i] = (tempos){1,0,t};
			printf("\t\t > tiempo %f \n", tiempos[i].tiempo);
		} else {
			tiempos[i] = (tempos){0,0,t};
			printf("\t\t > tiempo %f \n", tiempos[i].tiempo);
		}
		i++;
		free(v);
	}
}

/*
* API
*/
cota_t genCota(funcion func, double exp){
	cota_t cota;
	char *token1;
	char *token2;
	char aux[256];

	if(func.isComplex){
		cota.cota = func;
		cota.exp = exp;
		token1 = strtok(cota.cota.name,"$");
		token2 = strtok(NULL,"$");
		if(token2 != NULL) {
			sprintf(aux, "%s%2.1f%s", token1, cota.exp, token2);
			strcpy(cota.cota.name, aux);
		} else {
			sprintf(aux, "%s%2.1f", token1, cota.exp);
			strcpy(cota.cota.name, aux);
		}

	} else {
		cota.cota = func;
		cota.exp = 0;
	}

	return cota;
}

double execute(funcion op , int n, double exp, int derivada){

	if (!derivada) {

		switch (op.index) {
			case 0:
				return log(n);
			case 1:
				return n;
			case 2:
				return n*log(n);
			case 3:
				return pow(n,exp);
			case 4:
				return pow(n,exp)*log(n);
			default:
				return -1;
		}

	} else {

		switch (op.index) {
			case 0:
				return 1.0/n;
			case 1:
				return 0;
			case 2:
				return log(n)+(1);
			case 3:
				if(exp == 0)
					return 1;
				else
					return exp*pow(n,exp-1);
			case 4:
				if(exp == 0)
					return 1.0;
				else
					return (exp*pow(n,exp-1)*log(n))+(pow(n,exp)*1/n);
			default:
				return -1;
		}
	}
}

algoritmo initAlgorithem(char *name, typeAlgorithemFunction func, situacion sList[], int ini
		, int mult, int fin, int nTemp){
	algoritmo algoritmo;

	strcpy(algoritmo.alg_name, name);
	algoritmo.func = func;
	algoritmo.ini = ini;
	algoritmo.mult = mult;
	algoritmo.fin = fin;
	algoritmo.nTemp = nTemp;
	memcpy(algoritmo.sList, sList, NUM_SITUACIONES * sizeof(situacion));

	return algoritmo;
}

situacion initSituation(char *name, typeSituationFunction func, cota_t sobre, cota_t ajus, cota_t sub) {
	situacion sit ;
	strcpy(sit.sit_name, name);
	sit.func = func;
	sit.sobre = sobre;
	sit.ajus = ajus;
	sit.sub = sub;
	return sit;
}

void lecturaTiempos_v(algoritmo algoritmos[]){
	int i;
	int j;

	printf(" - Leyendo tiempos \n");
	printf(" ************************************ \n");

	for(i = 0; i<NUM_ALGORITMOS; i++) {
		for (j = 0; j < NUM_SITUACIONES; j++) {
			leerTiempo_v(algoritmos[i],
			             algoritmos[i].sList[j],
			             algoritmos[i].sList[j].tiempos,
			             algoritmos[i].sList[j].valN);
		}
	}
}

void mostrarResultados(algoritmo algoritmos[]){
	int j, i, k;

	int valN;
	double tiempo;

	for(i = 0; i < NUM_ALGORITMOS; i++) {
		for (j = 0;  j < NUM_SITUACIONES; j++) {

			printf("\n-------------------------------------------------------------\n");
			printf("\nOrdenación %s con inicialización %s\n\n", algoritmos[i].alg_name
					, algoritmos[i].sList[j].sit_name);

			printf("   %-10s%-15s%-15s%-15s%-15s%-7s\n", "n", "t(n)",algoritmos[i].sList[j].sobre.cota.name,
			       algoritmos[i].sList[j].ajus.cota.name,algoritmos[i].sList[j].sub.cota.name,"anomala");

			for (k = 0; k<algoritmos[i].nTemp; k++) {

				valN = algoritmos[i].sList[j].valN[k];
				tiempo = algoritmos[i].sList[j].tiempos[k].tiempo;

				if(algoritmos[i].sList[j].tiempos[k].is_under_500) {

					printf("(*)%-10d%-15.5f%-15.8f%-15.8f%-15.8f%7d\n", valN, tiempo,
					       tiempo / execute(algoritmos[i].sList[j].sobre.cota, valN, algoritmos[i].sList[j].sobre.exp,0),
					       tiempo / execute(algoritmos[i].sList[j].ajus.cota, valN, algoritmos[i].sList[j].ajus.exp,0),
					       tiempo / execute(algoritmos[i].sList[j].sub.cota, valN, algoritmos[i].sList[j].sub.exp,0),
					       algoritmos[i].sList[j].tiempos[k].is_anomalo
					);
				} else {
					printf("   %-10d%-15.5f%-15.8f%-15.8f%-15.8f%7d\n", valN, tiempo,
					       tiempo / execute(algoritmos[i].sList[j].sobre.cota, valN, algoritmos[i].sList[j].sobre.exp,0),
					       tiempo / execute(algoritmos[i].sList[j].ajus.cota, valN, algoritmos[i].sList[j].ajus.exp,0),
					       tiempo / execute(algoritmos[i].sList[j].sub.cota, valN, algoritmos[i].sList[j].sub.exp,0),
					       algoritmos[i].sList[j].tiempos[k].is_anomalo
					);
				}
			}
		}
	}
}
