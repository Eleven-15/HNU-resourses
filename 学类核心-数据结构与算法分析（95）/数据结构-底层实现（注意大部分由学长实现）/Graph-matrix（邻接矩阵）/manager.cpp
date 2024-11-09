#include<iostream>
#include<cstring>
#include "graphm.h"
#include "graph.h"
#include "create.h" 
using namespace std;

int main(){
	//now let's create our graph
	//we read info from the textfile 
	FILE *fid;
	fid = fopen("test.gph", "rt");
	Graph<string>* G;
	G = createGraph(fid);
	Gprint(G);
	return 0;
}
