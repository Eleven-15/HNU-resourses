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

/*template <typename VertexType>
struct graphlist{
   VertexType data;
   List<Edge>* vl;
};*/
template <typename VertexType>
class Graphl : public Graph<VertexType> {
private:
  struct graphlist{
         VertexType data;
         List<Edge>* vl;
  };
  //List<Edge>** vertex;        // List headers
  int numVertex, numEdge;     // Number of vertices, edges 
  int *mark;                  // Pointer to mark array
  bool undirected;  // true if graph is undirected, false if directed
  //VertexType vexs[MAX_VERTEX_NUM];	//存储顶点信息 
  graphlist* gl;
public:
  Graphl(int numVert)
    { Init(numVert); }

  ~Graphl() {       // Destructor
    delete [] mark; // Return dynamically allocated memory
    //for (int i=0; i<numVertex; i++) delete [] gl[i];
    delete [] gl;
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
    gl =  new graphlist[numVertex];
    for (i=0; i<numVertex; i++)
      gl[i].vl = new LList<Edge>();
  }

  int n() { return numVertex; } // Number of vertices
  int e() { return numEdge; }   // Number of edges

  int first(int v) { // Return first neighbor of "v"
    if (gl[v].vl->length() == 0)
      return numVertex;      // No neighbor
    gl[v].vl->moveToStart();
    Edge it = gl[v].vl->getValue();
    return it.vertex();
  }

  // Get v's next neighbor after w
  int next(int v, int w) {
    Edge it;
    if (isEdge(v, w)) {
      if ((gl[v].vl->currPos()+1) < gl[v].vl->length()) {
        gl[v].vl->next();
        it = gl[v].vl->getValue();
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
			if(Comp(u,gl[i].data))	//Comp模板函数写在book.h中 
				return i;
		}
		return -1;
	}
	/**返回某个顶点的值(实际信息) **/ 
	VertexType getVex(int v){
		return gl[v].data;
	} 
    /**给某个顶点赋值**/
	void putVex(int v,VertexType value){
		gl[v].data = value;
	}
		
  
  // Set edge (i, j) to "weight"
  void setEdge(int i, int j, int weight) {
    Assert(weight>0, "May not set weight to 0");
    Edge currEdge(j, weight);
    if (isEdge(i, j)) { // Edge already exists in graph
      gl[i].vl->remove();
      gl[i].vl->insert(currEdge);
    }
    else { // Keep neighbors sorted by vertex index
      numEdge++;
      for (gl[i].vl->moveToStart();
           gl[i].vl->currPos() < gl[i].vl->length();
           gl[i].vl->next()) {
        Edge temp = gl[i].vl->getValue();
        if (temp.vertex() > j) break;
      }
      gl[i].vl->insert(currEdge);
      if(undirected){//若是无向图 
      	Edge currEdge(i, weight);
	    	for (gl[j].vl->moveToStart();
	           gl[j].vl->currPos() < gl[j].vl->length();
	           gl[j].vl->next()) {
	        Edge temp = gl[j].vl->getValue();
	        if (temp.vertex() > i) break;
	      }
	      gl[j].vl->insert(currEdge);
			}  
    }
  }

  void delEdge(int i, int j) {  // Delete edge (i, j)
    if (isEdge(i,j)) {
      gl[i].vl->remove();
      numEdge--;
    }
    if(undirected){
    	if (isEdge(j,i)){
	      gl[j].vl->remove();
	      numEdge--; 
   		}
   	}
  }

  bool isEdge(int i, int j) { // Is (i,j) an edge?
    Edge it;
    for (gl[i].vl->moveToStart();
         gl[i].vl->currPos() < gl[i].vl->length();
         gl[i].vl->next()) {            // Check whole list
      Edge temp = gl[i].vl->getValue();
      if (temp.vertex() == j) return true;
    }
    return false;
  }

  int weight(int i, int j) { // Return weight of (i, j)
    Edge curr;
    if (isEdge(i, j)) {
      curr = gl[i].vl->getValue();
      return curr.weight();
    }
    else return 0;
  }
 
  int getMark(int v) { return mark[v]; }
  void setMark(int v, int val) { mark[v] = val; }
};

