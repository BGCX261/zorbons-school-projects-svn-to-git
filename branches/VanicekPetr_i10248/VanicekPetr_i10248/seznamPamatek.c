#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "pamatka.h"
#include "gps.h"
#define R 6372.795
#define PI 3.14159265

tPamatka *prvni=NULL, *akt=NULL;			// *první - první poloka seznamu	||	*akt - aktuální v poøadí (poslední)

void VlozNaPosl(tPamatka *novaPamatka)
{
	if (prvni == NULL)
	{
		prvni = novaPamatka;
	} else {		
			akt->dalsi = novaPamatka;
	}
	akt = novaPamatka;
}

tGPS *UlozGPS(double latit, double longit)	// latit - severní šíøka || longit - vıchodní délka
{
	tGPS *souradnice;
	souradnice = (tGPS *) malloc (sizeof(tGPS));

	souradnice->latit = latit;
	souradnice->longit = longit;
}

void OdeberMezery(char *str)
{
	char *konec;		//urèeno pro poslední znak øetìzce *str

  while(isspace(*str)) str++;	// ovìøení pøítomnosti øetìzce, tj. zda délka není nulová
  if(*str == 0)
    return;

  konec = str + strlen(str) - 1;	// získání posledního znaku øetìzce
  while(konec > str && isspace(*konec)) konec--;	/* Cyklus bude probíhat pokud se nedojde dekrementací a na poèátek øetìzce 
													 pøièem se kontroluje zda procházenı znak je mezerou, pokud ne, tak dojde k 
													 ukonèení dekremenace a dojde z získání nové délky øetìzce */
  *(konec+1) = 0;
}


int NactiData(char *nazev)
{
	int i = 0;
	int zn = 0;		// zn = znak, 'i' nepouito z dùvodu jeho pouití
	FILE *soubor;
	char *nazevSouboru = nazev;

	tGPS *souradnice;
	tPamatka *pamatka;

	char radek[120];		// pro naètení èádku souboru

	char charStupneN[3];
	char charMinutyN[8];
	char charStupneE[3];
	char charMinutyE[8];

	int stupneN;
	double minutyN;
	int stupneE;
	double minutyE;

	double latitGPS;
	double longitGPS;

	int poziceNazvu = 69;
	int poziceLatS = 20;
	int poziceLatM = 23;
	int poziceLongS = 33;
	int poziceLongM = 36;

	int delka;
	
	char *pomMesto = (char *) malloc (200 * sizeof(char)); // pomocné mìsto

	soubor = fopen(nazevSouboru, "r");	// otevøení souboru jen pro ètení + ovìøení správného otevøení souboru s pøípadnım vıpisem (odchytem) chyby
	if (soubor == NULL) {
		printf("Soubor se nepodarilo otevrit.");
		return 1;
	}

	if (pomMesto == NULL) {				// ovìøení neprázdného pomocného mìsta 
		return 1;
	}
	
	while (fgets(radek, sizeof(radek), soubor) != NULL)		// cyklus s podmínkou pro ètení øádkù dokud nenarazí na NULLovı (ádnı, prázdnı) øádek
	{
		delka = strlen(radek);
		radek[delka - 1] = '\0';		// zkrácení øádku o znak

		strncpy(charStupneN, radek + poziceLatS, 2);	// uloení daného poètu znakù (2 || 7) do textového øetìzce z pozice strukturovaného souboru
		strncpy(charMinutyN, radek + poziceLatM, 7);
		strncpy(charStupneE, radek + poziceLongS, 2);
		strncpy(charMinutyE, radek + poziceLongM, 7);
		charStupneN[2] = '\0';		// zkrácení na poadovanou délku
		charMinutyN[7] = '\0';
		charStupneE[2] = '\0';
		charMinutyE[7] = '\0';

		stupneN = atoi(charStupneN);			// pøevedení stupòù z textové (char) hodnoty na hodnotu typu integer
		minutyN = (atof(charMinutyN) / 60);		// pøevod minut na float vhodnı pro èást minut za desetinnou èárkou
		stupneE = atoi(charStupneE);
		minutyE = (atof(charMinutyE) / 60);	
		
		latitGPS = stupneN + minutyN;			// zisk hodnoty souøadnic seètením celıch stupnù a minut v reálném èísle
		longitGPS = stupneE + minutyE;
		
		strcpy(pomMesto, radek + poziceNazvu);	// vybrání èásti øetìzce z názvu pro uloení názvu mìsta (ještì vèetnì všeho napravo od nìj)
		strtok(pomMesto, "^");					// odebrání èásti zbyteènıch znakù a po znak '^', stále s mezerami

		OdeberMezery(pomMesto);					// funkce pouita pro dùkladnìjší oèištìní názvu od mezer

		souradnice = UlozGPS(latitGPS, longitGPS);		// z vıše zmínìnıch souøadnic vytvoøena kompletní GPS souøadnice
		pamatka = VytvorPamatku(pomMesto, souradnice);	// kompletace památky z názvu mìsta a její souøadnice

		VlozNaPosl(pamatka);			//vloení vytvoøené památky na konec lineárního seznamu
	}

	fclose(soubor);

	return 0;
}

