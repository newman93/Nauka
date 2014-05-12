/*
	Author: Adrian Kowalski
*/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Graph
{
	private:
		vector<vector <int>> AM;	// adjacency matrix
		vector<vector <int>> AL;	// adjacency list
		vector<vector <int>> IM;	// incidence matrix
		vector<vector <int>> IL;	// incidence list
		int vertex;
		int edge;
		int representation;	//0 - adjacency matrix | 1 - adjacency list | 2 - incidence matrix | 3 - incidence list
	public:
		Graph() : vertex(0), edge(0), representation(4) {};
		~Graph();
		void initialize(int _v, int _e, int _r);
		void set();
		void transform(int _rep);
		void show();
		int get_representation() { return representation; }
		void clear_AL() { vector<vector<int>>().swap(AL); AL.resize(edge + 1); } 
		void clear_IL() { vector<vector<int>>().swap(IL); IL.resize(vertex + 1); }
};

void Graph::initialize(int _v, int _e, int _r) 
{
		vertex = _v;
		edge = _e;
		representation = _r;
	//adjacency matrix 
		AM.resize(vertex + 1);
		for(int i = 1; i <= vertex; ++i) 
			AM[i].resize(vertex + 1);
		for (int i = 1; i <= vertex; ++i)
			for (int j = 1; j <= vertex; ++j)
				AM[i][j] = 0;
	//adjacency list
		AL.resize(edge + 1);
	//incidence matrix
		IM.resize(edge + 1);
		for (int i = 1; i <= edge; ++i)
			IM[i].resize(vertex + 1);
		for (int i = 1; i <= edge; ++i)
			for (int j = 1; j <= vertex; ++j)
				IM[i][j] = 0;
	//incidence list
		IL.resize(vertex+1);
};

Graph::~Graph()
{
	vector<vector<int>>().swap(AM);
	vector<vector<int>>().swap(AL);
	vector<vector<int>>().swap(IM);
	vector<vector<int>>().swap(IL);
};

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
};

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
	} else if (representation == 1)
	{
		cout << "Adjacency List" << endl;
		for (int i = 1; i <= edge; ++i)
		{
			cout << i << ":";
			for (vector<int>::iterator it = AL[i].begin(); it != AL[i].end(); ++it)
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
		cout << "Incidence List" << endl;
		for (int i = 1; i <= vertex; ++i)
		{
			cout << i << ":";
			for (vector<int>::iterator it = IL[i].begin(); it != IL[i].end(); ++it)
				cout << " " << *it;
			cout << endl;
		}
	}
};

