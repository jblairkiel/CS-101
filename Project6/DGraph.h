#ifndef DGRAPH_H_
#define DGRAPH_H_

#include <string>

using namespace std;

struct node {
		int vertex;		
		int x;				
		int y;
		int weight;
		node *next;
};

struct edge {
	node *vertex1;
	node *vertex2;
	int weight;
};

class DGraph{

	private:
		node *verticesList[500];
		edge *adjacencyList[500];
		int distances[500];
		int parent[500];
		int vertCount;
		int edgeCount;
		

	public:
		DGraph(int vertices, int edges);
		void addVertex(int vertex, int x, int y);
		node* addEdge(int v1, int v2);
		int calculateWeight(node *v1, node *v2);
		
};
#endif
