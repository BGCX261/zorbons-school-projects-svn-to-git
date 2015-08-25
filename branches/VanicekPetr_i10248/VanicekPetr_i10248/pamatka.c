#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pamatka.h"

tPamatka *VytvorPamatku(char *pamatka, tGPS *gpsPamatky)
{
	tPamatka *pDocasna = (tPamatka *) malloc (sizeof(tPamatka));

	if (pDocasna == NULL)
	{
		printf("Alokovani pamatky se nezdarilo!");
		exit(0);
	}

	strcpy(pDocasna->mesto, pamatka);
	pDocasna->gps = *gpsPamatky;
	pDocasna->dalsi = NULL;

	return pDocasna;
}

void *VypisPamatku(tPamatka *pamatka)
{
	tGPS gps = pamatka->gps;
	printf("%-20s    GPS - lat: %.4f, lon: %.4f \n", pamatka->mesto, gps.latit, gps.longit);

}