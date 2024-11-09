#include"BinTree.h"
template<typename E>
void printNode(BinNode<E>*tmp)//打印结点的值的函数
{
	cout << tmp->getValue() << " ";
}

//update2018.4.23
//先序和中序递归建树 
template<typename E> 
//pre:先序遍历 preStart先序序列的第一个元素下标，preEnd则为最后一个元素下标
//in:同理 
BinNode<E>* creatBinaryTree(string pre[], int preStart,int preEnd,string in[],int inStart,int inEnd)
{
//边界情况 
	if(preStart>preEnd || inStart > inEnd)
	{
		return NULL;
	}
	BinNode<E>*node=new BinNode<E>(pre[preStart]);
	for(int i=inStart;i<=inEnd;i++)
	{
		if(in[i]==pre[preStart])//从先序序列找到根节点，再从中序序列划分左右子树 
		{
			node->setLeft(creatBinaryTree<E>(pre,preStart+1,preStart+i-inStart,in,inStart,i-1));
			node->setRight(creatBinaryTree<E>(pre,preStart+i-inStart+1,preEnd,in,i+1,inEnd));
			break; 
		}
	}
	return node;
} 

void creatBinaryTree(BinTree<string>*BT)//构建二叉树的函数，包含了上面的构建二叉树的主函数，仅仅起到了在主函数中简洁一些的作用
{
	cout << "现在进入构建二叉树程序......" << endl;
	int n=0;
	cout<<"请输入二叉树有多少个节点，不计算空节点"<<endl;
	cin>>n;
	string *pre=new string[n];
	string *in=new string[n];
	cout<<"请输入先序遍历序列，空格隔开"<<endl;
	for(int i=0;i<n;i++)
	cin>>pre[i];
	cout<<"请输入中序遍历序列，空格隔开"<<endl;
	for(int i=0;i<n;i++)
	cin>>in[i];
	BT->setRoot(creatBinaryTree<string>(pre,0,n-1,in,0,n-1));
}
int main()
{
	//本程序的二叉树是一个模板类，若想改变为别的类型，可以在相关的地方在“<>”中修改相关参数,本程序默认为最具有普遍性的string
	BinTree<string>*BT = new BinTree<string>;
	creatBinaryTree(BT);
	//在这里，已经构建好了一棵二叉树
	//下面是二叉树的基本函数操作的展示
	cout << "there are some functions here" << endl;
	cout << "0:判断是否为空树：";
	if (BT->BinTreeEmpty() == true)
		cout << "是" << endl;
	else
		cout << "否" << endl;
	cout << "1:前序遍历:";
	BT->preOrder(printNode);
	cout << endl;
	cout << "2:中序遍历:";
	BT->inOrder(printNode);
	cout << endl;
	cout << "3:后序遍历:";
	BT->postOrder(printNode);
	cout << endl;
	cout << "4:层次遍历:";
	BT->LevelOrderTranverse(printNode);
	cout << endl;
	cout << "5:记录树的深度:";
	cout << BT->BinTreeDepth() << endl;
	cout << "6:记录树的高度:";
	cout << BT->BinTreeHeight() << endl;
	cout << "7:统计结点:";
	cout << BT->BinTreeNodes() << endl;
	cout << "8:统计叶子结点:";
	cout << BT->BinTreeLeafs() << endl;
	cout << "9:在二叉树中查找某个值是否存在，默认查找“C”:";
	if (BT->find("C") == true)
		cout << "存在" << endl;
	else
		cout << "不存在" << endl;
	cout << "10:是否清空:";
	BT->clear();
	cout << "已清空" << endl;
	cout << "5:记录树的深度:";
	cout << BT->BinTreeDepth() << endl;
	cout << "6:记录树的高度:";
	cout << BT->BinTreeHeight() << endl;
	cout << "7:统计结点:";
	cout << BT->BinTreeNodes() << endl;
	cout << "8:统计叶子结点:";
	cout << BT->BinTreeLeafs() << endl;
	system("pause");
}
