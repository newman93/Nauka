#include <iostream>
#include <string>
#include <functional>


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
		int show_result() { return result; } 
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

int p(char _c)
{
	switch(_c)
	{
		case '+': ;
        case '-': 	return 1;
		case '*': ;
        case '/':	return 2;
    }
  
  	
  	return 0;
}

void Calculator::transform_in()
{
      char S[50];
      int sptr = 0;
      char c;
      
      if (input_notation == 1 && output_notation == 0)
      {
	  	  	input = output;
		  	input_notation = 0;
		  	output_notation = 1;
		  	output = "";
      }
 
      for (unsigned int j = 0; j < input.size(); ++j)
      {
	  		c = input[j];

            switch(c)
            {
            	case '(':	S[sptr++] = '(';
                            break;
                case ')':	while(S[sptr-1] != '(')
                           	output += S[--sptr];
                           	sptr--;
                           	break;
                case '+' : ;
                case '-' : ;
                case '*' : ;
                case '/' :	while(sptr && p(S[sptr-1]) > p(c))
                           	output += S[--sptr];
                           	S[sptr++] = c;
                           	break;
                default:   	output += c;
                           	break;
            }
      }
      while (sptr)
	  	output += S[--sptr];
	  output_notation = 1;
}

void Calculator::transform_pn()
{
		struct S
		{
			string ch;
			struct S *prev;
			struct S *next;
		} *stack[50];
		
		char c1,c2;
		
		struct S *op1,  *op2;
		struct S *tmp;
		
		int sptr = 0;
		
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
						op1 = stack[--sptr];
						op2 = stack[--sptr];
						tmp = new struct S;
						tmp->ch = c1;
						tmp->next = op1;
						tmp->next->ch = tmp->next->ch + ')';
						tmp->prev = op2;
						tmp->prev->ch = '(' + tmp->prev->ch;
						stack[sptr++] = tmp;
						
					}
					else
					{
						op1 = stack[--sptr];
						op2 = stack[--sptr];
						tmp = new struct S;
						tmp->ch = c1;
						tmp->next = op1;
						tmp->prev = op2;
						stack[sptr++] = tmp;
					}
				}
				else
				{
					tmp = new struct S;
					tmp->ch = c1;
					tmp->next = NULL;
					tmp->prev= NULL;
					stack[sptr++] = tmp;
				}
        }
        show_my(stack[--sptr]);
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
	cout << "Result: " << this->show_result() << endl;
}

void Calculator::calculate()
{
	double  S[50];
	int sptr = 0;
    double  a, b, w;
    char c;
	
	if (input_notation == 1)
	{
		for (unsigned int i =0; i < input.size(); ++i)
		{
    
			c = input[i];

			if(c >= 48 && c <= 57)
				S[sptr++] = c - 48;
			else
			{
				b = S[--sptr]; a = S[--sptr];
				switch(c)
				{
					case '+': w = a + b; break;
					case '-': w = a - b; break;
					case '*': w = a * b; break;
					case '/': w = a / b; break;
				}
				S[sptr++] = w;
			}
		}
		result = S[--sptr];
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

