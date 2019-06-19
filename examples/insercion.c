#include <stdlib.h>
#include <stdio.h>
#include "../lib/c_computacional.h"
#include "../lib/v_initializer.h"

void insercion (int v[], int n){
    int i;
    int j;
    int aux;

    for(i=1; i<n; i++){
        aux = v[i];
        j = i - 1;

        while(j>=0 && v[j]>aux){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = aux;
    }
}

void test(int n){
    int i;
    int v[n];
 
    aleatorio(v, n);

    for(i = 0; i<n; i++){
        printf("%d,", v[i]);
    }
    printf("\n");

    insercion(v, n);
    for(i = 0; i<n; i++){
        printf("%d,", v[i]);
    }

    printf("\n");
    
}



int main(int argc, char **argv)
{
    inicializar_semilla();

	test(100);
	
	situacion sList[NUM_SITUACIONES] = {
		initSituation("ascendente", ascendente, genCota(Nexp_x, 0.8), genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2)),
		initSituation("descendente", descendente, genCota(Nexp_x, 1.8), genCota(Nexp_x, 2.0), genCota(Nexp_x, 2.2)),
		initSituation("aleatorio", aleatorio, genCota(Nexp_x, 1.8), genCota(Nexp_x, 2.0), genCota(Nexp_x, 2.2))};
		
	algoritmo algs[NUM_ALGORITMOS] = {initAlgorithem("insercion", insercion, sList, 2000, 2, 64000, 6)};
	
	lecturaTiempos_v(algs);
	
	mostrarResultados(algs);
	 
	return 0;
}
 