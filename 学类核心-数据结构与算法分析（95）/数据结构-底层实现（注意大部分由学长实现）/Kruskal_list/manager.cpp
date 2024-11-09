#include<iostream>
#include<cstring>
#include "graphl.h"
#include "graph.h"
#include "create.h" 
#include "heap.h"
#define ROOT -1
#include "uf.h"
#define INFINITY 9999

using namespace std;

void AddEdgetoMST(Graph<string>* G,int v1, int v2) {
  cout << "增加边 " << G->getVex(v1) << " <--> " << G->getVex(v2) << ":"<<G->weight(v1,v2)<<endl;
}

// Simple class to store data in the heap: edge and its distance
class KruskElem {         // An element for the heap
public:
  int from, to, distance; // The edge being stored
  KruskElem() { from = -1;  to = -1; distance = -1; }
  KruskElem(int f, int t, int d)
    { from = f; to = t; distance = d; }
};

// Comparator to compare two KruskElem's
class Comp {
public:
  static bool prior(KruskElem x, KruskElem y)
    { return x.distance < y.distance; }
};

void Kruskel(Graph<string>* G) {   // Kruskal's MST algorithm
  ParPtrTree A(G->n());    // Equivalence class array
  KruskElem E[G->e()];     // Array of edges for min-heap
  int i;
  int edgecnt = 0;
  for (i=0; i<G->n(); i++) // Put the edges on the array
    for (int w=G->first(i); w<G->n(); w = G->next(i,w)) {
    	if(w>i){//无向图 保证A->B B->A值存一次 
    		E[edgecnt].distance = G->weight(i, w);
      	E[edgecnt].from = i;
      	E[edgecnt++].to = w;
			}
    }
  // Heapify the edges
  heap<KruskElem, Comp> H(E, edgecnt, edgecnt);
  
  int numMST = G->n();       // Initially n equiv classes

  //cout<<"differ:"<<A.differ(m, n)<<endl;
  for (i=0; numMST>1; i++) { // Combine equiv classes
    KruskElem temp;
    temp = H.removefirst(); // Get next cheapest edge
    int v = temp.from;  int u = temp.to;
    if (A.differ(v, u)) {  // If in different equiv classes
      A.UNION(v, u);       // Combine equiv classes
      AddEdgetoMST(G,temp.from, temp.to);  // Add edge to MST
      numMST--;            // One less MST
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
	
	cout<<"--------------------------------\n"
			<<"调用Kruskal求解最小生成树：\n";
	Kruskel(G);
	cout<<"MST构建完成！\n";
	
	return 0;
}
