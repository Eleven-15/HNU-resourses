#define MAXCODELEN 20       // Max length of a huffman code 哈弗曼编码最大长度 
#define CODETABLELEN 100    // Maximum number of codes storable 编码表最大长度 
// CodeTable maps objects to their associated codes.编码表：将元素和编码一一对应 
template <typename E>
class CodeTable {
private:
  	E* obs;     
  	char** codes;  // Associated code values 相应编码值 
  	int currsize;  // Current number of objects in table 编码表当前元素个数 
  	int maxsize;   // Max objects permitted in table 表中最大容量 
public:
  	CodeTable(int size) {
    obs = new E[size];
    codes = new char*[size];
    for (int i = 0; i<size; i++) {
      	codes[i] = new char[MAXCODELEN+1];
      	for(int j=0; j<=MAXCODELEN; j++)
        	codes[i][j] = '-';
		codes[i][MAXCODELEN] = '\0';
    }
    maxsize = size;  currsize = 0;
  }

  void addobject(E& obj) {
    Assert(currsize < maxsize, "CodeTable is full!");
    obs[currsize++] = obj;
  }

  char* getcode(E obj) {
    for (int i=0; i<currsize; i++)
      if(obj == obs[i]) return codes[i];
    return NULL;
  }
};  
