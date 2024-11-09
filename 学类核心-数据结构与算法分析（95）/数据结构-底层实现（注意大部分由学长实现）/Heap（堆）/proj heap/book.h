#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

void Assert(bool val, string s) {
  if (!val) { 
    cout << "Assertion Failed: " << s << endl;
    exit(-1);
  }
}

// Swap two elements in a generic array
//交换数组中的两个元素 
template<typename E>
inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

// Your basic int type as an object.
//定义Int类 
class Int {
private:
  int val;
public:
  Int(int input=0) { val = input; }
  int key() const { return val; }
  // Overload = to support Int foo = 5 syntax 运算符重载 
  Int operator= (int input) { val = input; return val; }
};

// Let us print out Ints easily 运算符重载 
ostream& operator<<(ostream& s, const Int& i)
  { return s << i.key(); }
ostream& operator<<(ostream& s, const Int* i)
  { return s << i->key(); }

