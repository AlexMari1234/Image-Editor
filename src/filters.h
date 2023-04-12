#pragma once
//minimul dintre 2 numere
int minim(int x, int y);

//maximum dintre 2 numere
int maxim(int x, int y);

//pixelul trb sa fie in intervalul [val_min, val_max]
//si in caz ca nu este il fac cel mai apropiat capat de acesta
double fclamp(double x, int val_min, int val_max);

//creez o matrice auxiliara care va fi noua matrice
//a pixelilor in urma aplicarii filtrului dat ca parametru
double **incarca_filtru(double val_filtru[3][3],
						double **mat, imagine *img);

//modifica fiecare matrice rgb conform filtrului aplicat
void selectie_filtru(double val_filtru[3][3], imagine *img);

//verifica tipul filtrului citit daca este vreunul din cei 4
//din enunt.In cazul in care se gaseste filtrul se aplica
//pentru matricea rgb conform matricei initializate a lui
//in functie
void filtre(imagine *img, char *tip_efect);

