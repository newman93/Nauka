/* 
    Autor: Adrian Kowalski
*/
//powtórka przed kolokwium

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm> 

using namespace std;

class Wisielec
{
	private:
				string haslo;
				string zaszyfrowane_haslo;
				string sprawdzone;
				int licznik_pozycji;
				int stan;
				int stan_gry; // 0 - w trakcie, 1 - wygrana, 2 - przegrana
	public:
				Wisielec(string _h = "", string _z = "", string _spr = "", int _s = 0, int _s_g = 0, int _l_p = 0) : haslo(_h), zaszyfrowane_haslo(_z), stan(_s), stan_gry(_s_g), licznik_pozycji(_l_p), sprawdzone(_spr) {}
				~Wisielec();
				void ustaw_haslo(string _h);
				void rysuj_stan_gry();
				void rysuj_stan_hasla();
				bool sprawdz(char _s);
				int zwroc_stan_gry() { return stan_gry; }
				void czysc() { printf("\033[2J"); printf("\033[0;0f"); }
};

Wisielec::~Wisielec()
{
};

void Wisielec::ustaw_haslo(string _h)
{
	haslo = _h;
	transform(haslo.begin(), haslo.end(), haslo.begin(), ::tolower);
	
	for (int i = 0; i < haslo.size(); ++i)
		zaszyfrowane_haslo += "_";
};

void Wisielec::rysuj_stan_hasla()
{
	cout << "Haslo: " << endl;
	cout << zaszyfrowane_haslo << endl;
};

void Wisielec::rysuj_stan_gry()
{
	cout << "   Stan gry  " << endl;
	
	switch (stan)
	{
		case 0: 
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout <<"             " << endl;
				break;
		case 1:
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout <<"/            " << endl;
				break;
		case 2:
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout << "            " << endl;
				cout <<"/\\          " << endl;
				break;
		case 3:
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 4:
				cout << "|---------  " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 5:
				cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 6:
				cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|        O  " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 7:
				cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|        O  " << endl;
				cout << "|        |  " << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 8:
				cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|        O  " << endl;
				cout << "|        |\\" << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 9:
				cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|        O  " << endl;
				cout << "|       /|\\" << endl;
				cout << "|           " << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 10:
			    cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|        O  " << endl;
				cout << "|       /|\\" << endl;
				cout << "|         \\" << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
		case 11:
				cout << "|---------  " << endl;
				cout << "|        |  " << endl;
				cout << "|        O  " << endl;
				cout << "|       /|\\" << endl;
				cout << "|       / \\" << endl;
				cout << "|           " << endl;
				cout <<"/\\          " << endl;
				break;
	};
};

bool Wisielec::sprawdz(char _s)
{
    bool flaga = false;
    
    for (int i = 0; i < sprawdzone.size(); ++i)
		if (sprawdzone[i] == _s) 
			return false;
	
    for (int i = 0; i < haslo.size(); ++i)
    {
		if (haslo[i] == tolower(_s))
		{
			++licznik_pozycji;
			flaga = true;
			zaszyfrowane_haslo[i] = tolower(_s);
		};
	};
		
	if (flaga == false) 
	{
		++stan;
		if (stan == 11) 
			stan_gry = 2;
	}
	else
		sprawdzone += _s;
	
	if (licznik_pozycji == haslo.size())
		stan_gry = 1;

	return flaga;
};

int main()
{
	int wybor;
	
	do
	{	
		Wisielec game;
	
	    string haslo;
	    
		cout << "            " << endl;
		cout << "  Wisielec  " << endl;
		cout << "Wprowadz haslo: ";
		cin >> haslo;
		cin.get();
		game.ustaw_haslo(haslo);
	
		game.czysc();
	
		char znak;
	
		do
		{
			cout << "            " << endl;
			cout << "  Wisielec  " << endl;
			game.rysuj_stan_hasla();
			game.rysuj_stan_gry();
			cout << "Wprowadz znak: ";
			cin >> znak;
			cin.get();
			game.sprawdz(znak);
			game.czysc();
		} while (game.zwroc_stan_gry() == 0);
	 
		switch (game.zwroc_stan_gry()) 
		{
			case 1:
					cout << " Wygrałeś!  " << endl;
					break;
			case 2:
					cout << "Przegrałeś! " << endl;
					break;
		};
		
		do
		{
			cout << " Chcesz zagrać ponownie?" << endl;
			cout << " 1. Tak " << endl;
			cout << " 2. Nie " << endl;
			cin >> wybor;
			game.czysc();
		} while (wybor != 1 && wybor != 2);
		
	} while (wybor != 2 ); 
	return 0;
}
