/*
    Autor: Adrian Kowalski
*/

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class TablicaTekstow
{
	private:
			char **tab;
			int rozmiar;
	public:
			TablicaTekstow() : tab(nullptr), rozmiar(0) {} 
			~TablicaTekstow();
			void dodaj(const char *_t);
			void pokaz();
			TablicaTekstow(const TablicaTekstow &_t);
			TablicaTekstow & operator=(const TablicaTekstow &_t);
};

TablicaTekstow::~TablicaTekstow()
{
	for (int i = 0; i < rozmiar; ++i)
		delete tab[i];
	delete []tab;
};

void TablicaTekstow::dodaj(const char *_t)
{
	if (rozmiar == 0)
	{
		tab = new char*[1];
		tab[0] = new char[strlen(_t)+1];
		strcpy(tab[0],_t);
		rozmiar = 1;
	}
	else
	{
		char **tmp = new char*[rozmiar];
		for (int i = 0; i < rozmiar; ++i)
		{
			tmp[i] = new char[strlen(tab[i])+1];
			strcpy(tmp[i],tab[i]);
			delete tab[i];
		}
		delete []tab;
		++rozmiar;
		tab = new char*[rozmiar];
		for (int i = 0; i < (rozmiar-1); ++i)
		{
			tab[i] = new char[strlen(tmp[i])+1];
			strcpy(tab[i], tmp[i]);
			delete tmp[i];
		}
		delete []tmp;
		tab[rozmiar-1] = new char[strlen(_t)+1];
		strcpy(tab[rozmiar-1], _t);
	}
};

void TablicaTekstow::pokaz()
{
	for (int i = 0; i < rozmiar; ++i)
		cout << tab[i] << endl;
};

TablicaTekstow::TablicaTekstow(const TablicaTekstow &_t)
{
	rozmiar = _t.rozmiar;
	tab = new char*[rozmiar];
	for (int i = 0; i < rozmiar; ++i)
	{
		tab[i] = new char[strlen(_t.tab[i])+1];
		strcpy(tab[i], _t.tab[i]);
	}
};

TablicaTekstow & TablicaTekstow::operator=(const TablicaTekstow &_t)
{
	for (int i = 0; i < rozmiar; ++i)
		delete tab[i];
	delete []tab;
	
	rozmiar = _t.rozmiar;
	tab = new char*[rozmiar];
	for (int i = 0; i < rozmiar; ++i)
	{
		tab[i] = new char[strlen(_t.tab[i])+1];
		strcpy(tab[i], _t.tab[i]);
	}
	
	return *this;
};

int main()
{
	try
	{
		TablicaTekstow obj_1;
		TablicaTekstow obj_2;
		
		const char *tmp_1 = "Czesc! Jutro masz egzamin!";
		const char *tmp_2 = "Co?! Jaki egzamin?!";
		const char *tmp_3 = "Egzamin z C++";
		const char *tmp_4 = "No nie... Przecież nie zdam :(";
		const char *tmp_5 = "Nie narzekaj, tylko bierz sie do solidnej nauki";
		
		obj_1.dodaj(tmp_1);
		obj_1.dodaj(tmp_2);
		
		cout << "obj_1" << endl;
		
		obj_1.pokaz();
		
		obj_2.dodaj(tmp_3);
		obj_2.dodaj(tmp_4);
		obj_2.dodaj(tmp_5);
		
		cout << "obj_2" << endl;
	
		obj_2.pokaz();
		
		obj_1 = obj_2;
		
		cout << "obj_1 = obj_2" << endl;
		
		obj_1.pokaz();
	}
	catch (...)
	{
		cout << "Wyjatek!" << endl;
	};  
	
	return 0;
}
