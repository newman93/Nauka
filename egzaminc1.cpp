/*
    Autor: Adrian Kowalski
*/

#include <iostream>
#include <cstring>

class Text
{
	private:
			char* text;
	public:
			Text(char *_t);
			~Text();
			Text & operator+(const Text & _txt);
			Text(const Text & _txt);
			Text & operator=(const Text & _txt);
			void show();
};

Text::Text(char *_t)
{
	text = new char[strlen(_t)+1];
	strcpy(text, _t);
};

Text::~Text()
{
	delete []text;
};

Text::Text(const Text & _txt)
{
	text = new char[strlen(_txt.text)+1];
	strcpy(text, _txt.text);
};

Text & Text::operator+(const Text & _txt)
{
	char *tmp = new char[strlen(this->text)+1];
	strcpy(tmp, this->text);
	delete []this->text;
	text = new char[strlen(tmp)+strlen(_txt.text)+1];
	strcpy(text,tmp);
	strcat(text, _txt.text);
};

Text & Text::operator=(const Text & _txt)
{
	delete []this->text;
	text = new char[strlen(_txt.text)+1];
	strcpy(this->text, _txt.text);
};

void Text::show()
{
	std::cout << text << std::endl;
};

int main()
{
	try
	{
		Text obj_1("egzamin");
		Text obj_2("kolokwium");
		obj_1.show();
		obj_2.show();
		
		obj_1 + obj_2;
		
		obj_1.show();
		
		obj_1 = obj_2;
		
		obj_1.show();
	} catch(...)
	{
		std::cout << "Wyjątek!" << std::endl;
	}
	
	return 0;
}
