#include <iostream>
typedef int E;
class BSTNode{
private:
	E data;//二叉树节点存储的值   
	BSTNode* lc;
	BSTNode* rc;//左右孩子指针  
public:
	BSTNode()//初始化节点 
	{ 
		lc=rc=NULL;
	}  
	BSTNode(E e,BSTNode* l=NULL,BSTNode* r=NULL)//构建一个非空节点 
	{
		data=e;lc=l;rc=r;	
	}
	E getData(){ return data;}
	BSTNode* left(){ return lc; }
	BSTNode* right(){ return rc; }
	void setLeft(BSTNode* b){lc=b;}
	void setRight(BSTNode* b){rc=b;}
	void setElement(const E& e) { data=e; }
};
