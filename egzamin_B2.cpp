/*
    Autor: Adrian Kowalski
*/

#include <iostream>
#include <string>
#include <list>
#include <algorithm> 

using namespace std;

class Towar
{
	private:
			string nazwa;
			string kategoria;
			double cena;
			string kod;
	public:
			Towar(string _n, string _k, double _c, string _ko) : nazwa(_n), kategoria(_k), cena(_c), kod(_ko) {}
			~Towar() {}
			string getNazwa() const { return nazwa; }
			string getKategoria() const { return kategoria; }
			string getKod() const { return kod; }
			double getCena() const { return cena; }
			void setNazwa(string _n) { nazwa = _n; }
			void setKategoria(string _k) { kategoria = _k; }
			void setCena(double _c) { cena = _c; }
};

class LT
{
	private:
			list<Towar> lista;
	public:
			LT() {}
			~LT() { lista.clear(); }
			void dodaj(const Towar &_t);
			bool usun(const char *_kod);
			void szukaj(const char *_txt, list<Towar> &_result);
			void pokaz();
};

struct by_kod 
{
    string kod;
    by_kod(string _k) : kod(_k) { }
    bool operator()(const Towar &_t) const { return kod == _t.getKod(); }
};

void LT::dodaj(const Towar &_t)
{
	list<Towar>::iterator it = find_if(lista.begin(), lista.end(), by_kod(_t.getKod()));
	
	if (it != lista.end())
	{
		it->setNazwa(_t.getNazwa());
		it->setKategoria(_t.getKategoria());
		it->setCena(_t.getCena());
	}
	else
		lista.push_back(_t);
};

bool LT::usun(const char *kod)
{
	list<Towar>::iterator it = find_if(lista.begin(), lista.end(), by_kod(kod));
	
	if (it != lista.end())
	{
		lista.erase(it);
		return true;
	}
	else
		return false;
}; 

void LT::szukaj(const char *_txt, list<Towar> &_result)
{
	for (list<Towar>::iterator it = lista.begin(); it != lista.end(); ++it)
		if (it->getNazwa().find(_txt) != string::npos || it->getKategoria().find(_txt) != string::npos)
			_result.push_back(*it);
};

void LT::pokaz()
{
	for (list<Towar>::iterator it = lista.begin(); it != lista.end(); ++it)
		cout << it->getNazwa() << " " << it->getKategoria() << " " << it->getKod() << " " << it->getCena() << endl;
};

int main()
{
	try
	{
		LT obj;
		list<Towar> result;
		Towar t_1("laptop", "elektronika", 2500.50, "1225");
		Towar t_2("netbook", "elektronika", 3300.50, "1225");
		Towar t_3("krzeslo", "meble", 100, "3345");
		Towar t_4("krzem", "pierwiastek", 50.25, "6678");
		Towar t_5("krzesiwo", "przedmiot", 50.25, "3320");
		obj.dodaj(t_1);
		obj.dodaj(t_2);
		obj.dodaj(t_3);
		obj.dodaj(t_4);
		obj.dodaj(t_5);
		obj.pokaz();
		if (obj.usun("3345"))
			cout << "Usunieto" <<  endl;
		else
			cout << "Nie usunieto" << endl;
		obj.pokaz();
		obj.szukaj("krze", result);
		cout << "Result" << endl;
		for (list<Towar>::iterator it = result.begin(); it != result.end(); ++it)
			cout << it->getNazwa() << " " << it->getKategoria() << " " << it->getKod() << " " << it->getCena() << endl;
	}
	catch(...)
	{
		cout << "Wyjatek!" << endl;
	}
	
	return 0;
}
