#define _CRT_SECURE_NO_DEPRECATE // pre Visual Studio  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Autor: 		Miroslav Todorovic
	Cviciaci:	Igor Stupavský
	Predmet:	Zaklady Proceduralneho Programovania 1
	Uloha: 		Projekt 
	Semester: 	Zimny
	Datum: 		29.11.2020
*/

//////////////////////////////////////////////////////////
#define SUBOR "tabulka.csv"								// Subor "tabulka.csv" som deklaroval ako SUBOR
#define TEMPORARY "temporary.tmp"						// Subor "temporary.tmp" budem pouzivat vo funkcii rmdriver(); Deklaroval som ho ako TEMPORARY
#define NAME_AND_SURNAME 101							// Max pocet znakov pre retazec ktory uklada cele meno a priezvisko
#define NAME 61											// Max pocet znakov pre retazec meno
#define SURNAME 41										// Max pocet znakov pre retazec priezvisko
#define MIN_ROK 1800									// Pre rok som zadal minimalnu hodonotu od 1800
#define MAX_ROK 2020									// Max hodnota pre rok je 2020
#define CAR_BRAND 11									// Max pocet znakov pre retazec ktory uklada znacku auta
#define MAX_CAR_BRANDS 4								// Max pocet pre znacky auta
#define MAX_RACE_ROUNDS 5								// Max pocet kol pre kazdeho jazdca
#define check_gender(x)  ( x == 'm' ? "muz" : "zena")	// Makro na vypis pohlavia daneho jazdca
//////////////////////////////////////////////////////////

/* DEKLARACIA VSETKYCH HLAVNYCH FUNKCII */
int sum(void);							// 
int driver(void);						// 
int lap(void);							// 
int gender(void);						// 
int brand(void);						// 				
int year(void);							//
int average(void);						// 
int under(void);						// 
int change(void);						// 
int newdriver(void);					// 
int rmdriver(void);						// 
//////////////////////////////////////////

/*									DEKLARACIA POMOCNYCH FUNKCII 											*/
int kontrolaUdajov(char* krstne_meno, char* priezvisko, char pohlavie, int rok, char* znacka, float *casy);	//
int kontrolaZnackeAuta(char *znacka);																		//
void krstneMenoPriezvisko(char *meno_priezvisko, char *krstne_meno, char *priezvisko);						// 
void moznosti(void);																  						//  
void functionEnd(void);																						// 
float najlepsieKolo(float *casy);																			// 
float najhorsieKolo(float *casy);																			// 
float priemerneKolo(float *casy);																			// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() 
{ 
	int koniec = 1; 	// Tuto premenu puzivam vo while cyklu, ak puzivatel vlozi x, koniec sa zmeni na 0 a ukonci sa cyklus - koniec programu
	char vstup; 		// Premenna na nacitanie vstupu z klavesnice - jedne pismeno
	
	moznosti();			// Volame funkciu ktora nam vypise moznosti ktore nam poskituje program
	
	while(koniec != 0)
	{
		printf("\n>");
		scanf(" %c", &vstup);
		switch(vstup)
		{

			case 's': 	// Pre vstup 's' volame funkciu sum
				sum(); 	
				break;
			case 'd':	// Pre vstup 'd' volame funkciu driver
				driver();
				break;
			case 'l':	// Pre vstup 'l' volame funkciu lap
				lap();
				break;
			case 'g':	// Pre vstup 'g' volame funkciu gender
				gender();
				break;
			case 'b':	// Pre vstup 'b' volame funkciu brand
				brand();
				break;
			case 'y':	// Pre vstup 'y' volame funkciu year
				year();
				break;
			case 'a':	// Pre vstup 'a' volame funkciu average
				average();
				break;
			case 'u':	// Pre vstup 'u' volame funkciu under
				under();
				break;
			case 'c':	// Pre vstup 'c' volame funkciu change
				change();
				break;
			case 'n':	// Pre vstup 'n' volame funkciu newdriver
				newdriver();
				break;	
			case 'r':	// Pre vstup 'r' volame funkciu rmdriver
				rmdriver();
				break;
			case 'm':	// Pre vstup 'm' volame funkciu moznosti - Tato funkcia nie je ziadana pre projekt - Ja som ju pridal 
				moznosti();
				break;
			case 'x': 	// Pre vstup 'x' nevolame funkciu ale vypiseme spravu a ukoncime program
				printf("Koniec programu.\nDovienia."); 
				koniec = 0; 
				break;
			default: 	// V pripade ak pouzivatel zadal iny vstup nez co ponuka program vypise sa sprava pre nespravny vstup 
				printf("Chyba! Nespravny vstup, skuste znovu.\n");
				break;
		}
	}
	
	return 0;
}

