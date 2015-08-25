#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pamatka.h"

tPamatka *vytvorPamatku(char *pamatka, tGPS gpsPamatky)
{
	tPamatka *pDocasna = (tPamatka *) malloc (sizeof(tPamatka));

	if (pDocasna == NULL)
	{
		printf("Alokovani pamatky se nezdarilo!");
		exit(0);
	}

	strcpy(pDocasna->mesto, pamatka);
	pDocasna->gps = gpsPamatky;
	pDocasna->dalsi = NULL;

	return NULL;
}

void vypisPamatku(tPamatka *pamatka)
{
	printf("%s", pamatka->mesto, pamatka->gps);
}