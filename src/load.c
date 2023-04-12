#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include<string.h>

#include "struct_image.h"
#include "load.h"

void incarcare_dim(imagine *img)
{
	img->poz_start.latime = 0;
	img->poz_start.inaltime = 0;
	img->poz_final.latime = img->dim_img.latime;
	img->poz_final.inaltime = img->dim_img.inaltime;
}

incarcare imag_noua(char *fisier, imagine *img)
{
	int stare = 1;//presupun ca fisierul exista
	fpos_t  poz  = {};

	//citesc partea comuna(tip_imag, latime, inaltime, val_max(daca e cazul))
	citire_comuna(fisier, img, &poz, &stare);

	//daca nu exista fisierul atunci imaginea este neincarcata
	if (stare == 0)
		return NEINCARCATA;

	//daca tipul imaginii este P(1..3) atunci citesc in format ascii
	//iar in caz contrat citesc in format binar
	if (img->tip_img <= 3)
		citire_ascii(fisier, img, &poz);
	else
		citire_binar(fisier, img, &poz);

	//imaginea este incarcata si fisierul s-a incarcat cu succes
	fprintf(stdout, "Loaded %s\n", fisier);
	return INCARCATA;
}

void citire_comuna(char *fisier, imagine *img, fpos_t *poz, int *stare)
{
	//in cazul in care fisierul nu exista atunci starea devine 0
	//caci am presupus mai sus ca este 1 cand fisierul exista
	//si afisez mesajul corespunzator erorii inexistentei fisierului
	FILE *in = fopen(fisier, "r");
	if (!in) {
		fprintf(stdout, "Failed to load %s\n", fisier);
		*stare = 0;
		return;
	}

	//n m reprezinta nr de linii si col, ok ne zice cand se termina
	//citirea comuna
	int n = 0, m = 0, ok = 1;
	char *sir = malloc(NR_MAX_CAR_CITITE);
	while (ok == 1) {
		fscanf(in, "%s", sir);
		if (sir[0] != '\0') {
			if (sir[0] == 'P') {
				//daca primul caracter este P atunci al doilea reprezinta
				//tipul imaginii
				img->tip_img = sir[1] - '0';
				if (img->tip_img % 3 != 0)
					img->stare = ALB_NEGRU;
				else
					img->stare = CULOARE;

			} else if (sir[0] == '#') { // daca avem # atunci citim toata linia
				fgets(sir, NR_MAX_CAR_CITITE, in);

			} else if (n == 0 && m == 0) {//daca nu s-au initializat lin si col
				n = atoi(sir);
				img->dim_img.latime = n;

				fscanf(in, "%s", sir);
				m = atoi(sir);
				img->dim_img.inaltime = m;

				aloc_imag(img);
				incarcare_dim(img);
				if (img->tip_img == 1 || img->tip_img == 4)
					ok = 0;
			//daca tipul imag nu e p1 sau p4 mai am de citit val_max
			} else if (img->tip_img != 1 && img->tip_img != 4 && ok == 1) {
				img->val_max = atoi(sir);
				ok = 0;
			}
		}
	}

	fgetpos(in, poz);
	fclose(in);
	free(sir);
}

void citire_ascii(char *fisier, imagine *img, fpos_t *poz)
{
	//in cazul in care nu se deschide fisierul nu facem nimic
	FILE *in = fopen(fisier, "r");
	if (!in) {
		fprintf(stderr, "eroare\n");
		return;
	}

	//ma duc in fisier la pozitia la care am ramas dupa citirea comuna
	fsetpos(in, poz);
	unsigned char aux;//citesc un caracter de tip unsigned char si la fiecare
	//pas il pun in matricea aferenta de pixeli in format double

	for (int i = 0; i < img->dim_img.inaltime; i++)
		for (int j = 0; j < img->dim_img.latime; j++) {
			if (img->tip_img % 3 != 0) {
				fscanf(in, "%hhu", &aux);
				img->pixeli.alb_negru[i][j] = (double)aux;
			} else {
				fscanf(in, "%hhu", &aux);
				img->pixeli.rosu[i][j] = (double)aux;

				fscanf(in, "%hhu", &aux);
				img->pixeli.verde[i][j] = (double)aux;

				fscanf(in, "%hhu", &aux);
				img->pixeli.albastru[i][j] = (double)aux;
			}
		}

	fclose(in);
}

