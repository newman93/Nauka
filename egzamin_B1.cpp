/*
    Autor: Adrian Kowalski
*/

#include  <iostream>
#include <cstring>

using namespace std;

class Osoba
{
	private:
			char imie[32];
			char nazw[32];
	public:
			Osoba(const char *_i, const char *_n) { strcpy(imie, _i); strcpy(nazw, _n); } 
			~Osoba() {}
			char * getImie() { return imie; }
			char * getNazw() { return nazw;} 
};

struct Element
{
	Osoba *obj;
	Element *next;
};

class List
{
	private:
			typedef struct
			{
				int counter;
				Element * head;
				Element * tail;
			} Info;
			Info inf;
	public:
		List() { inf.head = inf.tail = nullptr; inf.counter = 0; }
		~List() { make_empty(); }
		List(const List & _l);
		List & operator=(const List &_l);
		bool is_empty() { return (inf.head == nullptr); }		//dodatkowo
		void make_empty();										//
		void show();											//
		bool dodaj(const char *imie, const char *nazw);
};


void List::make_empty()
{
	if (!is_empty())
	{
		if (inf.head == inf.tail)
		{
			delete inf.head->obj;
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
		else
		{
			Element *tmp = inf.head;
			while (tmp != inf.tail)
			{
				tmp = tmp->next;
				delete inf.head->obj;
				delete inf.head;
				inf.head = tmp;
			}
			delete inf.head->obj;
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
	}
};

bool List::dodaj(const char *imie, const char *nazw)
{
	Element *el = new Element;
	el->obj = new Osoba(imie, nazw);
	
	if(is_empty())
	{
		el->next = nullptr;
		inf.head = inf.tail = el;
		inf.counter = 1;
	}
	else
	{
		(inf.tail)->next = el;
		Element *tmp = inf.tail;
		el->next = nullptr;
		inf.tail = el;
		el = tmp;
		inf.counter += 1;
	}
	
	return true;
};

void List::show()
{
	if (!is_empty())
	{
		Element *tmp = inf.head;
		int i = 0;
		while (tmp != nullptr)
		{
			cout << ++i << " " << tmp->obj->getImie() << " " << tmp->obj->getNazw() << endl;
			tmp = tmp->next;
		}
	}
};

List::List(const List & _l)
{
	Element *tmp = _l.inf.head;
	
	Element *el = new Element;
	el->obj = new Osoba(tmp->obj->getImie(), tmp->obj->getNazw());
	
	el->next = nullptr;
	inf.head = inf.tail = el;
	inf.counter = 1;
	
	tmp = tmp->next;
	while (tmp != nullptr)
	{
		Element *el = new Element;
		el->obj = new Osoba(tmp->obj->getImie(), tmp->obj->getNazw());
		inf.tail->next = el;
		Element *tmp_1 = inf.tail;
		el->next = nullptr;
		inf.tail = el;
		el = tmp_1;
		inf.counter += 1;
		tmp = tmp->next;
	}
};
		
List & List::operator=(const List &_l)
{
	this->make_empty();
	
	Element *tmp = _l.inf.head;
	
	Element *el = new Element;
	el->obj = new Osoba(tmp->obj->getImie(), tmp->obj->getNazw());
	
	el->next = nullptr;
	this->inf.head = this->inf.tail = el;
	this->inf.counter = 1;
	
	tmp = tmp->next;
	while (tmp != nullptr)
	{
		Element *el = new Element;
		el->obj = new Osoba(tmp->obj->getImie(), tmp->obj->getNazw());
		this->inf.tail->next = el;
		Element *tmp_1 = this->inf.tail;
		el->next = nullptr;
		this->inf.tail = el;
		el = tmp_1;
		this->inf.counter += 1;
		tmp = tmp->next;
	}
	
	return *this;
};

int main()
{
	try
	{
		List obj_1;
		obj_1.dodaj("Adrian", "Kowalski");
		obj_1.dodaj("Adam", "Kowalski");
		obj_1.dodaj("Antoni", "Kowalski");
		cout << "obj_1" << endl;
		obj_1.show();
		List obj_2;
		obj_2.dodaj("Mateusz", "Nowak");
		obj_2.dodaj("Marcin" , "Nowak");
		cout << "obj_2" << endl;
		obj_2.show();
		List obj_3;
		obj_3.dodaj("Tomasz", "Szpak");
		cout << "obj_3" << endl;
		obj_3.show();
		obj_2 = obj_3;
		cout << "obj_2 = obj_3" << endl;
		obj_2.show();
		obj_3 = obj_1;
		cout << "obj_3 = obj_1" << endl;
		obj_3.show();
	}
	catch(...)
	{
		cout << "Wyjatek!" << endl;
	}
	
	return 0;
}
