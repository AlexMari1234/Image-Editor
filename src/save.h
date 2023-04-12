#pragma once

//salveaza o imagine in format binar
void salveaza_binar(imagine img, char *fisier);

//salveaza o imagine in format ascii
void salveaza_ascii(imagine img, char *fisier);

//selecteaza tipul salvarii imaginii:ascii/binar
void salveaza(imagine img, char **parametri);
