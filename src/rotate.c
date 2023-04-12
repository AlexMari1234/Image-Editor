#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "struct_image.h"
#include "load.h"
#include "select.h"
#include "rotate.h"

void rotire_90(double **mat, imagine *img)
{
	int x1 = img->poz_start.latime;
	int x2 = img->poz_final.latime;
	int y1 = img->poz_start.inaltime;
	int y2 = img->poz_final.inaltime;

	double **mat_noua = aloc_mat(y2 - y1, x2 - x1);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return;
	}

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat_noua[i - y1][j - x1] = mat[y2 - 1 - (j - x1)][x1 + i - y1];

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat[i][j] = mat_noua[i - y1][j - x1];

	elib_mat(mat_noua, y2 - y1);
}

void rotire_180(double **mat, imagine *img)
{
	int x1 = img->poz_start.latime;
	int x2 = img->poz_final.latime;
	int y1 = img->poz_start.inaltime;
	int y2 = img->poz_final.inaltime;

	double **mat_noua = aloc_mat(y2 - y1, x2 - x1);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return;
	}

	int s1 = y1 + y2 - 1;
	int s2 = x1 + x2 - 1;

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat_noua[i - y1][j - x1] = mat[s1 - i][s2 - j];

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat[i][j] = mat_noua[i - y1][j - x1];

	elib_mat(mat_noua, y2 - y1);
}

void rotire_270(double **mat, imagine *img)
{
	int x1 = img->poz_start.latime;
	int x2 = img->poz_final.latime;
	int y1 = img->poz_start.inaltime;
	int y2 = img->poz_final.inaltime;

	double **mat_noua = aloc_mat(y2 - y1, x2 - x1);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return;
	}

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat_noua[i - y1][j - x1] = mat[y1 + j - x1][x2 - 1 - (i - y1)];

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			mat[i][j] = mat_noua[i - y1][j - x1];

	elib_mat(mat_noua, y2 - y1);
}

void rotire_90_imag(double ***mat, imagine *img)
{
	int y = img->dim_img.inaltime;
	int x = img->dim_img.latime;

	double **mat_noua = aloc_mat(x, y);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return;
	}

	for (int i = 0; i < x; i++)
		for (int j = 0 ; j < y; j++)
			mat_noua[i][j] = (*mat)[y - 1 - j][i];

	elib_mat((*mat), y);
	(*mat) = mat_noua;
}

void rotire_180_imag(double **mat, imagine *img)
{
	int y = img->dim_img.inaltime;
	int x = img->dim_img.latime;

	double **mat_noua = aloc_mat(y, x);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return;
	}

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			mat_noua[i][j] = mat[y - 1 - i][x - j - 1];

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			mat[i][j] = mat_noua[i][j];

	elib_mat(mat_noua, y);
}

void rotire_270_imag(double ***mat, imagine *img)
{
	int y = img->dim_img.inaltime;
	int x = img->dim_img.latime;

	double **mat_noua = aloc_mat(x, y);
	if (verif_aloc(mat_noua) == 0) {
		elib_img(img);
		return;
	}

	for (int i = 0; i < x; i++)
		for (int j = 0 ; j < y; j++)
			mat_noua[i][j] = (*mat)[j][x - i - 1];

	elib_mat((*mat), y);
	(*mat) = mat_noua;
}

void rotire_imag(imagine *img, int x, int y, int grade)
{
	printf("Rotated %d\n", grade);

	//daca nr de grade e negativ il facem echivalentul
	//sau cu +360
	if (grade < 0)
		grade += 360;
	//daca unghiul e de 0 grade sau 360 nu facem nimic
	if (grade == 0 || grade == 360)
		return;

	//rotesc matricea(rgb / alb_negru) in functie de nr
	//de grade primit ca parametru
	if (img->tip_img % 3 != 0) {
		if (grade == 90)
			rotire_90_imag(&img->pixeli.alb_negru, img);
		else if (grade == 180)
			rotire_180_imag(img->pixeli.alb_negru, img);
		else if (grade == 270)
			rotire_270_imag(&img->pixeli.alb_negru, img);
	} else {
		if (grade == 90) {
			rotire_90_imag(&img->pixeli.rosu, img);
			rotire_90_imag(&img->pixeli.verde, img);
			rotire_90_imag(&img->pixeli.albastru, img);
		} else if (grade == 180) {
			rotire_180_imag(img->pixeli.rosu, img);
			rotire_180_imag(img->pixeli.verde, img);
			rotire_180_imag(img->pixeli.albastru, img);
		} else if (grade == 270) {
			rotire_270_imag(&img->pixeli.rosu, img);
			rotire_270_imag(&img->pixeli.verde, img);
			rotire_270_imag(&img->pixeli.albastru, img);
		}
	}

	//daca rotesc la 90 sau 270 interschimbam latimea si inaltimea
	if (grade != 180) {
		img->dim_img.latime = y;
		img->dim_img.inaltime = x;
		img->poz_final.latime = y;
		img->poz_final.inaltime = x;
	}
}

void rotire_patrat(imagine *img, int grade)
{
	//daca submatricea selectata este dreptunghi atunci se termina
	//programul, caci noua ne trebuie sa fie patrat
	if (img_frm(img) == DREPTUNGHI) {
		printf("Selection must be square\n");
	} else {
		printf("Rotated %d\n", grade);
		//daca nr de grade e negativ il facem echivalentul
		//sau cu +360
		if (grade < 0)
			grade += 360;
		//daca unghiul e de 0 grade sau 360 nu facem nimic
		if (grade == 0 || grade == 360)
			return;
		//rotesc matricea(rgb / alb_negru) in functie de nr
		//de grade primit ca parametru
		if (img->tip_img % 3 != 0) {
			if (grade == 90)
				rotire_90(img->pixeli.alb_negru, img);
			else if (grade == 180)
				rotire_180(img->pixeli.alb_negru, img);
			else if (grade == 270)
				rotire_270(img->pixeli.alb_negru, img);
	} else {
		if (grade == 90) {
			rotire_90(img->pixeli.rosu, img);
			rotire_90(img->pixeli.verde, img);
			rotire_90(img->pixeli.albastru, img);
		} else if (grade == 180) {
			rotire_180(img->pixeli.rosu, img);
			rotire_180(img->pixeli.verde, img);
			rotire_180(img->pixeli.albastru, img);
		} else if (grade == 270) {
			rotire_270(img->pixeli.rosu, img);
			rotire_270(img->pixeli.verde, img);
			rotire_270(img->pixeli.albastru, img);
		}
	}
	}
}

void rotatie(imagine *img, char *unghi)
{
	int x1 = img->poz_start.latime;
	int x2 = img->poz_final.latime;
	int y1 = img->poz_start.inaltime;
	int y2 = img->poz_final.inaltime;
	int y = img->dim_img.inaltime;
	int x = img->dim_img.latime;

	int grade = atoi(unghi);
	if (grade % 90 != 0 || (grade % 90 == 0 && (grade < -360 || grade > 360))) {
		printf("Unsupported rotation angle\n");
		return;
	}

	if (x1 == 0 && y1 == 0 && x2 == x && y2 == y)
		rotire_imag(img, x, y, grade);
	else
		rotire_patrat(img, grade);
}
