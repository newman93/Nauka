/*
        Autor: Adrian Kowalski
*/

#include <iostream>

using namespace std;

template <class T, int n>
struct Element
{
        T tab[n];
        Element *next;
};

template <class T, int n>
class Iterator;

template <class T, int n>
class List
{
        private:
                        typedef struct
                        {
                                int counter;
                                Element<T,n> *head;
                                Element<T,n> *tail;
                        } Info;
                Info inf;
        public:
                        List() { inf.head = inf.tail = nullptr; inf.counter = 0; }
                        ~List() { make_empty(); }
                        Iterator<T,n> *iterator();
                        void dodaj(const T *_tab);
                        List(const List<T,n> &_l);
                        List<T,n> & operator=(const List<T,n> &_l);
                        bool is_empty() { return (inf.head == nullptr); }                       //dodatkowo
                        void make_empty();                                                                                      //
                        void show();                                                                                            //
                        Element<T,n> * getHead() { return inf.head; }
};

template <class T, int n>
class Iterator
{
    private:
            Element<T,n> *el;
    public:
            Iterator() : el(nullptr) {}
            Iterator(Element<T,n> *_el) : el(_el) {}
            T * get() { return el->tab; }
            Iterator<T,n> & operator++() { if (!(el->next == nullptr)) { el = el->next; } return *this; }
            bool operator()(const Iterator &_it) { if (el != nullptr) return true; else return false; }    
};

template <class T, int n>
void List<T,n>::dodaj(const T *_tab)
{
        Element<T,n> *obj = new Element<T,n>;
        for (int i = 0; i < n; ++i)
                obj->tab[i] = _tab[i];              
        if (is_empty())
        {
                obj->next = nullptr;
                inf.head = inf.tail = obj;
                inf.counter = 1;
        }
        else
        {
                (inf.tail)->next = obj;
                Element<T,n> *tmp = inf.tail;
                obj->next = nullptr;
                inf.tail = obj;
                inf.counter += 1;
        }
};

template <class T, int n>
List<T,n>::List(const List<T,n> &_l)
{
        inf.head = inf.tail = nullptr;
        inf.counter = 0;
        *this = _l;
};                     

template <class T, int n>
List<T,n> & List<T,n>::operator=(const List<T,n> &_l)
{
        this->make_empty();     
        Element<T,n> *tmp = _l.inf.head;
        Element<T,n> *obj = new Element<T,n>;
        for (int i = 0; i < n; ++i)
                obj->tab[i] = tmp->tab[i];
        obj->next = nullptr;
        this->inf.head = this->inf.tail = obj;
        this->inf.counter = 1;
        tmp = tmp->next;
        while (tmp != nullptr)
        {
                Element<T,n> *obj = new Element<T,n>;
                for (int i = 0; i < n; ++i)
                        obj->tab[i] = tmp->tab[i];
                this->inf.tail->next = obj;
                obj->next = nullptr;
                this->inf.tail = obj;
                this->inf.counter += 1;
                tmp = tmp->next;
        }
        return *this;
};

template <class T, int n>
void List<T,n>::make_empty()
{
        if (!is_empty())
        {
                delete inf.head;
                inf.head = inf.tail = nullptr;
                inf.counter = 0;
        }
        else
        {
                Element<T,n> *tmp = inf.head;
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
};

template <class T, int n>
void List<T,n>::show()
{
        if (!is_empty())
        {
                Element<T,n> *tmp = inf.head;
                int i = 0;
                while (tmp != nullptr)
                {
                        cout << ++i << ":";
                        for (int j = 0; j < n; ++j)
                                cout << " " << tmp->tab[j];
                        cout << endl;
                        tmp = tmp->next;
                }
        }
};

int main()
{
        try
        {
                List<int,3> lista_1;
               
                const int tab_1[3] = { 1, 3, 5 };
                const int tab_2[3] = { 2, 8, 12 };
                const int tab_3[3] = { 4, 16, 14 };
                const int tab_4[3] = { 1, 3, 5 };
               
                lista_1.dodaj(tab_1);
                lista_1.dodaj(tab_2);
                lista_1.dodaj(tab_3);
                lista_1.dodaj(tab_4);
               
                cout << "lista_1" << endl;
                lista_1.show();
               
                List<int,3> lista_2;
                const int tab_5[3] = { 5, 3, 1 };
                const int tab_6[3] = { 12, 8, 2 };
                const int tab_7[3] = { 14, 16, 4 };
                const int tab_8[3] = { 5, 3, 1 };
               
                lista_2.dodaj(tab_5);
                lista_2.dodaj(tab_6);
                lista_2.dodaj(tab_7);
                lista_2.dodaj(tab_8);
               
                cout << "lista_2" << endl;
                lista_2.show();
               
                lista_1 = lista_2;
               
                cout << "lista_1 = lista_2" << endl;
                lista_1.show();
                
                cout << "Iterator" << endl;
                
                Iterator<int,3> it(lista_2.getHead());
                
                int *wek_1 = it.get();
            
                for (int i = 0; i < 3; ++i)
                    cout << wek_1[i] << " ";
                cout << endl;
                
                ++it;
                  int *wek_2 = it.get();
            
                for (int i = 0; i < 3; ++i)
                    cout << wek_2[i] << " ";
                cout << endl;   
        }
        catch(...)
        {
                cout << "Wyjatek!" << endl;
        }
        return 0;
}
