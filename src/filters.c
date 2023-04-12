#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#include "struct_image.h"
#include "load.h"
#include "filters.h"

int minim(int x, int y)
{
	if (x < y)
		return x;
	return y;
}

int maxim(int x, int y)
{
	if (x > y)
		return x;
	return y;
}

double fclamp(double x, int val_min, int val_max)
{
	if (x < val_min)
		return val_min;

	if (x > val_max)
		return val_max;

	return x;
}

double  **incarca_filtru(double val_filtru[3][3], double **mat,
						 imagine *img)
{
	double suma_filtre;
	int x1 = img->poz_start.latime;
	int y1 = img->poz_start.inaltime;
	int x2 = img->poz_final.latime;
	int y2 = img->poz_final.inaltime;
	int x = img->dim_img.latime;
	int y = img->dim_img.inaltime;

	//verific ca niciuna dintre coordonate sa nu fie margine
	//pentru ca pixelii de pe margine nu se modifica
	x1 = maxim(x1, 1);
	y1 = maxim(y1, 1);
	x2 = minim(x2, x - 1);
	y2 = minim(y2, y - 1);

	//aloc o matrice noua in care retin valorile
	//corespunzatoare sumei inmultirilor
	double **mat_noua = aloc_mat(y2 - y1, x2 - x1);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return NULL;
	}

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			suma_filtre = 0; // initializez suma cu 0
			for (int k = 0; k < 3; k++)
				for (int p = 0; p < 3; p++)
					suma_filtre += (double)val_filtru[k][p]
								* mat[i + k - 1][j + p - 1];
			//pun in matrice suma produselor calculata
			mat_noua[i - y1][j - x1] = fclamp(suma_filtre, 0, img->val_max);
		}
	//actualizez matricea selectata cu valorile noi dupa operatiile filtrelor
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat[i][j] = mat_noua[i - y1][j - x1];

	//eliberez matricea noua din memorie si returnez matricea modificata
	elib_mat(mat_noua, y2 - y1);
	return mat;
}

void selectie_filtru(double val_filtru[3][3], imagine *img)
{
	//modific fiecare tip de matrice rgb conform valorilor
	//matricei de pixeli a parametrului dat
	img->pixeli.rosu = incarca_filtru(val_filtru, img->pixeli.rosu, img);
	img->pixeli.verde = incarca_filtru(val_filtru, img->pixeli.verde, img);
	img->pixeli.albastru = incarca_filtru(val_filtru,
										  img->pixeli.albastru, img);
}

void filtre(imagine *img, char *tip_efect)
{
	//creez 4 matrici cu valorile corespunzatoare din enunt
	double edge[3][3] = {{-1.0, -1.0, -1.0},
						 {-1,  8.0, -1},
						 {-1, -1, -1}};

	double sharpen[3][3] = {{0.0, -1.0,  0.0},
							{-1.0, 5.0, -1.0},
							{0.0, -1.0,  0.0}};

	double blur[3][3] = {{1.0 / 9, 1.0 / 9, 1.0 / 9},
						 {1.0 / 9, 1.0 / 9, 1.0 / 9},
						 {1.0 / 9, 1.0 / 9, 1.0 / 9}};

	double gaussian_blur[3][3] = {{1.0 / 16, 2.0 / 16, 1.0 / 16},
								  {2.0 / 16, 4.0 / 16, 2.0 / 16},
								  {1.0 / 16, 2.0 / 16, 1.0 / 16}};
	//daca nu este niciun parametru dupa apply comanda e invalida
	if (!tip_efect) {
		printf("Invalid command\n");
		return;
	}

	//daca matricea este alb_negru afisez mesajul corespunzator
	if (img->tip_img % 3 != 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	int ok = 1; // presupun ca parametrul este unul din cei 4
	//verific ce parametru am si schimb matricea
	//conform matricei valorilor parametrului
	if (strcmp(tip_efect, "EDGE") == 0) {
		selectie_filtru(edge, img);
	} else if (strcmp(tip_efect, "SHARPEN") == 0) {
	    selectie_filtru(sharpen, img);
	} else if (strcmp(tip_efect, "BLUR") == 0) {
		selectie_filtru(blur, img);
	} else if (strcmp(tip_efect, "GAUSSIAN_BLUR") == 0) {
		selectie_filtru(gaussian_blur, img);
	} else {
		//daca nu am niciun parametru din cei 4
		//afisez mesajul corespunzator
		ok = 0;
		printf("APPLY parameter invalid\n");
	}

	//verific daca matricile noi alocate in cadrul functiilor
	//s-au alocat cum trebuie(malloc nu a dat gres)
	if (verif_aloc(img->pixeli.rosu) == 0)
		elib_img(img);

	if (verif_aloc(img->pixeli.rosu) == 0)
		elib_img(img);

	if (verif_aloc(img->pixeli.rosu) == 0)
		elib_img(img);

	if (ok == 1)
		printf("APPLY %s done\n", tip_efect);
}

