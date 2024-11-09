#include<iostream>
using namespace std;
template<typename E>
class BinNode//结点类
{
private:
	BinNode*lc;//左孩子
	BinNode*rc;//右孩子
	E elem;
public:
	BinNode()//默认构造函数
	{
		lc = NULL;
		rc = NULL;
	}
	BinNode(E tmp, BinNode*l=NULL, BinNode*r=NULL)//带参构造函数
	{
		elem = tmp;
		lc = l;
		rc = r;
	}
	BinNode*left()//返回左孩子
	{
		return lc;
	}
	BinNode*right()//返回右孩子
	{
		return rc;
	}
	void setLeft(BinNode*l)//设置左孩子
	{
		lc = l;
	}
	void setRight(BinNode*r)//设置右孩子
	{
		rc = r;
	}
	void setValue(E tmp)//设置当前结点的值
	{
		elem = tmp;
	}
	E getValue()//获得当前结点的值
	{
		return elem;
	}
	bool isLeaf()//判断当前结点是否为叶子结点
	{
		if (lc == NULL&&rc == NULL)
			return true;
		else
			return false;
	}
};