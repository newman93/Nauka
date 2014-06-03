#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cmath>

using namespace std;

enum pl
{
	kobieta,
	mezczyzna
};

enum pw
{
	mniej_niz_16,
	od_16_do_19,
	od_20_do_25,
	od_25_do_40,
	wiecej_niz_40
};

enum t_n
{
	tak,
	nie
};

enum st
{
	uczen,
	student,
	pracujacy,
	bezrobotny,
	emeryt
};

enum mz
{
	wies,
	miasto_mniej_niz_10,
	miasto_od_10_do_100,
	miasto_od_100_do_500,
	miasta_wicej_niz_500
};
	
enum in
{
	iwatch,
	konsola,
	smarttv,
	wiecej_niz_1,
	inny
};

enum cz
{
	mniej_niz_30,
	od_1_do_3,
	od_3_do_5,
	od_5_do_8,
	wicej_niz_8
};

enum pie
{
	mniej_niz_50,
	od_50_do_300,
	od_300_do_500,
	od_500_do_1000,
	wicej_niz_1000
};

enum prze
{
	nauka,
	praca,
	rozrywka,
	komunikacja,
	inne
};

struct profil
{
	enum pl plec;
	enum pw przedzial_wiekowy;
	enum mz miejsce_zamieszkania;
	enum st status_zawodowy;
	enum t_n smartphone;
	enum t_n tablet;
	enum t_n inne;
	enum in inne_tak;
	enum cz czas;
	enum pie pieniadze;
	enum t_n czasopisma;
	enum prze przeznaczenie;
	enum t_n rezygnacja;
};

class Ankieta
{
	private:
		struct profil *baza_danych;
		int ilosc_osob;
		string tab_pytan[13];
		string **tab_odpowiedzi;
		int **tab_zliczajaca;
	public:
		Ankieta(int _i);
		~Ankieta();
		void generator();
		void wyniki();
		void profile();
		void profile_pieniadze();
};

