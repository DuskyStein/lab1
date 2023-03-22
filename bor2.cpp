#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Graph {
	int V; 
	vector<vector<int> >graph; 

	int find(vector<int>& parent, int i)
	{
		if (parent[i] == i) {
			return i;
		}
		return find(parent, parent[i]);
	}


	void unionSet(vector<int>& parent, vector<int>& rank,
		int x, int y)
	{
		int xroot = find(parent, x);
		int yroot = find(parent, y);

		if (rank[xroot] < rank[yroot]) {
			parent[xroot] = yroot;
		}
		else if (rank[xroot] > rank[yroot]) {
			parent[yroot] = xroot;
		}

		else {
			parent[yroot] = xroot;
			rank[xroot]++;
		}
	}

public:
	Graph(int vertices)
	{
		V = vertices;
		graph = vector<vector<int> >();
	}

	void addEdge(int u, int v, int w)
	{
		graph.push_back({ u, v, w });
	}


	void boruvkaMST()
	{
		vector<int> parent(V);

		vector<int> rank(V);
		vector<vector<int> > cheapest(V,
			vector<int>(3, -1));

		int numTrees = V;
		int MSTweight = 0;

		for (int node = 0; node < V; node++) {
			parent[node] = node;
			rank[node] = 0;
		}

		while (numTrees > 1) {

			for (int i = 0; i < graph.size(); i++) {
				int u = graph[i][0], v = graph[i][1],
					w = graph[i][2];
				int set1 = find(parent, u),
					set2 = find(parent, v);

				if (set1 != set2) {
					if (cheapest[set1][2] == -1
						|| cheapest[set1][2] > w) {
						cheapest[set1] = { u, v, w };
					}
					if (cheapest[set2][2] == -1
						|| cheapest[set2][2] > w) {
						cheapest[set2] = { u, v, w };
					}
				}
			}

			for (int node = 0; node < V; node++) {

				if (cheapest[node][2] != -1) {
					int u = cheapest[node][0],
						v = cheapest[node][1],
						w = cheapest[node][2];
					int set1 = find(parent, u),
						set2 = find(parent, v);
					if (set1 != set2) {
						MSTweight += w;
						unionSet(parent, rank, set1, set2);
						printf("Edge %d-%d with weight %d "
							"included in MST\n",
							u, v, w);
						numTrees--;
					}
				}
			}
			for (int node = 0; node < V; node++) {

				cheapest[node][2] = -1;
			}
		}
		printf("Weight of MST is %d\n", MSTweight);
	}
};
int main()
{
	int GraphLength = 0;
	string line;
	int i = 0;
	int y = 0;


	ifstream MyFile("boruvka.txt");
	if (MyFile.is_open()) {
		std::getline(MyFile, line);
		std::cout<<"Graph Length: " << line;
		GraphLength = std::stoi(line);
		Graph g(GraphLength);

		while (getline(MyFile, line, '\n')) {
			stringstream ss;

			ss << line;

			string temp;
			int found;
			y = 0;
			std::cout << '\n';
			std::cout << "Node:" << i << "|";
			while (!ss.eof()) {

				ss >> temp;

				if (stringstream(temp) >> found) {
					if (found != 0) {
						g.addEdge(i, y, found);
					}
					std::cout << found << '(' << y << ')' << " ";
					y++;


				}

				temp = "";
			}
			i++;

		}

		g.boruvkaMST();

	}
	else
	{
		std::cout << "Error opening a file";
	}


}


