/********************************************************************
Projecto de ASA, 2014-2015 2' Semestre
LEIC - IST @ ALAMEDA

Grupo 162
Francisco Dias, Nº 75328
Andre Silva, Nº 75455
*********************************************************************/

/********************************************************************
	includes & defines
*********************************************************************/
#include <iostream>		// for std::cout and endl,
#include <vector>		// for list declaration
#include <limits.h>  	// for INT_MAX
#include <stdio.h>		// standard library

using namespace std;

#define IMPOSSIBLE 80

/********************************************************************
	Class and global variables
*********************************************************************/

int v, e;	// v - number of locals, e - number of costs (edges)
int source;	// int number corresponding to the source of the graph

// Edge Class
//
class Edge{
private:
	int u;  // source node
	int v;	// dest node
	int weight;	// cost between nodes
public:
	Edge(int _u, int _v, int _w){
		u = _u;
		v = _v;
		weight = _w;
	}

	int get_u(){ return u; }
	int get_v(){ return v; }
	int get_weight(){ return weight; }
	void set_weight(int _w){ weight = _w; }

	void print(){ cout << u+1 << " -- " << weight << " --> " << v+1 << endl; }
};


// Graph Class
//
class Graph{
private:
	int V;  // no. of vertices
	int E; 	// no. of edges
	vector<Edge> edges;  // vector of adjacent edges
public:
	Graph(int _V, int _E){
		V = _V;
		E = _E;
	}
	int get_v(){ return V; };
	int get_e(){ return E; };
	vector<Edge> get_edges(){ return edges; }

	void add_edge(int _u, int _v, int _w){
		Edge edge(_u, _v, _w);
		edges.push_back(edge);
	}

	void print(){
		for (int i=0; i<edges.size(); i++)
			edges[i].print();
	}

};

void printArr(int dist[], int distDup[], int imp[], int v) {
  // printf("Vertex Distance from Source\n");
  for (int i = 0; i < v; ++i) {
  	if(imp[i] == IMPOSSIBLE || dist[i] != distDup[i]) {
  		cout << "I" << endl;
  	}
  	else if(dist[i] == INT_MAX) {
	    cout << "U" << endl;
  	}
  	else {
  		cout << dist[i] << endl;
  	}
  }
}

void BellmanFord(Graph g, int source){
	int V = g.get_v();
	int E = g.get_e();
	int dist[V];
	int distDup[V];
	int imp[V];

	// initialize all values in graph to 0 and INF,
	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
		distDup[i] = INT_MAX;
		imp[i] = 0;
	}

	dist[source] = 0;
	distDup[source] = 0;

	// go V-1 times and relax vertices
	for (int i = 1; i < V-1; i++){
		for (int j = 0; j < E; j++){
			int u = g.get_edges()[j].get_u();
			int v = g.get_edges()[j].get_v();
			int weight = g.get_edges()[j].get_weight();

			//if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				distDup[v] = dist[u] + weight;
			}
		}
	}

	for (int i = 0; i < E; i++){
		int u = g.get_edges()[i].get_u();
		int v = g.get_edges()[i].get_v();
		int weight = g.get_edges()[i].get_weight();

		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			imp[u] = IMPOSSIBLE;
			imp[v] = IMPOSSIBLE;

			// FIND OTHER IMPOSSIBLE STUFF

			// printArr(dist, distDup, imp, V);

			// cout << "\n\n\n" << endl;


			for (int j = 0; j < E; j++){
				int u = g.get_edges()[j].get_u();
				int v = g.get_edges()[j].get_v();
				int weight = g.get_edges()[j].get_weight();

				//if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				if (distDup[u] != INT_MAX && distDup[u] + weight < distDup[v])
					distDup[v] = distDup[u] + weight;
			}

			printArr(dist, distDup, imp, V);

		}
	}
}

/********************************************************************
	Main program
*********************************************************************/
int main(){
	// scans first two integers (total of localities and total of costs)
	scanf("%u %u", &v, &e);
	// scans company's place? (source)
	scanf("%u", &source);
	source = source-1;
	// creates graph
	Graph g(v, e);
	// scans all costs per location and populates graph
	for (int i = 0; i < e; i++){
		int a, b, w;  // a & b are elements in the graph (the previews "node") w is the cost
		scanf("%u %u %u", &a, &b, &w);
		g.add_edge(a-1, b-1, w);
	}

	// g.print();

	BellmanFord(g, source);

	// cout << result;
	// scans #r relations of coauthors
	//InitializeSingleSource(graph, source);
	//BellmanFord(graph, wheight, source);

	// print qtd of nodes p/distance
	// for(int i = 1, c = 1; i < n; i++, c++){
	// 	if(i+1 > n || dist[i] != dist[i+1]){
	// 		printf("%d\n", c);
	// 		c = 0;
	// 	}
	// }
}