Ankieta::Ankieta(int _i)
{
	ilosc_osob = _i;
	baza_danych = new struct profil[_i];
	tab_odpowiedzi = new string *[13];
	tab_zliczajaca = new int *[13];
	for (int i = 0; i < 13; ++i)
	{
		switch(i)
		{
			case 0:
			case 4:
			case 5:
			case 6:
			case 10:
			case 12: 
						tab_odpowiedzi[i] = new string[2];
						tab_zliczajaca[i] = new int[2];
						break;
			case 1:
			case 2:
			case 3:
			case 7:
			case 8:
			case 9:
			case 11: 	
						tab_odpowiedzi[i] = new string[5];
						tab_zliczajaca[i] = new int[5];
						break;
		};
	};
	tab_pytan[0] = "Płeć:\n";
	tab_pytan[1] = "Przedział wiekowy:\n";
	tab_pytan[2] = "Miejsce zamieszkania:\n";
	tab_pytan[3] = "Status zawodowy:\n";
	tab_pytan[4] = "Czy posiada Pan/Pani smartphone`a?\n";
	tab_pytan[5] = "Czy posiada Pan/Pani tablet?\n";
	tab_pytan[6] = "Czy posiada Pan/Pani inne urządzenie tego typu?\n";
	tab_pytan[7] = "Proszę wybrać urządzenia, które Pan/Pani posiada:\n";
	tab_pytan[8] = "Ile czasu Pan/Pani spędza dziennie korzystając w ww. urządzeń?\n";
	tab_pytan[9] = "Ile rocznie Pan/Pani wydaje pieniędzy na zakup i utrzymanie ww. urządzeń?\n";
	tab_pytan[10] = "Czy czyta Pan/Pani czasopisma technologiczne?\n";
	tab_pytan[11] = "Do czego Pan/Pani w największym stopniu wykorzystuje ww. urządzenia?\n";
	tab_pytan[12] = "Czy potrafiłaby/potrafiłby Pani/Pan całkowicie zrezygnować z ww. urządzeń?\n";
	for (int i = 0; i < 13; ++i)
	{
		switch(i)
		{
			case 0:
			case 4:
			case 5:
			case 6:
			case 10:
			case 12: 
						tab_zliczajaca[i][0] = 0;
						tab_zliczajaca[i][1] = 0;
						break;
			case 7:		
			case 1:
			case 2:
			case 3:
			case 8:
			case 9:
			case 11: 	
						for (int j = 0; j < 5; ++j)
							tab_zliczajaca[i][j] = 0;
						break;
		};
	};
	for (int i = 0; i < 13; ++i)
	{
		switch(i)
		{
			case 4:
			case 5:
			case 6:
			case 10:
			case 12: 
						tab_odpowiedzi[i][0] = "tak";
						tab_odpowiedzi[i][1] = "nie";
						break;
			case 0:
						tab_odpowiedzi[i][0] = "kobieta";
						tab_odpowiedzi[i][1] = "mężczyzna";
						break;
			case 1:		tab_odpowiedzi[i][0] = "mniej niż 16";
						tab_odpowiedzi[i][1] = "od 16 do 19";
						tab_odpowiedzi[i][2] = "od 20 do 25";
						tab_odpowiedzi[i][3] = "od 25 do 40";
						tab_odpowiedzi[i][4] = "więcej niż 40";
						break;
			case 3:
						tab_odpowiedzi[i][0] = "uczeń";
						tab_odpowiedzi[i][1] = "student";
						tab_odpowiedzi[i][2] = "pracownik";
						tab_odpowiedzi[i][3] = "bezrobotny";
						tab_odpowiedzi[i][4] = "emeryt";
						break;
			case 2:
						tab_odpowiedzi[i][0] = "wieś";
						tab_odpowiedzi[i][1] = "miasto mniej niż 10 tys.";
						tab_odpowiedzi[i][2] = "miasto od 10 do 100 tys.";
						tab_odpowiedzi[i][3] = "miasto od 100 do 500 tys.";
						tab_odpowiedzi[i][4] = "miasto więcej niż 500 tys.";
						break;
			case 7:
						tab_odpowiedzi[i][0] = "iWatch";
						tab_odpowiedzi[i][1] = "konsola";
						tab_odpowiedzi[i][2] = "SmartTV";
						tab_odpowiedzi[i][3] = "więcej niż 1";
						tab_odpowiedzi[i][4] = "inne";
						break;
			case 8:
						tab_odpowiedzi[i][0] = "mniej niż 30 min";
						tab_odpowiedzi[i][1] = "od 1 do 3 h";
						tab_odpowiedzi[i][2] = "od 3 do 5 h";
						tab_odpowiedzi[i][3] = "od 5 do 8 h";
						tab_odpowiedzi[i][4] = "więcej niż 8 h";
						break;
			case 9:
						tab_odpowiedzi[i][0] = "mniej niż 50 zł";
						tab_odpowiedzi[i][1] = "od 50 do 300 zł";
						tab_odpowiedzi[i][2] = "od 300 do 500 zł";
						tab_odpowiedzi[i][3] = "od 500 do 1000 zł";
						tab_odpowiedzi[i][4] = "więcej niż 1000 zł";
						break;
			case 11:
						tab_odpowiedzi[i][0] = "nauka";
						tab_odpowiedzi[i][1] = "praca";
						tab_odpowiedzi[i][2] = "rozrywka";
						tab_odpowiedzi[i][3] = "komunikacja";
						tab_odpowiedzi[i][4] = "inne";
						break;
		};
	};
};

Ankieta::~Ankieta()
{
	delete[] baza_danych;
	for (int i = 0; i < 13; ++i)
		delete[] tab_odpowiedzi[i];
	delete[] tab_odpowiedzi;
};

