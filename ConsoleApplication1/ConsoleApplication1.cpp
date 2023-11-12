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
	printf("4. Zapisz wartosci funkcji do pliku                  [%c]\n", gwiazdki[3]);
	printf("5. Zapisz wartosci szumu funkcji do pliku            [%c]\n", gwiazdki[4]);
	printf("6. Odczytaj wartosci funkcji z pliku                 [%c]\n", gwiazdki[5]);
	printf("7. Odczytaj wartosci szumu funkcji z pliku           [%c]\n", gwiazdki[6]);
	printf("8. Odszumianie wartosci funkcji z pliku              [%c]\n", gwiazdki[7]);
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
		if (i != 0) *wspolczynniki = (double*)realloc(*wspolczynniki, (i + 1) * sizeof(double)); // Alokacja pamięci na tablicę
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
	printf("Podaj ilosc argumentow funkcji: ");
	do
	{
		scanf("%d", rozmiar);
		if (*rozmiar <= 0)
			printf("\n!!! BLAD !!!\nIlosc argumentow funkcji musi byc dodatnia!!!\n\nSproboj jeszcze raz podac ilosc argumentow funkcji: ");

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
		printf("\nBlad otwarcia pliku.\n");
	}
}

void wczytanieZPliku(double** tablicaY, double** tablicaX)
{

	char nazwa[20];
	printf("Podaj nazwe pliku do odczytu danych: ");
	scanf("%s", nazwa);
	char buf[0x26];
	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
	FILE* plik = fopen(buf, "r");
	if (plik == NULL)
	{
		printf("\nBlad otwarcia pliku.\n");
		return;
	}
	
	int rozmiar = 1;
	int n = 0;
	*tablicaY = (double*)malloc(sizeof(double));
	*tablicaX = (double*)malloc(sizeof(double));

	while (fgetc(plik) != EOF)
	{
		if (rozmiar <= n)
		{
			rozmiar = 2 * rozmiar;
			*tablicaY = (double*)realloc(*tablicaY, (rozmiar) * sizeof(double)); // Alokacja pamięci na tablicę
			*tablicaX = (double*)realloc(*tablicaX, (rozmiar) * sizeof(double)); // Alokacja pamięci na tablicę
		}
		fscanf(plik, "%lf ; %lf \n", *tablicaX + n, *tablicaY + n);
		printf("- Przyjeto wartosc X: %.2lf i  Y: %.2lf \n", (*tablicaX)[n], (*tablicaY)[n]);
		n++;
	}
	printf("\nDane zosatly odczytane z pliku %s\n", buf);
	printf("Przyjete odczyty: %d\n", n);
	fclose(plik);
}

void wyswietlMenuFiltracji(int* typ, int* zrodlo, int* okno)
{
	printf("\nMENU odszumienia wartosci funkcji\n");
	do
	{
		printf("\nWybierz metode odszumiania.\n1. Filtr medianowy\n2. Filtr sredniej ruchomej: ");
		scanf("%d", typ);
		if (!(*typ == 1 || *typ == 2)) printf("\nBLAD Sproboj ponownie\n");
	} while (!(*typ == 1 || *typ == 2));
	do
	{
		printf("\nWybierz dane do odszumienia\n1. Wygenerowane wartosci zaszumionej funkcji (#3)\n2. Wczytane z pliku wartosci zaszumionej funkcji(#7)\n: ");
		scanf("%d", zrodlo);
		if (!(*zrodlo == 1 || *zrodlo == 2)) printf("\nBLAD Sproboj ponownie\n");
	} while (!(*zrodlo == 1 || *zrodlo == 2));
	do
	{
		printf("\nPodaj zakres okna filtra odszumiania (liczba niepazysta wieksza od 1): ");
		scanf("%d", okno);
		if (!(*okno > 1 && *okno % 2 == 1)) printf("\nBLAD Sproboj ponownie\n");
	} while (!(*okno > 1 && *okno % 2 == 1));
}

void filtrujZSzumu_Mediana(double* tablicaSzumY, int rozmiar, int okno, double* odszumionySygnalY)
{

}

