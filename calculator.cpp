#include <iostream>
#include <string>
#include <functional>
#include <stack>


using namespace std;

class Calculator
{
	private:
		string input;
		string output;
		int input_notation; // 0 - infix notation | 1 - postfix notation
		int output_notation;
		double result;
	public:
		Calculator(string _i = "", string _o = "", double _r = 0.0, int _in = 3, int _ot = 3);
		~Calculator();
		void set();
		void transform_pn();
		void transform_in();
		void calculate();
		void show_data();
};

Calculator::Calculator(string _i, string _o, double _r, int _in, int _ot)
{
	input = _i;
	output = _o;
	result = _r;
	input_notation = _in;
	output_notation = _ot;
}

Calculator::~Calculator()
{
}

void Calculator::transform_in()
{
	  stack<char> S;
      char c;
      
      if (input_notation == 1 && output_notation == 0)
      {
		  input = output;
		  input_notation = 0;
		  output_notation = 1;
		  output = "";
	  }
 
	  auto p = [](char _c)->int { switch(_c) { case '+': ; case '-': return 1; case '*': ; case '/': return 2; } return 0; };
 
      for (unsigned int j = 0; j < input.size(); ++j)
      {
			c = input[j];

            switch(c)
            {
                case '(' : S.push('(');
                           break;
                case ')' : while(S.top() != '(')
						   {
								output += S.top();
								S.pop();
						   }
						   S.pop();
                           break;
                case '+' : ;
                case '-' : ;
                case '*' : ;
                case '/' : while(!S.empty() && p(S.top()) > p(c))
						   {	
								output += S.top();
								S.pop();
						   }
                           S.push(c);
                           break;
                default:   output += c;
                           break;
            }
      }
      while (!S.empty())
      {
			output += S.top();
			S.pop();
	  }
	  output_notation = 1;
}

void Calculator::transform_pn()
{
		struct S
		{
			string ch;
			struct S *prev;
			struct S *next;
		};
		stack<struct S*> S;
		
		char c1,c2;
		
		struct S *op1,  *op2;
		struct S *tmp;
		
		if (input_notation == 0 && output_notation == 1)
		{
			input = output;
			input_notation = 1;
			output = "";
		}
		
		function<void(struct S*)> show_my;
		show_my = [&](struct S *tmp)->void { if (tmp != NULL) { show_my(tmp->prev); output += tmp->ch; show_my(tmp->next); }};
		
        for (unsigned int j =0; j < input.size(); ++j)
        {
				c1 = input[j];

				if (c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/')
				{
					c2 = input[j+1];
					if (c2 == '+' || c2 == '-' || c2 == '*' || c2 == '/')
					{
						op1 = S.top(); S.pop();
						op2 = S.top(); S.pop();
						tmp = new struct S;
						tmp->ch = c1;
						tmp->next = op1;
						tmp->next->ch = tmp->next->ch + ')';
						tmp->prev = op2;
						tmp->prev->ch = '(' + tmp->prev->ch;
						S.push(tmp);
					}
					else
					{
						op1 = S.top(); S.pop();
						op2 = S.top(); S.pop();
						tmp = new struct S;
						tmp->ch = c1;
						tmp->next = op1;
						tmp->prev = op2;
						S.push(tmp);
					}
				}
				else
				{
					tmp = new struct S;
					tmp->ch = c1;
					tmp->next = NULL;
					tmp->prev= NULL;
					S.push(tmp);
				}
        }
        show_my(S.top());
        output_notation = 0;
}

void Calculator::set()
{
	int choice{3}; 
	
	do
	{
		cout << "Chose notation:" << endl;
		cout << "1. Infix notaion" << endl;
		cout << "2. Postfix notation" << endl;
		cin >> choice;
		if (choice - 1 == 0)
		{	
			input_notation = 0;
			break;
		}	
		else if (choice - 1 == 1)
		{
			input_notation = 1;
			break;
		}
		else
			cout << "Error" << endl;
	} while ((choice - 1 == 1) || (choice - 1 == 0));
	cout << "Input: ";
	cin >> input;
	cout << endl;
}

void Calculator::show_data()
{	
	cout << "Input: " << input <<  endl;
	cout << "Output: " << output <<  endl;
	cout << "Result: " << result << endl;
}

void Calculator::calculate()
{
	stack<double> S;
    double  a, b, w;
    char c;
	
	if (input_notation == 1)
	{
		for (unsigned int i =0; i < input.size(); ++i)
		{
    
			c = input[i];

			if(c >= 48 && c <= 57)
				S.push(c - 48);
			else
			{
				b = S.top(); S.pop(); 
				a = S.top(); S.pop();
				switch(c)
				{
					case '+': w = a + b; break;
					case '-': w = a - b; break;
					case '*': w = a * b; break;
					case '/': w = a / b; break;
				}
				S.push(w);
			}
		}
		result = S.top();
		S.pop();
	}
	else
		cout << "Error" << endl;
}

int main()
{
	Calculator obj;
	
	int choice;

	cout << "Calculator" << endl;

	do
	{
		cout << "1. Input data" << endl;
		cout << "2. Postfix Notation -> Infix Notation" << endl;
		cout << "3. Infix Notation -> Postfix Notation" << endl;
		cout << "4. Calculate (input - postfix notation)" << endl;
		cout << "5. Show data" << endl;
		cout << "6. Clear" << endl;
		cout << "7. Exit" << endl;
		
		cin >> choice;
		
		switch (choice)
		{
			case 1 : 	obj.set();
						break;
			case 2 :
						obj.transform_pn();
						break;
			case 3 : 
						obj.transform_in();
						break;
			case 4 : 
						obj.calculate();
						break;
			case 5 :    obj.show_data();
						break;
			case 6 : 	system("clear");
						break;
			case 7 : 	break;
			default : 	cout << "Error" << endl;
						break;
		}
	} while(choice != 7);
	
	cout << "..........." << endl;
	
	
	return 0;
}
