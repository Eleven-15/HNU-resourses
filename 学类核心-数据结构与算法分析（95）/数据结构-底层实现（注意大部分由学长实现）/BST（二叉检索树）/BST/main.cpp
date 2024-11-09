#include "BST.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;
void creat(BST& tree,int n,vector<int> &A);
void print(int f);
int height(BSTNode *root);
void PrintNodeByLevel(BSTNode *root,int n);   
int main()
{
	int i,n,nC,val,flag,temp;
	BST tree;
	vector<int> A;
	cout<<"本程序对BST树的基本操作进行演示"<<endl;
	cout<<"输入元素的总数n，以回车结束:"<<endl;
	cin>>n;
	if(n<=0) {
		cout<<"输入不合法"<<endl; exit(0); 
	}
	cout<<"输入n个元素，中间以空格隔开"<<endl;
	for(i=0;i<n;i++){
		cin>>val;
		A.push_back(val);
	}
	creat(tree,n,A);//构建BST
	nC=tree.nodecount();
	cout<<"层次遍历输出BST树："<<endl;
	PrintNodeByLevel(tree.getRoot(),nC);	
	cout<<"请输入要插入的值"<<endl;
	cin>>val;
	tree.insert(val);
	nC=tree.nodecount();
	cout<<"新树如下："<<endl;
	PrintNodeByLevel(tree.getRoot(),nC);
    cout<<"请输入要删除的值"<<endl;
	cin>>val;
	temp=tree.remove(val);
	if(temp==1){
	    nC=tree.nodecount();
	    cout<<"新树如下："<<endl;
	    PrintNodeByLevel(tree.getRoot(),nC);
    }
    else cout<<"操作失败！"<<endl;
	cout<<"请输入要查找的值，ctrl+Z结束程序"<<endl; 
	while(cin>>val){
		flag=tree.find(val);//查找函数 
		print(flag);//输出函数 
		count=0;//每次查找完毕将count复原 
	}
	return 0;
}
void creat(BST& tree,int n,vector<int> &A){
	int i;
	for(i=0;i<n;i++){
		tree.insert(A[i]);
	}
} 
void print(int f){
	if(f)
		cout<<"查找成功  "<<count<<endl;
	else
		cout<<"查找不成功  "<<count<<endl; 
}
int height(BSTNode *root){//求树的高度 
    int lh,rh,h;
    if(root==NULL) return -1;
    lh=height(root->left());
    rh=height(root->right());
    h=lh>rh?lh:rh;
    return (h+1);
}
void PrintNodeByLevel(BSTNode *root,int nC){  
    int parentSize=1, childSize=0;  
    int ncount=0,level=0,i=0,j=0,k=0;
    int *A=new int[1000000];//新建数组
    BSTNode *temp;
	BSTNode *temp1=new BSTNode(-1,NULL,NULL);//用-1的节点表示空节点 
    queue<BSTNode *> q;
	q.push(root);
    do  //利用队列进行层次遍历 
    {
        temp=q.front(); 
        if(temp->getData()!=-1)
            ncount++;//记录已输出的有效节点个数 
		A[i++]=temp->getData();//将节点信息存入数组中 
        q.pop();
        if(temp->left()!=NULL){   //检查temp指针所指的父节点的左孩子 
            q.push(temp->left());  
            childSize ++;  
        }
		else q.push(temp1);	
        if(temp->right()!=NULL){  //检查temp指针所指的父节点的右孩子 
            q.push(temp->right());  
            childSize ++;  
        }
		else q.push(temp1);
        parentSize--; 
        if(parentSize==0) 
        {  
            parentSize=childSize;  
            childSize=0;  
        }  
    }while (ncount!=nC);
    level=height(root)+1;
	for(i=0,j=0;i<level;i++)  //层次地输出节点 
	{
		k=0;
		while(k<pow(2,i))
		{
			if(A[j]==-1)
			  cout<<"* ";     //'*'号表示空节点
			else if(A[j]==0) ;//A[j]未存储节点值时值为0，不输出 
			else cout<<A[j]<<" ";
			k++;
			j++;
		}
		cout<<endl;
	} 
	delete [] A;//释放数组空间 
} 

	
	
