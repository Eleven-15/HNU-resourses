#include<iostream>
#include<cstring>
#include "book.h"
#include "graphm.h"
#include "graph.h"
#include "create.h" 
#define INFINITY 9999

using namespace std;

void AddEdgetoMST(Graph<string>* G,int v1, int v2) {
  cout << "增加边 " << G->getVex(v1) << " <--> " << G->getVex(v2) << ":"<<G->weight(v1,v2)<<endl;
}

int minVertex(Graph<string>* G, int* D) { // Find min cost vertex
  int i, v = -1;
  for (i=0; i<G->n(); i++) // Initialize v to some unvisited vertex;
    if (G->getMark(i) == UNVISITED) { v = i; break; }
  for (i=0; i<G->n(); i++)  // Now find smallest value
    if ((G->getMark(i) == UNVISITED) && (D[i] < D[v])) v = i;
  return v;
}

void Prim(Graph<string>* G, int* D, int s) { // Prim's MST algorithm
  int V[G->n()];                     // Store closest vertex
  int i, w;
  for (i=0; i<G->n(); i++) {         // Process the vertices
    int v = minVertex(G, D);
    G->setMark(v, VISITED);
    if (v != s)
      AddEdgetoMST(G,V[v], v);         // Add edge to MST
    if (D[v] == INFINITY) return;    // Unreachable vertices
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
      if (D[w] > G->weight(v,w)) {
        D[w] = G->weight(v,w);       // Update distance
        V[w] = v;                    // Where it came from
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
	
	int D[G->n()];
  for (int i=0; i<G->n(); i++)     // Initialize
    D[i] = INFINITY;
  
	//将位置为0的顶点A作为起点 
	D[0] = 0;
	cout<<"--------------------------------\n"
			<<"以顶点A为起始，调用Prim求解最小生成树：\n";
	Prim(G, D, 0);
	cout<<"MST构建完成！\n";
	cout<<"--------------------------------\n"
			<<"最终得到的D[i]数组(以顶点Vi为一端的最短边的权值)为：\n"; 
  for(int k=0; k<G->n(); k++)
    cout << D[k] << " ";
  cout << endl;
	
	return 0;
}
