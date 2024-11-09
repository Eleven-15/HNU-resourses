#include <iostream>
#include <cstring>
#include "graphl.h"
#include "graph.h"
#include "create.h"
#define INFINITY 9999

using namespace std;
int minVertex(Graph<string>*, int*);

// Compute shortest path distances from "s".
// Return these distances in "D".
void Dijkstra(Graph<string>* G, int* D, int s) {
  int i, v, w;
  for (i=0; i<G->n(); i++) {      // Process the vertices
    v = minVertex(G, D);
    if (D[v] == INFINITY) return; // Unreachable vertices
    G->setMark(v, VISITED);
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
      if (D[w] > (D[v] + G->weight(v, w)))
        D[w] = D[v] + G->weight(v, w);
  }
}

int minVertex(Graph<string>* G, int* D) { // Find min cost vertex
  int i, v = -1;
  // Initialize v to some unvisited vertex
  for (i=0; i<G->n(); i++)
    if (G->getMark(i) == UNVISITED) { v = i; break; }
  for (i++; i<G->n(); i++)  // Now find smallest D value
    if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
      v = i;
  return v;
}


int main(){

	FILE *fid;
	fid = fopen("test.gph", "rt");
	
	Graph<string>* G;
	//创建图（create.h) 
	G = createGraph(fid);
	//打印图（create.h) 
	Gprint(G);
	
	int D[G->n()];
  for (int i=0; i<G->n(); i++)     // Initialize
    D[i] = INFINITY;
  
	//将位置为0的顶点A作为起点 
	D[0] = 0;
	Dijkstra(G, D, 0);
	cout<<"--------------------------------\n"
			<<"以顶点A为起始，调用Dijkstra求解单源最短路径\n"
			<<"各个顶点到顶点A的最短距离依次为：\n"; 
  for(int k=0; k<G->n(); k++)
    cout << D[k] << " ";
  cout << endl;
	
	return 0;
}
