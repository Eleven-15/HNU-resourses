//堆的抽象类 
template <typename E> class heap {
private:
  void operator =(const heap&) {}     
  heap(const heap&) {}        
  virtual void siftdown(int pos) = 0;
public:
  	heap() {}                       
	virtual ~heap() {}   
	//建堆操作           
  	virtual void buildHeap() = 0;   
	//向堆中插入一个元素        
  	virtual void insert(const E& it) = 0;
  	//删除最大值 
 	virtual E removefirst() = 0;
	//删除指定位置的元素	
	virtual E remove(int pos) = 0;

};
