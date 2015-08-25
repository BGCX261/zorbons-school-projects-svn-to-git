#pragma once
#include "gps.h"

typedef struct pamatka{
		char mesto[30];
		tGPS gps;
		struct pamatka *dalsi;

}tPamatka;

tPamatka *vytvorPamatku(char *pamatka, tGPS *gpsPamatky);
void vypisPamatku(tPamatka *pamatka);
