#pragma once

#define NR_MAX_PAR_COM 4
#define NR_MAX_CAR_COM 5
#define NR_MAX_CAR_CITITE 100000

//tipurile de comenzi
typedef enum {
	LOAD, SELECT, SELECT_ALL,
	ROTATE, CROP, APPLY,
	SAVE, EXIT, NO_COMMAND
} comenzi;

//tipurile imaginii
typedef enum {
	P1, P2, P3, P4, P5, P6
} tip;

//tipurile matricilor de pixeli
typedef struct {
	double **alb_negru;
	double **rosu;
	double **verde;
	double **albastru;
} matrici;

//dimensiunile/coordonate alese
typedef struct {
	int latime, inaltime;
} marime;

//starea imaginii citita
typedef enum {
	NEALOCATA, ALB_NEGRU, CULOARE
} stare_imag;

//forma imaginii selectata
typedef enum {
	INVALID, PATRAT, DREPTUNGHI
} forma;

//datele necesare pentru o imagine
typedef struct {
	forma img_forma;
	stare_imag stare;
	tip tip_img;
	marime dim_img;
	marime poz_start;
	marime poz_final;
	int val_max;
	matrici pixeli;
} imagine;