int sum(void)		// Funkcia vypise vsetky informacie o jazdcovi 
{
	/* Premene pouzite pre spracovanie udajov zo suboru */
	FILE *fp;
	float *casy = NULL;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL;
	char pohlavie;
	int rok, i, riadok=0;

	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	
	/* Najprv otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if (fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	// Zaciatok funkcie - Kvoli tome ze je v subore dodrziavan jeden format, funkcia cita informacie zo suboru na tento sposob: 
	printf("\tFunkcia Summary: \n\n");
	// Postup nacitania zo suboru je podobny v kazdej funkcie, najprv meno a priezvisko do jedneho retazca, potom pohlavie, rok ...
	while ((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie, &rok, znacka, &casy[0], &casy[1], &casy[2], &casy[3], &casy[4])) != EOF)
	{														
		riadok++;		// Tato premena pocita na ktorem sme riadku v subore, ak je nieco nespravne vlozene vypise ktory jazdec ma chybu
		
		krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko); // Tato pomocna funkcia oddeluje krstne meno a priezvisko
		
		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy)) // Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane
		{
			/* Vypis vsetkych nacitanych informacii */
			printf("%s %s, nar. %d, ", krstne_meno, priezvisko, rok);	
			printf("%s, Automobil: %s\n", check_gender(pohlavie), znacka);
			printf("Casy okruhov: ");
			for(i=0; i<MAX_RACE_ROUNDS; i++)
			{
				if(i == MAX_RACE_ROUNDS-1)
				{
					printf("%.3f\n", casy[i]);
				}
				else
				{
					printf("%.3f;", casy[i]);
				}
			}
		}
		else
		{
			printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok); // Ak nastala chyba pri nacitavany vypise sa tato sprava a ukonci sa funkcia
			break;
		}
	}
	functionEnd(); // Pomocna funkcia iba nakresli ciaru ked sa funkcia ukonci
	
	if (fclose(fp) == EOF) // Testujeme ci sa subor zatvoril
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
}

