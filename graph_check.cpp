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
		bool *visited;
		bool is_cyclic_util(int _v, bool _visited[], int _parent);
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
		visited = new bool[vertex + 1];
		for(int i = 1; i <= vertex; ++i) 
			visited[i] = false;
};

Graph::~Graph()
{	
	vector<vector<int>>().swap(AM);
	delete[] visited;
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

//If the graph is undirected, the adjacency matrix is symmetric. 
bool Graph::whether_the_graph_is_directed()
{
	bool flag = false;
	
	vector<vector<int>> tmp;
	tmp.resize(vertex + 1);
	for (int i = 1; i <= vertex; ++i) 
		tmp[i].resize(vertex + 1);
	for (int j = 1; j <= vertex; ++j)
		for (int i = 1; i <= vertex; ++i)
			tmp[j][i] = AM[i][j];
			
	for (int i = 1; i <= vertex; ++i)
		for (int j = 1; j <= vertex; ++j)
			if (tmp[i][j] != AM[i][j])
			{
				flag = true;
				break;
			}
	return flag;
};

//Theorem: In an undirected graph G, a DFS produces only tree and back edges. 
//Theorem: An undirected graph is acyclic iff a DFS yields no back edges. 
//	- If acyclic, there are no back edges (back edge implies a cycle) 
//	- If no back edges, then graph is acyclic because 
//		* DFS will produce only tree 
//		* Trees are by definition acyclic		
bool Graph::whether_the_graph_is_acyclic()
{
	if (!(this->whether_the_graph_is_directed()))
	{
	} else
	{
}

};
		
bool Graph::whether_the_graph_is_connected()
{
};

//The adjacency matrix of a complete graph contains all ones except along the diagonal where there are only zeros.
bool Graph::whether_the_graph_is_complete()
{
	bool flag = true; 	
	
	for (int i = 1; i <= vertex; ++i)
		for (int j = 1; j <= vertex; ++j)
		{
			if (i == j)
			{
				if (AM[i][j] != 0)
				{
					flag = false;
					i = vertex + 1;
					break;
				}
			 } else
			 {
				 if (AM[i][j] == 0)
				 {
					 flag = false;
					 i = vertex + 1;
					 break;
				 }
				}
			}
	return flag;
};


void show_list_of_verticies(vector<int> _v)
{
	cout << "List of verticies:";
	for (vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
		cout << " " << *it;
	cout << endl;
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
						obj.whether_the_graph_is_directed()? cout << "Yes" << endl : cout << "No" << endl;
						break;
			case 4:			
						obj.whether_the_graph_is_acyclic()? cout << "Yes" << endl : cout << "No" << endl;;
						break;
			case 5:			
						obj.whether_the_graph_is_connected()? cout << "Yes" << endl : cout << "No" << endl;;
						break;
			case 6:			
						obj.whether_the_graph_is_complete()? cout << "Yes" << endl : cout << "No" << endl;;
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
