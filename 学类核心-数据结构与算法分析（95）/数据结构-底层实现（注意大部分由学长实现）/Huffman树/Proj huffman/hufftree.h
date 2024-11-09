template <typename E>
class HuffTree {
private:
  HuffNode<E>* Root; // Tree root 树根节点 
public:
  	HuffTree(E& val, int freq) // Leaf constructor叶节点构造函数 
    { Root = new LeafNode<E>(val, freq); }
  	// Internal node constructor内部节点构造函数 
  	HuffTree(HuffTree<E>* l, HuffTree<E>* r)
    { Root = new IntlNode<E>(l->root(), r->root()); }
  	~HuffTree() {}                          // Destructor析构函数 
  	HuffNode<E>* root() { return Root; }    // Get root 获得根节点 
  	int weight() { return Root->weight(); } // Root weight 获得根权值 
};
