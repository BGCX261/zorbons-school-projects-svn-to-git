#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "pamatka.h"
#include "gps.h"
#define R 6372.795
#define PI 3.14159265

tPamatka *prvni=NULL, *akt=NULL;			// *prvn� - prvn� polo�ka seznamu	||	*akt - aktu�ln� v po�ad� (posledn�)

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

tGPS *UlozGPS(double latit, double longit)	// latit - severn� ���ka || longit - v�chodn� d�lka
{
	tGPS *souradnice;
	souradnice = (tGPS *) malloc (sizeof(tGPS));

	souradnice->latit = latit;
	souradnice->longit = longit;
}

void OdeberMezery(char *str)
{
	char *konec;		//ur�eno pro posledn� znak �et�zce *str

  while(isspace(*str)) str++;	// ov��en� p��tomnosti �et�zce, tj. zda d�lka nen� nulov�
  if(*str == 0)
    return;

  konec = str + strlen(str) - 1;	// z�sk�n� posledn�ho znaku �et�zce
  while(konec > str && isspace(*konec)) konec--;	/* Cyklus bude prob�hat pokud se nedojde dekrementac� a� na po��tek �et�zce 
													 p�i�em� se kontroluje zda proch�zen� znak je mezerou, pokud ne, tak dojde k 
													 ukon�en� dekremenace a dojde z z�sk�n� nov� d�lky �et�zce */
  *(konec+1) = 0;
}


int NactiData(char *nazev)
{
	int i = 0;
	int zn = 0;		// zn = znak, 'i' nepou�ito z d�vodu jeho pou�it�
	FILE *soubor;
	char *nazevSouboru = nazev;

	tGPS *souradnice;
	tPamatka *pamatka;

	char radek[120];		// pro na�ten� ��dku souboru

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
	
	char *pomMesto = (char *) malloc (200 * sizeof(char)); // pomocn� m�sto

	soubor = fopen(nazevSouboru, "r");	// otev�en� souboru jen pro �ten� + ov��en� spr�vn�ho otev�en� souboru s p��padn�m v�pisem (odchytem) chyby
	if (soubor == NULL) {
		printf("Soubor se nepodarilo otevrit.");
		return 1;
	}

	if (pomMesto == NULL) {				// ov��en� nepr�zdn�ho pomocn�ho m�sta 
		return 1;
	}
	
	while (fgets(radek, sizeof(radek), soubor) != NULL)		// cyklus s podm�nkou pro �ten� ��dk� dokud nenaraz� na NULLov� (��dn�, pr�zdn�) ��dek
	{
		delka = strlen(radek);
		radek[delka - 1] = '\0';		// zkr�cen� ��dku o znak

		strncpy(charStupneN, radek + poziceLatS, 2);	// ulo�en� dan�ho po�tu znak� (2 || 7) do textov�ho �et�zce z pozice strukturovan�ho souboru
		strncpy(charMinutyN, radek + poziceLatM, 7);
		strncpy(charStupneE, radek + poziceLongS, 2);
		strncpy(charMinutyE, radek + poziceLongM, 7);
		charStupneN[2] = '\0';		// zkr�cen� na po�adovanou d�lku
		charMinutyN[7] = '\0';
		charStupneE[2] = '\0';
		charMinutyE[7] = '\0';

		stupneN = atoi(charStupneN);			// p�eveden� stup�� z textov� (char) hodnoty na hodnotu typu integer
		minutyN = (atof(charMinutyN) / 60);		// p�evod minut na float vhodn� pro ��st minut za desetinnou ��rkou
		stupneE = atoi(charStupneE);
		minutyE = (atof(charMinutyE) / 60);	
		
		latitGPS = stupneN + minutyN;			// zisk hodnoty sou�adnic se�ten�m cel�ch stupn� a minut v re�ln�m ��sle
		longitGPS = stupneE + minutyE;
		
		strcpy(pomMesto, radek + poziceNazvu);	// vybr�n� ��sti �et�zce z n�zvu pro ulo�en� n�zvu m�sta (je�t� v�etn� v�eho napravo od n�j)
		strtok(pomMesto, "^");					// odebr�n� ��sti zbyte�n�ch znak� a� po znak '^', st�le s mezerami

		OdeberMezery(pomMesto);					// funkce pou�ita pro d�kladn�j�� o�i�t�n� n�zvu od mezer

		souradnice = UlozGPS(latitGPS, longitGPS);		// z v��e zm�n�n�ch sou�adnic vytvo�ena kompletn� GPS sou�adnice
		pamatka = VytvorPamatku(pomMesto, souradnice);	// kompletace pam�tky z n�zvu m�sta a jej� sou�adnice

		VlozNaPosl(pamatka);			//vlo�en� vytvo�en� pam�tky na konec line�rn�ho seznamu
	}

	fclose(soubor);

	return 0;
}

void Vypis() //vyu�ije VypisPamatku()
{
	int i = 1;
	if(prvni==NULL){
      printf("Seznam je prazdny!\n");
	}
	
	akt=prvni;
	while(akt != NULL)
		{
			 VypisPamatku(akt);
			 akt=akt->dalsi;		//postup na dal�� pam�tku v seznamu
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
		if (strcmp(nazev, pom->mesto) == 0) {		// porovn�v�n� zadan�ho m�sta s line�rn�m seznamem dokud se nenajde shoda
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
		vzdalenost = ZjistiVzdalenost(*gpsPamatky, pom->gps);		// zji��ov�n� vzd�lenost� mezi zadan�mi GPS sou�adnicemi a pam�tkami v seznamu
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

	if (prvni == NULL) {	//ov��en� napln�n� seznamu, zda je alespo� jedna polo�ka, jinak NULL
		return NULL;
	}

	pom = NULL;
	nejPrvni = prvni;
	nejDruha = NULL;
	nejTreti = NULL;
	
	nejPrvniVzd = ZjistiVzdalenost(*gpsPamatky, nejPrvni->gps);

	// za��tek na druh�
	pom = nejPrvni->dalsi;

	// jsou - li dv�, za�ni na t�et�
	if (nejPrvni->dalsi != NULL) {
		nejDruha = nejPrvni->dalsi;
		nejDruhaVzd = ZjistiVzdalenost(*gpsPamatky, nejDruha->gps);
		pom = nejDruha->dalsi;
	}
	// jsou - li t�i, za�ni na �tvrt�
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

void ZrusData()		//provede dealokaci seznamu pam�tek
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