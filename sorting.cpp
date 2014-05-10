/*
	Author: Adrian Kowalski
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Sort
{
	private:
		int *tab;
		int size;
	public:
		Sort(int _t[], int _r);
		~Sort();
		void insert_sort();
		void bubble_sort();
		void shaker_sort();
		void quick_sort(int _l, int _r);
		void make_heap(int _k, int _n);
		void heap_sort(int _n);
		void merge(int _p, int _m, int _k);
		void merge_sort(int _p, int _k);
		void swap(int & _a,int & _b);
		void randomize();
		void show();
};	

void randomize(int _t[], int _r);

int main()
{
	int tab[25];
	randomize(tab,25);
	
	Sort obj(tab, 25);
	
	cout << "Random data:" << endl;
	obj.show();
	obj.insert_sort();
	cout << "Insert sort:" << endl;
	obj.show();
	obj.randomize();
	cout << "Randomize():" << endl;
	obj.show();
	obj.bubble_sort();
	cout << "Bubble sort:" << endl;
	obj.show();
	obj.randomize();
	cout << "Randomize():" << endl;
	obj.show();
	obj.shaker_sort();
	cout << "Shaker sort:" << endl;
	obj.show();
	obj.randomize();
	cout << "Randomize():" << endl;
	obj.show();
	obj.quick_sort(0,25);
	cout << "Quick sort:" << endl;
	obj.show();
	obj.randomize();
	cout << "Randomize():" << endl;
	obj.show();
	obj.heap_sort(25);
	cout << "Heap sort:" << endl;
	obj.show();
	obj.randomize();
	cout << "Randomize():" << endl;
	obj.show();
	obj.merge_sort(0,24);
	cout << "Merge sort:" << endl;
	obj.show();
	
	return 0;
}

Sort::Sort(int _t[], int _r)
{
	size = _r;
	tab = new int [_r];
	
	for (int i = 0; i < _r; ++i)
		tab[i] = _t[i];
};

Sort::~Sort()
{
	delete[] tab;
};

void Sort::swap(int & _a, int & _b)
{
	int tmp = _a;
	_a = _b;
	_b = tmp;
};

void Sort::show()
{
	for (int i = 0; i < size; ++i)
		std::cout << " " << tab[i];
	std::cout << std::endl; 
};

void Sort::insert_sort()
{
	for (int i = 1; i < size; ++i)
	{
		int j = i;	//fragment [0..,i-1] jest juz posortowany
		int tmp = tab[j];
		
		while ( (j > 0) && (tab[j-1] > tmp))
		{
			tab[j] = tab[j-1];
			j--;
		}
		tab[j] = tmp;
	}
};

void Sort::bubble_sort()
{
	for (int i = 1; i < size; ++i)
		for (int j = size; j >= i; j--)
			if (tab[j] < tab[j-1])
				swap(tab[j-1], tab[j]);
};

void Sort::shaker_sort()
{
	int left = 1;
	int right = size - 1;
	int k = size - 1;
	
	do
	{
		for (int j = right; j >= left; j--)
			if (tab[j-1] > tab[j])
			{
				swap(tab[j-1], tab[j]);
				k = j;
			}
		left = k + 1;
		for (int j = left; j <= right; j++)
			if (tab[j-1] > tab[j])
			{
				swap(tab[j-1], tab[j]);
				k = j;
			}
		right = k - 1;
	} while ( left <= right);
};

void Sort::quick_sort(int _l, int _r)
{
	if (_l < _r)
	{
		int m = _l;
		
		for (int i = _l + 1; i <= _r; i++)
			if (tab[i] < tab[_l])
				swap(tab[++m], tab[i]);
			swap(tab[_l], tab[m]);
			quick_sort(_l, m - 1);
			quick_sort(m + 1, _r);
	}
};

void Sort::make_heap(int _k, int _n)
{
	int i,j;
	
	i = tab[_k-1];
	while (_k <= _n/2)
	{
		j = 2*_k;
		if ((j < _n) && (tab[j-1] < tab[j])) j++;
		if (i >= tab[j-1])
			break;
		else
		{
			tab[_k-1] = tab[j-1];
			_k = j;
		}
	}
	tab[_k-1] = i;
};

void Sort::heap_sort(int _n)
{
	int k;
	
	for (k = _n/2; k > 0; k--) 
		make_heap(k,_n);
	do
	{
		swap(tab[0], tab[_n-1]);
		_n--;
		make_heap(1, _n);
	} while (_n > 1);
};

void Sort::merge(int _p, int _m, int _k)
{
	int tmp[size];
	int p1 = _p;
	int k1 = _m;
	int p2 = _m+1;
	int k2 = _k;
	int i = p1;
	
	while ((p1 <= k1) && (p2 <= k2))
	{
		if (tab[p1] < tab[p2])
			tmp[i++] = tab[p1++];
		else
			tmp[i++] = tab[p2++];
	}
	
	while ( p1 <= k1)
		tmp[i++] = tab[p1++];
	
	while ( p2 <= k2)
		tmp[i++] = tab[p2++];
	
	for(int i = _p; i <= _k; i++)
		tab[i] = tmp[i];
};


void Sort::merge_sort(int _p, int _k)
{
	if (_p < _k)
	{
		int m = (_p + _k) / 2;
		merge_sort(_p, m);
		merge_sort(m+1, _k);
		merge(_p, m, _k);
	}
};
	
void Sort::randomize()
{
	srand(time(NULL));
	for (int i = 0; i < size; ++i)
		tab[i] = std::rand() % 50;
};
	
void randomize(int _t[], int _r)
{
	srand(time(NULL));
	for (int i = 0; i < _r; ++i)
		_t[i] = std::rand() % 50;
};