int driver(void) 	// Funkcia vypise vsetky informacie o jazdcovi ktoreho hladame 
{
	FILE *fp;
	float *casy = NULL;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *priezvisko_najst = NULL;
	char pohlavie;
	int rok, i, riadok=0, jazdec_najden = 0;

	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	priezvisko_najst = (char *)malloc(SURNAME * sizeof(char));
	
	/* Najprv otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	// Funckia vypise spravu a ziada od pouzivatela aby vlozil priezvisko jazdca od ktoreho hlada rozsirene informacie
	printf("\tFunkcia Driver: \n>Zadajte priezvisko jazdca ktoreho hladate: ");
	scanf("%s", priezvisko_najst);
	// Postup nacitania zo suboru je podobny v kazdej funkcie ktora potrebuje vypis vsetkych udajov
	while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0], &casy[1], &casy[2], &casy[3], &casy[4])) != EOF)
	{
		riadok++;	//Pocita pocet jazdcov
		krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko); // Tato pomocna funkcia oddeluje krstne meno a priezvisko
		
		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy)) // Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane
		{
			if(strcmp(priezvisko, priezvisko_najst) == 0) // Ak sme nasli jazdca tak vypisemo jeho informacie
			{
				printf("\n%s %s\nnar. %d, ", krstne_meno, priezvisko, rok);
				printf("%s\nAutomobil: %s\n", check_gender(pohlavie), znacka);
				printf("\nCasy okruhov: ");
				for(i=0; i<MAX_RACE_ROUNDS; i++)
				{
					if(i == MAX_RACE_ROUNDS-1)
					{
						printf("%.3f\n", casy[i]); // Novi riadok ak je posledne kolo
					}
					else
					{
						printf("%.3f;", casy[i]);
					}
				}
				printf("\n");
				printf("Najlepsie kolo: %.3f\n",najlepsieKolo(casy));	// Pri vypise sa vola pomocna funkcia na vypocet najlepsieho kola
				printf("Najhorsie kolo: %.3f\n",najhorsieKolo(casy));	// Najlepsie kolo
				printf("Priemerne kolo: %.3f\n",priemerneKolo(casy));	// Priemerne kolo
				jazdec_najden = 1; // Pomocna premenna, zmeni sa hodnota na 1 ak sme nasli jazdca
			}
		}
		else
		{
			printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok); // Ak kontrola udajov nasla chybu, vypise sa sprava
			break;
		}
	}

	if(jazdec_najden == 0) // Ak funkcia nenasla jazdca, vypise sa tato sprava
	{
		printf("Jazdec s priezviskom \"%s\" nebol najden v subore.\n", priezvisko_najst);
	}
	else
	{
		functionEnd();		// Ak sme nasli jazdca, nakresli ciaru
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(priezvisko_najst);
}

int lap(void)		// Funkcia vypise informacie o jazdcovi ktore ma najlepsie kolo od vsetkych zo suboru
{
	/* premenne */
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int rok, i, kolo, riadok=0;
	
	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));

	/* Najprv otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	printf("\tFunkcia Lap:\n");
	// Postup nacitania zo suboru je podobny v kazdej funkcie ktora potrebuje vypis vsetkych udajov
	while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
	{
		riadok++;
		krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko); // Tato pomocna funkcia oddeluje krstne meno a priezvisko
		
		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy)) 	// Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane
		{
			for(i=0 ;i<MAX_RACE_ROUNDS; i++) // For cyklus prejde cez vsetky kola a pamata do premenne najlepsi_cas to najlepsie
			{
				if(najlepsi_cas >= casy[i])
				{
					najlepsi_cas = casy[i];
					kolo = i+1;						// Zapise sa poradie do premenne kolo
					strcpy(jazdec, meno_priezvisko); // Zapise sa meno a priezvisko jazdca s najlepsim casom do premenne jazdec
				}
			}
		}
		else
		{
			printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
			break;
		}
	}
	if(jazdec != NULL && najlepsi_cas != 1000) // Ak sme spravne nasli jazdca, vypisu sa informacie 
	{
		printf("\nNajlepsie kolo: %.3f\n",najlepsi_cas);
		printf("Jazdec: %s\n", jazdec);
		printf("Cislo kola: %d\n", kolo);
		functionEnd(); // Nakresli ciaru
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int gender(void)	// Funkcia vypise najlepsie kolo a jazdca pre vsetky znacky auta
{
	/* premenne */
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie, pohlavie_najst;
	int rok, i, kolo, riadok=0;

	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	
	/* Najprv otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	/* Funkcia na zaciatku vypise spravu aby sme vlozili dalsi vstup */
	printf("\tFunkcia Gender:\n>Vlozte pohlavie jazdca, \'m\' alebo \'f\': ");
	scanf(" %c", &pohlavie_najst);
	/* Ked sme dostali ziadany vstup otestujeme ci je spravny, resp. ci je m alebo f, ak nie program nepokracuje a vypise spravu o chybe */
	if(pohlavie_najst == 'm' || pohlavie_najst == 'f')
	{
		// Postup nacitania zo suboru je podobny v kazdej funkcie ktora potrebuje vypis vsetkych udajov: 
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			riadok++;
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);		// Tato pomocna funkcia oddeluje krstne meno a priezvisko

			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy))	// Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane
			{
				if(pohlavie_najst == pohlavie)		// Ak sa rovna pohlavie, funkcia pokracuje
				{
					for(i=0 ;i<MAX_RACE_ROUNDS; i++)  // For cyklus prejde cez vsetky kola a pamata meno, kolo a najlepsi cas
					{
						if(najlepsi_cas >= casy[i])
						{
							najlepsi_cas = casy[i];
							kolo = i+1;
							strcpy(jazdec, meno_priezvisko);
						}
					}	
				}
			}
			else
			{
				printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok); 
				break;
			}
		}
		if(jazdec[0] != '\0' && najlepsi_cas != 1000) // Podmienky pre vypis najlepsieho jazdca
		{
			printf("\nNajlepsie kolo: %.3f\n",najlepsi_cas);
			printf("Jazdec: %s\n", jazdec);
			printf("Cislo kola: %d\n", kolo);
			functionEnd(); // Nakresli ciaru
		}
	}
	else
	{
		printf("Funkcia Gender: Nespravny vstup! Povolene pismena su \'m\' alebo \'f\'.\n");
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int brand(void)		// Funkcia vypise najlepsie kolo a jazdca pre kazdu znacky zvlast
{
	/* premenne */
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL, *znacky, *znacka_compare;
	char pohlavie;
	int rok, i, j, kolo, existuje = 0;
	
	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	znacky =(char *)malloc(MAX_CAR_BRANDS * CAR_BRAND * sizeof(*znacky));
	znacka_compare = (char *)malloc(CAR_BRAND * sizeof(char));
	
	/* Do retazca znacky ukladame vsetky mozne znacky */
	strcpy(znacky+0*CAR_BRAND, "bugatti");
	strcpy(znacky+1*CAR_BRAND, "ferrari");
	strcpy(znacky+2*CAR_BRAND, "porsche");
	strcpy(znacky+3*CAR_BRAND, "honda");
	
	/* Otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Brand:\n\n");
	/* Funkcia cita subor 4 krat lebo hlada a porovnava udaje pre 4 rozne znacky auta */
	for(i=0; i<MAX_CAR_BRANDS; i++)
	{
		rewind(fp);	// Vrati kurzor na zaciatok suboru
		strcpy(znacka_compare, znacky+i*CAR_BRAND); // Ulozime znacku v poradi do premenne znacka_compare a pouzime ju pre porovnavanie
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			if(strcmp(znacka_compare, znacka) == 0)	// Porovnavame znacku auta so znackou v subore, mozno by bolo lepsie strcmp(znacky+ i*CAR_BRAND, znacka)
			{	
				for(j=0; j<MAX_RACE_ROUNDS; j++)	// For cyklus prejde cez vsetky kola a pamata meno, kolo a najlepsi cas
				{
					if(najlepsi_cas >= casy[j])
					{
						najlepsi_cas = casy[j];
						kolo = j+1;
						strcpy(jazdec, meno_priezvisko);
						existuje = 1;		// Ak sme nasli jazdca hodnota 1 za zapise do premenne existuje
					}
				}
			}
		}
		if(existuje)	// Pomocna premena nam pomohla vediet ci program nasiel jazdca pre znacku
		{
			printf("Znacka: %s\n", znacka_compare);
			printf("Najlepsie kolo: %.3f\n",najlepsi_cas);
			printf("Jazdec: %s\n", jazdec);
			printf("Cislo kola: %d\n\n", kolo);
		}
		else // ak nenasiel jazdca, vypise sa sprava ze nenasiel
		{
			printf("Znacka: %s\n", znacka_compare);
			printf("Neexistuje jazdec v zozname.\n\n");
		}
		/* nastavi premenne na default */
		existuje = 0;			
		najlepsi_cas = 1000;
		kolo = 0;
	}
	functionEnd();
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(znacky);
	free(znacka_compare);
}

