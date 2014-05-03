/*
	Author: Adrian Kowalski
*/

			S.push(string(1, c));
		else if ( c == '+' || c == '-' || c == '*' || c == '/' )
		{	
			op1 = S.top(); S.pop();
			op2 = S.top(); S.pop();
			S.push("(" + op2 + string(1,c) + op1 + ")");
		}
	}
	output = S.top();
	S.pop();
	output_notation = 0;
}

void Calculator::set()
{
	int choice; 

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
	cin.clear();				//necessary for input with white spaces			
	cin.sync();					//
	cin.get();					//
	getline(cin,input);			//
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

void Calculator::test()
{
		input_notation = 0;
		cout << "INPUT: " << input << endl;
		transform_in();
		transform_pn();
		calculate();
		transform_in();
		show_data();
		cout << endl;
}

int main()
{
	Calculator obj;
	Calculator obj_1("(2 + 3)*4*5");
	Calculator obj_2("3*5/(3-1)");
	Calculator obj_3("3+2*4/(6-1)");
	
	cout << "Test" << endl;
	
	obj_1.test();
	obj_2.test();
	obj_3.test();

	
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

