#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "struct_image.h"
#include "save.h"

void salveaza_binar(imagine img, char *fisier)
{
	//in cazul in care nu se deschide fisierul nu facem nimic
	FILE *out = fopen(fisier, "wb");
	if (!out) {
		fprintf(stderr, "eroare\n");
		return;
	}

	//daca imaginea este in format ascii trb sa o transformam
	//in binar marind tipul acesteia cu 3
	if (img.tip_img <= 3)
		img.tip_img += 3;

	//afisez tipul imaginii, latimea si inaltimea
	fprintf(out, "P%d\n", img.tip_img);
	fprintf(out, "%d %d\n", img.dim_img.latime, img.dim_img.inaltime);

	//in cazul in care imaginea este de tip P5 sau P6 afisez val_max
	if (img.tip_img >= 5)
		fprintf(out, "%d\n", img.val_max);

	int x = img.dim_img.latime;
	int y = img.dim_img.inaltime;

	int aux;//rotunjeste la fiecare pas pixelul aferent si il afisam
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			if (img.tip_img <= 5) {
				aux = (int)round(img.pixeli.alb_negru[i][j]);
				fwrite(&aux, 1, 1, out);
			} else {
				aux = (int)round(img.pixeli.rosu[i][j]);
				fwrite(&aux, 1, 1, out);

				aux = (int)round(img.pixeli.verde[i][j]);
				fwrite(&aux, 1, 1, out);

				aux = (int)round(img.pixeli.albastru[i][j]);
				fwrite(&aux, 1, 1, out);
			}
		}

	fclose(out);
}

void salveaza_ascii(imagine img, char *fisier)
{
	//in cazul in care nu se deschide fisierul nu facem nimic
	FILE *out = fopen(fisier, "w");
	if (!out) {
		fprintf(stderr, "eroare\n");
		return;
	}

	//daca imaginea este in format binar trb sa o transformam
	//in ascii scazand tipul acesteia cu 3
	if (img.tip_img >= 4)
		img.tip_img -= 3;

	//afisez tipul imaginii, latimea si inaltimea
	fprintf(out, "P%d\n", img.tip_img);
	fprintf(out, "%d %d\n", img.dim_img.latime, img.dim_img.inaltime);

	//in cazul in care imaginea este de tip P2 sau P3 afisez val_max
	if (img.tip_img >= 2)
		fprintf(out, "%d\n", img.val_max);

	int x = img.dim_img.latime;
	int y = img.dim_img.inaltime;

	//rotunjesc la fiecare pas pixelul catre cel mai aproape intreg si il afisez
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (img.tip_img <= 2) {
				img.pixeli.alb_negru[i][j] = round(img.pixeli.alb_negru[i][j]);
				fprintf(out, "%.0f ", img.pixeli.alb_negru[i][j]);
			} else {
				img.pixeli.rosu[i][j] = round(img.pixeli.rosu[i][j]);
				fprintf(out, "%.0f ", img.pixeli.rosu[i][j]);

				img.pixeli.verde[i][j] = round(img.pixeli.verde[i][j]);
				fprintf(out, "%.0f ", img.pixeli.verde[i][j]);

				img.pixeli.albastru[i][j] = round(img.pixeli.albastru[i][j]);
				fprintf(out, "%.0f ", img.pixeli.albastru[i][j]);
			}
		}

		fprintf(out, "\n");
	}

	fclose(out);
}

void salveaza(imagine img, char **parametri)
{
	//verific daca imaginea trb salvata in format ascii sau binar
	if (strcmp(parametri[1], "ascii") == 0)
		salveaza_ascii(img, parametri[0]);
	else
		salveaza_binar(img, parametri[0]);

	//afisez mesajul selectiei parametrului citit
	printf("Saved %s\n", parametri[0]);
}

