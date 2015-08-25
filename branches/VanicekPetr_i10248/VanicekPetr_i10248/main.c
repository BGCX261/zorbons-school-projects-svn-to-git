#include <stdio.h>

#include "seznamPamatek.h"
#include "gps.h"
#include "pamatka.h"

#define ZDROJ "DataImport_Zamky.txt"
int main()
{
	int i;
	int volba;
	double gpsLat;
	double gpsLong;
	char *nazev = (char *) malloc(20 * sizeof(char));
	tGPS souradnice;
	tPamatka *nejblizsi;
	tPamatka **triNejblizsi;

	while(1) {
		printf("\nVolby:\n");
		printf(	"(1) - Nacteni dat \n"
				"(2) - Hledani dle nazvu \n"
				"(3) - Hledani nejblize umistene pamatky \n"
				"(4) - Hledanani tri nejblizsich pamatek \n"
				"(5) - Zruseni dat \n"
				"(6) - Vypsani dat \n"
				"(7) - Ukonceni programu \n");
		scanf("%d", &volba);

		switch(volba) {
			case 1:
				NactiData(ZDROJ);
				break;
			
			case 2:
				printf("Zadej nazev mesta (velká písmena): ");
				fflush(stdin);
				gets(nazev);
				nejblizsi = NajdiDleNazvu(nazev);
				if (nejblizsi != NULL) {
				  VypisPamatku(nejblizsi);
				} else {
				  printf("Nenalezena");
				} 
				system("pause");
				break;

			case 3:
				printf("Zadej severni sirku (format XX.XXXX)");
				scanf("%lf", &gpsLat);
				printf("Zadej vychodni delku (format XX.XXXX)");
				scanf("%lf", &gpsLong);
				souradnice.latit = gpsLat;
				souradnice.longit = gpsLong;
				nejblizsi = NajdiNejblizsi(&souradnice);
				if (nejblizsi != NULL) {
				  VypisPamatku(nejblizsi);
				} else {
				  printf("Nenalezena");
				}
				system("pause");
				break;

			case 4:
				printf("Zadej severni sirku (format XX.XXXX)");
				scanf("%lf", &gpsLat);
				printf("Zadej vychodni delku (format XX.XXXX)");
				scanf("%lf", &gpsLong);
				souradnice.latit = gpsLat;
				souradnice.longit = gpsLong;
				triNejblizsi = NajdiTriNejblizsi(&souradnice);
				if (triNejblizsi != NULL) {
					for (i = 0; i < sizeof(triNejblizsi); i++)
					{
						if (*(triNejblizsi + i) != NULL) {
							VypisPamatku(*(triNejblizsi + i));
						}
					}
					} else {
						 printf("Nenalezeno");
					}
				system("pause");
				break;

			case 5:
				ZrusData();
				system("pause");
				break;

			case 6:
				Vypis();
				system("pause");
				break;

			case 7:
				printf("Program bude ukoncen.\n");
				exit(0);
				break;
			
			default:
				printf("Neplatna volba! Opakujte zadani! \n");
				system("pause");
				break;
		}

	}


	return 0;
}