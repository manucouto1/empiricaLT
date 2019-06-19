#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "v_initializer.h"

void inicializar_semilla() {
	srand(time(NULL));
}

void aleatorio(int *v, int n) {/* se generan números pseudoaleatorio_t entre -n y +n */
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}
void ascendente(int *v, int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = i;
}
void descendente(int *v, int n){
	int i;

	for (i = 0; i < n; i++) {
		v[i] = n - i - 1;
	}
}