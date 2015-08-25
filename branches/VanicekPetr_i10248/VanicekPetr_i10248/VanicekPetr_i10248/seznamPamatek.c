#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "pamatka.h"
//#define SOUBOR "DataImport_Zamky.txt"
#define R 6372.795
#define PI 3.14159265

tPamatka *prvni=NULL, *akt=NULL;

void vlozNaPosl(tPamatka *novaPamatka)
{
	if (prvni == NULL)
	{
		prvni = novaPamatka;
	} else {
		while(akt->dalsi){
         akt = akt->dalsi;
      };
	}
	akt = novaPamatka;
}

tGPS ulozGPS(double latit, double longit)
{
	char *mesto;
	tGPS *souradnice;
	souradnice = (tGPS *) malloc (2 *sizeof(tGPS));

	souradnice->latit = latit;
	souradnice->longit = longit;

	//return souradnice->latit;
}

void nactiData(char *nazev) // *nazev (jmeno / cesta k souboru) - - použije VytvorPamatku a VlozNaPosl
{
	int i = 0;
	int zn = 0;
	FILE *soubor;
	char *nazevSouboru = nazev;
	tGPS *souradnice = (tGPS *) malloc(sizeof(tGPS));

	char *radek = (char *) malloc(80 * sizeof(char));
	char *mesto = (char *) malloc(20 * sizeof(char));

	char charStupneN[3];
	char charMinutyN[8];
	char charStupneE[3];
	char charMinutyE[8];

	double stupneN;
	double minutyN;
	double stupneE;
	double minutyE;

	double latitGPS;
	double longitGPS;

	int poziceNazvu = 69;
	int poziceLatS = 20;
	int poziceLatM = 23;
	int poziceLongS = 33;
	int poziceLongM = 36;

	
	char *pomMesto;
	char hranice[] = "^";

	soubor = fopen(nazevSouboru, "r");
	



	for (i = 0; i < strlen(radek); i++)
	{
		*(radek+i) = fgetc(soubor);
	}

	for (i = poziceNazvu; i < strlen(mesto) + poziceNazvu; i++)
	{
		*(mesto+zn) = *(radek+i);
		zn++;
	}

	strncpy(charStupneN, radek + poziceLatS, 2);
	strncpy(charMinutyN, radek + poziceLatM, 7);
	strncpy(charStupneE, radek + poziceLongS, 2);
	strncpy(charMinutyE, radek + poziceLongM, 7);
	charStupneN[2] = '\0';
	charMinutyN[7] = '\0';
	charStupneE[2] = '\0';
	charMinutyE[7] = '\0';

	stupneN = atof(charStupneN);
	minutyN = ( (atof(charMinutyN)) / 60 );
	stupneE = atof(charStupneE);
	minutyE =  ( (atof(charMinutyE)) / 60 );

	latitGPS = stupneN + minutyN;
	longitGPS = stupneE + minutyE;

	/*printf("%.4f \n", latitGPS);
	printf("%.4f \n", longitGPS);*/

	pomMesto = NULL;
	pomMesto = strtok( mesto, hranice );
	while( pomMesto != NULL ) {
		pomMesto = strtok( NULL, hranice );
	}

	for (i = strlen(mesto)-1; i > 0; i--)
	{
		if (mesto[i] == ' ')
		{
			mesto[i] = '\0';
			if (mesto[i-1] != ' ')
			{
				break;
			}
		}
	}

	*souradnice = ulozGPS(latitGPS, longitGPS);
	printf("N%.4f   E%.4f", souradnice->latit, souradnice->longit);

	vlozNaPosl(vytvorPamatku(mesto, souradnice));

	

	//printf("Mesto: %s	:	souradnice: N%d	E%d", mesto, latitGPS, longitGPS);
	//printf("%d", pocMezer);
	//printf("\n");	
}

void vypis() //využije VypisPamatku()
{
	if(prvni==NULL){
      printf("Seznam je prazdny!\n");
	}
	else{
		akt=prvni;
		while(akt)
		{
			printf("%d. pamatka:	%s	[zemepisna sirka - %lf	||	nzemepisna delka - %lf]\n", akt->mesto, akt->gps.latit, akt->gps.longit);
			 vypisPamatku(akt);
			 akt=akt->dalsi;
		}
	}
}

void najdiDleNazvu()
{

}

int zjistiVzdalenost(tGPS gpsPamatka1, tGPS gpsPamatka2)
{
	int vzdalenost;
	vzdalenost = acos(sin(gpsPamatka1.latit*PI/180)*sin(gpsPamatka2.latit*PI/180) 
					+ (cos(gpsPamatka1.latit*PI/180)*cos(gpsPamatka2.latit*PI/180) 
					* cos((gpsPamatka2.longit-gpsPamatka1.longit)*PI/180))) * R;
	return vzdalenost;
}

tPamatka najdiNejblizsi(tGPS *gpsPamatky)
{
	tPamatka *nejblizsi = (tPamatka *) malloc (sizeof(tPamatka*));
	return *nejblizsi;
}

tPamatka najdiTriNejblizsi(tGPS gpsPamatky)
{
	//return;
}

void zrusData()
{

}