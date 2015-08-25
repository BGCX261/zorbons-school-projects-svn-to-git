#pragma once
#include "gps.h"

typedef struct pamatka{
		char mesto[30];
		tGPS gps;
		struct pamatka *dalsi;

}tPamatka;

tPamatka *VytvorPamatku(char *pamatka, tGPS *gpsPamatky);
void *VypisPamatku(tPamatka *pamatka);
