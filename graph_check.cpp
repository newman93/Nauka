/*
	Author: Adrian Kowalski
*/
#include <iostream>
#include <vector>

using namespace std;

class Graph
{
	private:
		vector<vector <int>> AM;	// adjacency matrix
		int vertex;
		int edge;
	public:
		Graph() : vertex(0), edge(0) {};
		~Graph();
		void initialize(int _v, int _e);
		void set();
		void show();
		bool whether_the_graph_is_directed();
		bool whether_the_graph_is_acyclic();
		bool whether_the_graph_is_connected();
		bool whether_the_graph_is_complete();
		vector<int> from_vertex(int _v);
		vector<int> to_vertex(int _v);
};

void Graph::initialize(int _v, int _e) 
{
		vertex = _v;
		edge = _e;
	//adjacency matrix 
		AM.resize(vertex + 1);
		for(int i = 1; i <= vertex; ++i) 
			AM[i].resize(vertex + 1);
		for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				AM[i][j] = 0;
};

Graph::~Graph()
{	
	vector<vector<int>>().swap(AM);
};

void Graph::set()
{
	cout << "Edges: " << endl;
	int v1,v2;
	
	for (int i = 1; i <= edge; ++i)
	{
		cout << "o: "; 
		cin >> v1;
		cout << "i: ";
		cin >> v2;
		AM[v1][v2] = 1;
	}
};

void Graph::show()
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
};

vector<int> Graph::from_vertex(int _v)
{
	vector<int> tmp_1;
	for (int i = 1; i <= vertex; ++i)
		if (AM[_v][i] == 1)
			tmp_1.push_back(i);
	
	return tmp_1;
};
		
vector<int> Graph::to_vertex(int _v)
{
	vector<int> tmp_2;
	for (int i = 1; i <= vertex; ++i)
		if (AM[i][_v] == 1)
			tmp_2.push_back(i);
	return tmp_2;
};

bool Graph::whether_the_graph_is_directed()
{
};
		
bool Graph::whether_the_graph_is_acyclic()
{
};
		
bool Graph::whether_the_graph_is_connected()
{
};

bool Graph::whether_the_graph_is_complete()
{
};

void show_list_of_verticies(vector<int> _v)
{
	cout << "List of verticies:";
	for (vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
		cout << " " << *it;
	cout << endl;
};

void yes_no(bool _w)
{
	if (_w)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
};
		
int main()
{
	int choice;
	int vertex;
	int edge;
	int vertex_2;
	Graph obj;
	
	do
	{
		cout << "1. Create object" << endl;
		cout << "2. Show" << endl;
		cout << "3. Whether the graph is directed?" << endl;
		cout << "4. Whether the graph is acyclic?" << endl;
		cout << "5. Whether the graph is connected?" << endl;
		cout << "6. Whether the graph is complete?" << endl;
		cout << "7. List of verticies - from: " << endl;
		cout << "8. List of verticies - to: " << endl;
		cout << "9. Clear" << endl;
		cout << "10. Exit" << endl;
		cin >> choice;
		switch (choice)
		{
			case 1: 
						cout << "Number of vertices: ";
						cin >> vertex;
						cout << "Number of edges: ";
						cin >> edge;
						obj.initialize(vertex,edge);
						obj.set();
						break;
			case 2:
						obj.show();
						break;
			case 3:	
						yes_no(obj.whether_the_graph_is_directed());
						break;
			case 4:			
						yes_no(obj.whether_the_graph_is_acyclic());
						break;
			case 5:			
						yes_no(obj.whether_the_graph_is_connected());
						break;
			case 6:			
						yes_no(obj.whether_the_graph_is_complete());
						break;
			case 7:
						cout << "Vertex: ";
						cin >> vertex_2;
						show_list_of_verticies(obj.from_vertex(vertex_2));
						break;
			case 8:
						cout << "Vertex: ";
						cin >> vertex_2;
						show_list_of_verticies(obj.to_vertex(vertex_2));
						break;
			case 9:
						system("clear");
						break;
		}
	} while (choice != 10);
	
	return 0;
};
