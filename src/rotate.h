#pragma once

//rotesc cu 90/180/270 de grade o submatrice
//patratica dintr-o singura parcurgere
//folosind o matrice auxiliara
void rotire_90(double **mat, imagine * img);
void rotire_180(double **mat, imagine *img);
void rotire_270(double **mat, imagine *img);

//rotesc cu 90/180/270 toata imaginea prin o matrice auxiliara
void rotire_90_imag(double ***mat, imagine *img);
void rotire_180_imag(double **mat, imagine *img);
void rotire_270_imag(double ***mat, imagine *img);

//functia care roteste imaginea intreaga
void rotire_imag(imagine *img, int x, int y, int grade);

//functia care roteste o submatrice patratica
void rotire_patrat(imagine *img, int grade);

//functia de verifica ce tip de rotire trebuie sa faca
//ori pe toata imaginea ori pe o submatrice
void rotatie(imagine *img, char *unghi);
