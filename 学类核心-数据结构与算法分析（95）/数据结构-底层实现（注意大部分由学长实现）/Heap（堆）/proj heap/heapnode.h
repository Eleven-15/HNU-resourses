template <typename E> 
class Heapnode{
public:
	bool isLeaf(int pos,int n) const 
    { 
		return (pos >= n/2) && (pos < n); 
	}
  	int leftchild(int pos) const
    { 
		return 2*pos + 1; 
	}    // Return leftchild position 返回左孩子下标 
  	int rightchild(int pos) const
    { 
		return 2*pos + 2; 
	}    // Return rightchild position 返回右孩子下标 
  	int parent(int pos) const  // Return parent position 返回父结点下标 
    { 
		return (pos-1)/2; 
	}	
} 
