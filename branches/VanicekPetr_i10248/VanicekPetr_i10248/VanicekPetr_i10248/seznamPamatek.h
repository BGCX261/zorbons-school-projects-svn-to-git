#include <stdio.h>
#include <stdlib.h>

#include "pamatka.h"

void nactiData(char *nazev);
void vypis();
tPamatka *najdiDleNazvu(char *nazev);
tPamatka *najdiNejblizsi(tPamatka *pamatka);
tPamatka **najdiTriNejblizsi(tGPS *gpsPamatky);
void zrusData();