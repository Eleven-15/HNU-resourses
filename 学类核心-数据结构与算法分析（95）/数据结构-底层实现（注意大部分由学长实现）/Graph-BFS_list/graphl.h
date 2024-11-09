#include <stdio.h>
#include <ctype.h>

#define MAX_VERTEX_NUM 40
#define UNVISITED 0
#define VISITED 1

#include "link.h"
#include "llist.h"
#include "graph.h"


// Edge class for Adjacency List graph representation
class Edge {
  int vert, wt;
public:
  Edge() { vert = -1; wt = -1; }
  Edge(int v, int w) { vert = v; wt = w; }
  int vertex() { return vert; }
  int weight() { return wt; }
};

// Overload for the Edge << operator
ostream& operator << (ostream& s, Edge e)
{ return s << "(" << e.vertex() << ", " << e.weight() << ")"; }

template <typename VertexType>
class Graphl : public Graph<VertexType> {
private:
  List<Edge>** vertex;        // List headers
  int numVertex, numEdge;     // Number of vertices, edges 
  int *mark;                  // Pointer to mark array
  bool undirected;  // true if graph is undirected, false if directed
	VertexType vexs[MAX_VERTEX_NUM];	//存储顶点信息 
public:
  Graphl(int numVert)
    { Init(numVert); }

  ~Graphl() {       // Destructor
    delete [] mark; // Return dynamically allocated memory
    for (int i=0; i<numVertex; i++) delete [] vertex[i];
    delete [] vertex;
  }

  void Init(int n) {
    int i;
    numVertex = n;
    numEdge = 0;
    mark = new int[n];  // Initialize mark array
    for (i=0; i<numVertex; i++) {
    	mark[i] = UNVISITED;
		}
    // Create and initialize adjacency lists
    vertex = (List<Edge>**) new List<Edge>*[numVertex];
    for (i=0; i<numVertex; i++)
      vertex[i] = new LList<Edge>();
  }

  int n() { return numVertex; } // Number of vertices
  int e() { return numEdge; }   // Number of edges

  int first(int v) { // Return first neighbor of "v"
    if (vertex[v]->length() == 0)
      return numVertex;      // No neighbor
    vertex[v]->moveToStart();
    Edge it = vertex[v]->getValue();
    return it.vertex();
  }

  // Get v's next neighbor after w
  int next(int v, int w) {
    Edge it;
    if (isEdge(v, w)) {
      if ((vertex[v]->currPos()+1) < vertex[v]->length()) {
        vertex[v]->next();
        it = vertex[v]->getValue();
        return it.vertex();
      }
    }
    return n(); // No neighbor
  }
  
  //设置图的类型（有向图或无向图）
	void setType(bool flag){
		undirected=flag;
	}
	//获取图的类型
	bool getType(){
		return undirected;
	}
	/**返回顶点在图中的位置**/ 
	int locateVex(VertexType u){
		for(int i=0;i<numVertex;i++){
			if(Comp(u,vexs[i]))	//Comp模板函数写在book.h中 
				return i;
		}
		return -1;
	}
	/**返回某个顶点的值(实际信息) **/ 
	VertexType getVex(int v){
		return vexs[v];
	} 
  /**给某个顶点赋值**/
	void putVex(int v,VertexType value){
		vexs[v]=value;
	}
		
  
  // Set edge (i, j) to "weight"
  void setEdge(int i, int j, int weight) {
    Assert(weight>0, "May not set weight to 0");
    Edge currEdge(j, weight);
    if (isEdge(i, j)) { // Edge already exists in graph
      vertex[i]->remove();
      vertex[i]->insert(currEdge);
    }
    else { // Keep neighbors sorted by vertex index
      numEdge++;
      for (vertex[i]->moveToStart();
           vertex[i]->currPos() < vertex[i]->length();
           vertex[i]->next()) {
        Edge temp = vertex[i]->getValue();
        if (temp.vertex() > j) break;
      }
      vertex[i]->insert(currEdge);
      if(undirected){//若是无向图 
      	Edge currEdge(i, weight);
	    	for (vertex[j]->moveToStart();
	           vertex[j]->currPos() < vertex[j]->length();
	           vertex[j]->next()) {
	        Edge temp = vertex[j]->getValue();
	        if (temp.vertex() > i) break;
	      }
	      vertex[j]->insert(currEdge);
			}  
    }
  }

  void delEdge(int i, int j) {  // Delete edge (i, j)
    if (isEdge(i,j)) {
      vertex[i]->remove();
      numEdge--;
    }
    if(undirected){
    	if (isEdge(j,i)){
	      vertex[j]->remove();
	      numEdge--; 
   		}
   	}
  }

  bool isEdge(int i, int j) { // Is (i,j) an edge?
    Edge it;
    for (vertex[i]->moveToStart();
         vertex[i]->currPos() < vertex[i]->length();
         vertex[i]->next()) {            // Check whole list
      Edge temp = vertex[i]->getValue();
      if (temp.vertex() == j) return true;
    }
    return false;
  }

  int weight(int i, int j) { // Return weight of (i, j)
    Edge curr;
    if (isEdge(i, j)) {
      curr = vertex[i]->getValue();
      return curr.weight();
    }
    else return 0;
  }
  
  int getMark(int v) { return mark[v]; }
  void setMark(int v, int val) { mark[v] = val; }
};

