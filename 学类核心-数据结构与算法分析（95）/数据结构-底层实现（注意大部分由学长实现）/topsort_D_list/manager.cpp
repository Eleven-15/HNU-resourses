#include<iostream>
#include<cstring>
#include<stack>
#include "graphl.h"
#include "graph.h"
#include "create.h" 
#define INFINITY 9999

using namespace std;

void tophelp(Graph<string>*,stack<string>& S, int);

void topsort(Graph<string>* G,stack<string>& S) {   // Topological sort: recursive
  int i;
  for (i=0; i<G->n(); i++) // Initialize Mark array
    G->setMark(i, UNVISITED);
  for (i=0; i<G->n(); i++) // Process all vertices
    if (G->getMark(i) == UNVISITED)
      tophelp(G, S, i);       // Call recursive helper function
  while(!S.empty()){
  	cout<<S.top()<<" ";
  	S.pop();
	}
}

void tophelp(Graph<string>* G, stack<string>& S,int v) { // Process vertex v
  G->setMark(v, VISITED);
  for (int w=G->first(v); w<G->n(); w = G->next(v,w))
    if (G->getMark(w) == UNVISITED)
      tophelp(G, S,w);
  S.push(G->getVex(v));
}

int main(){
	
	FILE *fid;
	fid = fopen("test.gph", "rt");
	
	Graph<string>* G;

	//创建图（create.h) 
	G = createGraph(fid);
	//打印图（create.h) 
	Gprint(G);
	
	stack<string> S;
	cout<<"--------------------------------\n"
			<<"调用topsort打印顶点顺序：\n";

  topsort(G,S);
 
	return 0;
}
