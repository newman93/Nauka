/*
    Autor: Adrian Kowalski
*/

#include <iostream>
#include <list>
#include <map>
#include <utility>

using namespace std;

class GN
{
    private:
            class Polaczenie
            {
                public:
                        int wierzcholek_1;
                        int wierzcholek_2;
                        Polaczenie(int _w1, int _w2) : wierzcholek_1(_w1), wierzcholek_2(_w2) {}
                        bool operator <(const Polaczenie &_rhs ) const
                        {
                            return true;
                        }
            };
            map<Polaczenie, double> graf;
    public:
        GN() {}
        ~GN() {}
        void dodajKrawedz(int _w1, int _w2, double _dl);
        bool usunKrawedz(int _w1, int _w2);
        void sasiedzi(int _w, list<int> &_r);
        void pokaz();
};

void GN::dodajKrawedz(int _w1, int _w2, double _dl)
{
    bool czy_istnieje = false;
    
    map<Polaczenie, double>::iterator it;
    
    for (it = graf.begin(); it != graf.end(); ++it) 
    {
        if ((((it->first).wierzcholek_1 == _w1) && ((it->first).wierzcholek_2 == _w2))||(((it->first).wierzcholek_1 == _w2) && ((it->first).wierzcholek_2 == _w1)))     
        {
            it->second = _dl;
            czy_istnieje = true;
        }
    }   
   if (!czy_istnieje) 
    {
        Polaczenie *pomocniczy = new Polaczenie(_w1, _w2);
        graf.insert(pair<Polaczenie, double>(*(new Polaczenie(_w1,_w2)), _dl));
    }
};

bool GN::usunKrawedz(int _w1, int _w2)
{
    bool czy_usunieto = false;
    map<Polaczenie, double>::iterator it;
    for (it = graf.begin(); it != graf.end(); ++it) 
    {
        if ((((it->first).wierzcholek_1 == _w1) && ((it->first).wierzcholek_2 == _w2))||(((it->first).wierzcholek_1 == _w2) && ((it->first).wierzcholek_2 == _w1)))         
        {
            graf.erase(it);
            czy_usunieto = true;
        }
    }
    return czy_usunieto;
};

void GN::sasiedzi(int _w, list<int> &_r)
{
    map<Polaczenie, double>::iterator it;
    for (it = graf.begin(); it != graf.end(); ++it) 
    {
        if ((it->first).wierzcholek_2 == _w)
            _r.push_back((it->first).wierzcholek_1);
        if ((it->first).wierzcholek_1 == _w)
            _r.push_back((it->first).wierzcholek_2);
    }
};

void GN::pokaz()
{
    map<Polaczenie, double>::iterator it;
    for (it = graf.begin(); it != graf.end(); ++it)
    {
        cout << (it->first).wierzcholek_1 << "-" << (it->first).wierzcholek_2 << ": " << it->second << endl; 
    }
};

int main()
{
   try
   {
        GN obj;
        
        obj.dodajKrawedz(1,2,2);
        obj.dodajKrawedz(2,3,1);
        obj.dodajKrawedz(3,1,3);
        obj.dodajKrawedz(1,4,8);
        obj.dodajKrawedz(1,5,10);
        
        cout << "obj" << endl;
        
        obj.pokaz();
        
        obj.dodajKrawedz(2,1,3);
        
        cout << "obj_po_zmianie_1-2" << endl;
        
        obj.dodajKrawedz(2,1,3);
        
        obj.pokaz();
        
        cout << "obj_po_usunieciu_2-3" << endl;
        
        obj.usunKrawedz(2,3);        
        
        obj.pokaz();
        
        cout << "sasiedzi_1" << endl;
        
        list<int> lista;
        obj.sasiedzi(1, lista);
        
        list<int>::iterator ite;
        
        for (ite = lista.begin(); ite != lista.end(); ++ite)
            cout << *ite << endl;
        
        
   }
   catch (...)
   {
       cout << "Wyjatek!" <<  endl;
   }
   
   return 0;
}
