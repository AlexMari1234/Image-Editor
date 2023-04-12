#pragma once
//verifica daca imaginea selectata este echivalenta
//cu toata imaginea
int verif_img_intreaga(int x1, int y1, int x2,
					   int y2, int x, int y);

//actualizeaza matricea de pixeli cu cea selectata
double **schimba_mat(double ***mat, int x1, int y1,
					 int x2, int y2, int y);

//schimba matricea corespunzatoare tipului imaginii
//in urma selectiei coordonatelor si actualizeaza
//dimensiunile imaginii
void select_crop(imagine *img);
