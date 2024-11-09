// General tree representation for UNION/FIND
//一般树表示并查集 

class ParPtrTree {
private:
  int* array;                    // Node array 顶点数组 
  int size;                      // Size of node array
  int FIND(int) const;           // Find root查找该顶点的根 
public:
  ParPtrTree(int);                   // Constructor构造函数 
  ~ParPtrTree() { delete [] array; } // Destructor析构函数 
  void UNION(int, int); 	// Merge equivalences合并 
  bool differ(int, int);    // True if not in same tree判断是否属来自同一棵树 
};
ParPtrTree::ParPtrTree(int sz) { // Constructor构造函数 
  size = sz;
  array = new int[sz];           // Create node array建立顶点数组 
  for(int i=0; i<sz; i++) array[i] = ROOT;
}

// Return True if nodes are in different trees
//若不是同一棵树返回true 
bool ParPtrTree::differ(int a, int b) {
  int root1 = FIND(a);           // Find root of node a.找a的根 
  int root2 = FIND(b);           // Find root of node b.找b的根 
  return root1 != root2;         // Compare roots.比较两根 
}

void ParPtrTree::UNION(int a, int b) { // Merge subtrees.合并树 
  int root1 = FIND(a);           // Find root of node a
  int root2 = FIND(b);           // Find root of node b
  if (root1 != root2) array[root2] = root1; // Merge
}
// FIND with path compression 返回根的值 
int ParPtrTree::FIND(int curr) const {
  if (array[curr] == ROOT) return curr; // At root已经是根则返回 
  array[curr] = FIND(array[curr]);
  return array[curr];
}

