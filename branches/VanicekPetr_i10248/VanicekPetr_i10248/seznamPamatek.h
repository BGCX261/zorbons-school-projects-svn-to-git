#include <stdio.h>
#include <stdlib.h>

#include "pamatka.h"

/* Deklarace funkcí pro použití v "seznamPamatek.c" */

int NactiData(char *nazev);
void Vypis();
tPamatka *NajdiDleNazvu(char *nazev);
tPamatka *NajdiNejblizsi(tGPS *gpsPamatky);
tPamatka **NajdiTriNejblizsi(tGPS *gpsPamatky);
void ZrusData();