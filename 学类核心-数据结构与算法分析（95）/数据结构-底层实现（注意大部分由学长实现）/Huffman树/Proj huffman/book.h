//book.h文件中定义了常用的swap、Assert函数 
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using namespace std;
const int defaultSize = 10; 

//若val为0即断言错误，则输出字符串s并异常终止程序 
void Assert(bool val, string s) {
  if (!val) { // Assertion failed -- close the program
    cout << "Assertion Failed: " << s << endl;
    exit(-1);
  }
}
// Swap two elements in a generic array 交换数组中两个元素 
template<typename E>
inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}



