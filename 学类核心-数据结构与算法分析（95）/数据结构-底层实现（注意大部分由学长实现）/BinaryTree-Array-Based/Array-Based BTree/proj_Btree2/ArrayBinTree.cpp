#include <iostream>
#include<iomanip>
#include "ANode.h" 
#include "ABinTree.h"
using namespace std;
typedef char E;
char c[50];
string s;
ANode a;
ABinTree T;

//建树操作 以层次遍历输入 
int CreateBiTree(string s){
	strcpy(c,s.c_str());
	for(int i=0;c[i]!='\0';i++){
		a.setLeft(i);
		a.setRight(i);	
		a.setElement(c[i]);
		T.nodeArray.push_back(a);
	}
	return 0;//返回根节点下标 
}
int main()
{
	int r;
	int depth;
	int num;
    cout<<"提示："<<endl
    	<<"以字符串形式输入要构建的二叉树时，按层次遍历的顺序输入，所有的空节点以#代替"<<endl
		<<"注意！要输入到最深层叶节点的下一层，并且该层元素为2^i个#符号！"<<endl
		<<"例：ABC#DEF########"<<endl
		<<"请输入：";
  cin>>s; 
	//建树 
	r=CreateBiTree(s);
	cout<<"-----------------------------------"<<endl; 
  cout<<"判断树是否是空树：";
  if(T.BiTreeEmpty(r))
      cout<<"输入为一棵空树"<<endl;
  else cout<<"不是空树"<<endl;
  
 cout<<"前序遍历："; 
  T.preorder(T.Root());
  cout<<endl;

  cout<<"中序遍历：";
  T.Inorder(r);
  cout<<endl;

  cout<<"后序遍历：";
  T.postorder(r);
  cout<<endl;

  cout<<"层次遍历：";
  T.LevelOrderTraverse(r);
  cout<<endl;
  
  cout<<"树的深度：";
  depth=T.BiTreeDepth(r);
  cout<<depth<<endl;
  
  cout<<"树的结点个数：";
  num=T.count(r);
  cout<<num<<endl;

	return 0;
}
