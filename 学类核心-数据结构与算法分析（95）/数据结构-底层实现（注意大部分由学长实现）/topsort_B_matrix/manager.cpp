#include<iostream>
#include<cstring>
#include "book.h"
#include "graphm.h"
#include "graph.h"
#include "create.h" 
#include "aqueue.h"
#define INFINITY 9999

using namespace std;

// Topological sort: Queue
void topsort(Graph<string>* G, Queue<int>* Q) {
  int Count[G->n()];
  int v, w;
  for (v=0; v<G->n(); v++) Count[v] = 0; // Initialize
  for (v=0; v<G->n(); v++)   // Process every edge
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
       Count[w]++;           // Add to v2's prereq count
  for (v=0; v<G->n(); v++)   // Initialize queue
    if (Count[v] == 0)       // Vertex has no prerequisites
      Q->enqueue(v);
  while (Q->length() != 0) { // Process the vertices
    v = Q->dequeue();
    cout<<G->getVex(v)<<" ";             // PreVisit for "v"
    for (w=G->first(v); w<G->n(); w = G->next(v,w)) {
      Count[w]--;            // One less prerequisite
      if (Count[w] == 0)     // This vertex is now free
        Q->enqueue(w);
    }
  }
}

int main(){
	
	FILE *fid;
	fid = fopen("test.gph", "rt");
	
	Graph<string>* G;

	//创建图（create.h) 
	G = createGraph(fid);
	//打印图（create.h) 
	Gprint(G);
	
	Queue<int>* Q = new AQueue<int>(G->n());
	
	cout<<"--------------------------------\n"
			<<"调用topsort打印顶点顺序：\n";

  topsort(G, Q);
 
	return 0;
}
