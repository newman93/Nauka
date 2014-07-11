/* 
  Autor: Adrian Kowalski
*/

#include <iostream>

using std::cout;
using std::endl;

template <class K, class V>
class Iterator;

template <class K, class V>
class Rel
{
	private:
			typedef struct
			{
				K pierwszy;
				V drugi;
			} Para;
			Para *tab;
			int licznik;
	public:
			Iterator<K,V> * interator(); 
			friend class Iterator<K,V>;
			Rel() : tab(nullptr), licznik(0) {}
			~Rel() { delete []tab; }
			bool dodaj(const K &_k, const V &_v);
			bool znajdz(const K &_k, const V &_v);
			Rel & operator+=(const Rel &_r);
			void pokaz();								//dodatkowo
};

template <class K, class V>
bool Rel<K,V>::dodaj(const K &_k, const V &_v)
{
	for (int i = 0; i < licznik; ++i)
		if (tab[i].pierwszy == _k && tab[i].drugi == _v)
			return false;
				
	Para *tmp = new Para[licznik];
	for (int i = 0; i < licznik; ++i)
		tmp[i] = tab[i];
	delete []tab;
	tab = new Para[licznik+1];
	for (int i = 0; i < licznik; ++i)
		tab[i] = tmp[i];
	tab[licznik] = { _k, _v };
	++licznik;
	
	return true;
};

template <class K, class V>
bool Rel<K,V>::znajdz(const K &_k, const V &_v)
{
	for (int i = 0; i < licznik; ++i)
		if (tab[i].pierwszy == _k && tab[i].drugi == _v)
			return true;
	return false;
};
			
template <class K, class V>			
Rel<K,V> & Rel<K,V>::operator+=(const Rel &_r)
{
	for (int i = 0; i < _r.licznik; ++i)
		if (!this->znajdz(_r.tab[i].pierwszy, _r.tab[i].drugi))
			this->dodaj(_r.tab[i].pierwszy, _r.tab[i].drugi);
	return *this;
}

template <class K, class V>
void Rel<K,V>::pokaz()
{
	for (int i = 0; i < licznik; ++i)
		cout << tab[i].pierwszy << " " << tab[i].drugi << endl;
};

template <class K, class V>
class Iterator
{
	private:
			Rel<K,V> *re;
			int pozycja;
	public:
			Iterator() : re(nullptr), pozycja(0) {} 
			Iterator(const Rel<K,V> *_r) { re = _r; pozycja = 0; } 
			const K & pierwszy() { return re->tab[pozycja].pierwszy; }
			const V & drugi() { return re->tab[pozycja].drugi; }
			Iterator<K,V> & operator++() { if(!czyKoniec()) { ++pozycja; } return *this; }
			bool czyKoniec();
		
};

template <class K, class V>
bool Iterator<K,V>::czyKoniec()
{
	if (pozycja == (re->licznik - 1))
		return true;
	else
		return false;
};

int main()
{
	try
	{
		Rel<int, double> rel_1;
		
		rel_1.dodaj(1, 2.2);
		rel_1.dodaj(1, 2.3);
		rel_1.dodaj(2, 2.2);
		rel_1.dodaj(2, 2.2);
		rel_1.dodaj(5, 8.8);
		cout << "rel_1" << endl;
		rel_1.pokaz();
		
		Rel<int, double> rel_2;
		
		rel_2.dodaj(5, 8.8);
		rel_2.dodaj(9, 10.15);
		cout << "rel_2" << endl;
		rel_2.pokaz();
		
		if (rel_1.znajdz(1, 2.2))
			cout << "Znalazlem: (1, 2.2)" << endl;
		else
			cout << "Nie znalazlem: (1, 2.2)" << endl;
			
		rel_1 += rel_2;
		
		cout << "rel_1 += rel_2" << endl;
		rel_1.pokaz();
		
		cout << "Iterator" << endl;
		cout << "rel_2" << endl;
		Iterator<int, double> it(&rel_2);
		cout << it.pierwszy() << " " << it.drugi() << endl;
		++it;
		cout << it.pierwszy() << " " << it.drugi() << endl;
		++it;
		cout << it.pierwszy() << " " << it.drugi() << endl;
	}
	catch(...)
	{
		cout << "Wyjatek!" << endl;
	}
	return 0;
}