void Ankieta::generator()
{
	srand(1);
	struct profil osoba;
	
	for (int i = 0; i < ilosc_osob; ++i)
	{
		osoba.plec = rand() % 2;
		osoba.przedzial_wiekowy = rand() % 5; 
		if (osoba.przedzial_wiekowy == 0)
			osoba.status_zawodowy = 0;
		else if (osoba.przedzial_wiekowy == 1)
			osoba.status_zawodowy = 0;
		else if (osoba.przedzial_wiekowy == 2)
			osoba.status_zawodowy = 1;
		else if (osoba.przedzial_wiekowy == 3)
		{
			if (i % 2 == 0)
				osoba.status_zawodowy = 2;
			else
				osoba.status_zawodowy = 3;
		} else if (osoba.przedzial_wiekowy == 4)
		{
			if (i % 2 == 0)
				osoba.status_zawodowy = 2;
			else
				osoba.status_zawodowy = 4;
	    }
		osoba.miejsce_zamieszkania = rand() % 5;
		osoba.smartphone = rand() % 2;
		osoba.tablet = rand() % 2;
		osoba.inne = rand() % 2;
		if (osoba.inne == 0)
			osoba.inne_tak = rand() % 5;
		else
			osoba.inne_tak = 5; //zabezpieczenie
		osoba.czas = rand() % 5;
		osoba.pieniadze = rand() % 5;
		if (osoba.status_zawodowy == 0 || osoba.status_zawodowy == 4)
		{
			do
			{
				osoba.przeznaczenie = rand() % 5;
			} while (osoba.przeznaczenie != 1);
		} else
		{
			osoba.przeznaczenie = rand() % 5;
		}
		osoba.czasopisma = rand() % 2;
		osoba.rezygnacja = rand() % 2;
		baza_danych[i] = osoba;
	}
};	

