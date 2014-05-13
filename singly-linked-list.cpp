/*
	Author: Adrian Kowalski
*/

/*

    	|---------------|	|---------------|	|---------------|   
    	|     value	|     	|     value	|     	|     value	|
    	|---------------|	|---------------|	|---------------|   
	|     next	|------>|     next	|------>|     next	|------> NULL
	|---------------|	|---------------|	|---------------|      
		^						^
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
#include <string>

using namespace std;

template <class DataType>
struct Element
{
	DataType value;
	Element<DataType> *next;	
	Element<DataType> *prev;
};

template <class DataType>
class List
{
	private:
		typedef struct
		{
			int counter;
			Element<DataType> *head;
			Element<DataType> *tail;
		} Info;
		Info inf;
	public:
		List() { inf.head = inf.tail = nullptr; inf.counter = 0; }			
		~List();
		void push_back(DataType _x);
		void pop_back();
		void push_front(DataType _x);
		void pop_front();
		void insert_at_position(DataType _x, int _p);
		bool find(DataType _f);	
		bool is_empty() { return (inf.head == nullptr); } 
		void make_empty();
		void show();
};	

int main()
{
	List <int> l_1;

	try
	{
		l_1.push_back(10);
		l_1.push_back(20);
		l_1.push_back(30);
		l_1.pop_front();
		l_1.pop_back();
		l_1.push_front(1);
		l_1.push_back(4);
		l_1.insert_at_position(3,3);
		l_1.find(5)? cout << "False\n" : cout << "True\n";
		l_1.make_empty();
		l_1.push_front(1);
		l_1.insert_at_position(2,2);
		l_1.show();
		
	} catch(string exception)
	{
		cout << exception; 
	}
	
	return 0;
};

template <class DataType>
List<DataType>::~List()
{
	make_empty();
};

template <class DataType>
void List<DataType>::push_back(DataType _x)
{
	Element<DataType> *obj = new Element<DataType>;
	obj->value = _x;

	if (is_empty())
	{
		obj->next = nullptr;
		inf.head = inf.tail = obj;
		inf.counter = 1;
	}
	else
	{
		(inf.tail)->next = obj;
		Element<DataType> *tmp = inf.tail;  
		obj->next = nullptr;
		inf.tail = obj;
		obj = tmp;
		inf.counter += 1;
	}
};

template <class DataType>
void List<DataType>::push_front(DataType _x)
{
	Element<DataType> *obj = new Element<DataType>;
	obj->value = _x;
	
	if (is_empty())
	{
		obj->next = nullptr;
		inf.head = inf.tail = obj;
		inf.counter = 1;
	}
	else
	{
		Element<DataType> *tmp = obj;  
		obj->next = inf.head;
		obj = inf.head;
		inf.head = tmp;
		inf.counter += 1;
	}
};

template <class DataType>	
void List<DataType>::pop_back()
{
	if (!is_empty())
	{
		if (inf.counter > 1)
		{
			Element<DataType> *tmp = inf.head;
			while (tmp->next->next != nullptr)
				tmp = tmp->next;
			delete inf.tail;
			tmp->next = nullptr;
			inf.tail = tmp;
			inf.counter -= 1;
		}
		else
		{
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
	} else
	{
		string exception = "List is empty!\n";
		throw exception;
	}
};

template <class DataType>		
void List<DataType>::pop_front()
{
	if (!is_empty())
	{
		if (inf.counter > 1)
		{
			Element<DataType> *tmp = inf.head->next;
			delete inf.head;
			inf.head = tmp;
			inf.counter -= 1;
		}
		else
		{
			delete inf.head;
			inf.head = inf.tail = nullptr;
			inf.counter = 0;
		}
	} else
	{
		string exception = "List is empty!\n";
		throw exception;
	}
};

template <class DataType>
void List<DataType>::insert_at_position(DataType _x, int _p)
{
	if (_p > inf.counter + 1)
	{
		string exception = "List ends on the earlier position!"; 
		throw exception;
	} else if ( _p < 0)
	{
		string exception = "Position can not be a negative number!\n";
		throw exception;
	} else if (_p == inf.counter && is_empty())
	{
		Element<DataType> *obj = new Element<DataType>;
		obj->value = _x;
		
		obj->next = nullptr;
		inf.head = inf.tail = obj;
		inf.counter = 1;
	} else
	{
		Element<DataType> *obj = new Element<DataType>;
		obj->value = _x;
		
		Element<DataType> *tmp = new Element<DataType>;
		tmp = inf.head;
		
		for (int i = 1; i < _p-1; ++i)
			tmp = tmp->next;
		obj->next = tmp->next;
		tmp->next = obj;
	}
};

template <class DataType>
bool List<DataType>::find(DataType _f)
{
	bool flag = false;;
	
	if (!is_empty())
	{
		Element<DataType> *tmp = inf.head;
		while (tmp->value != _f && tmp->next != nullptr)
			tmp = tmp->next;
		if (tmp->value == _f)
			flag = true;
	} else
	{	
		string exception = "List is empty!\n";
		throw exception;
	}
	return flag;
};	

template <class DataType>
void List<DataType>::make_empty()
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
			Element<DataType> *tmp = inf.head;
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
	} else
	{	
		string exception = "List is empty!\n";
		throw exception;
	}
};

template <class DataType>
void List<DataType>::show()
{
	if (!is_empty())
	{
		Element<DataType> *tmp = inf.head;
		int i{0};
		while (tmp != nullptr)
		{
			cout << "#" << ++i << ": " << tmp->value << endl;
			tmp = tmp->next;
		}
	} else
	{
		string exception = "List is empty!\n";
		throw exception;
	}
};
