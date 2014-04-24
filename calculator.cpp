#include <iostream>
#include <string>

using namespace std;

class Calculator
{
	private:
		string input;
		string output;
		int result;
	public:
		Calculator(string _i = "", string _o = "", int _r = 0);
		~Calculator();
		void set(string _i);
		void transform_onp();
		void transform_nt();
		void calculate();
		void show_data();
		int show_result() { return result; }
};

Calculator::Calculator(string _i, string _o, int _r)
{
	input = _i;
	output = _o;
	result = _r;
};

Calculator::~Calculator()
{
}

int p(char _c)
{
	switch(_c)
	{
		case '+'     : ;
        case '-'     : return 1;
        case '*'     : ;
        case '/'     : return 2;
        case '^'     : return 3;
   }
  
  return 0;
}

void Calculator::transform_nt()
{
	  char S[50];
      int sptr = 0;
      char c;
      
      for (unsigned int j = 0; j < input.size(); ++j)
      {
			c = input[j];

            if(c == '=')
            {
                while(sptr)
                    output += S[--sptr];
                break;
            }

            switch(c)
            {
                case ' ' : break;
                case '(' : S[sptr++] = '(';
                           break;
                case ')' : while(S[sptr-1] != '(')
                           output += S[--sptr];
                           sptr--;
                           break;
                case '+' : ;
                case '-' : ;
                case '*' : ;
                case '/' : ;
                case '^' : while(sptr && p(S[sptr-1]) > p(c))
                           output += S[--sptr];
                           S[sptr++] = c;
                           break;
                default:   output += c;
                           break;
            }
      }
}
//jak zrobić rekurencyjną lambdę? :(
struct S
{
	char ch;
	struct S *prev;
	struct S *next;
} *stack[50];
		

string show_my(struct S *tmp)
{
	static string tmp2;
    if (tmp != NULL)
    {
        show_my(tmp->prev);
        tmp2 += tmp->ch;
        show_my(tmp->next);
    }
    
    return tmp2;
}

void Calculator::transform_onp()
{
		
		char c;
		
		struct S *op1,  *op2;
		struct S *tmp;
		
		int sptr = 0;
        for (unsigned int j =0; j < input.size(); ++j)
        {
				c = input[j];

				if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
				{
					op1 = stack[--sptr];
					op2 = stack[--sptr];
					tmp = new struct S;
					tmp->ch = c;
					tmp->next = op1;
					tmp->prev = op2;
					stack[sptr++] = tmp;
				}
				else
				{
					tmp = new struct S;
					tmp->ch = c;
					tmp->next = NULL;
					tmp->prev= NULL;
					stack[sptr++] = tmp;
				}
        }
        output += show_my(stack[--sptr]);
}

void Calculator::set(string _i)
{
	input = _i;
}

void Calculator::show_data()
{
	cout << "Input: " << input << endl;
	cout << "Output: " << output << endl;
}

void Calculator::calculate()
{
	double S[50];      
	int sptr = 0;            
	char c;
	string e;             
	double v1,v2;         


	for (unsigned int i = 0; i < input.size(); ++i)
	{ 
		c = input[i];

		if(c == '=') break; 

		if(c >= 48 && c <= 57)        
		{	
			v1 = c - 48;
			S[sptr++] = v1;      
		}
		else
		{                   
			v2 = S[--sptr];      
			v1 = S[--sptr];
			switch(c)      
			{
				case '+' : v1 += v2; break;
				case '-' : v1 -= v2; break;
				case '*' : v1 *= v2; break;
				case '/' : v1 /= v2; break;
			}
			S[sptr++] = v1;     
		}
	}

	result = S[--sptr]; 
}

int main()
{
	Calculator obj;
	
	string input;
	int choice;
	
	cout << "Input: " << endl;
	cin >> input;
	obj.set(input);
	
	cout << "1. ONP -> NT" << endl;
	cout << "2. NT -> ONP" << endl;
	cout << "3. Calculate ONP" << endl;
	cin >> choice;
	
	switch (choice)
	{
		case 1 :
			   {
					obj.transform_onp();
					obj.show_data();
					break;
			   }
		case 2 : 
			   {	
					obj.transform_nt(); 
					obj.show_data();
					break;
				}
		case 3 : 
				{
					obj.calculate();
					cout << obj.show_result() << endl;
					break;
				}
		default : cout << "Error" << endl;
				  break;
	}
	
	return 0;
}