int year(void)		// Funkcia vypise najlepsie kolo a jazdca pod zadany rok 
{
	/* premenne */
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int rok, i, kolo, riadok=0, najden_jazdec = 0, vstup_rok = 0, rok_n;

	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	
	/* Otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	/* Funkcia ziada od pouzivatela aby vlozil rok */
	printf("\tFunkcia Year:\n>Zadajte rok: ");
	scanf("%d", &vstup_rok);
	
	if(vstup_rok >= MIN_ROK) // Ak je zadany rok vacsi alebo rovny 2020, funkcia nepokracuje
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			riadok++;
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);

			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy))	// Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane 
			{
				if( rok <= vstup_rok)
				{
					for(i=0 ;i<MAX_RACE_ROUNDS; i++) // For cyklus prejde cez vsetky kola a pamata meno, kolo a najlepsi cas
					{
						if(najlepsi_cas >= casy[i])
						{
							najlepsi_cas = casy[i];
							kolo = i+1;
							rok_n = rok;
							strcpy(jazdec, meno_priezvisko);
						}
					}
					najden_jazdec = 1;	
				}
			}
			else
			{
				printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
				break;
			}
		}
		if(najden_jazdec) // Ak sme nasli jazdca vypisu sa informacie, ak nie tak sa vypise ze sme nenasli jazdca
		{
			printf("\n%s\n", jazdec);
			printf("nar. %d\n", rok_n);
			printf("Najlepsie kolo: %.3f\n",najlepsi_cas);
			printf("Cislo kola: %d\n", kolo);
			functionEnd();	// Nakresli ciaru
		}
		else
		{
			printf("Nenasli sme najlepsie.\n");
		}
	}
	else	// Funkcia KontrolaUdajov ukonci program ak nie je dodrziavan format YYYY
	{
		if(vstup_rok < 1000)
		{
			printf("Funkcia Year: Nespravny vstup! Vstup musi byt vo formate \"YYYY\".\n");
		}
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int average(void)	// Funkcia vypise priemer vsetkych jazdcov a na konci vypise jazdca s najlepsim priemerom
{
	/* premenne */
	FILE *fp;
	float *casy = NULL, priemer_jazdca = 0, najlepsie_priemerne = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int rok, kolo, riadok=0;

	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	
	/* Otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	printf("\tFunkcia Average:\nVypis priemernych kol: \n\n");
	
	while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
	{
		riadok++;
		krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);

		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy))	// Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane 
		{
			priemer_jazdca = priemerneKolo(casy);							// Do premenne priemer_jazdca sa zapise priemer nacitanych kol 
			printf("%s - %.3f\n", meno_priezvisko, priemer_jazdca);			// Vypise sa jazdec a jeho priemer
			
			/* Pametame najlepsi priemer a jazdca */
			if(najlepsie_priemerne >= priemer_jazdca)						
			{
				strcpy(jazdec, meno_priezvisko);
				najlepsie_priemerne = priemer_jazdca;
			}
		}
		else
		{
			printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
			break;
		}
	}
	if(jazdec[0] != '\0' ) // Ak sme uspesne zapisali jazdca s najlepsim priemerom vypiseme ho
	{
		printf("\nNajlepsie:\n");
		printf("%s - %.3f\n", jazdec, najlepsie_priemerne);
		functionEnd(); // Nakresli ciaru
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int under(void)		// Funkcia vypise kazdeho jazdca v subore a ich kola ak su pod vlozenou hodnotou
{
	/* premenne */
	FILE *fp;
	float *casy = NULL, realne_cislo;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int i, rok, kola, vypis_casov, riadok=0;

	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));

	/* Otvorime subor a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	/* Funkcia najprv ziada od pouzivatela aby vlozil hodnotu */
	printf("\tFunkcia Under: Vypis kol pod vlozenou hodnotou.\n>Zadajte hodnotu: ");
	scanf("%f", &realne_cislo);
	putchar('\n');
	if(realne_cislo > 0) // Ak vlozena hodnota nie je 0, program pokracuje
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			riadok++;
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
	
			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy)) // Pomocna funkcia kontroluje ci su vsetky udaje spravne nacitane 
			{
				kola = 0;
				printf("%s - ", meno_priezvisko); 
				for(i=0; i<MAX_RACE_ROUNDS; i++)	// For cyklus aby sme nasli pocet kol ktore su pod vlozenou hodnotou
				{
					if(realne_cislo >= casy[i])
					{
						kola++;
					}
				}
				/* Gramaticky spravne vypisy pre pocet kol :) */
				if(kola > 1 && kola < MAX_RACE_ROUNDS)
				{
					printf("%d kola, ", kola);
				}
				else if(kola == 0)
				{
					printf("%d kol\n", kola);
				}
				else if(kola == 1)
				{
					printf("%d kolo, ", kola);
				}
				else
				{	
					printf("%d kol, ", kola);
				}
				
				vypis_casov = kola;
				kola = 1;
				for(i=0; i<MAX_RACE_ROUNDS ;i++)	// For cyklus na vypis poradia kol a ich hodnoty
				{
					if(realne_cislo >= casy[i] ) 
					{
						if(vypis_casov == kola) 	// Ak je posledne tak novy riadok
						{
							printf("%d (%.3f)\n", i+1, casy[i]);	
						}
						else
						{
							printf("%d (%.3f), ", i+1, casy[i]);
							kola++;
						}
					}
				}
			}
			else
			{
				printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
				break;
			}
		}
	functionEnd();		// Nakresli ciaru
	}
	else
	{
		printf("Funkcia Under: Chyba! Cislo musi byt vacsie od 0.\n"); 	// Sprava ak pouzivatel vlozi hodnotu mensiu alebo rovnu 0
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Uvolnime pouzitu pamat */
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}
int change(void)	// Funkcia aktualizuje novi cas jazdca ktoreho zada pouzivatel
{
	/* premenne */
	FILE *fp, *fp_tmp;
	
	float *casy = NULL, cas_zmena;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *buffer = NULL, *priezvisko_zmena = NULL;
	char pohlavie;
	int rok, kolo_zmena, i, jazdec_najden = 0, chyba = 1;
	long int pozicia=0;
	
	/* Alokovanie premmenych */
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	buffer = (char *)malloc(1000 * sizeof(char));
	priezvisko_zmena = (char *)malloc(SURNAME * sizeof(char));
	
	/* Otvorime subor pre citanie a vymenu udajov, a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "r+");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	/* Funkcia ziada od pouzivatela aby vlozil Priezvisko jazdca ktoreho chce zmenit */
	printf("\tFunkcia Change:\n");
	printf(">Zadajte priezvisko jazdca pre zmenu: ");
	scanf("%s", priezvisko_zmena);
	
	if(priezvisko_zmena[0] != '\0') // Ak premenna nie je prazdna, program pokracuje
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko); // Kontrola nacitanych udajov zo suboru
			
			if(strcmp(priezvisko, priezvisko_zmena) == 0) // Ak najdeme jazdca, program pokracuje
			{
				jazdec_najden = 1;	// Nasli sme jazdca, ciel tejto premenne je ze ak najdeme jazdca a potom program nepokracuje, nevypise ze nenasiel jazdca
				printf("Nasli sme jazdca!\n>Zadajte kolo ktore chcete zmenit: ");
				scanf("%d", &kolo_zmena);
				if(kolo_zmena > 0 && kolo_zmena <= MAX_RACE_ROUNDS)		// Zadane kolo musi byt od 1 - 5, ak nie program nepokracuje 
				{
					printf(">Zadajte novi cas: "); // Ak je splnena podmienka ideme na dalsi vstup a to je novi cas
					scanf("%f", &cas_zmena);
				}
				else
				{
					printf("CHYBA! Kolo na zmenu musi byt iba od 1 do 5.\n");
					break;
				}
				if((cas_zmena > 10) && (cas_zmena < 100)) // Ak je novi cas dvojciferne cislo, program pokracuje
				{
					pozicia = ftell(fp);		// ftell zisti poziciu v subore 
					pozicia -= 37;				// odpocitame od sucasne pozicie 37 znakov, lebo format v subore casy je 37 znakov
					fseek(fp, pozicia, SEEK_SET);		// nastavime kurzor na danu poziciu
					for(i=0; i<MAX_RACE_ROUNDS; i++)	// For cylus ktory zapise do suboru novi cas na zadanu poziciu
					{
						if(i == (kolo_zmena-1))
						{
							fprintf(fp, ";%.3f", cas_zmena);
						}
						else
						{
							fprintf(fp, ";%.3f", casy[i]);
						}
					}
					fprintf(fp, "\n");
					chyba = 0;		// Ak program skoncil hodnota premenne chyba bude 0
					break;
				}
				else
				{
					printf("CHYBA! Novy cas musi byt dvojciferne cislo.\n");

				}
			}	
		}			
	}
	
	if(jazdec_najden == 0) // Ak nenasiel jazdca, vypise sa sprava
	{
		printf("Jazdec s priezviskom \"%s\" nebol najden v tabulke.\n", priezvisko_zmena);
	}
	
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	if(!chyba)
	{
		printf("Uspesne sa zmenili udaje!\n");
		functionEnd();
		sum();
	}
	/* Uvolnime pouzitu pamat */
	free(priezvisko_zmena);
	free(meno_priezvisko);
	free(krstne_meno);
	free(priezvisko);
	free(casy);
	free(znacka);
	free(buffer);
}

