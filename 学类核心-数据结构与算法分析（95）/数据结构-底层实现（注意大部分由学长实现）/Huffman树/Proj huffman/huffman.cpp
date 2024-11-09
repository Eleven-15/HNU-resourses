#include <cstring>
#include "book.h"
#include "heap.h"
#include "codetable.h"
#include "huffnode.h"
#include "hufftree.h"

//测试函数声明 
void do_commands(HuffTree<char>* theTree,CodeTable<char>* theTable, FILE *fp); 
int read_freqs(CodeTable<char>* ct, FILE* fp);
void buildcode(HuffNode<char>* root, CodeTable<char>* ct,char* prefix, int level, double& total);
void decode(HuffTree<char>* theTree, char* code, char& msg, int& cnt);

//"<<"运算符重载
template <typename E>
ostream& operator << (ostream& s, HuffNode<E>* z)
{
  	if (z->isLeaf())
    	return s << ((LeafNode<E>*)z)->val();
  	else
    	return s << z->weight();
}

// Comparator for the heap 比较两个堆大小返回布尔值 
class minTreeComp {
public:
  	static bool prior(HuffTree<char>* x, HuffTree<char>* y)
	{ return x->weight() < y->weight(); }
};

// Space for the heap's array 建立存储堆的数组 
HuffTree<char>** TreeArray = NULL;

// Build a Huffman tree from a collection of frequencies
//用已收集的频数构建哈弗曼树 
template <typename E> HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
  	heap<HuffTree<E>*,minTreeComp>* forest =
    	new heap<HuffTree<E>*, minTreeComp>(TreeArray,count, count); 
  	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
  	while (forest->size() > 1) {
	    temp1 = forest->removefirst(); 	//Pull first two trees off the list  
	    temp2 = forest->removefirst();	//取出最前面的两棵树 
	    temp3 = new HuffTree<E>(temp1, temp2);//合并两棵树 
	    forest->insert(temp3);  // Put the new tree back on list 将新树加入列表
	    delete temp1;        // Must delete the remnants of the trees we created
	    delete temp2;        // 删除原来的两棵树  
  	}
  	return temp3;
}

//主函数测试部分 
int main() {
  // This will be the eventual Huffman tree 
  //存储最终建成的哈弗曼树 
  HuffTree<char>* theTree;
  CodeTable<char>* theTable = new CodeTable<char>(CODETABLELEN);
  // Working storage for the tree traversal that builds the code table 
  //存储树遍历的值来构建编码表 
  char prefix[MAXCODELEN+1];//prefix 前缀 
  // total is used to calculate the average code length
  double total = 0;
  FILE *fp;  // The file pointer文件指针 

  Assert((fp = fopen("huffbook.huff", "rt")) != NULL, "No such file");

  // Now, read in the list of frequencies, and initialize the forest of Huffman trees.
  //读取频数文件列表，初始化哈弗曼树森林(即多个单结点） 
  cout << "读取文件中每个元素及其对应的频数\n";
  int count = read_freqs(theTable, fp);

  // Now, build the tree.构建哈弗曼树 
  theTree = buildHuff<char>(TreeArray, count);
  cout << "已构建哈弗曼树\n";
  
  // Now, output the tree, which also creates the code table.
  //输出已构建好编码表的哈弗曼树 
  cout << "输出哈弗曼树编码表：\n";
  buildcode(theTree->root(), theTable, prefix, 0, total);
  cout << "平均编码长度为："
       << total/(double)theTree->weight() << "\n";

  // Finally, do the encode/decode commands to test the system.
  //最后，测试编码和解码命令 
  do_commands(theTree, theTable, fp);
  return 0;
}

