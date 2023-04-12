#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "struct_image.h"
#include "load.h"
#include "select.h"
#include "crop.h"

//verific daca este selectata toata imaginea

int verif_img_intreaga(int x1, int y1, int x2,
					   int y2, int x, int y)
{
	if (x1 + y1 == 0 && x2 + y2 == x + y)
		return 1;

	return 0;
}

//inlocuieste matricea veche cu cea selectata

double **schimba_mat(double ***mat, int x1, int y1,
					 int x2, int y2, int y)
{
	double **mat_noua = aloc_mat(y2 - y1, x2 - x1);
	if (verif_aloc(mat_noua) == 0)
		return NULL;

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat_noua[i - y1][j - x1] = (*mat)[i][j];

	elib_mat((*mat), y);
	return mat_noua;
}

void select_crop(imagine *img)
{
	int x1 = img->poz_start.latime;
	int x2 = img->poz_final.latime;
	int y1 = img->poz_start.inaltime;
	int y2 = img->poz_final.inaltime;
	int x = img->dim_img.latime;
	int y = img->dim_img.inaltime;

	//daca se selecteaza toata imaginea nu modific nimic
	if (verif_img_intreaga(x1, y1, x2, y2, x, y) == 1) {
		printf("Image cropped\n");
		return;
	}

	//daca imaginea este alb_negru schimb pixelii din matricea alb_negru
	if (img->stare == ALB_NEGRU) {
		img->pixeli.alb_negru = schimba_mat(&img->pixeli.alb_negru, x1, y1,
											x2, y2, y);
		if (verif_aloc(img->pixeli.alb_negru) == 0) {
			elib_img(img);
			return;
		}
	} else {
		//imaginea este rgb si schimb pixelii matricilor rosu, verde, albastru
		img->pixeli.rosu = schimba_mat(&img->pixeli.rosu, x1, y1, x2, y2, y);
		if (verif_aloc(img->pixeli.rosu) == 0) {
			elib_img(img);
			return;
		}

		img->pixeli.verde = schimba_mat(&img->pixeli.verde, x1, y1, x2, y2, y);
		if (verif_aloc(img->pixeli.verde) == 0) {
			elib_img(img);
			return;
		}

		img->pixeli.albastru = schimba_mat(&img->pixeli.albastru, x1, y1,
										   x2, y2, y);
		if (verif_aloc(img->pixeli.albastru) == 0) {
			elib_img(img);
			return;
		}
	}

	x = x2 - x1;
	y = y2 - y1;

	//actualizez dimensiunile imaginii noi ca fiind diferenta dintre coordonate
	img->dim_img.latime = x;
	img->dim_img.inaltime = y;

	//actualizez coordonatele poz de start si final ale imaginii
	reinit_select_imag(img);
	printf("Image cropped\n");
}
