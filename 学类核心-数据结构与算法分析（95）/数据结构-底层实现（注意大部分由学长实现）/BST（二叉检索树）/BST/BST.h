#include "BSTNode.h"
#include <assert.h>
#include <stdlib.h>
using namespace std;
int count=0;
class BST:public BSTNode{
private:
	BSTNode* root; // Root of the BST 
	int nodeCount;
public:
	BST() {root = NULL; nodeCount = 0;}   //初始化一棵空树
	BSTNode* getRoot() {return root;}
	BSTNode* inserthelp(BSTNode*, const E&);
	BSTNode* removehelp(BSTNode*, const E&);
	BSTNode* deletemin(BSTNode*);
    BSTNode* getmin(BSTNode*);
	void printhelp(BSTNode*, int); 
	bool findhelp(BSTNode* ,const E& );
	int  nodecount(){return nodeCount;}
	void clearhelp(BSTNode* root);
	void clear()   // Reinitialize tree
    { 
	    clearhelp(root); 
		root = NULL; 
		nodeCount = 0;
	}
	void insert(E& e)
	{
		root = inserthelp(root,e); //调用inserthelp插入节点 
		nodeCount++;
	}
	E remove(E& e) 
	{
        E temp = findhelp(root,e);   // First find it
        if (temp != NULL) 
		{
          root = removehelp(root,e);
          nodeCount--;
        }
        count=0;
    return temp;
   }
	bool find( E& e)
	{
		return findhelp(root,e);	//调用findhelp查找 
	}
};

void BST::clearhelp(BSTNode* root) 
{
  if (root == NULL) return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

bool BST::findhelp(BSTNode* root,const E& val)
{
	if(root==NULL) return false;
	count++;
	if(val<root->getData())
		return findhelp(root->left(),val);
	else if(val>root->getData())
		return findhelp(root->right(),val);
	else
	    return true;			
}
BSTNode* BST::inserthelp(BSTNode* root,const E& val)
{
	if(root==NULL)
		return new BSTNode(val,NULL,NULL);
	if(val<root->getData())
		root->setLeft(inserthelp(root->left(),val));
	else 
		root->setRight(inserthelp(root->right(),val));
	return root;
}
BSTNode* BST::removehelp(BSTNode* rt, const E& val) {
  if (rt == NULL) return NULL;    // k is not in tree
  else if (val < rt->getData())
    rt->setLeft(removehelp(rt->left(), val));
  else if (val > rt->getData())
    rt->setRight(removehelp(rt->right(), val));
  else {                            // Found: remove it
    BSTNode* temp = rt;
    if (rt->left() == NULL) {     // Only a right child
      rt = rt->right();         //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL) { // Only a left child
      rt = rt->left();          //  so point to left
      delete temp;
    }
    else {                    // Both children are non-empty
      BSTNode* temp = getmin(rt->right());
      rt->setElement(temp->getData());
      rt->setRight(deletemin(rt->right()));
      delete temp;
    }
  }
  return rt;
}
// Delete the minimum value from the BST, returning the revised BST
BSTNode* BST::getmin(BSTNode* rt)
{
  if (rt->left() == NULL)
    return rt;
  else return getmin(rt->left());
}
BSTNode* BST::deletemin(BSTNode* rt)
{
  if (rt->left() == NULL) // Found min
    return rt->right();
  else {                      // Continue left
    rt->setLeft(deletemin(rt->left()));
    return rt;
  }
}

