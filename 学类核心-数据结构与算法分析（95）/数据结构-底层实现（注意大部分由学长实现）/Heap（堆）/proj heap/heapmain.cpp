#include "book.h"
#include "compare.h"
#include "Aheap.h"
using namespace std; 
int main() {
	int i, j;
	int n=10,count=0;
	Int A[10] = {9,3,0,2,4,7,5,6,8,1};
	Int C[10] = {73, 6, 57, 88, 60, 34, 83, 72, 48, 85};
	cout<<"初始数据："<<endl;
	for (i=0; i<10; i++)
		cout << C[i] << "  ";
	cout<<endl<<"建堆ing..."<<endl;
  	Aheap<Int, maxIntCompare> BH(C, 0, 20);
  	cout<<"建堆完成" <<endl<<endl;
	cout<<"按照层次遍历的顺序依次输出堆元素："<<endl;
  	for (i=0; i<10; i++)
    	cout << C[i] << "  ";
  	cout << endl;
  	
 	cout<<endl<<"-------演示依次插入数据建堆过程-------"<<endl; 
  	cout<<"初始堆为空"<<endl;
  	Aheap<Int, maxIntCompare> H(A, 0, 10);
  	for (i=0; i<n; i++){
		cout<<"插入元素"<<A[i];
		H.insert(A[i]);
		count++;
		cout<<",输出目前已建好的堆元素："<<endl;
		for(j=0;j<count;j++){
			cout << A[j] << "  ";
		}
		cout<<endl;		 
	}
	
	cout<<endl<<"删除数组中下标为3的元素:"<<H.remove(3)<<endl;
	cout<<"输出删除后堆中元素："<<endl;
	for (i=0; i<9; i++)
		cout << A[i] << "  ";
	cout<<endl;
	
	cout<<endl<<"删除堆中最大值："<<H.removefirst()<<endl;
	cout<<"输出删除后堆中元素："<<endl;
	for (i=0; i<8; i++)
		cout << A[i] << "  ";
	cout<<endl;
	
  	return 0;
}
