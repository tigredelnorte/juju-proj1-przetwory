#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <locale.h>
#include <string>

void TabWspolczynnikow(double* wspolczynniki)
{
	double A, B, C, D, E = 0, F;
	printf("Podaj w kolejnosci A, B, C, D, E, F wspolczynniki: \n");
	printf("A: ");
	scanf("%lf", &A);
	*(wspolczynniki) = A;  //0
	//printf("%lf", *(wspolczynniki));

	printf("B: ");
	scanf("%lf", &B);
	*(wspolczynniki + 1) = B; //1

	printf("C: ");
	scanf("%lf", &C);
	*(wspolczynniki + 2) = C; //2

	printf("D: ");
	scanf("%lf", &D);
	*(wspolczynniki + 3) = D; //3

	
	
	while (E == 0)
	{
		printf("E (nie 0): ");
		scanf("%lf", &E);
		if(E == 0)
		{
			printf("Dawaj jeszcze raz gamoniu!!!\n");
		}
	}
	*(wspolczynniki + 4) = E; //4


	printf("F: ");
	scanf("%lf", &F);
	*(wspolczynniki + 5) = F; //5

	// 0   1   2   3   4   5 
	// { } { } { } { } { } { }
	//  wez wartosc do miejsca "0" w tablicy

}
void Dziedzina(double* aMaly, double* aDuzy)        //wartosc
{
	printf("Podaj zakres dziedziny:\nNajmniejszy argument dziedziny: ");
	scanf("%lf", aMaly);
	//if ()
	printf("Największy argument dziedziny:\n");
	scanf("%lf", aDuzy);
}

double getSinus(double x, double* wspolczynniki)
{
	double potega = pow(x, 2);
	double S = *(wspolczynniki + 1) * potega + *(wspolczynniki + 2) * x;
	double wynikSinusa = sin(S);
	//printf("sin( %f ) = %f\n", S, y);
	return wynikSinusa;
}
double getCosinus(double x, double* wspolczynniki)
{
	double C = *(wspolczynniki + 4) * x - *(wspolczynniki + 5);
	double wynikCosinusa = cos(C);
	return wynikCosinusa;
}
double getFunkcja(double x, double* wspolczynniki)
{
	double funkcja = *(wspolczynniki + 1) * getSinus(x, wspolczynniki) + *(wspolczynniki + 3) / getCosinus(x, wspolczynniki);
	return funkcja;
}

void generatorFunkcji(double* wspolczynniki, double aMaly, double aDuzy, double* tabWynikowa, int iloscArgumentow)
{
	//wielkoscTab = ilosc argumentow

	// dla kazdego argumentu wywolac wartosc z funkcji
	int liczbaElementowTabeli = 20;
	for (int i = 0; i <= liczbaElementowTabeli; i++)
	{
		double skokArg = (aDuzy - aMaly) / liczbaElementowTabeli;
		double wynikFunkcji = getFunkcja(aMaly, wspolczynniki);
		*(tabWynikowa + i) = wynikFunkcji;
		aMaly = aMaly + skokArg;
	}
	//while (aMaly <= aDuzy)
	//{
	//	double skokArg = (aDuzy - aMaly) / 20;
	//	double wynikFunkcji = getFunkcja(aMaly, wspolczynniki);
	//	*(tabWynikowa) = wynikFunkcji;
	//	aMaly = aMaly + skokArg;
	//	//*(tabWynikowa n);  //tabWynikowa[n]
	//	//n++;
	//}
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
void AmplitudaiLosowanieSzumu(int amplituda, double* tablicaSzum, double zaszumienie)
{
	printf("Podaj prawdopodobienstwo zaszumienia w procentach od 0% do 100%: ");
	scanf("%lf", zaszumienie);
	printf("Podaj wartosc wychylenia w amplitudzie:\n");
	scanf("%lf", amplituda);

	//*tablicaSzum = rand() % (amplituda + amplituda + 1) - amplituda; //zakres liczb szumów
	int i;
	for (i = 0; i < 1000; i++);
	{
		*(tablicaSzum + i) = rand() % (amplituda + amplituda + 1) - amplituda; //przypisanie szumu do 0 miejsca

		//*(tablicaSzum + i) * zaszumienie
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

void zapisDoPliku(double* tablicaSzum)
{
	FILE* plik;
	int i;
	plik = fopen("losowe.csv", "w");        //plik csv do otworzenia w excel
	if (plik != NULL)
	{
		for (i = 0; i < 10; i++)
		{
			fprintf(plik, "Wylosowana liczba to: %.2lf;", tablicaSzum[i]);  // frpitnf "wydrukuj plik" //; czyli w nastepnym kolmunach zapisywanie
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

	printf("Podaj wartości literowe do funkcji A*sin(Bx^2+C*x) + D / (x-1) * cos(E*x - F)\nPodaj po kolei:\n");
	double wspolczynniki[6];
	TabWspolczynnikow(wspolczynniki);

	double aMaly, aDuzy;
	Dziedzina(&aMaly, &aDuzy);      //adres


	//int n = aDuzy; // ostatni argument w tab  
	//int iloscArgumentow = 20;
	//for(iloscArgumentow = 0; iloscArgumentow <= iloscArgumentow; iloscArgumentow++)
	//iloscArgumentow= (aDuzy - aMaly)/0.1;

	double tabWynikowa[1000];
	double tablicaSzum[1000];
	generatorFunkcji(wspolczynniki, aMaly, aDuzy, tabWynikowa, /*iloscArgumentow*/ ((aDuzy - aMaly) / 0.1));

	int amplituda = 5;
	double zaszumienie = 0;
	AmplitudaiLosowanieSzumu(amplituda, tablicaSzum, zaszumienie);

	zapisDoPliku(tablicaSzum);
}



//Jedna dziedzina jest losowanie szumu w danej amplitudzie
//Druga dziedzina jest losowanie szansy na wylosowanie wartości szumu
//A trzecia dziedzina mogło by być losowanie dziedziny