void Graph::transform(int _rep)
{
	if (representation == 0)
	{
		switch (_rep)
		{
			case 1:
					{
						this->clear_AL();
						int e = 1;                                     //edge
						for (int i = 1; i <= vertex; ++i)
							for (int j = 1; j <= vertex; ++j)
								if (AM[i][j] == 1)
								{
									AL[e].push_back(i);
									AL[e].push_back(j);
									++e;
								}
						representation = 1;
					}
					break;
			case 2:
					{
					    int e = 1;									//edge
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
						representation = 2;
					}
					break;
			case 3:	
					{
						this->clear_IL();
						for (int i = 1; i <= vertex; ++i)
							for (int j = 1; j <= vertex; ++j)
								if (AM[i][j] == 1)
									IL[i].push_back(j);
						representation = 3;
					}
					break;
		}				
	} else if (representation == 1)
	{
		switch (_rep)
		{
			case 0:
					{
						for (int i = 1; i <= edge; ++i)
							AM[*(AL[i].begin())][*(AL[i].end() - 1)] = 1;
						representation = 0;
					}
					break;
			case 2:
					{
						for (int i = 1; i <= edge; ++i)
						{
							if (*(AL[i].begin()) != *(AL[i].end() - 1))
							{
								IM[i][*(AL[i].begin())] = -1;
								IM[i][*(AL[i].end() - 1)] = 1;
							} else
								IM[i][*(AL[i].begin())] = 2;
						}
						representation = 2;
					}
					break;
			case 3:	
					{
						this->clear_IL();
						for (int i = 1; i <= edge; ++i)
							IL[*(AL[i].begin())].push_back(*(AL[i].end() - 1));
						representation = 3;
					}	
					break;
		}
	} else if (representation == 2)
	{
		switch (_rep)
		{
			case 0:
					{
						for (int i = 1; i <= edge; ++i)
						{
								int tmp_1{0};
						        	int tmp_2{0};
								for (int j = 1; j <= vertex; ++j)
								{
									if (IM[i][j] == 1)
										tmp_1 = j;
									else if (IM[i][j] == -1)
										tmp_2 = j;
									else if (IM[i][j] == 2)
									{
										AM[j][j] = 1;
										break;
									}
								}
								if (tmp_1 != 0 && tmp_2 != 0)
									AM[tmp_2][tmp_1] = 1;
						}
						representation = 0;
					}
					break;
			case 1:
					{
						this->clear_AL();
						for (int i = 1; i <= edge; ++i)
						{
								int tmp_1{0};
						        	int tmp_2{0};
								for (int j = 1; j <= vertex; ++j)
								{
									if (IM[i][j] == 1)
										tmp_1 = j;
									else if (IM[i][j] == -1)
										tmp_2 = j;
									else if (IM[i][j] == 2)
									{
										AL[i].push_back(j);
										AL[i].push_back(j);
										break;
									}
								}
								if (tmp_1 != 0 && tmp_2 != 0)
								{
									AL[i].push_back(tmp_2);
									AL[i].push_back(tmp_1);
								}
						}
						representation = 1;
					}
					break;
			case 3:	
					{
						this->clear_IL();
						for (int i = 1; i <= edge; ++i)
						{
								int tmp_1{0};
						        	int tmp_2{0};
								for (int j = 1; j <= vertex; ++j)
								{
									if (IM[i][j] == 1)
										tmp_1 = j;
									else if (IM[i][j] == -1)
										tmp_2 = j;
									else if (IM[i][j] == 2)
									{
										IL[j].push_back(j);
										break;
									}
								}
								if (tmp_1 != 0 && tmp_2 != 0)
									IL[tmp_2].push_back(tmp_1);
						}
						representation = 3;
					}
					break;
		}
	} else if (representation == 3)
	{
		switch (_rep)
		{
			case 0:
					{
						for (int i = 1; i <= vertex; ++i)
							for (vector<int>::iterator it = IL[i].begin(); it != IL[i].end(); ++it)
								AM[i][*it] = 1;
						representation = 0;
					}
					break;
			case 1:
					{
						this->clear_AL();
						int e = 1;
						for (int i = 1; i <= vertex; ++i)
							for (vector<int>::iterator it = IL[i].begin(); it != IL[i].end(); ++it)
							{
								AL[e].push_back(i);
								AL[e].push_back(*it);
								++e;
							}
						representation = 1;
					}
					break;
			case 2:	
					{
						int e = 1;
						for (int i = 1; i <= vertex; ++i)
							for (vector<int>::iterator it = IL[i].begin(); it != IL[i].end(); ++it)
							{
								if (i != *it)
								{
									IM[e][i] = -1;
									IM[e][*it] = 1;
									++e;
								} else
								{
									IM[e][i] = 2;
									++e;
								}
							}	
						representation = 2;
					}
					break;
		}
	}
};

int main()
{
	int choice;
	int choice_2;
	int vertex;
	int edge;
	int representation;
	Graph obj;
	
	cout << "\033[0;36m" << "Directed Graph" << "\033[m"<< endl;
	do
	{
		cout << "Current Representation: ";
		switch(obj.get_representation())
		{
			case 0:
						cout << "\033[0;34m" << "Adjacency Matrix" << "\033[m" << endl;
						break;
			case 1:
						cout << "\033[0;34m" << "Adjacency List" << "\033[m" << endl;
						break;
			case 2:
						cout << "\033[0;34m" << "Incidence Matrix" << "\033[m" << endl;
						break;
			case 3:
						cout << "\033[0;34m" << "Incidence List" << "\033[m" << endl;
						break;
			case 4:
						cout << "\033[0;34m" <<  "No Object" << "\033[m" <<  endl;
						break;
		}
		cout << "1. Create object" << endl;
		cout << "2. Transform" << endl;
		cout << "3. Show" << endl;
		cout << "4. Clear" << endl;
		cout << "5. Exit" << endl;
		cin >> choice;
		switch (choice)
		{
			case 1: 
						cout << "Number of vertices: ";
						cin >> vertex;
						cout << "Number of edges: ";
						cin >> edge;
						cout << "Reperesentation" << endl;
						cout << "1. Adjacency Matrix" << endl;
						cout << "2. Adjacency List" << endl;
						cout << "3. Incidence Matrix" << endl;
						cout << "4. Incidence List" << endl;
						cin >> representation;
						obj.initialize(vertex,edge,representation - 1);
						obj.set();
						break;
			case  2:
						cout << "1. ->Adjacency Matrix" << endl;
						cout << "2. ->Adjacency List" << endl;
						cout << "3. ->Incidence Matrix" << endl;
						cout << "4. ->Incidence List" << endl;
						cin >> choice_2;
						obj.transform(choice_2 - 1);
						break;
			case 3:
						obj.show();
						break;
			case 4:
						system("clear");
						break;
		}
	} while (choice != 5);
	
	return 0;
}
	
