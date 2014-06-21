/*
	Author: Adrian Kowalski
*/

/*
    |-----------------------------------------------------------------------|
    |	|---------------|	|---------------|	|---------------|   |
    |	|     value	|	|     value	|	|     value	|   |
    |	|---------------|	|---------------|	|---------------|   |
|---|-->|     next	|------>|     next	|------>|     next	|---|---|
|   |	|---------------|	|---------------|	|---------------|   |   |
|   |---|     prev      |<------|     prev      |<------|     prev      |<--|	|				
| 	|---------------|	|---------------|	|---------------|       |
|		^						^		|
|-------------------------------------------------------------------------------|
		|						|
		|		|---------------|		|
		|---------------|     head      |		|
				|---------------|		|
				|     tail      |---------------|
				|---------------|		
				|    counter    |
				|---------------|


*/
#include <iostream>

using namespace std;

typedef struct el
{
	int value;
	struct el *next;	
	struct el *prev;
} Element;

class List
{
	private:				//dodac mozliwosc przesuwania ekementow listy
		typedef struct
		{
			int counter;
			Element *head;
			Element *tail;
		} Info;
		Info inf;
	public:
		List() { inf.head = inf.tail = nullptr; inf.counter = 0; }			
		~List();
		void push_back(int _x);
		void pop_back();	
		bool empty() { return (inf.head == nullptr); } 
		void show();
};	

List::~List()
{	
	if (inf.head == inf.tail)
	{
		delete inf.head;
	}
	else
	{
		Element *tmp;
		tmp = inf.head->prev;
		while (tmp != inf.head)
		{
			tmp = tmp->prev;
			delete tmp->next;
		}
		delete inf.head;
	}
}

void List::push_back(int _x)
{
	Element *obj = new Element;
	obj->value = _x;

	if (empty())
	{
		obj->next = obj;
		obj->prev = obj;
		inf.head = inf.tail = obj;
		inf.counter = 1;
	}
	else
	{
		obj->next = inf.head;
		obj->prev = inf.tail;
		(inf.tail)->next = obj;
		inf.tail = obj;
		inf.head->prev = inf.tail;
		inf.counter += 1;
	}
}

void List::pop_back()
{
	if (!empty())
	{
		if (inf.counter > 1)
		{
			inf.tail->prev->next = inf.head; 
			inf.head->prev = inf.tail->prev;
			delete inf.tail;
			inf.tail = inf.head->prev;
			inf.counter -= 1;
		}
		else
		{
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
	}
	else
		cout << "List is empty!" << endl;
		
}

void List::show()
{
	Element *tmp;
	int i = 1;
	tmp = inf.head;
	
	if (!empty())
	{
		do
		{
			cout << " #" << i << ": " << tmp->value;
			++i; 
			tmp = tmp->next;
		} while (tmp != inf.head);
	cout << endl;
	}
	else
		cout << "List is empty!" << endl;
}

int main()
{
	List cdll;
	int choice;
	int value;
	
	cout << "Circular Doubly Linked List" << endl;
	
	do
	{
		cout << "1. Push back" << endl;
		cout << "2. Pop back" << endl;
		cout << "3. Show list" << endl;
		cout << "4. Exit" << endl;
		cin >> choice;
		
		switch (choice)
		{
			case 1:
					cout << "Value: ";
					cin >> value;
					cout << endl;
					cdll.push_back(value);
					break;
			case 2:
					cdll.pop_back();
					break;
			case 3:
					cdll.show();
					break;
			case 4:
					break;
			default: 
					cout << "Error!" << endl;
					break;
		}
	} while (choice != 4);
	return 0;
}
