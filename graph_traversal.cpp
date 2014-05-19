/*
	Author: Adrian Kowalski
*/ 

#include <iostream>
#include <list>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
	private:
		list<int> *AL;
		int vertex;
		int edge;
	    bool *visited;
	public:
		Graph() : vertex(0), edge(0) {};
		~Graph();
		void set();
		void show();
		void initialize(int _v, int _e);
		void restart_visited();
		void depth_first_search_stack(int _v);
		void depth_first_search_recursion(int _v);
		void breadth_first_search(int _v);
};


int main()
{
	
	int choice;
	int choice2;
	int vertex;
	int vertex2;
	int edge;
	Graph obj;
	
	do
	{
		cout << "1. Create object" << endl;
		cout << "2. Show" << endl;
		cout << "3. Depth-first search" << endl;
		cout << "4. Breadth-first Search" << endl; 
		cout << "5. Clear" << endl;
		cout << "6. Exit" << endl;
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
						cout << "1. With stack" << endl;
						cout << "2. Recursion" << endl;
						cin >> choice2;
						cout << "Vertex: ";
						cin >> vertex2;
						switch (choice2)
						{
							case 1:
										obj.depth_first_search_stack(vertex2);
										obj.restart_visited();
										break;
							case 2:
										obj.depth_first_search_recursion(vertex2);
										obj.restart_visited();
										cout << endl;
										break;
							default:	
										cout << "Error!" << endl;
										break;
						}
						break;
			case 4:
						cout << "Vertex: ";
						cin >> vertex2;
						breadth_first_search(vertex2); 
						obj.restart_visited();
						break;
			case 5:
						system("clear");
						break;
			case 6:
						break;
			default :
						cout << "Error!" << endl;
						break;
		}
	} while (choice != 6);
	return 0;
};

Graph::~Graph()
{
	 delete[] AL;
	 delete[] visited;
};

void Graph::initialize(int _v, int _e) 
{
	vertex = _v;
	edge = _e;
	AL = new list<int> [edge + 1];
	visited = new bool[edge + 1];
	for(int i = 1; i <= edge; i++) 
		visited[i] = false;
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
		AL[i].push_back(v1);
		AL[i].push_back(v2);
	}
};

void Graph::depth_first_search_stack(int _v)
{
	int v; 
	stack<int> Stack;
	Stack.push(_v);
	
	while(!Stack.empty())
	{
      
		v = Stack.top();  Stack.pop();

		if(!visited[v])
		{
			visited[v] = true;
			for (list<int>::iterator it = AL[v].begin(); it != AL[v].end(); it++)
				if (!visited[*it]) 
					Stack.push(*it);
			cout << v << " ";
		}
	}
	cout << endl;
};

void Graph::breadth_first_search(int _v)
{
  queue<int> Queue;
  
  Queue.push(_v);

  while(!Queue.empty())     
  {
    _v = Queue.front();   
    Queue.pop();          

    cout << _v << " ";  

    for(list<int>::iterator it = AL[_v].begin(); it != AL[_v].end(); it++)
      if(!visited[*it])
      {
        visited[*it] = true;
        Queue.push(*it);        
      }
  }
  cout << endl;
};

void Graph::depth_first_search_recursion(int _v)
{
	visited[_v] = true;

	cout << _v << " ";

	for(list<int>::iterator it = AL[_v].rbegin(); it != AL[_v].rend(); it++)
		if(!visited[*it]) 
			depth_first_search_recursion(*it);
};
 
void Graph::show()
{
	cout << "Adjacency List" << endl;
	for (int i = 1; i <= edge; ++i)
	{
		cout << i << ":";
		for (list<int>::iterator it = AL[i].begin(); it != AL[i].end(); ++it)
			cout << " " << *it;
		cout << endl;
	}
	cout << endl;
};

void Graph::restart_visited()
{
	for(int i = 1; i <= edge; i++) 
		visited[i] = false;
};