void citire_binar(char *fisier, imagine *img, fpos_t *poz)
{
	//in cazul in care nu se deschide fisierul nu facem nimic
	FILE *in = fopen(fisier, "rb");
	if (!in) {
		fprintf(stderr, "eroare\n");
		return;
	}

	//ma duc in fisier la pozitia la care am ramas dupa citirea comuna
	fsetpos(in, poz);
	fseek(in, 1, SEEK_CUR);

	uint_fast8_t x;//citesc un caracter de tip unsigned char si la fiecare
	//pas il pun in matricea aferenta de pixeli in format double
	for (int i = 0; i < img->dim_img.inaltime; i++)
		for (int j = 0; j < img->dim_img.latime; j++) {
			if (img->tip_img % 3 != 0) {
				fread(&x, 1, 1, in);
				img->pixeli.alb_negru[i][j] = (double)x;
			} else {
				fread(&x, 1, 1, in);
				img->pixeli.rosu[i][j] = (double)x;

				fread(&x, 1, 1, in);
				img->pixeli.verde[i][j] = (double)x;

				fread(&x, 1, 1, in);
				img->pixeli.albastru[i][j] = (double)x;
			}
		}

	fclose(in);
}

void elib_mat(double **mat, int n)
{
	for (int i = 0; i < n; i++)
		free(mat[i]);

	free(mat);
}

double **aloc_mat(int n, int m)
{
	double **a = malloc(n * sizeof(double *));
	if (verif_aloc(a) == 0) {
		fprintf(stderr, "Incarcare nereusita\n");
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		a[i] = malloc(m * sizeof(double));
		if (!a[i]) {
			fprintf(stderr, "incarcare nereusita\n");
			elib_mat(a, i);
			return NULL;
		}
	}
	return a;
}

//verific daca s-a alocat corect o matrice
double verif_aloc(double **a)
{
	if (!a) {
		fprintf(stderr, "eroare\n");
		return 0;
	}

	return 1;
}

void aloc_imag(imagine *img)
{
	int x = img->dim_img.latime;
	int y = img->dim_img.inaltime;
	if (img->tip_img % 3 != 0) {
		img->stare = ALB_NEGRU;
		img->pixeli.alb_negru = aloc_mat(y, x);
		if (verif_aloc(img->pixeli.alb_negru) == 0) {
			elib_img(img);
			return;
		}
	} else {
		img->stare = CULOARE;
		img->pixeli.rosu = aloc_mat(y, x);
		if (verif_aloc(img->pixeli.rosu) == 0) {
			elib_img(img);
			return;
		}

		img->pixeli.verde = aloc_mat(y, x);
		if (verif_aloc(img->pixeli.verde) == 0) {
			elib_img(img);
			return;
		}

		img->pixeli.albastru = aloc_mat(y, x);
		if (verif_aloc(img->pixeli.albastru) == 0) {
			elib_img(img);
			return;
		}
	}
}

void elib_img(imagine *img)
{
	stare_imag stare_curr = img->stare;
	int nr_lin = img->dim_img.inaltime;

	if (stare_curr == ALB_NEGRU) {
		elib_mat(img->pixeli.alb_negru, nr_lin);
	} else if (stare_curr == CULOARE) {
		elib_mat(img->pixeli.rosu, nr_lin);
		elib_mat(img->pixeli.verde, nr_lin);
		elib_mat(img->pixeli.albastru, nr_lin);
	}
}

