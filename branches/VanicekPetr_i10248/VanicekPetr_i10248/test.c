
/*
#include "seznamPamatek.h"
#include "pamatka.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

tPamatka* prvni=NULL, *akt=NULL;

tGPS *aaAlokujGPS(double severSirka, double vychodDelka) {

   tGPS *noveGPS;

   noveGPS = (tGPS *)malloc(sizeof(tGPS));
   noveGPS->latit = severSirka;
   noveGPS->longit = vychodDelka;
   return noveGPS;

}

double aaprevedNaStupne(double x) {
	return x/60;
}

int aaNactiData(char *filename) {

	FILE *fr = fopen ( filename, "r" );

	if(fr != NULL) {
		char gpsNStupne[3];
		char gpsNMinuty[8];
		char gpsEStupne[3];
		char gpsEMinuty[8];
		char gpsJmenoPamatky[21];
		char *p_gpsJmenoPamatky = gpsJmenoPamatky;
		char line [116];

		double gpsNStupneCislo;
		double gpsNMinutyCislo;
		double gpsNLatit;

		double gpsEStupneCislo;
		double gpsEMinutyCislo;
		double gpsELongit;

	while ( fgets (line, sizeof line, fr) != NULL ) {
		strncpy(gpsNStupne, line + 20, 2);
		gpsNStupne[2] = '\0';
		strncpy(gpsNMinuty, line + 23, 7);
		gpsNMinuty[7] = '\0';
		strncpy(gpsEStupne, line + 33, 2);
		gpsEStupne[2] = '\0';
		strncpy(gpsEMinuty, line + 36, 7);
		gpsEMinuty[7] = '\0';
		strncpy(gpsJmenoPamatky, line + 69, 20);
		gpsJmenoPamatky[20] = '\0';

		gpsNStupneCislo = atof(gpsNStupne);
		gpsNMinutyCislo = atof(gpsNMinuty);
		gpsNLatit = gpsNStupneCislo + aaprevedNaStupne(gpsNMinutyCislo);

		gpsEStupneCislo = atof(gpsEStupne);
		gpsEMinutyCislo = atof(gpsEMinuty);
		gpsELongit = gpsEStupneCislo + prevedNaStupne(gpsEMinutyCislo);
	

		aaVlozNaPosledni(VytvorPamatku(p_gpsJmenoPamatky, *aaAlokujGPS(gpsNLatit, gpsELongit)));


		//printf("JMENO: %s N-stupne: %.3lf, E-stupne: %.3lf\n", gpsJmenoPamatky, gpsNLatit, gpsELongit);

	}

	if((fclose (fr)) == EOF) {
		printf("Soubor %s se nepodarilo uzavrit.", filename);
		return 1;
	}
	
	} else {
		printf("Soubor %s se nepodarilo otevrit.", filename);
		return 1; 
	}

	return 0;
}

void aaVypis(){

   int poradi=0;

   if(prvni==NULL){
      printf("Seznam je prazdny!\n");
   }
   else{
      akt=prvni;
      while(akt){
         poradi++;
		 //printf("%d. pamatka: %s\zemepisna sirka - %lf\nzemepisna delka - %lf\n\n", poradi, akt->pamatka, akt->gps.latit, akt->gps.longit);
		 VypisPamatku(akt, poradi);
         akt=akt->dalsi;
      }
   }

}

void aaVlozNaPosledni(tPamatka *svytvorPamatka){

   if(prvni == NULL){
      prvni = svytvorPamatka;
   }
   else{
      akt = prvni;
      while(akt->dalsi){
         akt = akt->dalsi;
      }
      akt->dalsi = svytvorPamatka;
   }

}
*/