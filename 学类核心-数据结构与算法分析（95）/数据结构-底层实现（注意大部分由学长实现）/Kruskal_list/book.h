
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//comp的模板函数
template <typename T>
inline bool Cmp(T t1,T t2){
	if(t1==t2)
		return true;
	return false;
} 
//模板特殊化
template<>
bool Cmp<string>(string s1,string s2){
	if(strcmp(s1.c_str(),s2.c_str())==0)
		return true;
	return false;
} 

// Assert: If "val" is false, print a message and terminate
// the program
void Assert(bool val, string s) {
  if (!val) { // Assertion failed -- close the program
    cout << "Assertion Failed: " << s << endl;
    exit(-1);
  }
}

template<typename E>
inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

