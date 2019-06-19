#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/c_computacional.h"
#include "../lib/v_initializer.h"

#define MAX_SIZE 128000

typedef struct {
    int tam;
    int *vector;
} monticulo_t;

void intercambiar(monticulo_t *m, int i, int j){
    int aux;
    aux = m->vector[i];
    m->vector[i] = m->vector[j];
    m->vector[j] = aux;
}

void hundir(monticulo_t *m, int i){
    int j, hIzq, hDer;

    do {
        hIzq = 2*i+1;
        hDer = 2*(i+1);
        j = i;

        i = (hDer<m->tam && m->vector[hDer]>m->vector[i])? hDer: i;
        i = (hIzq<m->tam && m->vector[hIzq]>m->vector[i])? hIzq: i;

        intercambiar(m, j, i);
        
    } while(j != i);
}

int eliminarMax(monticulo_t *m){
    int x;
    x = m->vector[0];
    m->vector[0] = m->vector[m->tam - 1];
    m->tam = m->tam - 1;

    if(m->tam > 0) {
        hundir(m, 0);
    }
    
    return x;
}

void crearMonticulo(int v[], int n, monticulo_t *m){
    int i;
    m->tam = n;
    
    memcpy(m->vector, v, sizeof(int)*n);

    for(i = m->tam/2; i>=0; i--){
        hundir(m,i);
    }
}

void monticulo(int v[], int n){
    int i;
    monticulo_t *m;

    m = malloc(sizeof(monticulo_t));
    m->vector = malloc(sizeof(int)*n);

    crearMonticulo(v, n, m);
    
    for(i=0; i<n; i++){
        v[n-i-1] = eliminarMax(m);   
    }
    
    free(m->vector);
    free(m);
}

void test_monticulo(int n){
    int i;
    int v[n];
 
    aleatorio(v, n);

    for(i = 0; i<n; i++){
        printf("%d,", v[i]);
    }
    printf("\n");

    monticulo(v, n);
    
    for(i = 0; i<n; i++){
        printf("%d,", v[i]);
    }
 
    printf("\n");
}

int main(int argc, char **argv)
{
    inicializar_semilla();

	test_monticulo(10);
    
    
    situacion sList[NUM_SITUACIONES] = {
    initSituation("ascendente", ascendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
    initSituation("descendente", descendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
    initSituation("aleatorio", aleatorio, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4))};
    
	algoritmo algs[NUM_ALGORITMOS] = {initAlgorithem("monticulo", monticulo, sList, 500, 2, 30000, 6)};
	
	lecturaTiempos_v(algs); 
	
	mostrarResultados(algs);
  
	return 0;
}