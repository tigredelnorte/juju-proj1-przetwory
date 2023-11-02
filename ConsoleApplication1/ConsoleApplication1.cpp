#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <locale.h>
#include <string>
#include <windows.h>

void TabWspolczynnikow(double **wspolczynniki)
{
	Sleep(1000);
	printf("Witaj Użytkowniku.\n");
	Sleep(1000);
	printf("Dla funkcji:\n");
	Sleep(1000);
	printf("A*sin(Bx^2+C*x) + D / (x-1) * cos(E*x - F)\n");
	Sleep(1000);
	printf("Podaj w kolejnosci wartości wspolczynnikow A, B, C, D, E, F:\n");
	Sleep(1000);

	*wspolczynniki = (double*)malloc(sizeof(double));
	if (*wspolczynniki == NULL) {
		printf("Błąd alokacji pamięci.\n");
		return; // Wyjście z funkcji w przypadku błędu
	}
	char A = 'A';
	for (int i = 0; i < 6; i++) {
		if (i != 0) *wspolczynniki = (double*)realloc(*wspolczynniki, (i + 2) * sizeof(double)); // Alokacja pamięci na tablicę
		printf("Podaj wartość dla %c: ", A + i);
		scanf("%lf", *wspolczynniki + i); // Wczytywanie wartości do tablicy
		printf("- Przyjęto wartość %.2lf\n", (*wspolczynniki)[i]);
		Sleep(500);

	}

	//printf("A: ");
	//scanf("%lf", *wspolczynniki);
	//if (*wspolczynniki == NULL) {
	//	printf("Błąd alokacji pamięci.\n");
	//	return; // Wyjście z funkcji w przypadku błędu
	//}
	////(*wspolczynniki)[0] = A;
	////printf("%lf", *(wspolczynniki));

	//*wspolczynniki = (double*)realloc(*wspolczynniki, 2 * sizeof(double));
	//printf("B: ");
	//scanf("%lf", *wspolczynniki + 1);
	////(*wspolczynniki)[1] = B; //1

	//*wspolczynniki = (double*)realloc(*wspolczynniki, 3 * sizeof(double));
	//printf("C: ");
	//scanf("%lf", *wspolczynniki + 2);
	////*wspolczynniki + 2 = C; //2

	//*wspolczynniki = (double*)realloc(*wspolczynniki, 4 * sizeof(double));
	//printf("D: ");
	//scanf("%lf", *wspolczynniki + 3);
	////*(wspolczynniki + 3) = D; //3

	//*wspolczynniki = (double*)realloc(*wspolczynniki, (1) * sizeof(double));
	//while (*wspolczynniki + 4 == 0)
	//{
	//	printf("E (nie 0): ");
	//	scanf("%lf", *wspolczynniki + 4);
	//	if(*wspolczynniki + 4 == 0)
	//	{
	//		printf("Dawaj jeszcze raz gamoniu!!!\n");
	//	}
	//}
	////*(wspolczynniki + 4) = E; //4

	//*wspolczynniki = (double*)realloc(*wspolczynniki, (5) * sizeof(double));
	//printf("F: ");
	//scanf("%lf", *wspolczynniki + 5);
	////*(wspolczynniki + 5) = F; //5

	//// 0   1   2   3   4   5 
	//// { } { } { } { } { } { }
	////  wez wartosc do miejsca "0" w tablicy

}

void Dziedzina(double* aMaly, double* aDuzy)
{
	printf("Podaj zakres dziedziny:\nNajmniejszy argument dziedziny: ");
	scanf("%lf", aMaly);
	printf("Największy argument dziedziny: ");
	scanf("%lf", aDuzy);
}

void alokacjaPamieci(double** tabWynikowa, double** tablicaSzum, int* rozmiar)
{
	printf("Podaj rozmiar tablicy/ Podaj ilosc argumentow w funkcji: ");
	scanf("%d", rozmiar);
	if (rozmiar == 0)
	{
		printf("Pusta tablica\n Brak argumentow dla funkcji\n");
	}
	else
		*tabWynikowa = (double*)malloc(*rozmiar * sizeof(**tabWynikowa));
	*tablicaSzum = (double*)malloc(*rozmiar * sizeof(**tablicaSzum));
}

double getSinus(double x, double* wspolczynniki)
{
	//sin(Bx^2+C*x)
	double potega = pow(x, 2);
	double S = *(wspolczynniki + 1) * potega + *(wspolczynniki + 2) * x;
	double wynikSinusa = sin(S);
	return wynikSinusa;
}

double getCosinus(double x, double* wspolczynniki)
{
	//cos(E*x - F)
	double C = *(wspolczynniki + 4) * x - *(wspolczynniki + 5);
	double wynikCosinusa = cos(C);
	return wynikCosinusa;
}

double getFunkcja(double x, double* wspolczynniki)
{
	//printf("Pobrane wartości:\n");
	//for (int i = 0; i < 6; i++) {
	//	printf("Wartość %d: %.2lf\n", i + 1, *(wspolczynniki + i));
	//	printf("Wartość %d: %.2lf\n", i + 1, wspolczynniki[i]);
	//}
	//               A *                         sin(Bx^2+C*x)            + D                 /  (x-1) * cos(E*x - F)
	double funkcja = *(wspolczynniki) * getSinus(x, wspolczynniki) + *(wspolczynniki +3)/ ((x - 1) * getCosinus(x, wspolczynniki));
	return funkcja;
}

