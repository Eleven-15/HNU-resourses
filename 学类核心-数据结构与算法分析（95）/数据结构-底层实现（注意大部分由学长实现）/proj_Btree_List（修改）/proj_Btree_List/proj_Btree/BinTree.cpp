#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include "BiNode.h" 
#include "BinTree.h"
using namespace std;
typedef char E;
char c[50];
int count=0;
string s;
BiNode* r;
BinTree T;

//建树 
BiNode* CreateBiTree(char ch){
	BiNode* rt;
	if(ch=='#')  rt=NULL;
	else{
		rt=new BiNode;
		rt->setElement(ch);
		ch=c[++count];
		rt->setLeft(CreateBiTree(ch));
		ch=c[++count];
		rt->setRight(CreateBiTree(ch));
	}
	//设置根节点 
	T.setroot(rt);
	return rt;
}
	
int main()
{

	char ch;
	int depth;
	int num;
    printf("please input the tree: ");
    cout<<"以前序遍历的顺序输入，空节点以#代替,例AB#D##CE##F##"<<endl; 
    cin>>s;
    strcpy(c,s.c_str());
    r=CreateBiTree(c[0]);
   
    cout<<"判断树是否是空树：";
    if(T.BiTreeEmpty(r))
        cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
    
    cout<<"前序遍历："; 
    T.preorder(r);
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
