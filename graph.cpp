/*
	Author: Adrian Kowalski
*/
#include <iostream>
#include <iomanip>
#include <list>

using namespace std;

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
		void show();
		void transform();
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
		AL = new list<int> [vertex+1];
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
	 for(int i = 1; i <= vertex; ++i)
         delete[] AM[i];
    delete[] AM;
    delete[] AL;
    for(int i = 1; i <= edge; ++i)
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
			AL[v1].push_back(v2);
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
	
	} 
}

void Graph::show()
{
	if (representation == 0)
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
	}
	else if (representation == 1)
	{
		cout << "Adjacency List" << endl;
		for (int i = 1; i <= vertex; ++i)
		{
			cout << i << ":";
			for (list<int>::iterator it = AL[i].begin(); it != AL[i].end(); ++it)
				cout << " " << *it;
			cout << endl;
		}
	} else if (representation == 2)
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
	} else if (representation == 3)
	{
	}
}

void Graph::transform()
{
	if (representation == 0)
	{
		for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				if (AM[i][j] == 1)
					AL[i].push_back(j);
		representation = 1;
	}	
	else if (representation == 1)
	{
		for (int i = 1; i <= vertex; ++i)
		{
			for (list<int>::iterator it = AL[i].begin(); it != AL[i].end(); ++it)
				AM[i][*it] = 1;
		}
		representation = 2;
	} else if (representation == 2)	
	{
		int e = 1;				//edge
		for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				if (AM[i][j] == 1 && i != j)
				{
					IM[e][i] = -1;
					IM[e][j] = 1;
					++e;
				}
				else if (AM[i][j] == 1 && i == j)
				{
					IM[e][j] = 2;
					++e;
				}
	} else if (representation == 3)
	{
	
	}
}

int main()
{
	Graph g(6, 7, 0);
	
	g.set();

	g.show();
	
	g.transform();
	
	g.show();
	
	g.transform();
	g.transform();
	
	g.show();
 
	cin.get();
	cin.get();
	return 0;
}
	
