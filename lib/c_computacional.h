#ifndef __C_COMPUT_H__
#define __C_COMPUT_H__

typedef void (*typeSituationFunction)(int *v, int nargs);
typedef void (*typeAlgorithemFunction)(int *v, int nargs);

#define NUM_SITUACIONES 3
#define NUM_ALGORITMOS 1

typedef struct {
	char name[256];
	int isComplex;
	int index;
} funcion;

#define LOG (funcion) {"log(n)",0,0}
#define N_x (funcion) {"n",0,1}
#define NxLogN (funcion) {"n*log(n)",0,2}
#define Nexp_x (funcion) {"n^$",1,3}
#define Nexp_x_LOG (funcion) {"n^$*log(n)",1,4}

typedef  struct {
	funcion cota;
	double exp;
}cota_t;

typedef struct {
	int is_under_500;
	int is_anomalo;
	double tiempo;
} tempos;

typedef struct {
	cota_t sobre;
	cota_t ajus;
	cota_t sub;
	typeSituationFunction func;
	tempos tiempos[256];
	int valN[256];
	char sit_name[256];

} situacion;

typedef struct {
	int ini;
	int fin;
	int mult;
	int nTemp;
	typeAlgorithemFunction func;
	char alg_name[256];
	situacion sList[NUM_SITUACIONES];

} algoritmo;

cota_t genCota(funcion func, double exp);
double execute(funcion op , int n, double exp, int derivada);

situacion initSituation(char *name, typeSituationFunction func, cota_t sobre, cota_t ajus, cota_t sub);
algoritmo initAlgorithem(char *name, typeAlgorithemFunction func, situacion sList[], int ini
		, int mult, int fin, int nTemp);

void lecturaTiempos_v(algoritmo algoritmos[]);
void mostrarResultados(algoritmo algoritmos[]);

#endif