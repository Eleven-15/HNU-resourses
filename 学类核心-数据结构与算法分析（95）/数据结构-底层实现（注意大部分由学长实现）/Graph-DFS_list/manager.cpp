#include <iostream>
#include <cstring>
#include "graphl.h"
#include "graph.h"
#include "create.h"

using namespace std;

void PreVisit(Graph<string>* G, int v) {
  cout << "PreVisit vertex " << G->getVex(v) << "\n";
}

void PostVisit(Graph<string>* G, int v) {
  cout << "PostVisit vertex " << G->getVex(v) << "\n";
}

void DFS(Graph<string>* G, int v) { // Depth first search
  PreVisit(G, v);           // Take appropriate action
  G->setMark(v, VISITED);
  for (int w=G->first(v); w<G->n(); w = G->next(v,w))
    if (G->getMark(w) == UNVISITED)
      DFS(G, w);
  //PostVisit(G, v);          // Take appropriate action
}

void doTraverse(Graph<string>* G, int v) {
  cout<< "--------------------------------"<<endl
			<<"从顶点" << G->getVex(v) << "起DFS遍历: \n";
  DFS(G, v);
}

void graphTraverse(Graph<string>* G) {
  int v;
  for (v=0; v<G->n(); v++)
    G->setMark(v, UNVISITED);  // Initialize mark bits
  for (v=0; v<G->n(); v++)
    if (G->getMark(v) == UNVISITED)
      doTraverse(G, v);
}

int main(){

	FILE *fid;
	fid = fopen("test.gph", "rt");
	
	Graph<string>* G;
	//创建图（create.h) 
	G = createGraph(fid);
	//打印图（create.h) 
	Gprint(G);
	
	//遍历图 
  graphTraverse(G);
	
	return 0;
}
