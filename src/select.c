#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "struct_image.h"
#include "select.h"

int_fast8_t verif_select(char **parametri)
{
	int_fast8_t ok = 1;
	for (int_fast8_t i = 0; i < 4 && ok == 1; i++) {
		for (int_fast8_t j = 0; parametri[i][j] != '\0' && ok == 1; j++)
			if (!((parametri[i][j] >= '0' && parametri[i][j] <= '9') ||
				  parametri[i][j] == '-'))
				ok = 0;
	}
	return ok;
}

void swap_coord(int_fast32_t *a, int_fast32_t *b)
{
	int_fast32_t aux = *a;
	*a = *b;
	*b = aux;
}

int_fast32_t verif_param(int_fast32_t x1, int_fast32_t y1, int_fast32_t x2,
						 int_fast32_t y2, imagine *img)
{
	int latime = img->dim_img.latime;
	int inaltime = img->dim_img.inaltime;

	if (!(x1 >= 0 && x1 <= latime))
		return 0;

	if (!(x2 >= 0 && x2 <= latime))
		return 0;

	if (!(y1 >= 0 && y1 <= inaltime))
		return 0;

	if (!(y2 >= 0 && y2 <= inaltime))
		return 0;

	if (x1 == x2)
		return 0;

	if (y1 == y2)
		return 0;

	return 1;
}

forma select_param(imagine *img, char **param)
{
	//in cazul in care parametri nu sunt valizi
	//se afiseaza mesajul corespunzator
	if (verif_select(param) == 0) {
		printf("Invalid command\n");
		return INVALID;
	}
	//convertesc sirurile date ca parametri in int-uri
	int ok = 1;
	int_fast32_t x1 = atoi(param[0]);
	int_fast32_t y1 = atoi(param[1]);
	int_fast32_t x2 = atoi(param[2]);
	int_fast32_t y2 = atoi(param[3]);

	//verific daca coordonatele selectate fac parte din
	//interiorul imaginii intregi
	if (verif_param(x1, y1, x2, y2, img) == 1) {
		//daca x1 > x2 le interschimb
		if (x1 > x2)
			swap_coord(&x1, &x2);
		//daca y1 > y2 le interschimb
		if (y1 > y2)
			swap_coord(&y1, &y2);

		//afisez mesajul corespunzator si actualizez
		//coordonatele cele noi ale pozitiilor de statrt si final
		printf("Selected %ld %ld %ld %ld\n", x1, y1, x2, y2);
		img->poz_start.latime = x1;
		img->poz_start.inaltime = y1;
		img->poz_final.latime = x2;
		img->poz_final.inaltime = y2;
	} else {
		//coordonatele nu sunt ok si afisez mesajul aferent
		printf("Invalid set of coordinates\n");
		ok = 0;
	}

	//returnez forma imaginii selectate
	if (ok == 0)
		return INVALID;
	else
		return img_frm(img);
}

void reinit_select_imag(imagine *img)
{
	img->poz_start.latime = 0;
	img->poz_final.latime = img->dim_img.latime;
	img->poz_start.inaltime = 0;
	img->poz_final.inaltime = img->dim_img.inaltime;
}

forma img_frm(imagine *img)
{
	int latime = img->poz_final.latime - img->poz_start.latime;
	int inaltime = img->poz_final.inaltime - img->poz_start.inaltime;

	if (latime != inaltime)
		return DREPTUNGHI;
	else
		return PATRAT;
}
