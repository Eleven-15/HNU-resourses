// Heap class 堆类 
template <typename E, typename Comp> class heap {
private:
  	E* Heap;          // Pointer to the heap array 堆数组指针 
  	int maxsize;     	// Maximum size of the heap 最大容量 
  	int n;            // Number of elements now in the heap 元素当前位置 

  	// Helper function to put element in its correct place 下拉函数 
  	void siftdown(int pos) {
    	while (!isLeaf(pos)) { 	//Stop if pos is a leaf 是叶节点就停止下拉 
	      int j = leftchild(pos);  
		  int rc = rightchild(pos);
	      if ((rc < n) && Comp::prior(Heap[rc], Heap[j]))
	        j = rc;            	// Set j to greater child's value 将j赋值为较大子节点的值 
	      if (Comp::prior(Heap[pos], Heap[j])) return; 
	      swap(Heap, pos, j);
	      pos = j;             	// Move down 下拉 
    }
  }

public:
  	heap(E* h, int num, int max)     // Constructor构造函数 
    { Heap = h;  n = num;  maxsize = max;  buildHeap(); }
  	int size() const       			// Return current heap size 返回当前堆大小 
    { return n; }
  	bool isLeaf(int pos) const 	
    { return (pos >= n/2) && (pos < n); }
  	int leftchild(int pos) const
    { return 2*pos + 1; }    	// Return leftchild position 返回左孩子位置 
  	int rightchild(int pos) const
    { return 2*pos + 2; }    	// Return rightchild position 返回右孩子位置 
  	int parent(int pos) const  	// Return parent position 返回父结点位置 
    { return (pos-1)/2; }
  	void buildHeap()           	// Heapify contents of Heap 建堆 
    { for (int i=n/2-1; i>=0; i--) siftdown(i); }

  	// Insert "it" into the heap 将it插入堆 
  	void insert(const E& it) {
    Assert(n < maxsize, "Heap is full");
    int curr = n++;
    Heap[curr] = it;       		// Start at end of heap 先插在末尾 
    // Now sift up until curr's parent > curr 上移直到当前节点父结点大于当前节点 
    while ((curr!=0) &&
           (Comp::prior(Heap[curr], Heap[parent(curr)]))) {
      swap(Heap, curr, parent(curr));
      curr = parent(curr);
    }
  }
  	// Remove first value 删除最大值 
  	E removefirst() {
    Assert (n > 0, "Heap is empty");
    swap(Heap, 0, --n);       // Swap first with last value 将最上面节点与最后一个节点交换 
    if (n != 0) siftdown(0);  // Siftdown new root val 下拉根节点 
    return Heap[n];           // Return deleted value 返回删除节点 
  }

  // Remove and return element at specified position 删除任意位置节点 
  	E remove(int pos) {
    Assert((pos >= 0) && (pos < n), "Bad position");
    if (pos == (n-1)) n--; // Last element, no work to do 最后一个节点则不处理 
    else
    {
      swap(Heap, pos, --n);         
      while ((pos != 0) &&
             (Comp::prior(Heap[pos], Heap[parent(pos)]))) {
        swap(Heap, pos, parent(pos)); 
        pos = parent(pos);
      }
      if (n != 0) siftdown(pos);  
    }
    return Heap[n];
  }
};