void filtrujZSzumu_Srednia(double* daneOryginalne, int rozmiar, int okno, double* danePoOdszumieniu)
{
	//printf("Pobrane wartości:\n");
	//for (int i = 0; i < rozmiar; i++) {
	//	printf("Wartość %.2lf\n", *(tablicaSzumY + i));
	//}
	int polowaOkna = okno / 2;

	for (int i = polowaOkna; i < rozmiar - polowaOkna; i++) {
		double suma = 0.0;
		for (int j = i - polowaOkna; j <= i + polowaOkna; j++) {
			suma += daneOryginalne[j];
		}
		danePoOdszumieniu[i] = suma / okno;
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "polish_poland");

	char gwiazdki[8]
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
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
			printf("Tabela wyników:\n");
			for (int i = 0; i < 6; i++) {
				printf("Wartosc dla X: %d wynosi: %.2lf\n", i, wspolczynniki[i]);
			}
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
					for (int i = 0; i < rozmiar; i++) {
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
				gwiazdki[2] = star;
			}
			break;
		case 4:
			if (tabWynik == NULL)
			{
				printf("\n!!! BLAD !!!\nFunkcja nie zostala jeszcze wygenerowana.\n");
			}
			else
			{
				zapisDoPliku(tabWynik, rozmiar, pierwszyArg, skokArg);
				gwiazdki[3] = star;
			}
			break;
		case 5:
			if (tabSzum == NULL)
			{
				printf("\n!!! BLAD !!!\nFunkcja nie zostala jeszcze zaszumiona.\n");
			} else
			{
				zapisDoPliku(tabSzum, rozmiar, pierwszyArg, skokArg);
				gwiazdki[4] = star;
			}
			break;
		case 6:
			wczytanieZPliku(&odczytTabWynikY, &odczytTabWynikX);
			if (odczytTabWynikX != NULL)
			{
				gwiazdki[5] = star;
			}
			printf("Pobrane wartości:\n");
			for (int i = 0; i < 11; i++) {
				printf("Wartość X %d: %.2lf\n", i + 1, odczytTabWynikX[i]);
				printf("Wartość Y %d: %.2lf\n", i + 1, odczytTabWynikY[i]);
			}
			break;
		case 7:
			wczytanieZPliku(&odczytTabSzumY, &odczytTabSzumX);
			if (odczytTabSzumX != NULL)
			{
				gwiazdki[6] = star;
			}
			break;
		case 8:
			int typFiltracji, zrodloSygnalu, oknoFiltra;
			wyswietlMenuFiltracji(&typFiltracji, &zrodloSygnalu, &oknoFiltra);

			double* wybranySygnalX, * wybranySygnalY, * odszumionySygnalY, * daneOryginalneY;
			wybranySygnalX = (double*)malloc(rozmiar * sizeof(*wybranySygnalX));
			wybranySygnalY = (double*)malloc(rozmiar * sizeof(*wybranySygnalY));
			odszumionySygnalY = (double*)malloc(rozmiar * sizeof(*odszumionySygnalY));
			daneOryginalneY = (double*)malloc(rozmiar * sizeof(*odszumionySygnalY));

			if (zrodloSygnalu == 1)
			{
				for (int i = 0; i < rozmiar; i++) { //kopiowanie danych do nowego wsażnika bez połączenia ze danymi ze starego
					daneOryginalneY[i] = tabSzum[i];
					odszumionySygnalY[i] = tabSzum[i];
				}

				for (int i = 0; i < rozmiar; i++)
				{
					printf("TEST");
					wybranySygnalX[i] = pierwszyArg + i * skokArg;
				}
			}
			else if (zrodloSygnalu == 2)
			{
				wybranySygnalX = odczytTabSzumX;
				wybranySygnalY = odczytTabSzumY;
			}

			if (typFiltracji == 1) //MEDIANA
			{
				//filtrujZSzumu_Mediana(wybranySygnalY, rozmiar, oknoFiltra, odszumionySygnalY);
			}
			else if (typFiltracji == 2) //SREDNIA
			{
				if (oknoFiltra > rozmiar) {
					printf("Błędna szerokość okna.\n");
				} else filtrujZSzumu_Srednia(daneOryginalneY, rozmiar, oknoFiltra, odszumionySygnalY);
			}
			printf("Pobrane wartości:\n");
			for (int i = 0; i < rozmiar; i++) {
				printf("Wartość %lf: %.2lf , %.2lf, %.2lf\n", wybranySygnalX[i], daneOryginalneY[i], odszumionySygnalY[i], tabSzum[i]);
			}
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