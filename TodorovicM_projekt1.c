#define _CRT_SECURE_NO_DEPRECATE // pre Visual Studio 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Autor: Miroslav Todorovic
	Cviciaci: Igor Stupavský
	Datum: 28.11.2020
*/

/////////////////////////////////////////////////////
#define SUBOR "tabulka.csv"
#define TEMPORARY "temporary.tmp"
#define NAME_AND_SURNAME 101
#define NAME 61
#define SURNAME 41
#define MIN_ROK 1800
#define MAX_ROK 2020
#define CAR_BRAND 11
#define MAX_CAR_BRANDS 4
#define MAX_RACE_ROUNDS 5
#define check_gender(x)  ( x == 'm' ? "muz" : "zena")
//////////////////////////////////////////////////////

//DEKLARACIA VSETKYCH POUZITYCH FUNKCII 
int sum(void);
int driver(void);
int lap(void);
int gender(void);
int brand(void);
int year(void);
int average(void);
int under(void);
int change(void);
int newdriver(void);
int rmdriver(void);

void krstneMenoPriezvisko(char *meno_priezvisko, char *krstne_meno, char *priezvisko);
void moznosti(void);
void functionEnd(void);

float najlepsieKolo(float *casy);
float najhorsieKolo(float *casy);
float priemerneKolo(float *casy);

int kontrolaUdajov(char* krstne_meno, char* priezvisko, char pohlavie, int rok, char* znacka, float *casy);
int kontrolaZnackeAuta(char *znacka);
///////////////////////////////////////

int main()
{
	int koniec = 1;
	char vstup;
	
	moznosti();
	
	while(koniec != 0)
	{
		printf("\n>");
		scanf(" %c", &vstup);
		switch(vstup)
		{

			case 's': 
				sum(); 
				break;
			case 'd':
				driver();
				break;
			case 'l':
				lap();
				break;
			case 'g':
				gender();
				break;
			case 'b':
				brand();
				break;
			case 'y':
				year();
				break;
			case 'a':
				average();
				break;
			case 'u':
				under();
				break;
			case 'c':
				change();
				break;
			case 'n':
				newdriver();
				break;	
			case 'r':
				rmdriver();
				break;
			case 'm':
				moznosti();
				break;
			case 'x': 
				printf("Koniec programu.\nDovienia."); 
				koniec = 0; 
				break;
			default: 
				printf("Chyba! Nespravny vstup, skuste znovu.\n");
				break;
		}
	}
	
	return 0;
}

int sum(void)
{
	FILE *fp;
	float *casy = NULL;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL;
	char pohlavie;
	int rok, i, riadok=0;
	
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	
	fp = fopen(SUBOR, "r");
		if (fp == NULL)
		{
			printf("Subor sa nepodarilo otvorit.\n");
			return 0;
		}
	
		printf("\tFunkcia Summary: \n\n");
		while ((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie, &rok, znacka, &casy[0], &casy[1], &casy[2], &casy[3], &casy[4])) != EOF)
		{
			riadok++;
			
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
			
			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
			{
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
				printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
				break;
			}
		}
	functionEnd();
	
	if (fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
}

int driver(void)
{
	FILE *fp;
	float *casy = NULL;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *priezvisko_najst = NULL;
	char pohlavie;
	int rok, i, riadok=0, jazdec_najden = 0;

	
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	priezvisko_najst = (char *)malloc(SURNAME * sizeof(char));
	
	fp = fopen(SUBOR, "r");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Driver: \n>Zadajte priezvisko jazdca ktoreho hladate: ");
	scanf("%s", priezvisko_najst);
	
	while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0], &casy[1], &casy[2], &casy[3], &casy[4])) != EOF)
	{
		riadok++;
		krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
		
		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
		{
			if(strcmp(priezvisko, priezvisko_najst) == 0)
			{
				printf("\n%s %s\nnar. %d, ", krstne_meno, priezvisko, rok);
				printf("%s\nAutomobil: %s\n", check_gender(pohlavie), znacka);
				printf("\nCasy okruhov: ");
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
				printf("\n\n");
				printf("Najlepsie kolo: %.3f\n",najlepsieKolo(casy));
				printf("Najhorsie kolo: %.3f\n",najhorsieKolo(casy));
				printf("Priemerne kolo: %.3f\n",priemerneKolo(casy));
				jazdec_najden = 1;
			}
		}
		else
		{
			printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
			break;
		}
	}

	if(jazdec_najden == 0)
	{
		printf("Jazdec s priezviskom \"%s\" nebol najden v subore.\n", priezvisko_najst);
	}
	else
	{
		functionEnd();
	}
	
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(priezvisko_najst);
}