//do_commands命令函数执行decode(解码）、encode(编码)进行功能测试 
void do_commands(HuffTree<char>* theTree,CodeTable<char>* theTable, FILE *fp)
{
  	int currchar;
  	char buff[80];

  	while(fgets(buff, 99, fp)) {
    if(strncmp(buff, "decode", 6) == 0) {
      	for (currchar=0; buff[currchar] != '"'; currchar++);
      	cout << "解码：" << &buff[currchar++];
      	while (buff[currchar] != '"') {
        	int cnt = 0;
        	char msg;
        	decode(theTree, &buff[currchar], msg, cnt);
        	cout << msg << endl;
			currchar += cnt;
      	}
    }
    else if(strncmp(buff, "encode", 6) == 0) {
      	for (currchar=0; buff[currchar] != '"'; currchar++);
      	cout << "编码：" << &buff[currchar++];
      	for(; buff[currchar] != '"' ; currchar++) 
        	if (buff[currchar] == ' ') cout << ' ';
        	else cout << theTable->getcode(buff[currchar]);
    }
  }
}
void decode(HuffTree<char>* theTree, char* code, char& msg, int& cnt) 
{
  	HuffNode<char>* currnode = theTree->root();
  	while (!currnode->isLeaf()) {
    	cnt++;
    	if (code[cnt-1] == '0') currnode = ((IntlNode<char>*)currnode)->left();
    	else if (code[cnt-1] == '1') currnode = ((IntlNode<char>*)currnode)->right();
    	else Assert(false, "Bad code character");
  	}
  	msg = ((LeafNode<char>*)currnode)->val();
}

// Read the list of frequencies, make the forest, and set the list of 
//entries into the code table. 读取频数文件内容，初始化单个数据节点 
int read_freqs(CodeTable<char>* ct, FILE* fp)
{ 	
	// Read a list of strings and frequencies from standard input,
  	// building a list of Huffman coding tree nodes
  	//从标准输入读取一组字符和频数，并创建哈弗曼编码节点列表 
	char buff[100];
	char buff2[100];
	char *ptr;
	char *ptr2;
	int freq;

  	Assert(fgets(buff, 99, fp) != NULL, "Couldn't read character count");//读取元素总个数 
  	ptr = buff;
	Assert(isdigit(*ptr) != 0, "Must be a digit here.");
	int count = atoi(ptr);
	TreeArray = new HuffTree<char>*[count];
	for (int i=0; i<count; i++) { 
	  	//文件中元素个数不够则断言终止 
	    Assert(fgets(buff, 99, fp) != NULL, "Ran out of codes too early");  
	    // process the entry, creating a new HuffTree
	    //处理每个入口，对读取到的字符创建一棵哈弗曼树 
	    for(ptr=buff; *ptr==' '; ptr++);  
	    Assert(*ptr == '"', "First char was not a quote mark.");
	    for (ptr2=buff2,ptr++; *ptr!='"'; ptr++)
	      	*ptr2++ = *ptr;
	    *ptr2 = '\0'; // End of string 字符串结束标志 
	    for (ptr++; *ptr==' '; ptr++);
	    Assert(isdigit(*ptr) != 0, "Must be a digit here.");
	    freq = atoi(ptr);
	    ct->addobject(buff2[0]);
	    TreeArray[i] = new HuffTree<char>(buff2[0], freq);
  	}
  	return count;
}
//建立哈弗曼编码 
void buildcode(HuffNode<char>* root, CodeTable<char>* ct,char* prefix, int level, double& total)
{
  	if (root->isLeaf()) {
    	cout << ((LeafNode<char>*)root)->val() << "\t" << prefix << "\n";
    	strcpy(ct->getcode(((LeafNode<char>*)root)->val()), prefix);
    	total += level * root->weight();
  	}
  	else{
    prefix[level] = '0';
    prefix[level+1] = '\0';
    buildcode(((IntlNode<char>*)root)->left(), ct, prefix, level+1, total);
    prefix[level] = '1';
    prefix[level+1] = '\0';
    buildcode(((IntlNode<char>*)root)->right(), ct, prefix, level+1, total);
    prefix[level] = '\0';
  	}
}

