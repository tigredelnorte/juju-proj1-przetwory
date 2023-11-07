﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <locale.h>
#include <string>
#include <windows.h>

void wyswietlMenu(char* gwiazdki)
{
	printf("\e[1;1H\e[2J");
	printf("\n**************************************************\n");
	printf("*               Generator funkcji                *\n");
	printf("* y = A*sin(Bx^2+C*x) + D / (x-1) * cos(E*x - F) *\n");
	printf("**************************************************\n");

	printf("\n                    MENU\n");
	printf("1. Zdefiniuj współczynniki A, B, C, D, E, F          [%c]\n", gwiazdki[0]);
	printf("2. Zdefiniuj zakres i ilość argumentów funkcji       [%c]\n", gwiazdki[1]);
	printf("3. Generuj wartości funkcji                          [%c]\n", gwiazdki[2]);
	printf("4. Zdefiniuj i wygeneruj zaszumione wartości funkcji [%c]\n", gwiazdki[3]);
	printf("5. Odczytaj wartości funkcji z pliku\n");
	printf("6. Zapisz wartości funkcji do pliku\n");
	printf("7. Odczytaj wartości funkcji z pliku\n");
	printf("8. Wyjście\n");
	printf("Wybierz opcję (1-8): ");
}
void tabWspolczynnikow(double **wspolczynniki)
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

void dziedzina(double* aMaly, double* aDuzy)
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

double obliczSinus(double x, double* wspolczynniki)
{
	//sin(Bx^2+C*x)
	double potega = pow(x, 2);
	double S = *(wspolczynniki + 1) * potega + *(wspolczynniki + 2) * x;
	double wynikSinusa = sin(S);
	return wynikSinusa;
}

double obliczCosinus(double x, double* wspolczynniki)
{
	//cos(E*x - F)
	double C = *(wspolczynniki + 4) * x - *(wspolczynniki + 5);
	double wynikCosinusa = cos(C);
	return wynikCosinusa;
}

double obliczFunkcje(double x, double* wspolczynniki)
{
	//               A *                         sin(Bx^2+C*x)            + D                 /  (x-1) * cos(E*x - F)
	double funkcja = *(wspolczynniki) * obliczSinus(x, wspolczynniki) + *(wspolczynniki +3)/ ((x - 1) * obliczCosinus(x, wspolczynniki));
	return funkcja;
}

