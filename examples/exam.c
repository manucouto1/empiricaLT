#include <stdlib.h>
#include <stdio.h>
#include "../lib/c_computacional.h"
#include "../lib/v_initializer.h"

void ordenar (int v[], int n){
	int p = (n / 2);
	int x,i,j = 0;
			
	while (p >= 1){
		for(i = (n - p); i>=1 ; i--) {
			x = v[i-1];
			j = i + p;
			while ( j <=n && v[j-1] < x) {			
				v[j-p-1] = v[j-1];
				j = j + p;
			}
			v[j-p-1] = x;
		}
		p = p/2;
	}
}

int main(int argc, char **argv)
{
	inicializar_semilla();

	//test();

	situacion sList[NUM_SITUACIONES] = {
		initSituation("ascendente", ascendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.1), genCota(Nexp_x, 1.2)),
		initSituation("descendente", descendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
		initSituation("aleatorio", aleatorio, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4))};
		
	algoritmo algs[NUM_ALGORITMOS] = {initAlgorithem("ordenar", ordenar, sList, 2000, 2, 32000, 5)};
	
	lecturaTiempos_v(algs);
	
	mostrarResultados(algs);
	
	return 0;
}