int lap(void)
{
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int rok, i, kolo, riadok=0;
	
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));

	fp = fopen(SUBOR, "r");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Lap:\n");
	while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
	{
		riadok++;
		krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
		
		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
		{
			for(i=0 ;i<MAX_RACE_ROUNDS; i++)
			{
				if(najlepsi_cas >= casy[i])
				{
					najlepsi_cas = casy[i];
					kolo = i+1;
					strcpy(jazdec, meno_priezvisko);
				}
			}
		}
		else
		{
			printf("\tCHYBA: Jazdec cislo %d nie je spravne zapisany v subore.\n", riadok);
			break;
		}
	}
	if(jazdec != NULL && najlepsi_cas != 1000)
	{
		printf("\nNajlepsie kolo: %.3f\n",najlepsi_cas);
		printf("Jazdec: %s\n", jazdec);
		printf("Cislo kola: %d\n", kolo);
		functionEnd();
	}

	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int gender(void)
{
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie, pohlavie_najst;
	int rok, i, kolo, riadok=0;

	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	
	fp = fopen(SUBOR, "r");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Gender:\n>Vlozte pohlavie jazdca, \'m\' alebo \'f\': ");
	scanf(" %c", &pohlavie_najst);
	
	if(pohlavie_najst == 'm' || pohlavie_najst == 'f')
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			riadok++;
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);

			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
			{
				if(pohlavie_najst == pohlavie)
				{
					for(i=0 ;i<MAX_RACE_ROUNDS; i++)
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
		if(jazdec != NULL && najlepsi_cas != 1000)
		{
			printf("\nNajlepsie kolo: %.3f\n",najlepsi_cas);
			printf("Jazdec: %s\n", jazdec);
			printf("Cislo kola: %d\n", kolo);
			functionEnd();
		}
	}
	else
	{
		printf("Funkcia Gender: Nespravny vstup! Povolene pismena su \'m\' alebo \'f\'.\n");
	}
	
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int brand(void)
{
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL, *znacky, *znacka_compare;
	char pohlavie;
	int rok, i, j, kolo, existuje = 0;
	

	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	znacky =(char *)malloc(MAX_CAR_BRANDS * CAR_BRAND * sizeof(*znacky));
	znacka_compare = (char *)malloc(CAR_BRAND * sizeof(char));
	
	strcpy(znacky+0*CAR_BRAND, "bugatti");
	strcpy(znacky+1*CAR_BRAND, "ferrari");
	strcpy(znacky+2*CAR_BRAND, "porsche");
	strcpy(znacky+3*CAR_BRAND, "honda");
	
	fp = fopen(SUBOR, "r");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Brand:\n\n");
	for(i=0; i<MAX_CAR_BRANDS; i++)
	{
		rewind(fp);	
		strcpy(znacka_compare, znacky+i*CAR_BRAND);
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			if(strcmp(znacka_compare, znacka) == 0)
			{	
				for(j=0; j<MAX_RACE_ROUNDS; j++)
				{
					if(najlepsi_cas >= casy[j])
					{
						najlepsi_cas = casy[j];
						kolo = j+1;
						strcpy(jazdec, meno_priezvisko);
						existuje = 1;
					}
				}
			}
		}
		if(existuje)
		{
			printf("Znacka: %s\n", znacka_compare);
			printf("Najlepsie kolo: %.3f\n",najlepsi_cas);
			printf("Jazdec: %s\n", jazdec);
			printf("Cislo kola: %d\n\n", kolo);
		}
		else
		{
			printf("Znacka: %s\n", znacka_compare);
			printf("Neexistuje jazdec v zozname.\n\n");
		}
		existuje = 0;
		najlepsi_cas = 1000;
		kolo = 0;
	}
	functionEnd();
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(znacky);
	free(znacka_compare);
}

