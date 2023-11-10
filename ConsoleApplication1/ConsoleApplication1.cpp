#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <locale.h>
#include <string>
#include <windows.h>

void wyswietlMenu(char* gwiazdki)
{
	printf("\n*******************************************************\n");
	printf("*                 Generator funkcji                   *\n");
	printf("* y = A*sin(B*x^2 + C*x) + D / (x - 1) * cos(E*x - F) *\n");
	printf("*******************************************************\n");

	printf("\n                    MENU\n");
	printf("1. Zdefiniuj wspolczynniki A, B, C, D, E, F          [%c]\n", gwiazdki[0]);
	printf("2. Zdefiniuj zakres i ilosc argumentow funkcji       [%c]\n", gwiazdki[1]);
	printf("3. Generuj wartosci funkcji                          [%c]\n", gwiazdki[2]);
	printf("4. Zdefiniuj i wygeneruj zaszumione wartosci funkcji [%c]\n", gwiazdki[3]);
	printf("5. Zapisz wartosci funkcji do pliku\n");
	printf("5. Zapisz wartosci szumu funkcji do pliku\n");
	printf("7. Odczytaj wartosci funkcji z pliku\n");
	printf("8. Odczytaj wartosci funkcji z pliku\n");
	printf("9. Odczytaj wartosci funkcji z pliku\n");
	printf("0. Wyjscie\n");
	printf("Wybierz opcje (0-9): ");
}
void tabWspolczynnikow(double** wspolczynniki)
{
	printf("Podaj w kolejnosci wartosci wspolczynnikow A, B, C, D, E, F:\n");
	Sleep(1000);

	*wspolczynniki = (double*)malloc(sizeof(double));
	if (*wspolczynniki == NULL) {
		printf("Bład alokacji pamieci.\n");
		return; // Wyjście z funkcji w przypadku błędu
	}
	char A = 'A';
	for (int i = 0; i < 6; i++) {
		if (i != 0) *wspolczynniki = (double*)realloc(*wspolczynniki, (i + 2) * sizeof(double)); // Alokacja pamięci na tablicę
		printf("Podaj wartosc dla %c: ", A + i);
		scanf("%lf", *wspolczynniki + i); // Wczytywanie wartości do tablicy
		printf("- Przyjeto wartosc %.2lf\n", (*wspolczynniki)[i]);
		Sleep(500);
	}
}

void dziedzina(double* aMaly, double* aDuzy)
{
	printf("Podaj zakres dziedziny:\nNajmniejszy argument dziedziny: ");
	scanf("%lf", aMaly);
	printf("Najwiekszy argument dziedziny: ");
	scanf("%lf", aDuzy);
}

void alokacjaPamieci(double** tabWynikowa, double** tablicaSzum, int* rozmiar)
{
	printf("Podaj ilosc argumentow w funkcji: ");

	do
	{
		scanf("%d", rozmiar);
		if (*rozmiar <= 0) printf("\n          !!! BLAD !!!\nIlosc argumentow funkcji musi byc dodatnia!!!\n\nSproboj jeszcze raz podac ilosc argumentow funkcji: ");

	} while (*rozmiar <= 0);

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
	printf("Najwiekszy argument dziedziny szumu:\n");
	scanf("%lf", aDuzySzumu);
	while (*aMalySzumu > *aDuzySzumu)
	{
		printf("Najmniejsza wartośc amplitudy szumu jest wieksza od najwiekszej wartosci amplitudy szumu.\nPodaj ponownie: \n");
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
		printf("Błedny procent zaszumienia.\n");
		return;
	}

	printf("Podaj amplitude zaszumienia: ");
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
	char nazwa[20];
	printf("Podaj nazwe pliku: ");
	scanf("%s", nazwa);
	char buf[0x25];
	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
	FILE* plik = fopen(buf, "w");

	if (plik == NULL)
	{
		for (int i = 0; i < rozmiar; i++)
		{
			fprintf(plik, "%.2lf\n", tablicaSzum[i]);
		}
	}
	else
		printf("Bład otwarcia pliku.\n");
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