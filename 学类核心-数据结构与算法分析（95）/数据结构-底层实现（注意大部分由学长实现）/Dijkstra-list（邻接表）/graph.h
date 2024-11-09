#ifndef GRAPH
#define GRAPH

template <typename VertexType>
class Graph {
private:
  void operator =(const Graph&) {}     // Protect assignment
  Graph(const Graph&) {}         // Protect copy constructor

public:
  Graph() {}          // Default constructor
  virtual ~Graph() {} // Base destructor

  // Initialize a graph of n vertices
  virtual void Init(int n) =0;

  // Return: the number of vertices and edges
  virtual int n() =0;
  virtual int e() =0;

  // Return v's first neighbor
  virtual int first(int v) =0;

 // Return v's next neighbor
  virtual int next(int v, int w) =0;
  
  //设置图的类型（有向图或无向图）
	virtual void setType(bool flag)=0;
	//获取图的类型
	virtual bool getType()=0; 
	//找到(包含实际信息的）顶点在图中的位置 
  virtual int locateVex(VertexType u) =0;
  //返回某个顶点的值(实际信息) 
  virtual VertexType getVex(int v)=0; 
  //给某个顶点赋值
	virtual void putVex(int v,VertexType value) =0;
	
	 
  // Set the weight for an edge
  virtual void setEdge(int v1, int v2, int wght) =0;

  // Delete an edge
  // i, j: The vertices
  virtual void delEdge(int v1, int v2) =0;

  // Determine if an edge is in the graph
  // i, j: The vertices
  // Return: true if edge i,j has non-zero weight
  virtual bool isEdge(int i, int j) =0;

  // Return an edge's weight
  // i, j: The vertices
  // Return: The weight of edge i,j, or zero
  virtual int weight(int v1, int v2) =0;

  // Get and Set the mark value for a vertex
  // v: The vertex
  // val: The value to set
  virtual int getMark(int v) =0;
  virtual void setMark(int v, int val) =0;
};
#endif
