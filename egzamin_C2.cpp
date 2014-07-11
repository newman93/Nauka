/*
    Autor: Adrian Kowalski
*/

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Osoba
{
    protected:
			string imie;
			string nazw;
			string pesel;
	public:
			Osoba(string _i, string _n, string _p) : imie(_i), nazw(_n), pesel(_p) {}
			~Osoba() {}
			void setImie(const char *_i) { imie = _i; }
			void setNazw(const char *_n) { nazw = _n; }
			string getImie() { return imie; }
			string getNazw() { return nazw; }
			string getPesel() { return pesel; }
};

struct by_pesel 
{
    const string pesel;
    by_pesel(string pesel) : pesel(pesel) {}
    bool operator()(Osoba &_os ) { return pesel == _os.getPesel(); }
};

struct the_same 
{
    const string imie;
    const string nazw;
    const string pesel;
    the_same(string imie, string nazw, string pesel) : imie(imie), nazw(nazw), pesel(pesel) {}
    bool operator()(Osoba & _os ) {  if (pesel == _os.getPesel() && imie == _os.getImie() && nazw == _os.getNazw()) return true; else return false; }
};

class ZbiorOsob
{
	private:
			list<Osoba> lista;
	public:
			ZbiorOsob() {}																//dodatkowo do testow			
			~ZbiorOsob() { lista.clear(); }											    //
			void show();															    //
			void dodaj(const char *imie, const char *nazw, const char *pesel);
			bool find(const char *pesel);
			bool operator<(ZbiorOsob & _zo);
};

void ZbiorOsob::show()
{
	for (list<Osoba>::iterator it = lista.begin(); it != lista.end(); ++it)
		cout << it->getImie() << " " << it->getNazw() << " " << it->getPesel() << endl;
}; 

void ZbiorOsob::dodaj(const char *imie, const char *nazw, const char *pesel)
{
	list<Osoba>::iterator it = find_if(lista.begin(), lista.end(), by_pesel(pesel));

	if (it != lista.end())
	{
		it->setImie(imie);
		it->setNazw(nazw);
	}
	else
	{
		lista.push_back(Osoba(imie, nazw, pesel));
	}
};

bool ZbiorOsob::find(const char *pesel)
{
	if (find_if(lista.begin(), lista.end(), by_pesel(pesel)) == lista.end())
		return false;
	else
		return true;
};		

bool  ZbiorOsob::operator<(ZbiorOsob & _zo) 
{
    bool czy_zawiera = false;
    if (lista.size() <= _zo.lista.size())
    {
        czy_zawiera = true;
        list<Osoba>::iterator it;
        for (it = lista.begin(); it != lista.end(); ++it)
            if (!_zo.find((*it).getPesel().c_str()))
                czy_zawiera = false;
        }
    return czy_zawiera;
};

int main()
{
	try
	{
		ZbiorOsob obj_1;
		obj_1.dodaj("Adrian", "Kowalski", "22221999");
		obj_1.dodaj("Adam", "Kowalski", "21041999");
        
        cout << "obj_1" << endl;
        
		obj_1.show();
		if (obj_1.find("21041999"))
			cout << "Znaleziono" << endl;
		else
		cout << "Nie znaleziono" << endl;
		obj_1.dodaj("Kamil", "Kowalski", "22221999");
		obj_1.show();
        
        ZbiorOsob obj_2;
    	obj_2.dodaj("Kamil", "Kowalski", "22221999");
        
        cout << "obj_2" << endl;
        
		obj_2.show();
        
        cout << "obj_2 < obj_1" << endl;
        
        if (obj_2 < obj_1)
            cout << "zawiera_sie" << endl;
        else
            cout << "nie_zawiera_sie" << endl;
            
	} catch(...)
	{
		cout << "Wyjatek!" << endl;
	}
	return 0;
}