int newdriver(void)	// Funkcia vlozi noveho jazdca do suboru
{
	/* premenne */
	FILE *fp;
	char *meno_priezvisko = NULL, *new_meno = NULL, *new_priezvisko = NULL, *new_znacka = NULL, *buffer = NULL;
	char *new_pohlavie = NULL;
	float *new_casy = NULL;
	int i, new_rok, zapis_jazdca = 1 ;

	/* Alokovanie premmenych */
	new_casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	new_meno = (char *)malloc(NAME * sizeof(char));
	new_priezvisko = (char *)malloc(SURNAME * sizeof(char));
	new_znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	new_pohlavie = (char *)malloc(2 * sizeof(char));
	buffer = (char *)malloc(1000 * sizeof(char));
	
	/* Otvorime subor na pridanie noveho jazdca, a otestujeme ci sa otvoril */
	fp = fopen(SUBOR, "a+");
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	/* Zacina funkcia newdriver, dal som do while cyklu lebo som chcel aby funkcia nepokracovala ak pouzivatel vlozi nejake blbosti */
	while(zapis_jazdca != 0)
	{
		printf("\tFunkcia New Driver:\nZadajte informacie pre noveho jazdca.\n>Meno a Priezvisko: ");
		scanf(" %[^\n]", meno_priezvisko);
		krstneMenoPriezvisko(meno_priezvisko, new_meno, new_priezvisko);

		if(new_priezvisko[0] != '\0' && new_meno[0] != '\0') // Ak existuju meno a priezvisko, program pokracuje
		{
			printf(">Rok narodenia(YYYY): ");					// Vlozime rok 
			scanf("%d", &new_rok);
		}
		else 
		{   
			printf("CHYBA! Musite spravne zapisat meno a priezvisko.\n"); // Ak neexistuje meno tak funkcia nepokracuje
			break;
		}
		
		if(new_rok < 1000 || new_rok > MAX_ROK)	// Ak je rok nespravne zapisany, funkcia nepokracuje
		{
			printf("CHYBA! Rok musi byt vo formate YYYY a mensi ako 2021.\n"); 
			break;
		}
		else
		{
			printf(">Pohlavie - 'm' alebo 'f': ");				// Vlozime pohlavie
			scanf(" %s", new_pohlavie);
		}
		if(new_pohlavie[0] == 'm' || new_pohlavie[0] == 'f')	// Ak je pohlavie m alebo f, pokracujeme vlozit znacku auta
		{
			printf(">Znacku auta: ");							// Vlozime znacku
			scanf("%s", new_znacka);
		}
		else
		{
			printf("CHYBA! Povolene pismena su \'m\' alebo \'f\'.");
			break;
		}
		if(kontrolaZnackeAuta(new_znacka))		// Ak je znacka rozna ako 4 mozne znacky tak program nepokracuje
		{
			printf(">Pet hodnot vo formate\n>\"cas1;cas2;cas3;cas4;cas5\" : ");	// Vlozime 5 novych hodnot pre casy 
			scanf("%f;%f;%f;%f;%f", &new_casy[0], &new_casy[1], &new_casy[2], &new_casy[3], &new_casy[4]);
			/* Ak sme nejaku hodnotu nezadali, ideme na for cyklus a zapisujeme ju - program ne konci ak sa pouzivatel dostane do tohto bodu */
			for(i=0; i<MAX_RACE_ROUNDS; i++) 
			{
				if(new_casy[i] < 10) // Musi byt dvojciferne cislo aby sa dodrziaval format
				{
					printf("Nezapisali ste dobre %d cas.\nZapiste este raz: ", i+1);
					scanf("%f", &new_casy[i]);
					i--;	// zmensi za i pre istotu ak pouzivatel vlozil zlu hodnotu znovu
					continue;
				}
				else if(new_casy[i] >= 100)
				{
					printf("Nezapisali ste dobre %d cas.\nZapiste este raz: ", i+1);
					scanf("%f", &new_casy[i]);
					i--;
					continue;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			printf("CHYBA! Mozne znacky su: bugatti, ferrari, porsche a honda."); // Sprava pre vypis ak je vlozena znacka ina ako povolena
			break;
		}
		
		while(1)	// Ak program neskoncil do teraz, znamena ze mame vsetky udaje a ideme na koniec suboru aby sme ich zapisali 
		{
			fgets(buffer, 1000, fp); // Kazdy riadok dame do buffera lebo nepotrebujeme tieto informacie
			if(buffer[strlen(buffer) - 1] != '\n') // Ak sa na koniec riadku nenachadza '\n' pridame ho, aby subor pekne vyzeral :)
			{
				fprintf(fp, "\n");
			}
			if(feof(fp))	// Ak sme na koniec suboru, zapiseme noveho jazdca a funkcia skonci while cyklus
			{
				fprintf(fp, "%s %s;%c;%d;%s;%.3f;%.3f;%.3f;%.3f;%.3f", new_meno, new_priezvisko, new_pohlavie[0], new_rok, new_znacka,
																	 new_casy[0],new_casy[1],new_casy[2],new_casy[3],new_casy[4]);
				fprintf(fp, "\n");
				break;
			} 
		}
		zapis_jazdca--;	// Tato premenna sa zmensi ak sme zapisali jazdca
	}
	/* Zatvarame subor a testujeme ci sa zatvoril */
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	
	if(zapis_jazdca == 0) // Ak je 0, novi jazdec je zapisany a zavolame funkciu sum. Na konci bude novi jazdec
	{
		sum();
	}
	/* Uvolnime pouzitu pamat */
	free(new_casy);
	free(meno_priezvisko);
	free(new_priezvisko);
	free(new_meno);
	free(new_znacka);
	free(buffer);
}

int rmdriver(void)	// Funkcia zmaze zadaneho jazdca zo suboru
{
	/* premenne */
	FILE *fp, *fp_tmp;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *buffer = NULL, *priezvisko_zmazat = NULL;
	int jazdec_najden = 0;

	/* Alokovanie premmenych */
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	buffer = (char *)malloc(1000 * sizeof(char));
	priezvisko_zmazat = (char *)malloc(SURNAME * sizeof(char));

	/* Otvorime subory a otestujeme ci sa otvorili */
	fp = fopen(SUBOR, "r");
		if(fp == NULL)
		{
			printf("Subor sa nepodarilo otvorit.\n");
			return 0;
		}
	fp_tmp = fopen(TEMPORARY, "w");
		if(fp_tmp == NULL)
		{
			printf("Subor sa nepodarilo otvorit.\n");
			return 0;
		}
	
	/* Pre tuto funkciu potrebujeme aj temporary subor do ktoreho ukladame jazdcov ale okrem toho ktoreho chceme zmazat */
	printf("\tFunkcia Remove Driver:\n");
	printf("Zadajte priezvisko jazdca ktoreho chcete odstranit z tabulke: ");		// Funkcia najprv ziada od pouzivatela o priezvisko jazdca ktore ma zmazat zo suboru
	scanf("%s", priezvisko_zmazat);
	
	if(priezvisko_zmazat != NULL) // Ak pouzivatel zadal spravne priezvisko, funkcia pokracuje
	{
		while((fscanf(fp, "%[^;]%s\n",meno_priezvisko, buffer)) != EOF)
		{
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko); // Oddelime meno a priezvisko
			
			if(strcmp(priezvisko, priezvisko_zmazat) != 0)		// Porovnavame jazdcov a hladame toho jazdca ktoreho chceme zmazat
			{
				fprintf(fp_tmp,"%s %s%s\n", krstne_meno, priezvisko, buffer);	// Ak sa priezviska nerovnaju, vypisuju sa udaje do noveho suboru
			}
			else
			{
				printf("Jazdec s menom \"%s %s\" bol vymazany.\n", krstne_meno, priezvisko);	// Ak sme nasli jazdca, funkcia jednoducho pokracuje a do noveho suboru sa nezapise jazdec so zadanim priezviskom
				functionEnd();				// Nakresli ciaru
				jazdec_najden++;			// Nasli sme jazdca, a tato premenna potom nie je 0
			}	
		}
	}
	else
	{
		printf("CHYBA! Zadajte priezvisko.\n");	//Ak puzivatel zadal iba pismeno, vypise sa tato sprava
	}
	if(jazdec_najden == 0)
	{
		printf("Jazdec s priezviskom \"%s\" nebol najden v tabulke.\n", priezvisko_zmazat); // Ak funkcia nenasla zadane priezvisko, vyspise sa tato sprava
	}
	/* Zatvarame subory a testujeme ci sa zatvorili */
	if(fclose(fp_tmp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	if(fclose(fp) == EOF )
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	/* Vymazeme temporary subor a nastavime jeho meno na ten co pouzivame */
	remove(SUBOR);
	rename(TEMPORARY,SUBOR);
	remove(TEMPORARY);
	/* Uvolnime pouzitu pamat */
	free(priezvisko_zmazat);
	free(meno_priezvisko);
	free(krstne_meno);
	free(priezvisko);
	free(buffer);
}

void krstneMenoPriezvisko(char *meno_priezvisko, char *krstne_meno, char *priezvisko) // Funkcia oddeli meno a priezvisko
{
	int i, j, n;
	n = strlen(meno_priezvisko);	// Velkost retazca
	j = n;

	for(i=n-1; i>=0; i--)
	{
		if(meno_priezvisko[i] != ' ')	// Hlada medzeru, a ak najde zapamata poziciu a ukonci cyklus
		{
			j--;
		}
		else
		{
			j--;
			break;
		}
	}
	if(j != 0)	//Ak nenasiel medzeru, neoddeluje nic
	{
		for(i=0; i<n; i++)
		{
			krstne_meno[i] = '\0';
		}
		for(i=0; i<j; i++)
		{
			krstne_meno[i] = meno_priezvisko[i];
		}
		
		for(i=0; i<n-j; i++)
		{
			priezvisko[i] = meno_priezvisko[i+j+1];
		}
	}
	else
	{
		priezvisko[0] = '\0';  //Nastavi na biele znaky ak funkcia nic neurobi
		krstne_meno[0] = '\0';
	}
}

int kontrolaZnackeAuta(char *znacka)	// Funkcia kontroluje nacitanu znacku
{
	if(strcmp(znacka, "bugatti") == 0)	// Porovnava ci nacitana znacka existuje v zozname moznych znaciek a vrati 1 ak je
	{
		return 1;
	}
	else if(strcmp(znacka, "porsche") == 0)
	{
		return 1;
	}
	else if(strcmp(znacka, "ferrari") == 0)
	{
		return 1;
	}
	else if(strcmp(znacka, "honda") == 0)
	{
		return 1;
	}
	else
	{
		return 0;	// Vrati 0 ak neexistuje znacka
	}
}

int kontrolaUdajov(char* krstne_meno, char* priezvisko, char pohlavie, int rok, char* znacka, float *casy)	// Funkcia kontroluje vsetky udaje ci nie su NULL
{
	if(krstne_meno != NULL && priezvisko != NULL && rok > MIN_ROK && rok <= MAX_ROK && (pohlavie == 'm' || pohlavie == 'f') && 
		znacka != NULL && kontrolaZnackeAuta(znacka) != 0 && casy != NULL  )
		{
			return 1;
		}
		else 
		{
			return 0;
		}
}

float najlepsieKolo(float *casy) 	// Funkcia vrati najlepsie kolo z 5 moznych
{
	int i;
	float najlepsie = casy[0];
	for(i=1; i<MAX_RACE_ROUNDS; i++)
	{
		if(najlepsie > casy[i])
		{
			najlepsie = casy[i];
		}
	}
	return najlepsie;
}

float najhorsieKolo(float *casy)	// Funkcia vrati najhorsie kolo z 5 moznych
{
	int i;
	float najhorsie = casy[0];
	for(i=1; i<MAX_RACE_ROUNDS; i++)
	{
		if(najhorsie < casy[i])
		{
			najhorsie = casy[i];
		}
	}
	return najhorsie;
}

float priemerneKolo(float *casy)	// Funkcia vrati priemerne kolo
{
	int i;
	float priemer=0;
	for(i=0; i<MAX_RACE_ROUNDS; i++)
	{
		priemer += casy[i];
	}
	return priemer/MAX_RACE_ROUNDS;
}

void moznosti(void)					// Funkcia vypise moznosti pre pouzivatela
{
	printf("Moznosti pre pouzivatela:\n");
	printf("\tPrikaz \"s\" - Funkcia sum(): Vypis hodnot\n");
	printf("\tPrikaz \"d\" - Funkcia driver(): Vypis hodnot podla priezviska detail jazdca\n");
	printf("\tPrikaz \"l\" - Funkcia lap(): Vypis najlepsieho kola\n");
	printf("\tPrikaz \"g\" - Funkcia gender(): Vypis najlepsieho kola - Muz alebo Zena\n");
	printf("\tPrikaz \"b\" - Funkcia brand(): Vypis najlepsieho kola podla znaciek\n");
	printf("\tPrikaz \"y\" - Funkcia year(): Vypis najlepsieho kola - starsi ako rok z inputu\n");
	printf("\tPrikaz \"a\" - Funkcia average(): Vypis najlepsieho priemerneho kola\n");
	printf("\tPrikaz \"u\" - Funkcia under(): Vypis jazdcov, ktori dali kolo pod nejaky cas, a hodnoty\n");
	printf("\tPrikaz \"c\" - Funkcia change(): Prepisanie hodnoty nejakeho kola\n");
	printf("\tPrikaz \"n\" - Funkcia newdriver(): Pridanie noveho jazdca a zadanie hodnot\n");
	printf("\tPrikaz \"r\" - Funkcia rmdriver(): Vymazanie jazdca\n");
	printf("\tPrikaz \"m\" - Moznosti pre pouzivatela\n");
	printf("\tPrikaz \"x\" - Ukonci program\n");
	printf("<---------------------------------------------------------------------------------------------->\n");
}

void functionEnd(void)				// Funkcia iba nakresli ciaru :(
{
	printf("------------------------------------------------------/\n");
}


