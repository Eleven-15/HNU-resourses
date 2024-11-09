typedef char E;
class ANode{
private:
		E it;
		int lc;// Index of left child
		int rc;// Index of right child
		int p;
public:
  	ANode() { lc = rc = 0; }
  	//返回节点元素 
  	E element() { return it; }
  	//设置节点元素 
  	void setElement(E e) { it = e; }
  	//返回左结点下标 
  	int left() { return lc; }
  	//设置左孩子 
  	void setLeft(int i) { lc = 2*i+1; }
  	//返回右节点下标 
  	int right() { return rc; }
  	//设置右孩子 
  	void setRight(int i) { rc = 2*i+2; }
};

