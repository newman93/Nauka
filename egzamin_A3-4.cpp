/*
    Autor: Adrian Kowalski
*/

#include <iostream>

using namespace std;

emplate <class T>
struct Element
{
    T value;
    Element<T> *next;
};

template <class T>
class Iterator;

template <class T>
class List
{
private:
    typedef struct
    {
    	int counter;
		Element<T> *head;
		Element<T> *tail;
	} Info;
	Info inf;
public:
    friend class Iterator<T>;
    Iterator<T> *iterator();
	List() { inf.head = inf.tail = nullptr; inf.counter = 0; }
	~List(){ make_empty(); }
	bool push_back(const T &_a);
	template<typename U> friend List<U> operator+(const List<U> &_lhs, const List<U> &_rhs);
	void make_empty(); //dodatkowo
	void show(); //
	bool is_empty() { return (inf.head == nullptr); } //
	List(const List<T> &_a);
	List<T> & operator=(const List<T> &_a);
	List<T> & operator+=(const List<T> &_a);
    Element<T> * getHead() { return inf.head; }
};

template <class T>
class Iterator
{
    private:
            Element<T> *el;
    public:
            Iterator() : el(nullptr) {}
            Iterator(Element<T> *_e) : el(_e) {}
            T & get() { return el->value; }
            Iterator & operator++() { if (!isEnd()) { el = el->next; } return *this; }
            bool isEnd() { if (el->next == nullptr) { return true; } else { return false; } } 
};

template <class T>
List<T>::List(const List<T> &_a)
{
	inf.head = inf.tail = nullptr;
	inf.counter = 0;
	*this = _a;
};

template <class T>
List<T> & List<T>::operator=(const List<T> &_a)
{
	this->make_empty();
	Element<T> *tmp = _a.inf.head;
	while (tmp != nullptr)
	{
		this->push_back(tmp->value);
		tmp = tmp->next;
	}
	return *this;
};

template <class T>
bool List<T>::push_back(const T &_a)
{
	Element<T> *obj = new Element<T>;
	obj->value = _a;

	if (is_empty())
	{
		obj->next = nullptr;
		inf.head = inf.tail = obj;
		inf.counter = 1;
	}
	else
	{
		inf.tail->next = obj;
		Element<T> *tmp = inf.tail;
		obj->next = nullptr;
		inf.tail = obj;
		inf.counter++;
	}
	return true;
};

template <class T>
List<T> operator+(const List<T> &_lhs, const List<T> &_rhs)
{
	List<T> result = _lhs;
	result += _rhs;
	return result;
};

template <class T>
List<T> & List<T>::operator+=(const List<T> &_a)
{
	Element<T> *tmp = _a.inf.head;
	while (tmp != nullptr)
	{
		this->push_back(tmp->value);
		tmp = tmp->next;
	}
	return *this;
};

template <class T>
void List<T>::make_empty()
{
	if (!is_empty())
	{
		if (inf.head == inf.tail)
		{
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
		else
		{
			Element<T> *tmp = inf.head;
			while (tmp != inf.tail)
			{
				tmp = tmp->next;
				delete inf.head;
				inf.head = tmp;
			}
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
	}
};

template <class T>
void List<T>::show()
{
	if (!is_empty())
	{
		Element<T> *tmp = inf.head;
		int i = 0;
		while (tmp != nullptr)
		{
			cout << ++i << ": " << tmp->value << endl;
			tmp = tmp->next;
		}
	}

};

int main()
{
	try
	{
		List<int> list_1;
		list_1.push_back(10);
		list_1.push_back(20);
		list_1.push_back(30);

		cout << "list_1" << endl;

		list_1.show();

		List<int> list_2;

		list_2.push_back(40);
		list_2.push_back(50);

		cout << "list_2" << endl;

		list_2.show();

		List<int> list_3;

		list_3 = list_1 + list_2;

		cout << "List_1 + list_2" << endl;

		list_3.show();
        
        cout << "Iterator list_3" << endl;
        
        Iterator<int> it(list_3.getHead());
        cout << it.get() << endl;
        ++it;
        cout << it.get() << endl;
           ++it;
        cout << it.get() << endl;
           ++it;
        cout << it.get() << endl;
           ++it;
        cout << it.get() << endl;
	}
	catch (...)
	{
		cout << "Wyjatek!" << endl;
	}
	return 0;
}
