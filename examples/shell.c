#include <stdlib.h>
#include <stdio.h>
#include "../lib/c_computacional.h"
#include "../lib/v_initializer.h"

void shell(int v[], int n){
    int incremento = n;
    int i, j, tmp, seguir;
    
    do {
        incremento = incremento / 2;
        for(i = incremento; i<n; i++){
            tmp = v[i];
            j = i;
            seguir = 1;
            while (j - incremento >= 0 && seguir){
                if(tmp < v[j - incremento]){
                    v[j] = v[j-incremento];
                    j = j-incremento;
                } else 
                    seguir = 0;
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
}

void test(int n){
    int i;
    int v[n];
 
    aleatorio(v, n);

    for(i = 0; i<n; i++){
        printf("%d,", v[i]);
    }
    printf("\n");

    shell(v, n);
    for(i = 0; i<n; i++){
        printf("%d,", v[i]);
    }

    printf("\n");
    
}

int main(int argc, char **argv)
{
    inicializar_semilla();

	test(10);

    situacion sList[NUM_SITUACIONES] = {
    initSituation("ascendente", ascendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
    initSituation("descendente", descendente, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4)),
    initSituation("aleatorio", aleatorio, genCota(Nexp_x, 1.0), genCota(Nexp_x, 1.2), genCota(Nexp_x, 1.4))};
    
	algoritmo algs[NUM_ALGORITMOS] = {initAlgorithem("shell", shell, sList, 2000, 2, 128000, 7)};
	
	lecturaTiempos_v(algs);
	
	mostrarResultados(algs);

	return 0;
}
