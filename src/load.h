#pragma once

typedef enum {
	INCARCATA, NEINCARCATA
} incarcare;

//incarca coordonatele pozitiilor de start si final ale imaginii
void incarcare_dim(imagine *img);

//incarca o noua imagine care deschide un fisier
incarcare imag_noua(char *fisier, imagine *img);

//citeste antetul unei imagini(lucrurile comune pentru imagini ascii
//sau binare - tip imag, dimensiuni si val_max daca e cazul
void citire_comuna(char *fisier, imagine *img, fpos_t *poz, int *stare);

//citeste matricea de pixeli pentru tipul ascii
void citire_ascii(char *fisier, imagine *img, fpos_t *poz);

//citeste matricea de pixeli pentru tipul binar
void citire_binar(char *fisier, imagine *img, fpos_t *poz);

//elibereaza memoria alocata pentru o matrice
void elib_mat(double **mat, int n);

//aloc o matrice cu n linii, m coloane
//si verific daca s-a alocat cum trebuie
//initial cat si la fiecare parcurgere a unei linii
double **aloc_mat(int n, int m);

//verifica daca o matrice s-a alocat cum trebuie
double verif_aloc(double **a);

//aloc o matrice cu un nr de linii si coloane
//cunoscut in functie de tipul acesteia
//daca este rgb aloc 3 matrici(rosu, verde, albastru)
//iar daca este alb_negru aloc matricea alb_negru
//la fiecare pas verific daca alocarea a avut loc cu succes
void aloc_imag(imagine *img);

//eliberez o imagine in functie de ce tip
//este aceasta:rgb sau alb_negru
void elib_img(imagine *img);