void Ankieta::wyniki()
{
	fstream plik_dane("dane.txt", ios::out);
	
	plik_dane << "Wyniki ankiety: " << endl;
		
	for (int i = 0; i < ilosc_osob; ++i)	
	{
		if (baza_danych[i].plec == 0)
				++tab_zliczajaca[0][0];
		else
				++tab_zliczajaca[0][1];
		if (baza_danych[i].przedzial_wiekowy == 0)
				++tab_zliczajaca[1][0];
		else if (baza_danych[i].przedzial_wiekowy == 1)
				++tab_zliczajaca[1][1];
		else if (baza_danych[i].przedzial_wiekowy == 2)
				++tab_zliczajaca[1][2];
		else if (baza_danych[i].przedzial_wiekowy == 3)
				++tab_zliczajaca[1][3];
		else
				++tab_zliczajaca[1][4];
		if (baza_danych[i].miejsce_zamieszkania == 0)
				++tab_zliczajaca[2][0];
		else if (baza_danych[i].miejsce_zamieszkania == 1)
				++tab_zliczajaca[2][1];
		else if (baza_danych[i].miejsce_zamieszkania == 2)
				++tab_zliczajaca[2][2];
		else if (baza_danych[i].miejsce_zamieszkania == 3)
				++tab_zliczajaca[2][3];
		else
				++tab_zliczajaca[2][4];
		if (baza_danych[i].status_zawodowy == 0)
				++tab_zliczajaca[3][0];
		else if (baza_danych[i].status_zawodowy == 1)
				++tab_zliczajaca[3][1];
		else if (baza_danych[i].status_zawodowy == 2)
				++tab_zliczajaca[3][2];
		else if (baza_danych[i].status_zawodowy == 3)
				++tab_zliczajaca[3][3];
		else
				++tab_zliczajaca[3][4];
		if (baza_danych[i].smartphone == 0)
				++tab_zliczajaca[4][0];
		else
				++tab_zliczajaca[4][1];
		if (baza_danych[i].tablet == 0)
				++tab_zliczajaca[5][0];
		else
				++tab_zliczajaca[5][1];
		if (baza_danych[i].inne == 0)
				++tab_zliczajaca[6][0];
		else
				++tab_zliczajaca[6][1];
		if (baza_danych[i].inne_tak == 0)
				++tab_zliczajaca[7][0];
		else if (baza_danych[i].inne_tak == 1)
				++tab_zliczajaca[7][1];
		else if (baza_danych[i].inne_tak == 2)
				++tab_zliczajaca[7][2];
		else if (baza_danych[i].inne_tak == 3)
				++tab_zliczajaca[7][3];
		else if (baza_danych[i].inne_tak == 4)
				++tab_zliczajaca[7][4];
		if (baza_danych[i].czas == 0)
				++tab_zliczajaca[8][0];
		else if (baza_danych[i].czas == 1)
				++tab_zliczajaca[8][1];
		else if (baza_danych[i].czas == 2)
				++tab_zliczajaca[8][2];
		else if (baza_danych[i].czas == 3)
				++tab_zliczajaca[8][3];
		else
				++tab_zliczajaca[8][4];
		if (baza_danych[i].pieniadze == 0)
				++tab_zliczajaca[9][0];
		else if (baza_danych[i].pieniadze == 1)
				++tab_zliczajaca[9][1];
		else if (baza_danych[i].pieniadze == 2)
				++tab_zliczajaca[9][2];
		else if (baza_danych[i].pieniadze == 3)
				++tab_zliczajaca[9][3];
		else
				++tab_zliczajaca[9][4];
		if (baza_danych[i].czasopisma == 0)
				++tab_zliczajaca[10][0];
		else
				++tab_zliczajaca[10][1];
		if (baza_danych[i].przeznaczenie == 0)
				++tab_zliczajaca[11][0];
		else if (baza_danych[i].przeznaczenie == 1)
				++tab_zliczajaca[11][1];
		else if (baza_danych[i].przeznaczenie == 2)
				++tab_zliczajaca[11][2];
		else if (baza_danych[i].przeznaczenie == 3)
				++tab_zliczajaca[11][3];
		else
				++tab_zliczajaca[11][4];
		if (baza_danych[i].rezygnacja == 0)
				++tab_zliczajaca[12][0];
		else
				++tab_zliczajaca[12][1];
	};
	for (int i = 0; i < 13; ++i)
	{
		plik_dane << tab_pytan[i];
		
		switch(i)
		{
			case 0:
			case 4:
			case 5:
			case 6:
			case 10:
			case 12:    
						plik_dane << tab_odpowiedzi[i][0] << ": " << tab_zliczajaca[i][0] << endl;
						plik_dane << tab_odpowiedzi[i][1] << ": " << tab_zliczajaca[i][1] << endl;
						break;
			case 1:
			case 2:
			case 3:
			case 7:
			case 8:
			case 9:
			case 11: 	
						plik_dane << tab_odpowiedzi[i][0] << ": " << tab_zliczajaca[i][0] << endl;
						plik_dane << tab_odpowiedzi[i][1] << ": " << tab_zliczajaca[i][1] << endl;
						plik_dane << tab_odpowiedzi[i][2] << ": " << tab_zliczajaca[i][2] << endl;
						plik_dane << tab_odpowiedzi[i][3] << ": " << tab_zliczajaca[i][3] << endl;
						plik_dane << tab_odpowiedzi[i][4] << ": " << tab_zliczajaca[i][4] << endl;
						break;
		};
	};
	plik_dane.close();
};

