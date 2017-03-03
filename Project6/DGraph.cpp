#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include "DGraph.h"

using namespace std;

DGraph::DGraph(){

}

void DGraph::initialize(int vertices, int edges){
	vertCount = vertices;
	for (int i = 0; i<= vertCount; ++i){
		verticesList[i] = NULL;
	}
	edgeCount = edges;		
	for (int i = 0; i<= edgeCount; ++i){
		adjacencyList[i] = NULL;
	}
	return;
}

void DGraph::addVertex(int vert, int x1, int y1){
	node *newVertex = new node;
	newVertex->vertex = vert;
	//cout << "Made it here: " << vert << " | " << x1 << " | " << y1 << "\n";
	newVertex->x = x1;
	newVertex->y = y1;
	verticesList[vert] = newVertex;
	return;	
}

node* DGraph::addEdge(int v1, int v2){
	int weight = calculateWeight(verticesList[v1], verticesList[v2]);
	node *node2= verticesList[v2];
	node2->weight = weight;
	node2->next = verticesList[v1];
	return node2;
}

int DGraph::calculateWeight(node *v1, node *v2){
	int xs = (v2->x - v1->x);
	int ys = (v2->y - v1->y);
	return sqrt( (xs*xs) - (ys*ys));
}

void DGraph::heapify(vertex *minHeap, int size, int i, int pos[]){
	struct vertex temp;
	while ((2 * i) <= size) {
	if ((2 * i) + 1 > size) {
		if (minHeap[i].dist > minHeap[2 * i].dist) {
			pos[minHeap[i].vertex] = 2 * i;
			pos[minHeap[2 * i].vertex] = i;

			temp = minHeap[i];
			minHeap[i] = minHeap[2 * i];
			minHeap[2 * i] = temp;
		}

		break;
	}

	if (minHeap[i].dist > minHeap[2 * i].dist || minHeap[i].dist > minHeap[2 * i + 1].dist) {
		if (minHeap[2 * i].dist <= minHeap[(2 * i) + 1].dist) {
			pos[minHeap[i].vertex] = 2 * i;
			pos[minHeap[2 * i].vertex] = i;

			temp = minHeap[2 * i];
			minHeap[2 * i] = minHeap[i];
			minHeap[i] = temp;

			i = 2 * i;
		} else if (minHeap[2 * i].dist > minHeap[(2 * i) + 1].dist) {
			pos[minHeap[i].vertex] = 2 * i + 1;
			pos[minHeap[2 * i + 1].vertex] = i;

			temp = minHeap[(2 * i) + 1];
			minHeap[(2 * i) + 1] = minHeap[i];
			minHeap[i] = temp;
		
			i = (2 * i) + 1;
		}
	} else {
		break;
	}
}

void DGraph::buildHeap(vertex *minHeap, int size, int pos[]){
	    int i;

	    for (i = size / 2; i >= 1; --i) {
	        heapify(minHeap, size, i, pos);
	    }
}

void DGraph::decreaseKey(vertex *minHeap, struct vertex newNode, int pos[]){
	minHeap[pos[newNode.vertex]].dist = newNode.dist;

	int i = pos[newNode.vertex];
	struct vertex temp;

	while (i > 1) {
		if (minHeap[i / 2].dist > minHeap[i].dist) {
			pos[minHeap[i].vertex] = i / 2;
			pos[minHeap[i / 2].vertex] = i;

			temp = minHeap[i / 2];
			minHeap[i / 2] = minHeap[i];
			minHeap[i] = temp;

			i = i / 2;
		} else {
			break;
		}
	}
}

struct vertex extractMin(vertex *minHeap, int size, int pos[])
{
	pos[minHeap[1].vertex] = size;
 	pos[minHeap[size].vertex] = 1;

	struct vertex min = minHeap[1];

	minHeap[1] = minHeap[size];
 	--size;
 	heapify(minHeap, size, 1, pos);

	return min;
}


void DGraph::djikstra(int startPoint, int endPoint){

    	vertex minVertex = new vertex;
	vertex priorityQueue = new vertex*[vertcount]; 	// To use the array as 1-indexed
	int pos[vertcout];	// Stores the position (index) of vertex

	//All infinite distance
	for(int i = 0; i<=vertCount ; i++;){
		distancesArr[i] = INT_MAX;
		parent[i] = 0;
	}

	distances[startVertex] = 0;
	priorityQueue[startVertex].dist = 0;
	buildHeap(priorityQueue, vertices, pos);

	for (i = 1; i <= vertices; ++i) {     // Untill there are vertices to be processed
		minVertex = extractMin(priorityQueue, vertices, pos);   // Greedily process the nearest vertex

		struct node * trav = adjacencyList[minVertex.vertex];    // Checking all the vertices adjacent to 'min'

		while (trav != NULL) {
			int u = minVertex.vertex;
			int v = trav->vertex;
			int w = trav->weight;

			if (distances[u] != INT_MAX && distances[v] > distances[u] + w) {
				// We have discovered a new shortest route, make the neccesary adjustments in data
				distances[v] = distances[u] + w;
				parent[v] = u;

				// Making changes to the priority queue
				struct vertex changedVertex;

				changedVertex.vertex = v;
				changedVertex.dist = distances[v];	// new distance
				decreaseKey(priorityQueue, changedVertex, pos);
			}

			trav = trav->next;
		}
	}

}
