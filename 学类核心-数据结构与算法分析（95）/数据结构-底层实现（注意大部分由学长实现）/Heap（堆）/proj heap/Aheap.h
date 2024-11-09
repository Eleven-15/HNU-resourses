#include "heap.h"
//基于数组实现的堆 
template <typename E, typename Comp> class Aheap:public {
private:
  E* Heap;     //Pointer to the heap array 指向堆数组 
  int maxsize; // Maximum size of the heap 堆最大容量 
  int n;       // Number of elements now in the heap 堆中当前元素个数 

  // Helper function to put element in its correct place 
  //下拉元素到正确位置 
  void siftdown(int pos) {
    while (!isLeaf(pos,n)) { // Stop if pos is a leaf 是叶子节点就停止 
      int j = leftchild(pos);  int rc = rightchild(pos);
      if ((rc < n) && Comp::prior(Heap[rc], Heap[j]))
        j = rc;          
      if (Comp::prior(Heap[pos], Heap[j])) return; 
      swap(Heap, pos, j);
      pos = j;            
    }
  }

public:
  	Aheap(E* h, int num, int max)     
    { Heap = h;  n = num;  maxsize = max;  buildHeap(); }
  	int size() const       
    { return n; }
  	void buildHeap() // Heapify contents of Heap 建堆 
    { for (int i=n/2-1; i>=0; i--) siftdown(i); }

  // Insert "it" into the heap 插入元素到堆中 
  void insert(const E& it) {
    Assert(n < maxsize, "Heap is full");
    int curr = n++;
    Heap[curr] = it;           
    // Now sift up until curr's parent > curr
    //下拉直到位置正确 
    while ((curr!=0) &&(Comp::prior(Heap[curr], Heap[parent(curr)]))) {
      swap(Heap, curr, parent(curr));
      curr = parent(curr);
    }
  }
  // Remove first value 删除最大元素 
  E removefirst() {
    Assert (n > 0, "Heap is empty");
    swap(Heap, 0, --n);       // Swap first with last value 将最大值与最后一个元素交换 
    if (n != 0) siftdown(0);  // Siftdown new root val 下拉元素 
    return Heap[n];           // Return deleted value 返回删除的元素 
  }

  // Remove and return element at specified position
  //删除指定位置的元素 
  E remove(int pos) {
    Assert((pos >= 0) && (pos < n), "Bad position");
    if (pos == (n-1)) n--; // Last element, no work to do若是最后一个则直接删除 
    else
    {
      swap(Heap, pos, --n);          // Swap with last value 与最后一个交换 
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