void Ankieta::profile()
{
	fstream plik_dane("profile.txt", ios::out);
	
	plik_dane << "Wyniki ankiety: " << endl;
	
	int pieniadze_kobieta[5];
	int pieniadze_mezczyzna[5];
	int status_kobieta[5];
	int status_mezczyzna[5];
	
	for (int i = 0; i < 5; ++i)
	{
		pieniadze_kobieta[i] = 0;
		pieniadze_mezczyzna[i] = 0;
		status_kobieta[i] = 0;
		status_mezczyzna[i] = 0;
	}
		
	for (int i = 0; i < ilosc_osob; ++i)	
	{
		switch (baza_danych[i].plec)
		{
			case 0:
						if (baza_danych[i].pieniadze == 0)
							++pieniadze_kobieta[0];
						else if (baza_danych[i].pieniadze == 1)
							++pieniadze_kobieta[1];
						else if (baza_danych[i].pieniadze == 2)
							++pieniadze_kobieta[2];
						else if (baza_danych[i].pieniadze == 3)
							++pieniadze_kobieta[3];
						else
							++pieniadze_kobieta[4];
						break;
			case 1: 	
						if (baza_danych[i].pieniadze == 0)
							++pieniadze_mezczyzna[0];
						else if (baza_danych[i].pieniadze == 1)
							++pieniadze_mezczyzna[1];
						else if (baza_danych[i].pieniadze == 2)
							++pieniadze_mezczyzna[2];
						else if (baza_danych[i].pieniadze == 3)
							++pieniadze_mezczyzna[3];
						else
							++pieniadze_mezczyzna[4];
						break;
		}
	};
	for (int i = 0; i < ilosc_osob; ++i)	
	{
		switch (baza_danych[i].plec)
		{
			case 0:
						if (baza_danych[i].status_zawodowy == 0)
							++status_kobieta[0];
						else if (baza_danych[i].status_zawodowy == 1)
							++status_kobieta[1];
						else if (baza_danych[i].status_zawodowy == 2)
							++status_kobieta[2];
						else if (baza_danych[i].status_zawodowy == 3)
							++status_kobieta[3];
						else
							++status_kobieta[4];
						break;
			case 1: 	
						if (baza_danych[i].status_zawodowy == 0)
							++status_mezczyzna[0];
						else if (baza_danych[i].status_zawodowy == 1)
							++status_mezczyzna[1];
						else if (baza_danych[i].status_zawodowy == 2)
							++status_mezczyzna[2];
						else if (baza_danych[i].status_zawodowy == 3)
							++status_mezczyzna[3];
						else
							++status_mezczyzna[4];
						break;
		}
	};
	plik_dane << "Kobieta" << endl;
	plik_dane << tab_odpowiedzi[9][0] << ": " << pieniadze_kobieta[0] << endl;
	plik_dane << tab_odpowiedzi[9][1] << ": " << pieniadze_kobieta[1] << endl;
	plik_dane << tab_odpowiedzi[9][2] << ": " << pieniadze_kobieta[2] << endl;
	plik_dane << tab_odpowiedzi[9][3] << ": " << pieniadze_kobieta[3] << endl;
	plik_dane << tab_odpowiedzi[9][4] << ": " << pieniadze_kobieta[4] << endl;
	plik_dane << "Mezczyzna" << endl;
	plik_dane << tab_odpowiedzi[9][0] << ": " << pieniadze_mezczyzna[0] << endl;
	plik_dane << tab_odpowiedzi[9][1] << ": " << pieniadze_mezczyzna[1] << endl;
	plik_dane << tab_odpowiedzi[9][2] << ": " << pieniadze_mezczyzna[2] << endl;
	plik_dane << tab_odpowiedzi[9][3] << ": " << pieniadze_mezczyzna[3] << endl;
	plik_dane << tab_odpowiedzi[9][4] << ": " << pieniadze_mezczyzna[4] << endl;
	plik_dane << "Kobieta" << endl;
	plik_dane << tab_odpowiedzi[3][0] << ": " << status_kobieta[0] << endl;
	plik_dane << tab_odpowiedzi[3][1] << ": " << status_kobieta[1] << endl;
	plik_dane << tab_odpowiedzi[3][2] << ": " << status_kobieta[2] << endl;
	plik_dane << tab_odpowiedzi[3][3] << ": " << status_kobieta[3] << endl;
	plik_dane << tab_odpowiedzi[3][4] << ": " << status_kobieta[4] << endl;
	plik_dane << "Mezczyzna" << endl;
	plik_dane << tab_odpowiedzi[3][0] << ": " << status_mezczyzna[0] << endl;
	plik_dane << tab_odpowiedzi[3][1] << ": " << status_mezczyzna[1] << endl;
	plik_dane << tab_odpowiedzi[3][2] << ": " << status_mezczyzna[2] << endl;
	plik_dane << tab_odpowiedzi[3][3] << ": " << status_mezczyzna[3] << endl;
	plik_dane << tab_odpowiedzi[3][4] << ": " << status_mezczyzna[4] << endl;
	plik_dane.close();
};

