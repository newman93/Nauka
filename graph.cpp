/*
	Author: Adrian Kowalski
*/
#include <iostream>
#include <iomanip>
#include <list>

using namespace std;

typedef struct v
{
	string name;
	int age;
} VERTEX;

class Graph
{
	private:
		int **AM;			//dynamic allocation  | adjacency matrix
		list<int> *AL;		// list | adjacency list
		int **IM;			//dynamic allociation | incidence matrix
		list<int> *IL;		// list | incidence list
		int vertex;
		int edge;
		int representation;	//0 - adjacency matrix | 1 - adjacency list | 2 - incidence matrix | 3 - incidence list | 4 - all
	public:
		Graph(int _v, int _e, int _r);
		~Graph();
		void set();
		void show(int _rep);
		void transform_all();
};

Graph::Graph(int _v = 0, int _e = 0, int _r = 0) : vertex(_v), edge(_e), representation(_r) 
{
	//adjacency matrix 
		AM = new int * [vertex];
		for(int i = 1; i <= vertex; ++i) 
			AM[i] = new int [vertex];
		for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				AM[i][j] = 0;
	//adjacency list
		AL = new list<int> [edge+1];
	//incidence matrix
		IM = new int * [edge];
		for (int i = 1; i <= edge; ++i)
			IM[i] = new int [vertex];
		for (int i = 1; i <= edge; ++i)
			for (int j = 1; j <= vertex; ++j)
				IM[i][j] = 0;
	//incidence list
		IL = new list<int> [vertex+1];
}

Graph::~Graph()
{
    for(int i = 0; i <= vertex; ++i)
         delete[] AM[i];
    delete[] AM;
    delete[] AL;
    for(int i = 0; i <= edge; ++i)	//
         delete[] IM[i];
    delete[] IM;
    delete[] IL;
}

void Graph::set()
{
	cout << "Edges: " << endl;
	int v1,v2;
	
	if (representation == 0)
	{
		for (int i = 1; i <= edge; ++i)
		{
			cout << "o: "; 
			cin >> v1;
			cout << "i: ";
			cin >> v2;
			AM[v1][v2] = 1;
		}
	} else if (representation == 1)
	{
		for (int i = 1; i <= edge; ++i)
		{
			cout << "o: "; 
			cin >> v1;
			cout << "i: ";
			cin >> v2;
			AL[i].push_back(v1);
			AL[i].push_back(v2);
		}
	} else if (representation == 2)
	{
		for (int i = 1; i <= edge; ++i)
		{
			cout << "o: "; 
			cin >> v1;
			cout << "i: ";
			cin >> v2;
			if (v1 != v2)
			{
				IM[i][v1] = -1;
				IM[i][v2] = 1;
			}
			else
				IM[i][v1] = 2;
		}
	} else if (representation == 3)
	{
		for (int i = 1; i <= edge; ++i)
		{
			cout << "o: "; 
			cin >> v1;
			cout << "i: ";
			cin >> v2;
			IL[v1].push_back(v2);
		}
	} 
}

void Graph::show(int _rep)
{
	if (_rep == 0)
	{
		cout << "Adjacency Matrix" << endl;
		
		cout << " ";
		for (int i = 1; i <= vertex; ++i)
			cout << " " << i;
		cout << endl; 
		for (int i = 1; i <= vertex; ++i)
		{
			cout << i;
			for (int j = 1; j <= vertex; ++j)
				cout << " " << AM[i][j];
			cout << endl;	
		}
	} else if (_rep == 1)
	{
		cout << "Adjacency List" << endl;
		for (int i = 1; i <= edge; ++i)
		{
			cout << i << ":";
			for (list<int>::iterator it = AL[i].begin(); it != AL[i].end(); ++it)
				cout << " " << *it;
			cout << endl;
		}
	} else if (_rep == 2)
	{
		cout << "Incidence Matrix" << endl;
		cout << " ";
		for (int i = 1; i <= vertex; ++i)
			cout << " " <<  setw(3) << i;
		cout << endl; 
		for (int i = 1; i <= edge; ++i)
		{
			cout << i;
			for (int j = 1; j <= vertex; ++j)
				cout << " " <<  setw(3) << IM[i][j];
			cout << endl;	
		}
	} else if (_rep == 3)
	{
		cout << "Incidence List" << endl;
		for (int i = 1; i <= vertex; ++i)
		{
			cout << i << ":";
			for (list<int>::iterator it = IL[i].begin(); it != IL[i].end(); ++it)
				cout << " " << *it;
			cout << endl;
		}
	}
}

void Graph::transform_all()
{
	int e = 1;                                     //edge
	for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				if (AM[i][j] == 1)
				{
					AL[e].push_back(i);
					AL[e].push_back(j);
					++e;
				}
	e = 1;				
	for (int i = 1; i <= vertex; ++i)
		for (int j = 1; j <= vertex; ++j)
			if (AM[i][j] == 1 && i != j)
			{
				IM[e][i] = -1;
				IM[e][j] = 1;
				++e;
			} else if (AM[i][j] == 1 && i == j)
			{
				IM[e][j] = 2;
				++e;
			}
	for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				if (AM[i][j] == 1)
					IL[i].push_back(j);
}

int main()
{
	Graph g(6, 7, 0);
	
	g.set();
	
	g.transform_all();

	g.show(0);
	g.show(1);
	g.show(2);
	g.show(3);
	
	cin.get();
	cin.get();
	
	return 0;
}
	