void Vypis() //vyuije VypisPamatku()
{
	int i = 1;
	if(prvni==NULL){
      printf("Seznam je prazdny!\n");
	}
	
	akt=prvni;
	while(akt != NULL)
		{
			 VypisPamatku(akt);
			 akt=akt->dalsi;		//postup na další památku v seznamu
		}
	}

tPamatka *NajdiDleNazvu(char *nazev)
{
	tPamatka *pom;
	if (prvni == NULL) {
		return NULL;
	}

	pom = prvni;
	while (pom != NULL) {
		if (strcmp(nazev, pom->mesto) == 0) {		// porovnávání zadaného mìsta s lineárním seznamem dokud se nenajde shoda
			return pom;
		}
		pom = pom->dalsi;		// "inkremetace" (postup) v seznamu
	}
	return 0;

}

int ZjistiVzdalenost(tGPS gpsPamatka1, tGPS gpsPamatka2)
{
	int vzdalenost;
	vzdalenost = (int) ( acos(sin(gpsPamatka1.latit*PI/180)*sin(gpsPamatka2.latit*PI/180) 
					+ (cos(gpsPamatka1.latit*PI/180)*cos(gpsPamatka2.latit*PI/180) 
					* cos((gpsPamatka2.longit-gpsPamatka1.longit)*PI/180))) * R );
	return vzdalenost;
}

tPamatka *NajdiNejblizsi(tGPS *gpsPamatky)
{
	tPamatka *nejblizsi;
	tPamatka *pom;
	int vzdalenost, vzdalenostNejblizsi;

	if (prvni == NULL) {
		return NULL;
	}
	
	nejblizsi = prvni;
	vzdalenostNejblizsi = ZjistiVzdalenost(*gpsPamatky, nejblizsi->gps);

	pom = prvni->dalsi;
	while (pom != NULL) {
		vzdalenost = ZjistiVzdalenost(*gpsPamatky, pom->gps);		// zjišování vzdáleností mezi zadanımi GPS souøadnicemi a památkami v seznamu
		if (vzdalenost < vzdalenostNejblizsi) {
			nejblizsi = pom;
			vzdalenostNejblizsi = vzdalenost;
		}
		pom = pom->dalsi;
	}
	
	if (nejblizsi != NULL)
	{
		printf("Vzdalenost od zadaneho bodu je %d km, cilem je \n", vzdalenostNejblizsi);
	}
	return nejblizsi;

	

}

tPamatka **NajdiTriNejblizsi(tGPS *gpsPamatky)
{
	tPamatka **triNejblizsi = (tPamatka **) malloc (3 * sizeof(tPamatka*)); // alokace dyn. dvou rozm. pole
	tPamatka *nejPrvni, *nejDruha, *nejTreti, *pom;
	int nejPrvniVzd, nejDruhaVzd, nejTretiVzd, vzdalenost;
	tGPS gps;

	if (triNejblizsi == NULL) {
		return NULL;
	}

	if (prvni == NULL) {	//ovìøení naplnìní seznamu, zda je alespoò jedna poloka, jinak NULL
		return NULL;
	}

	pom = NULL;
	nejPrvni = prvni;
	nejDruha = NULL;
	nejTreti = NULL;
	
	nejPrvniVzd = ZjistiVzdalenost(*gpsPamatky, nejPrvni->gps);

	// zaèátek na druhé
	pom = nejPrvni->dalsi;

	// jsou - li dvì, zaèni na tøetí
	if (nejPrvni->dalsi != NULL) {
		nejDruha = nejPrvni->dalsi;
		nejDruhaVzd = ZjistiVzdalenost(*gpsPamatky, nejDruha->gps);
		pom = nejDruha->dalsi;
	}
	// jsou - li tøi, zaèni na ètvrté
	if (nejDruha->dalsi != NULL) {
		nejTreti = nejDruha->dalsi;
		nejTretiVzd = ZjistiVzdalenost(*gpsPamatky, nejTreti->gps);
		pom = nejTreti->dalsi;
	}

	while (pom != NULL) {

		vzdalenost = ZjistiVzdalenost(*gpsPamatky, pom->gps);

		if (vzdalenost < nejPrvniVzd) {
			nejPrvni = pom;
			nejPrvniVzd = vzdalenost;
		} else if (vzdalenost < nejDruhaVzd && nejDruha != NULL) {
			nejDruha = pom;
			nejDruhaVzd = vzdalenost;
		} else if (vzdalenost < nejTretiVzd && nejTreti != NULL) {
			nejTreti = pom;
			nejTretiVzd = vzdalenost;
		}

		pom = pom->dalsi;
	}

	*triNejblizsi = nejPrvni;
	*(triNejblizsi + 1) = nejDruha;
	*(triNejblizsi + 2) = nejTreti;

	return triNejblizsi;

}

void ZrusData()		//provede dealokaci seznamu památek
{
	tPamatka *pom = prvni;
	tPamatka *temp;
	while (pom != NULL) {
		temp = pom->dalsi;
		free(pom);
		pom = temp;
	}
	prvni = NULL;
	akt = NULL;

}