void Ankieta::profile_pieniadze()
{
	fstream plik_dane("profile_pieniadze.txt", ios::out);
	
	plik_dane << "Wyniki ankiety: " << endl;
	
	int pieniadze_kobieta[tab_zliczajaca[0][0]];
	int pieniadze_mezczyzna[tab_zliczajaca[0][1]];
	int pieniadze[ilosc_osob];
	int suma_wszyscy = 0;
	int suma_kobiety = 0;
	int suma_mezczyzni = 0;
	double tmp_wszyscy = 0;
	double tmp_kobiety = 0;
	double tmp_mezczyzni = 0;
	int kobieta = 0;
	int mezczyzna = 0;
	
	for (int i = 0; i < ilosc_osob; ++i)	
	{
		switch (baza_danych[i].plec)
		{
			case 0:
						if (baza_danych[i].pieniadze == 0)
							pieniadze_kobieta[kobieta] = (rand() % 40) + 11;
						else if (baza_danych[i].pieniadze == 1)
							pieniadze_kobieta[kobieta] = (rand() % 250) + 51;
						else if (baza_danych[i].pieniadze == 2)
							pieniadze_kobieta[kobieta] = (rand() % 200) + 301;
						else if (baza_danych[i].pieniadze == 3)
							pieniadze_kobieta[kobieta] = (rand() % 500) + 501;
						else
							pieniadze_kobieta[kobieta] = (rand() % 4000) + 1001;
						++kobieta;
						break;
			case 1: 	
						if (baza_danych[i].pieniadze == 0)
							pieniadze_mezczyzna[mezczyzna] = (rand() % 40) + 11;
						else if (baza_danych[i].pieniadze == 1)
							pieniadze_mezczyzna[mezczyzna] = (rand() % 250) + 51;
						else if (baza_danych[i].pieniadze == 2)
							pieniadze_mezczyzna[mezczyzna] = (rand() % 200) + 301;
						else if (baza_danych[i].pieniadze == 3)
							pieniadze_mezczyzna[mezczyzna] = (rand() % 500) + 501;
						else
							pieniadze_mezczyzna[mezczyzna] = (rand() % 4000) + 1001;
						++mezczyzna;
						break;
		}
	};
	
	plik_dane << "Kobieta" << endl;
	int j = 0;
	for (int  i = 0; i < 32; ++ i)
	{
		plik_dane << pieniadze_kobieta[i] << endl;
		suma_wszyscy += pieniadze_kobieta[i];
		pieniadze[j] = pieniadze_kobieta[i];
		++j;
	};
	
	suma_kobiety = suma_wszyscy;
		
	plik_dane << "Mezczyzna" << endl;
	 
	for (int  i = 0; i < 46; ++ i)
	{
		plik_dane << pieniadze_mezczyzna[i] << endl;
		suma_wszyscy += pieniadze_mezczyzna[i];
		pieniadze[j] = pieniadze_mezczyzna[i];
		++j;
	};
	
	suma_mezczyzni = suma_wszyscy - suma_kobiety;
	fstream plik("dane_r.txt", ios::out);
	int m = 0;
	int k = 0;
	for (int  i = 0; i < ilosc_osob; ++i)
	{
		if (baza_danych[i].plec == 0)
		{
			plik << pieniadze_kobieta[k] << "\t";
			plik << "kobieta" << "\t";
			switch (baza_danych[i].status_zawodowy)
			{
				case 0:
						plik << tab_odpowiedzi[3][0] << endl;
						break;
				case 1:
						plik << tab_odpowiedzi[3][1] << endl;
						break;
				case 2:
						plik << tab_odpowiedzi[3][2] << endl;
						break;
				case 3:
						plik << tab_odpowiedzi[3][3] << endl;
						break;
				case 4:
						plik << tab_odpowiedzi[3][4] << endl;
						break;
			};
			++k;
		}
		else
		{
			plik << pieniadze_mezczyzna[m] << "\t";
			plik << "mężczyzna" << "\t";
				switch (baza_danych[i].status_zawodowy)
			{
				case 0:
						plik << tab_odpowiedzi[3][0] << endl;
						break;
				case 1:
						plik << tab_odpowiedzi[3][1] << endl;
						break;
				case 2:
						plik << tab_odpowiedzi[3][2] << endl;
						break;
				case 3:
						plik << tab_odpowiedzi[3][3] << endl;
						break;
				case 4:
						plik << tab_odpowiedzi[3][4] << endl;
						break;
			};
			++m;
		}
	};
	plik.close();
	sort(pieniadze, pieniadze + 78);
	
	double srednia_wszyscy = (double)suma_wszyscy/ilosc_osob;
	double srednia_kobiety = (double)suma_kobiety/tab_zliczajaca[0][0];
	double srednia_mezczyzni = (double)suma_mezczyzni/tab_zliczajaca[0][1];
	
	for (int i = 0; i < ilosc_osob; ++i)
		tmp_wszyscy +=  pow(pieniadze[i] - srednia_wszyscy, 2);
	
	for (int i = 0; i < tab_zliczajaca[0][0]; ++i)
		tmp_kobiety +=  pow(pieniadze_kobieta[i] - srednia_kobiety, 2);
	
	for (int i = 0; i < tab_zliczajaca[0][1]; ++i)
		tmp_mezczyzni +=  pow(pieniadze_mezczyzna[i] - srednia_mezczyzni, 2);
		
	plik_dane << "Wszyscy" << endl;  
	plik_dane << "Srednia: ";
	plik_dane << srednia_wszyscy << endl;
	plik_dane << "Mediana: ";
	plik_dane << (double)(pieniadze[ilosc_osob/2 - 1] + pieniadze[ilosc_osob/2])/2 << endl;
	plik_dane << "Odchylenie standardowe: ";
	plik_dane << sqrt(tmp_wszyscy/ilosc_osob) << endl;
	
	plik_dane << "Kobiety" << endl;
	plik_dane << "Srednia: ";
	plik_dane << srednia_kobiety << endl;
	plik_dane << "Mediana: ";
	plik_dane << (double)(pieniadze_kobieta[tab_zliczajaca[0][0]/2 - 1] + pieniadze_kobieta[tab_zliczajaca[0][0]/2])/2 << endl;
	plik_dane << "Odchylenie standardowe: ";
	plik_dane << sqrt(tmp_kobiety/tab_zliczajaca[0][0]) << endl;
	
	plik_dane << "Mezczyzni" << endl;
	plik_dane << "Srednia: ";
	plik_dane << srednia_mezczyzni << endl;
	plik_dane << "Mediana: ";
	plik_dane << (double)(pieniadze_mezczyzna[tab_zliczajaca[0][1]/2 - 1] + pieniadze_mezczyzna[tab_zliczajaca[0][1]/2])/2 << endl;
	plik_dane << "Odchylenie standardowe: ";
	plik_dane << sqrt(tmp_mezczyzni/tab_zliczajaca[0][1]) << endl;
	
	plik_dane.close();
	/*//dane do obróbki w R
	sort(pieniadze_kobieta, pieniadze_kobieta + tab_zliczajaca[0][0]);
	sort(pieniadze_mezczyzna, pieniadze_mezczyzna + tab_zliczajaca[0][1]);
	fstream plik("dane_r.txt", ios::out);
	plik << "#1" << endl;
	for (int i = 0; i < ilosc_osob; ++i)
		plik << pieniadze[i] << "	";
	plik << endl;
	plik << "#2" << endl;
	for (int i = 0; i < tab_zliczajaca[0][0]; ++i)
		plik << pieniadze_kobieta[i] << "	";
	plik << endl;
	plik << "#3" << endl;
	for (int i = 0; i < tab_zliczajaca[0][1]; ++i)
		plik << pieniadze_mezczyzna[i] << "	";
	plik << endl;
	
	plik.close(); */
};

int main()
{
	Ankieta obj(78);
	
	obj.generator();
	obj.wyniki();
	obj.profile();
	obj.profile_pieniadze();
	
	return 0;
}
