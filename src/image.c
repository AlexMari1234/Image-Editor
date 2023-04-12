#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#include "struct_image.h"
#include "load.h"
#include "select.h"
#include "crop.h"
#include "save.h"
#include "rotate.h"
#include "filters.h"

//returneaza tipul comenzii daca este una din cele din enunt
//sau daca este invalida.In cazul in care gaseste o comanda
//valida atunci verific la fiecare pas numarul de parametri
//iar in caz in care acestia sunt ok atunci ii returnez
comenzi tip_comanda(char *sir_citit, char **adaug_param)
{
	int nr_cuv = 0;
	comenzi comanda_incarcata;
	char *p = strchr(sir_citit, '\n');
	char sep[] = " ";
	char *cuvant = strtok(sir_citit, sep);
	char **vect_de_cuv = malloc(NR_MAX_CAR_COM * sizeof(char *));
	if (p)
		*p = '\0';

	while (cuvant) {
		vect_de_cuv[nr_cuv] = cuvant;
		nr_cuv++;
		cuvant = strtok(NULL, sep);
	}

	if (strcmp(vect_de_cuv[0], "LOAD") == 0) {
		if (nr_cuv > 2) {
			comanda_incarcata = NO_COMMAND;
		} else {
			adaug_param[0] = vect_de_cuv[1];
			comanda_incarcata = LOAD;
		}
	} else if (strcmp(vect_de_cuv[0], "SELECT") == 0) {
		if (strcmp(vect_de_cuv[1], "ALL") == 0) {
			if (nr_cuv > 2)
				comanda_incarcata = NO_COMMAND;
			else
				comanda_incarcata = SELECT_ALL;
		} else {
			if (nr_cuv != 5) {
				comanda_incarcata = NO_COMMAND;
			} else {
				for (int_fast32_t i = 1; i < nr_cuv; i++)
					adaug_param[i - 1] = vect_de_cuv[i];
				comanda_incarcata = SELECT;
			}
		}
	} else if (strcmp(vect_de_cuv[0], "ROTATE") == 0) {
		if (nr_cuv > 2) {
			comanda_incarcata = NO_COMMAND;
		} else {
			adaug_param[0] = vect_de_cuv[1];
			comanda_incarcata = ROTATE;
		}
	} else if (strcmp(vect_de_cuv[0], "CROP") == 0) {
		if (nr_cuv > 1)
			comanda_incarcata = NO_COMMAND;
		else
			comanda_incarcata = CROP;
	} else if (strcmp(vect_de_cuv[0], "APPLY") == 0) {
		if (nr_cuv > 2) {
			comanda_incarcata = NO_COMMAND;
		} else {
			adaug_param[0] = vect_de_cuv[1];
			comanda_incarcata = APPLY;
		}
	} else if (strcmp(vect_de_cuv[0], "SAVE") == 0) {
		if (nr_cuv > 3) {
			comanda_incarcata = NO_COMMAND;
		} else {
			for (int_fast32_t i = 1; i < nr_cuv; i++)
				adaug_param[i - 1] = vect_de_cuv[i];
			if (nr_cuv == 2)
				adaug_param[1] = "\0";
			comanda_incarcata = SAVE;
		}
	} else if (strcmp(vect_de_cuv[0], "EXIT") == 0) {
		if (nr_cuv > 1)
			comanda_incarcata = NO_COMMAND;
		else
			comanda_incarcata = EXIT;
	} else {
		comanda_incarcata = NO_COMMAND;
	}

	free(vect_de_cuv);
	return comanda_incarcata;
}

//aceasta functie verifica ce comanda am citit
//si prelucreaza parametri primiti
//de fiecare data verific daca am incarcat o imagine
//la aplicarea unei comenzi, iar in cazul functiei LOAD
//eliberez imaginea anterioara daca a fost incarcata
void rezolva(int_fast8_t ok, incarcare stare_img, imagine img,
			 comenzi comanda, char *intrare_com, char **parametri)
{
	while (ok == 1) {
		fgets(intrare_com, NR_MAX_CAR_CITITE, stdin);
		comanda = tip_comanda(intrare_com, parametri);
		switch (comanda) {
		case LOAD:
			if (stare_img == INCARCATA)
				elib_img(&img);
			stare_img = imag_noua(parametri[0], &img);
			img.img_forma = img_frm(&img);
			break;
		case SELECT:
			if (stare_img == NEINCARCATA)
				printf("No image loaded\n");
			else
				img.img_forma = select_param(&img, parametri);
			break;
		case SELECT_ALL:
			if (stare_img == NEINCARCATA) {
				printf("No image loaded\n");
			} else {
				printf("Selected ALL\n");
				reinit_select_imag(&img);
				img.img_forma = img_frm(&img);
			}
			break;
		case CROP:
			if (stare_img == NEINCARCATA) {
				printf("No image loaded\n");
			} else {
				select_crop(&img);
				img.img_forma = img_frm(&img);
			}
			break;
		case ROTATE:
			if (stare_img == NEINCARCATA)
				printf("No image loaded\n");
			else
				rotatie(&img, parametri[0]);
			break;
		case APPLY:
			if (stare_img == NEINCARCATA)
				printf("No image loaded\n");
			else
				filtre(&img, parametri[0]);
			break;
		case SAVE:
			if (stare_img == NEINCARCATA)
				printf("No image loaded\n");
			else
				salveaza(img, parametri);
			break;
		case EXIT:
			if (stare_img == NEINCARCATA)
				printf("No image loaded\n");
			else
				elib_img(&img);
			ok = 0;
			break;
		case NO_COMMAND:
			printf("Invalid command\n");
			break;
		default:
			printf("Invalid command\n");
			break;
	}
	}
	free(intrare_com);
	free(parametri);
}

int main(void)
{
	int_fast8_t ok = 1;
	incarcare stare_img = NEINCARCATA;
	imagine img = {};
	comenzi comanda = NO_COMMAND;
	char *intrare_com = malloc(NR_MAX_CAR_CITITE * sizeof(*intrare_com));
	char **parametri = malloc(NR_MAX_PAR_COM * sizeof(char *));
	rezolva(ok, stare_img, img, comanda, intrare_com, parametri);
	return 0;
}