void generatorFunkcji(double* wspolczynniki, double aMaly, double* tabWynikowa, int rozmiar, double skokArg)
{
	double biezacyX = aMaly;
	for (int i = 0; i <= rozmiar; i++)
	{
		double wynikFunkcji = getFunkcja(biezacyX, wspolczynniki);
		*(tabWynikowa + i) = wynikFunkcji;
		biezacyX = biezacyX + skokArg;
	}
}

void dziedzinaSzumu(double* aMalySzumu, double* aDuzySzumu)
{
	printf("Podaj zakres dziedziny: \n");
	printf("Najmniejszy argument dziedziny szumu:\n");
	scanf("%lf", aMalySzumu);
	//if ()
	printf("Największy argument dziedziny szumu:\n");
	scanf("%lf", aDuzySzumu);
	while (*aMalySzumu > *aDuzySzumu)
	{
		printf("Najmniejsza wartośc amplitudy szumu jest większa od największej wartości amplitudy szumu.\nPodaj ponownie: \n");
		printf("Najmniejsza wartość amplitudy szumu:\n");
		scanf("%lf", aMalySzumu);
		printf("Największa wartość amplitudy szumu:\n");
		scanf("%lf", aDuzySzumu);
	}
}

void AmplitudaiLosowanieSzumu(double * tabWynikowa, double* tablicaSzum, int rozmiar)
{
	int amplituda = 0, zaszumienie = 0;
	printf("Podaj różną od 0 wartosc wychylenia w amplitudzie:\n");
	while (amplituda == 0)
	{
		scanf("%d", &amplituda);
		if (amplituda == 0)
		{
			printf("Blad, Amplituda musi być różna do 0: \n");
		}
	}

	printf("Podaj prawdopodobienstwo zaszumienia od 0 do 100 procent: ");
	while (zaszumienie == 0)
	{
		scanf("%d", &zaszumienie);
		if (zaszumienie <= 0 || zaszumienie >= 100)
		{
			printf("Blad, Podaj jeszcze raz zaszumienie: \n");
			zaszumienie = 0;

		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		double ampdouble = (double)amplituda;
		if (rand() % 100 < zaszumienie)
		{
			double szum = (rand() % (amplituda + amplituda + 1) - ampdouble);
			*(tablicaSzum + i) = szum;
			printf("%lf\n", szum);
		}
		else
		{
			*(tablicaSzum + i) = 0;
		}
	}
}

//	
//	//srand(time(NULL));
//	int i;
//	for (i = 0; i < 10; i++)
//	{
//		tablicaSzum[i] = rand() % 101 / 100.0;
//	}
//}
	//void wylosowanieSzumu()       
	//{
	//	AmplitudaSzumu();
	//	double losowanie;
	//	losowanie = (rand() % (amplituda) + dolnaAmplituda; //zakres
		//printf("Wylosowany szum z amplitudy to %lf\n", losowanie);
	//void generujLosowySzum(double* tablicaSzum)
	//{
	//	//DziedzinaSzumu(aMalySzumu, aDuzySzumu);
	//	//AmplitudaSzumu(dolnaAmplituda, gornaAmplituda);
	//	
	//	//srand(time(NULL));
	//	int i;
	//	for (i = 0; i < 10; i++)
	//	{
	//		tablicaSzum[i] = rand() % 101 / 100.0;
	//	}
	//}

void zapisDoPliku(double* tablicaSzum, int rozmiar)
{
	FILE* plik;
	int i;
	plik = fopen("losowe.csv", "w");        //plik csv do otworzenia w excel
	if (plik != NULL)
	{
		for (i = 0; i < rozmiar; i++)
		{
			fprintf(plik, "Wylosowana liczba szumu to: %.2lf\n", tablicaSzum[i]);  // frpitnf "wydrukuj plik" //; czyli w nastepnym kolmunach zapisywanie
		}
		fclose(plik);
	}
	else
		printf("Plik nie mogl zostac otwarty");
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "polish_poland");

	double* wspolczynniki = NULL;
	//TabWspolczynnikow(&wspolczynniki);

	// Wypisanie wartości z tablicy
	//printf("Pobrane wartości:\n");
	//for (int i = 0; i < 6; i++) {
	//	printf("Wartość %d: %.2lf\n", i + 1, wspolczynniki[i]);
	//}

	double aMaly, aDuzy;
	Dziedzina(&aMaly, &aDuzy);

	int rozmiar = 0;
	double *tabWynikowa = NULL, *tablicaSzum = NULL;
	alokacjaPamieci(&tabWynikowa, &tablicaSzum, &rozmiar);
	double skokArg = (aDuzy - aMaly) / rozmiar;
	generatorFunkcji(wspolczynniki, aMaly, tabWynikowa, rozmiar, skokArg);
	 //Wypisanie wartości z tablicy
	printf("Tabela wyników:\n");
	for (int i = 0; i < rozmiar; i++) {
		printf("Wartość dla X: %.2lf wynosi: %.2lf\n", aMaly + (i * skokArg), tabWynikowa[i]);
	}

	AmplitudaiLosowanieSzumu(tabWynikowa, tablicaSzum, rozmiar);
	printf("Pobrane wartości:\n");
	for (int i = 0; i < rozmiar; i++) {
	printf("Wartość %d: %.2lf\n", i + 1, tablicaSzum[i]);
	}
	zapisDoPliku(tablicaSzum, rozmiar);
	free(tabWynikowa);
	free(tablicaSzum);
}



//Jedna dziedzina jest losowanie szumu w danej amplitudzie
//Druga dziedzina jest losowanie szansy na wylosowanie wartości szumu
//A trzecia dziedzina mogło by być losowanie dziedziny