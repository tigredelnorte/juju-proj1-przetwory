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
	printf("2. Zdefiniuj i wygeneruj wartosci funkcji            [%c]\n", gwiazdki[1]);
	printf("3. Zdefiniuj i wygeneruj zaszumione wartosci funkcji [%c]\n", gwiazdki[2]);
	printf("4. Zapisz wartosci funkcji do pliku\n");
	printf("5. Zapisz wartosci szumu funkcji do pliku\n");
	printf("6. Odczytaj wartosci funkcji z pliku\n");
	printf("7. Odczytaj wartosci szumu funkcji z pliku\n");
	printf("8. Odszumianie wartosci funkcji z pliku\n");
	printf("9. Wyjscie\n");
	printf("Wybierz opcje (1-9): ");
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

void dziedzina(double* pierwszyArg, double* ostatniArg)
{
	printf("\nPodaj zakres dziedziny:\nNajmniejszy argument dziedziny: ");
	scanf("%lf", pierwszyArg);
	printf("Najwiekszy argument dziedziny: ");
	scanf("%lf", ostatniArg);
}

void alokacjaPamieci(double** tabWynikowa, double** tablicaSzum, int* rozmiar)
{
	printf("Podaj ilosc argumentow funkcji (poza poczatkowym argumentem): ");
	do
	{
		scanf("%d", rozmiar);
		if (*rozmiar <= 0)
			printf("\n!!! BLAD !!!\nIlosc argumentow funkcji musi byc dodatnia!!!\n\nSproboj jeszcze raz podac ilosc argumentow funkcji: ");

	} while (*rozmiar <= 0);
	*tabWynikowa = (double*)malloc(*rozmiar + 1 * sizeof(**tabWynikowa));
	*tablicaSzum = (double*)malloc(*rozmiar + 1 * sizeof(**tablicaSzum));
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

void generatorFunkcji(double* wspolczynniki, double pierwszyArg, double* tabWynikowa, int rozmiar, double skokArg)
{
	double biezacyX = pierwszyArg;
	for (int i = 0; i <= rozmiar; i++)
	{
		double wynikFunkcji = obliczFunkcje(biezacyX, wspolczynniki);
		*(tabWynikowa + i) = wynikFunkcji;
		biezacyX = biezacyX + skokArg;
	}
}

void dziedzinaSzumu(double* pierwszyArgSzumu, double* ostatniArgSzumu)
{
	printf("Podaj zakres dziedziny: \n");
	printf("Najmniejszy argument dziedziny szumu:\n");
	scanf("%lf", pierwszyArgSzumu);
	//if ()
	printf("Najwiekszy argument dziedziny szumu:\n");
	scanf("%lf", ostatniArgSzumu);
	while (*pierwszyArgSzumu > *ostatniArgSzumu)
	{
		printf("Najmniejsza wartośc amplitudy szumu jest wieksza od najwiekszej wartosci amplitudy szumu.\nPodaj ponownie: \n");
		printf("Najmniejsza wartość amplitudy szumu:\n");
		scanf("%lf", pierwszyArgSzumu);
		printf("Największa wartość amplitudy szumu:\n");
		scanf("%lf", ostatniArgSzumu);
	}
}

void amplitudaiLosowanieSzumu(double * tabWynikowa, double* tablicaSzum, int rozmiar)
{
	// Inicjalizacja generatora liczb losowych
	double procentZaszumienia, amplitudaZaszumienia;

	printf("\nPodaj procent zaszumienia (0-100): ");
	scanf("%lf", &procentZaszumienia);

	if (procentZaszumienia < 0 || procentZaszumienia > 100) {
		printf("Błedny procent zaszumienia.\n");
		return;
	}

	printf("Podaj amplitude zaszumienia: ");
	scanf("%lf", &amplitudaZaszumienia);

	for (int i = 0; i <= rozmiar; i++) {
		tablicaSzum[i] = tabWynikowa[i]; // Skopiuj oryginalne wyniki

		if ((double)rand() / RAND_MAX * 100.0 < procentZaszumienia) {
			// Wygeneruj losową wartość do zaszumienia z podanej amplitudy
			double zaszumienie = ((double)rand() / RAND_MAX) * amplitudaZaszumienia;

			// Zaszum wynik
			tablicaSzum[i] += zaszumienie;
		}
	}
}

void zapisDoPliku(double* tablicaWartosci, int rozmiar, double pierwszyArg, double skokArg )
{
	char nazwa[20];
	printf("Podaj nazwe pliku: ");
	scanf("%s", nazwa);
	char buf[0x26];
	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
	FILE* plik = fopen(buf, "w");

	if (plik != NULL)
	{
		for (int i = 0; i <= rozmiar; i++)
		{
			fprintf(plik, "%lf ; %lf\n", pierwszyArg + (i * skokArg), tablicaWartosci[i]);
		}
		fclose(plik);
		printf("\nDane zosatly zapisane do pliku %s\n", buf);
	}
	else
	{
		printf("\nBład otwarcia pliku.\n");
	}
}

void wczytanieZPliku(double** tablicaY, double** tablicaX)
{
	*tablicaY = (double*)malloc(sizeof(double));
	*tablicaX = (double*)malloc(sizeof(double));
	char nazwa[20];
	printf("Podaj nazwe pliku do odczytu danych: ");
	scanf("%s", nazwa);
	char buf[0x26];
	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
	FILE* plik = fopen(buf, "r");
	if (plik != NULL)
	{
		int n = 0;
		if (i != 0) *tablicaY = (double*)realloc(*tablicaY, (i + 2) * sizeof(double)); // Alokacja pamięci na tablicę

		while (fgetc(plik) != EOF)
		{
			fscanf(plik, "%lf ; %lf \n", &tablicaX[n], &tablicaY[n]);
			n++;
		}
		fclose(plik);
		printf("\nDane zosatly odczytane z pliku %s\n", buf);
	}
	else
	{
		printf("\nBład otwarcia pliku.\n");
	}
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
	double pierwszyArg, ostatniArg;
	int rozmiar = NULL;
	double* tabWynik = NULL, * tabSzum = NULL, skokArg = NULL;
	double* odczytTabWynikY = NULL, * odczytTabSzumY = NULL, * odczytTabWynikX = NULL, * odczytTabSzumX = NULL;
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
			if (wspolczynniki == NULL)
			{
				printf("\n!!! BLAD !!!\nWspolczynniki funkcji nie zostaly jeszcze podane.\n");
			}
			else
			{
				dziedzina(&pierwszyArg, &ostatniArg);
				alokacjaPamieci(&tabWynik, &tabSzum, &rozmiar);
				skokArg = (ostatniArg - pierwszyArg) / rozmiar;
				if (rozmiar > 0)
				{
					generatorFunkcji(wspolczynniki, pierwszyArg, tabWynik, rozmiar, skokArg);
					if (tabWynik != NULL) gwiazdki[1] = star;
					//Wypisanie wartości z tablicy
					printf("Tabela wyników:\n");
					for (int i = 0; i <= rozmiar; i++) {
						printf("Wartosc dla X: %.2lf wynosi: %.2lf\n", pierwszyArg + (i * skokArg), tabWynik[i]);
					}
				}
			}
			break;
		case 3:
			if (tabWynik == NULL)
			{
				printf("\n!!! BLAD !!!\nFunkcja nie zostala jeszcze wygenerowana.\n");
			}
			else
			{
				amplitudaiLosowanieSzumu(tabWynik, tabSzum, rozmiar);
				printf("Pobrane wartosci:\n");
				if (tabSzum != NULL) gwiazdki[2] = star;
				for (int i = 0; i < rozmiar; i++)
				{
					printf("Wartosc dla X: %.2lf wynosi: %.2lf\n", pierwszyArg + (i * skokArg), tabSzum[i]);
				}
			}
			break;
		case 4:
			if (tabWynik == NULL)
			{
				printf("\n!!! BLAD !!!\nFunkcja nie zostala jeszcze wygenerowana.\n");
			}
			else
				zapisDoPliku(tabWynik, rozmiar, pierwszyArg, skokArg);
			break;
		case 5:
			if (tabSzum == NULL)
			{
				printf("\n!!! BLAD !!!\nFunkcja nie zostala jeszcze zaszumiona.\n");
			} else
				zapisDoPliku(tabSzum, rozmiar, pierwszyArg, skokArg);
			break;
		case 6:
			wczytanieZPliku(&odczytTabWynikY, &odczytTabWynikX);
			break;
		case 7:
			wczytanieZPliku(&odczytTabSzumY, &odczytTabSzumX);
			break;
		case 8:
			filtrujZSzumu(tabSzum, rozmiar);
			break;
		case 9:
			printf("Program zostanie zakończony.\n");
			break;
		default:
			printf("Nieprawidłowy wybór. Wybierz opcję od 1 do 9.\n");
			break;
		}
	} while (wyborMenu != 9);
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