int year(void)
{
	FILE *fp;
	float *casy = NULL, najlepsi_cas = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int rok, i, kolo, riadok=0, najden_jazdec = 0, vstup_rok = 0, rok_n;

	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	
	fp = fopen(SUBOR, "r");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Year:\n>Zadajte rok: ");
	scanf("%d", &vstup_rok);
	
	if(vstup_rok >= MIN_ROK)
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			riadok++;
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);

			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
			{
				if( rok <= vstup_rok)
				{
					for(i=0 ;i<MAX_RACE_ROUNDS; i++)
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
		if(najden_jazdec)
		{
			printf("\n%s\n", jazdec);
			printf("nar. %d\n", rok_n);
			printf("Najlepsie kolo: %.3f\n",najlepsi_cas);
			printf("Cislo kola: %d\n", kolo);
			functionEnd();	
		}
		else
		{
			printf("Nenasli sme najlepsie.\n");
		}
	}
	else
	{
		if(vstup_rok < 1000)
		{
			printf("Funkcia Year: Nespravny vstup! Vstup musi byt vo formate \"YYYY\".\n");
		}
	}
	
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int average(void)
{
	FILE *fp;
	float *casy = NULL, priemer_jazdca = 0, najlepsie_priemerne = 1000;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int rok, kolo, riadok=0;

	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	
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

		if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
		{
			priemer_jazdca = priemerneKolo(casy);
			printf("%s - %.3f\n", meno_priezvisko, priemer_jazdca);
			
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
	if(jazdec != NULL )
	{
		printf("\nNajlepsie:\n");
		printf("%s - %.3f\n", jazdec, najlepsie_priemerne);
		functionEnd();
	}
	
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}

int under(void)
{
	FILE *fp;
	float *casy = NULL, realne_cislo;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *jazdec = NULL;
	char pohlavie;
	int i, rok, kola, vypis_casov, riadok=0;

	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	jazdec = (char *)malloc(NAME_AND_SURNAME * sizeof(char));

	
	fp = fopen(SUBOR, "r");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	printf("\tFunkcia Under: Vypis kol pod vlozenou hodnotou.\n>Zadajte hodnotu: ");
	scanf("%f", &realne_cislo);
	putchar('\n');
	if(realne_cislo > 0)
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			riadok++;
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
	
			if(kontrolaUdajov(krstne_meno, priezvisko, pohlavie, rok, znacka, casy) != 0) 
			{
				kola = 0;
				printf("%s - ", meno_priezvisko);
				for(i=0; i<MAX_RACE_ROUNDS; i++)
				{
					if(realne_cislo >= casy[i])
					{
						kola++;
					}
				}
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
				for(i=0; i<MAX_RACE_ROUNDS ;i++)
				{
					if(realne_cislo >= casy[i] )
					{
						if(vypis_casov == kola)
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
	functionEnd();
	}
	else
	{
		printf("Funkcia Under: Chyba! Cislo musi byt vacsie od 0.\n");
	}
	
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	free(casy);
	free(meno_priezvisko);
	free(priezvisko);
	free(krstne_meno);
	free(znacka);
	free(jazdec);
}
int change(void)
{
	FILE *fp, *fp_tmp;
	
	float *casy = NULL, cas_zmena;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *znacka = NULL, *buffer = NULL, *priezvisko_zmena = NULL;
	char pohlavie;
	int rok, kolo_zmena, i, jazdec_najden = 0, chyba = 1;
	long int pozicia=0;
	
	casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	buffer = (char *)malloc(1000 * sizeof(char));
	priezvisko_zmena = (char *)malloc(SURNAME * sizeof(char));
	
	fp = fopen(SUBOR, "r+");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	printf("\tFunkcia Change:\n");
	printf(">Zadajte priezvisko jazdca pre zmenu: ");
	scanf("%s", priezvisko_zmena);

	
	if(priezvisko_zmena != NULL)
	{
		while((fscanf(fp, "%[^;];%c;%d;%[^;];%f;%f;%f;%f;%f\n",meno_priezvisko, &pohlavie ,&rok, znacka, &casy[0],&casy[1],&casy[2],&casy[3],&casy[4])) != EOF)
		{
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
			if(strcmp(priezvisko, priezvisko_zmena) == 0)
			{
				jazdec_najden = 1;
				printf("Nasli sme jazdca!\n>Zadajte kolo ktore chcete zmenit: ");
				scanf("%d", &kolo_zmena);
				if(kolo_zmena > 0 && kolo_zmena <= MAX_RACE_ROUNDS)
				{
					printf(">Zadajte novi cas: ");
					scanf("%f", &cas_zmena);
				}
				else
				{
					printf("CHYBA! Kolo na zmenu musi byt iba od 1 do 5.\n");
					break;
				}
				if((cas_zmena > 10) && (cas_zmena < 100))
				{
					pozicia = ftell(fp);
					pozicia -= (45 + strlen(meno_priezvisko) + strlen(znacka));
					fseek(fp, pozicia, SEEK_SET);
					fprintf(fp, "%s %s;%c;%d;%s", krstne_meno, priezvisko, pohlavie ,rok, znacka);
					for(i=0; i<MAX_RACE_ROUNDS; i++)
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
					chyba = 0;
					break;
				}
				else
				{
					printf("CHYBA! Novy cas musi byt dvojciferne cislo.\n");

				}
			}	
		}			
	}
	
	if(jazdec_najden == 0)
	{
		printf("Jazdec s priezviskom \"%s\" nebol najden v tabulke.\n", priezvisko_zmena);
	}
	
	
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
	free(priezvisko_zmena);
	free(meno_priezvisko);
	free(krstne_meno);
	free(priezvisko);
	free(casy);
	free(znacka);
	free(buffer);
}

int newdriver(void)
{
	FILE *fp;
	char *meno_priezvisko = NULL, *new_meno = NULL, *new_priezvisko = NULL, *new_znacka = NULL, *buffer = NULL;
	char *new_pohlavie = NULL;
	float *new_casy = NULL;
	int i, new_rok, zapis_jazdca = 1 ;

	new_casy = (float *)calloc(MAX_RACE_ROUNDS, sizeof(float));
	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	new_meno = (char *)malloc(NAME * sizeof(char));
	new_priezvisko = (char *)malloc(SURNAME * sizeof(char));
	new_znacka = (char *)malloc(CAR_BRAND * sizeof(char));
	new_pohlavie = (char *)malloc(2 * sizeof(char));
	buffer = (char *)malloc(1000 * sizeof(char));
	
	fp = fopen(SUBOR, "a+");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	
	while(zapis_jazdca != 0)
	{
		printf("\tFunkcia New Driver:\nZadajte informacie pre noveho jazdca.\n>Meno a Priezvisko: ");
		scanf(" %[^\n]", meno_priezvisko);
		krstneMenoPriezvisko(meno_priezvisko, new_meno, new_priezvisko);

		if(new_priezvisko[0] != '\0' && new_meno[0] != '\0')
		{
			printf(">Rok narodenia(YYYY): ");
			scanf("%d", &new_rok);
		}
		else 
		{   
			printf("CHYBA! Musite spravne zapisat meno a priezvisko.\n");
			break;
		}
		
		if(new_rok < 1000 || new_rok > MAX_ROK)
		{
			printf("CHYBA! Rok musi byt vo formate YYYY a mensi ako 2021.\n"); 
			break;
		}
		else
		{
			printf(">Pohlavie - 'm' alebo 'f': ");
			scanf(" %s", new_pohlavie);
		}
		if(new_pohlavie[0] == 'm' || new_pohlavie[0] == 'f')
		{
			printf(">Znacku auta: ");
			scanf("%s", new_znacka);
		}
		else
		{
			printf("CHYBA! Povolene pismena su \'m\' alebo \'f\'.");
			break;
		}
		if(kontrolaZnackeAuta(new_znacka))
		{
			printf(">Pet hodnot vo formate\n>\"cas1;cas2;cas3;cas4;cas5\" : ");
			scanf("%f;%f;%f;%f;%f", &new_casy[0], &new_casy[1], &new_casy[2], &new_casy[3], &new_casy[4]);
			for(i=0; i<MAX_RACE_ROUNDS; i++)
			{
				if(new_casy[i] == 0)
				{
					printf("Nezapisali ste dobre %d cas.\nZapiste teraz: ", i+1);
					scanf("%f", &new_casy[i]);
					
					if(new_casy[i] <= 0)
					{
						printf("Stale nie je dobre zapisany.\nZapiste este raz: ");
						scanf("%f", &new_casy[i]);
						i--;
					}
				}
			}
		}
		else
		{
			printf("CHYBA! Mozne znacky su: bugatti, ferrari, porsche a honda.");
			break;
		}
		
		while(1)
		{
			fgets(buffer, 1000, fp);
			if(feof(fp))
			{
				fprintf(fp, "%s %s;%c;%d;%s;%.3f;%.3f;%.3f;%.3f;%.3f", new_meno, new_priezvisko, new_pohlavie[0], new_rok, new_znacka,
																	 new_casy[0],new_casy[1],new_casy[2],new_casy[3],new_casy[4]);
				fprintf(fp, "\n");
				break;
			}
		}
		zapis_jazdca--;	
	}
	
	if(fclose(fp) == EOF)
	{
		printf("Subor sa nepodarilo zatvorit.");
		return 0;
	}
	
	if(zapis_jazdca == 0)
	{
		sum();
	}
	
	free(new_casy);
	free(meno_priezvisko);
	free(new_priezvisko);
	free(new_meno);
	free(new_znacka);
	free(buffer);
}

int rmdriver(void)
{
	FILE *fp, *fp_tmp;
	char *meno_priezvisko = NULL, *krstne_meno = NULL, *priezvisko = NULL, *buffer = NULL, *priezvisko_zmazat = NULL;
	int jazdec_najden = 0;

	meno_priezvisko = (char *)malloc(NAME_AND_SURNAME * sizeof(char));
	krstne_meno = (char *)malloc(NAME * sizeof(char));
	priezvisko = (char *)malloc(SURNAME * sizeof(char));
	buffer = (char *)malloc(1000 * sizeof(char));
	priezvisko_zmazat = (char *)malloc(SURNAME * sizeof(char));

	fp = fopen(SUBOR, "r");
	fp_tmp = fopen(TEMPORARY, "w");
	
	if(fp == NULL)
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	printf("\tFunkcia Remove Driver:\n");
	printf("Zadajte priezvisko jazdca ktoreho chcete odstranit z tabulke: ");
	scanf("%s", priezvisko_zmazat);
	
	if(priezvisko_zmazat != NULL)
	{
		while((fscanf(fp, "%[^;]%s\n",meno_priezvisko, buffer)) != EOF)
		{
			krstneMenoPriezvisko(meno_priezvisko, krstne_meno, priezvisko);
			if(strcmp(priezvisko, priezvisko_zmazat) != 0)
			{
				fprintf(fp_tmp,"%s %s%s\n", krstne_meno, priezvisko, buffer);
			}
			else
			{
				printf("Jazdec s menom \"%s %s\" bol vymazany.\n", krstne_meno, priezvisko);
				functionEnd();
				jazdec_najden++;
			}	
		}
	}
	else
	{
		printf("CHYBA! Zadajte priezvisko.\n");	
	}
	
	if(jazdec_najden == 0)
	{
		printf("Jazdec s priezviskom \"%s\" nebol najden v tabulke.\n", priezvisko_zmazat);
	}
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
	remove(SUBOR);
	rename(TEMPORARY,SUBOR);
	remove(TEMPORARY);
	free(priezvisko_zmazat);
	free(meno_priezvisko);
	free(krstne_meno);
	free(priezvisko);
	free(buffer);
}

void krstneMenoPriezvisko(char *meno_priezvisko, char *krstne_meno, char *priezvisko)
{
	int i, j, n;
	n = strlen(meno_priezvisko);
	j = n;

	for(i=n-1; i>=0; i--)
	{
		if(meno_priezvisko[i] != ' ')
		{
			j--;
		}
		else
		{
			j--;
			break;
		}
	}
	if(j != 0)
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
		priezvisko[0] = '\0'; 
		krstne_meno[0] = '\0';
	}
}

int kontrolaZnackeAuta(char *znacka)
{
	if(strcmp(znacka, "bugatti") == 0)
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
		return 0;
	}
}

int kontrolaUdajov(char* krstne_meno, char* priezvisko, char pohlavie, int rok, char* znacka, float *casy)
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

float najlepsieKolo(float *casy)
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

float najhorsieKolo(float *casy)
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

float priemerneKolo(float *casy)
{
	int i;
	float priemer=0;
	for(i=0; i<MAX_RACE_ROUNDS; i++)
	{
		priemer += casy[i];
	}
	return priemer/MAX_RACE_ROUNDS;
}

void moznosti(void)
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

void functionEnd(void)
{
	printf("------------------------------------------------------/\n");
}