void generatorFunkcji(double* wspolczynniki, double aMaly, double* tabWynikowa, int rozmiar, double skokArg)
{
	double biezacyX = aMaly;
	for (int i = 0; i <= rozmiar; i++)
	{
		double wynikFunkcji = obliczFunkcje(biezacyX, wspolczynniki);
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

void amplitudaiLosowanieSzumu(double * tabWynikowa, double* tablicaSzum, int rozmiar)
{
	// Inicjalizacja generatora liczb losowych
	double procentZaszumienia, amplitudaZaszumienia;

	printf("Podaj procent zaszumienia (0-100): ");
	scanf("%lf", &procentZaszumienia);

	if (procentZaszumienia < 0 || procentZaszumienia > 100) {
		printf("Błędny procent zaszumienia.\n");
		return;
	}

	printf("Podaj amplitudę zaszumienia: ");
	scanf("%lf", &amplitudaZaszumienia);

	for (int i = 0; i < rozmiar; i++) {
		tablicaSzum[i] = tabWynikowa[i]; // Skopiuj oryginalne wyniki

		if ((double)rand() / RAND_MAX * 100.0 < procentZaszumienia) {
			// Wygeneruj losową wartość do zaszumienia z podanej amplitudy
			double zaszumienie = ((double)rand() / RAND_MAX) * amplitudaZaszumienia;

			// Zaszum wynik
			tablicaSzum[i] += zaszumienie;
		}
	}
}

void zapisDoPliku(double* tablicaSzum, int rozmiar)
{
	FILE* plik = fopen("export", "w");

	if (plik == NULL) {
		printf("Błąd otwarcia pliku.\n");
		return;
	}

	for (int i = 0; i < rozmiar; i++) {
		fprintf(plik, "%.2lf\n", tablicaSzum[i]);
	}

	fclose(plik);
	//FILE* plik;
	//int i;
	//plik = fopen("losowe.csv", "w");        //plik csv do otworzenia w excel
	//if (plik != NULL)
	//{
	//	for (i = 0; i < rozmiar; i++)
	//	{
	//		fprintf(plik, "Wylosowana liczba szumu to: %.2lf\n", tablicaSzum[i]);  // frpitnf "wydrukuj plik" //; czyli w nastepnym kolmunach zapisywanie
	//	}
	//	fclose(plik);
	//}
	//else
	//	printf("Plik nie mogl zostac otwarty");
}

void wczytanieZPliku(double* tablicaSzum, int rozmiar)
{

}
void filtrujZSzumu(double* tablicaSzum, int rozmiar) 
{

}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "polish_poland");

	char gwiazdki[4]
	{
		' ', ' ', ' ', ' '
	};
	char star = '*';
	char spacja = ' ';

	int wyborMenu = 0;
	double* wspolczynniki = NULL;
	double aMaly, aDuzy;
	int rozmiar = 0;
	double* tabWynikowa = NULL, * tabSzum = NULL, skokArg = NULL;
	do
	{
		wyswietlMenu(gwiazdki);
		scanf("%d", &wyborMenu);

		switch (wyborMenu) {
		case 1:
			tabWspolczynnikow(&wspolczynniki);
			if (wspolczynniki != NULL) gwiazdki[0] = star;
			break;
		case 2:
			dziedzina(&aMaly, &aDuzy);
			alokacjaPamieci(&tabWynikowa, &tabSzum, &rozmiar);
			skokArg = (aDuzy - aMaly) / rozmiar;
			if (rozmiar != 0) gwiazdki[1] = star;
			break;
		case 3:
			generatorFunkcji(wspolczynniki, aMaly, tabWynikowa, rozmiar, skokArg);
			if (tabWynikowa != NULL) gwiazdki[2] = star;
			//Wypisanie wartości z tablicy
			printf("Tabela wyników:\n");
			for (int i = 0; i < rozmiar; i++) {
				printf("Wartość dla X: %.2lf wynosi: %.2lf\n", aMaly + (i * skokArg), tabWynikowa[i]);
			}
			break;
		case 4:
			amplitudaiLosowanieSzumu(tabWynikowa, tabSzum, rozmiar);
			printf("Pobrane wartości:\n");
			if (tabSzum != NULL) gwiazdki[3] = star;
			for (int i = 0; i < rozmiar; i++) 
			{
				printf("Wartość %d: %.2lf\n", i + 1, tabSzum[i]);
			}
			break;
		case 5:
			zapisDoPliku(tabSzum, rozmiar);
			break;
		case 6:
			wczytanieZPliku(tabSzum, rozmiar);
			break;
		case 7:
			filtrujZSzumu(tabSzum, rozmiar);
			break;
		case 8:
			printf("Program zostanie zakończony.\n");
			break;
		default:
			printf("Nieprawidłowy wybór. Wybierz opcję od 1 do 4.\n");
			break;
		}
	} while (wyborMenu != 8);
	//free(tabWynikowa);
	//free(tablicaSzum);
	return 0;

}
// Wypisanie wartości z tablicy
//printf("Pobrane wartości:\n");
//for (int i = 0; i < 6; i++) {
//	printf("Wartość %d: %.2lf\n", i + 1, wspolczynniki[i]);
//}
//Jedna dziedzina jest losowanie szumu w danej amplitudzie
//Druga dziedzina jest losowanie szansy na wylosowanie wartości szumu
//A trzecia dziedzina mogło by być losowanie dziedziny