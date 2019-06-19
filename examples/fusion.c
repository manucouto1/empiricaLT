#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/c_computacional.h"
#include "../lib/v_initializer.h"

#define UMBRAL 0

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

void fusion(int *v, int Izda, int Dcha, int Ctro){
    int i, j, k;
    int aux[Dcha - Izda + 1];

    i = Izda; j = Ctro + 1; k = Izda;

    while (i <= Ctro && j <= Dcha) aux[k++] = ((v)[i] <= (v)[j]) ? (v)[i++] : (v)[j++];
        
    while (i <= Ctro) aux[k++] = (v)[i++];
        
    while (j <= Dcha) aux[k++] = (v)[j++];
        
    for(k = Izda; k<=Dcha; k++) (v)[k] = aux[k];
        
}

void fusion_rec(int *v, int Izda, int Dcha){
    int Ctro;
    if(Izda + UMBRAL < Dcha){
        Ctro = (Izda + Dcha) / 2;
        fusion_rec(v, Izda, Ctro);
        fusion_rec(v, Ctro + 1, Dcha);
        fusion(v, Izda, Dcha, Ctro);
    } 
}

void ord_fusion(int *v, int n){
    fusion_rec(v, 0, n - 1);    
}

void test(int n){
    int i;
    int *v= malloc(sizeof(int)*n);
 
    aleatorio(v, n);

    for(i = 0; i<n; i++){
        printf("%d, ", v[i]);
    }
    printf("\n");

    ord_fusion(v, n);
    
    for(i = 0; i<n; i++){
        printf("%d, ", v[i]);
    }
 
    printf("\n");

    free(v);
}
 
int main(int argc, char **argv)
{
    inicializar_semilla();

	test(10);
   
    situacion sList[NUM_SITUACIONES] = {
    initSituation("ascendente", ascendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
    initSituation("descendente", descendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
    initSituation("aleatorio", aleatorio, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4))};
    
	algoritmo algs[NUM_ALGORITMOS] = {initAlgorithem("fusion", ord_fusion, sList, 500, 2, 30000, 6)};
	
	lecturaTiempos_v(algs); 
	
	mostrarResultados(algs);
     /* */
	return 0;
}