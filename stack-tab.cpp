/*
	Author: Adrian Kowalski
*/

/*
                                        |
                                        |
                                        |
                                |---------------|
					 SIZE------>|	 ...V...    |												
								|---------------|				
								|      top      |				
								|---------------|			
								|    .......    |
								|---------------|		
								|     value     |
								|---------------|
						0------>|     empty     |
								|---------------|
*/

#include <iostream>
#include <string>

using namespace std;

template <class DataType> 
class Stack
{
	private:
		DataType *stack;
		int t;
		int s;
	public:
		Stack(int _s);
		~Stack();
		void push(DataType _x);
		void pop();
		DataType & top();
		bool is_empty();
		int size() { return t; }
		void clear() { t = 0; }
		void show();
};

int main()
{
	Stack<int> s_1(10);
	
	try
	{
		for (int i = 1; i < 9; ++i)
			s_1.push(i);
		for (int i = 1; i < 9; ++i)
			s_1.pop();
		cout << "Size: " << s_1.size() << endl;
		s_1.is_empty()? cout << "Yes\n" : cout << "No\n"; 
		for (int i = 1; i < 9; ++i)
			s_1.push(i);
		cout << "Top: " << s_1.top() << endl;
		s_1.show();
	} catch (string exception)
	{
		cout << exception;
	};
	
	return 0;
};

template <class DataType>
Stack<DataType>::Stack(int _s)
{
	stack = new DataType [_s];
	t = 0;
	s = _s;
};
		
template <class DataType>
Stack<DataType>::~Stack()
{
	delete[] stack;
};

template <class DataType>		
void Stack<DataType>::push(DataType _x)
{
	if (t < (s - 2))
		stack[++t] = _x;
	else
	{
		string exception = "Stack is full!\n";
		throw exception;
	}
};	

template <class DataType>		
void Stack<DataType>::pop()
{
	if (!is_empty())
		--t;
	else
	{
		string exception = "Stack is empty!\n";
		throw exception;
	}
};

template <class DataType>	
DataType & Stack<DataType>::top()
{
	if (!is_empty())
		return stack[t];
	else
	{
		string exception = "Stack is empty!\n";
		throw exception;
	}
};

template <class DataType>
bool Stack<DataType>::is_empty()
{ 
	return (t == 0);
};

template <class DataType>
void Stack<DataType>::show()
{
	if (!is_empty())
	{
		int j = 1;
		for (int i = t; i > 0; --i, ++j)
			cout << "#" << j << ": " << stack[i] << endl;
		cout << endl;
	} else 
	{
		string exception = "Stack is empty!\n";
		throw exception;
	}
};
