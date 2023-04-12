#pragma once

//interschimba 2 coordonate
void swap_coord(int_fast32_t *a, int_fast32_t *b);

//verifica daca parametri selectati sunt valizi
int_fast32_t verif_param(int_fast32_t x1, int_fast32_t y1,
						 int_fast32_t x2, int_fast32_t y2, imagine *img);

//returneaza forma selectiei facute
forma select_param(imagine *img, char **param);

//reinitializeaza coordonatele de inceput si final in cazul selectiei
//SELECT ALL
void reinit_select_imag(imagine *img);

//returneaza forma unei imagini
forma img_frm(imagine *img);
