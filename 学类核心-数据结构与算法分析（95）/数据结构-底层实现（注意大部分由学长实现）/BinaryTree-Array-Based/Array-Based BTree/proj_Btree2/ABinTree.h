#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
class ABinTree:public ANode{
private:
	int root;          	// Root of the BinTree BinTree树的根结点
public:
	vector<ANode> nodeArray; 	//用数组存储节点 
	int Root(){
		return 0;
	}
	void setroot(int n){
		root=n;
	}
	//是否为空树 
	bool BiTreeEmpty(int rt)
    {
	    if(nodeArray[rt].element()=='#') 
			return true; //是一棵空树 
	    else 
			return false;//不是空树 
    }

	//前序遍历 
	void preorder(int rt)
    {
    	if(nodeArray[rt].element()=='#')
    		return;
    	else
        {
            cout<<nodeArray[rt].element()<<" ";
            preorder(nodeArray[rt].left());
            preorder(nodeArray[rt].right());
        }
    }
	//中序遍历 
  void Inorder(int rt)
  {
      if(nodeArray[rt].element()!='#')
      {
          Inorder(nodeArray[rt].left());
	    cout<<nodeArray[rt].element()<<" ";
          Inorder(nodeArray[rt].right());
      }
  }
	//后序遍历 
    void postorder(int rt)
    {
        if(nodeArray[rt].element()!='#')
        {
            postorder(nodeArray[rt].left());
		    postorder(nodeArray[rt].right());
            cout<<nodeArray[rt].element()<<" ";
        }
    }
	//层次遍历 
    void LevelOrderTraverse(int rt)
    {
        queue<int> q;
        if(nodeArray[rt].element()!='#')
            q.push(rt);
        int temp;
        while(!q.empty())
        {
            temp=q.front();
            cout<<nodeArray[temp].element()<<' ';
            q.pop();
            int l=nodeArray[temp].left();
            int r=nodeArray[temp].right();
            if(nodeArray[l].element()!='#')
                q.push(l);
            if(nodeArray[r].element()!='#')
                q.push(r);
        }
    }
	//树的深度 
    int BiTreeDepth(int rt)
    {
	    int lh=0,rh=0 ;
        if(nodeArray[rt].element()!='#')
        {
            lh=BiTreeDepth(nodeArray[rt].left());
            rh=BiTreeDepth(nodeArray[rt].right());
            return (lh>rh?lh:rh)+1;
        }
        else  return 0 ;
    }
	//结点个数 
    int count(int rt)
    {
	    if(nodeArray[rt].element()!='#')  return count(nodeArray[rt].left())+count(nodeArray[rt].right())+1;
        else return 0;
    }
};

