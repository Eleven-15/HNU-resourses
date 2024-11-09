#include"BinTree.h"
template<typename E>
void printNode(BinNode<E>*tmp)//打印结点的值的函数
{
	cout << tmp->getValue() << " ";
}
template<typename E>
BinNode<E>* creatBinaryTree(string s[], int &x,int n)//构建二叉树的主函数，根据先序遍历，采用递归思想构建
{
	if (s[x] =="/")
		return NULL;
	else
	{
		BinNode<E>*node = new BinNode<E>(s[x]);
		x = x + 1;
		if (x < n);
		node->setLeft(creatBinaryTree<E>(s, x,n));
		x = x + 1;
		if (x < n);
		node->setRight(creatBinaryTree<E>(s, x,n));
		return node;
	}
}	
 void creatBinaryTree(BinTree<string>*BT)//构建二叉树的函数，包含了上面的构建二叉树的主函数，仅仅起到了在主函数中简洁一些的作用
{
	cout << "现在进入构建二叉树程序......" << endl;
	cout << "请输入二叉树有多少个结点(空结点也计算其中)" << endl;
	int n = 0;
	cin >> n;
	cout << "请按preorder顺序输入，遇到NULL请输入'/',用空格隔开或者回车隔开均可以" << endl;
	string*s = new string[n];
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	int now = 0;
	BT->setRoot(creatBinaryTree<string>(s, now, n));
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