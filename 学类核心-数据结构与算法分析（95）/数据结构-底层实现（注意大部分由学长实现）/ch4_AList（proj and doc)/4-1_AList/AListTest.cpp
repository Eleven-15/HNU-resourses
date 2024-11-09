#include "list.h"
#include "alist.h"
#include<iomanip>
#include<iostream>

using namespace std;
void print(AList<int>& A,int n);

// Main routine for array-based list driver class
int main(){
	int n;
	AList<int> L1(100);
  	cout<<"**************************"<<endl; 
  	cout<<"*顺序表中各个基本操作演示*"<<endl;// Declare some sample lists
	cout<<"**************************"<<endl<<endl;
  	cout<<"向顺序表中依次添加元素12、15、9、48、55"<<endl;
  	//调用顺序表中的append操作 
  	L1.append(12);
  	L1.append(15);
  	L1.append(9);
  	L1.append(48);
  	L1.append(55);
  	cout<<"添加元素后顺序表中内容为："<<endl; 
  	n=L1.length();//获取顺序表长度 
  	print(L1,n);
  	cout<<"当前顺序表长度为:"<<endl<<L1.length()<<endl<<endl; 
  	
  	cout<<"查看当前curr的值为："<<endl;
  	cout<<L1.currPos()<<endl<<endl;
  	
  	cout<<"设置线性表中栅栏curr的位置为2"<<endl;
	L1.moveToPos(2);
	cout<<"并在当前位置curr插入元素4"<<endl;
	//调用顺序表中的插入操作 
	L1.insert(4);
	cout<<"插入元素后顺序表中内容为："<<endl;
	n=L1.length();//获取顺序表长度  
	print(L1,n);
	
  	cout<<"设置线性表中栅栏curr的位置为4"<<endl;
  	L1.moveToPos(4);
  	cout<<"并删除当前位置curr处的元素" <<endl;
  	//调用顺序表的删除操作 
  	L1.remove(); 
  	cout<<"删除元素后顺序表中的内容为："<<endl;
  	n=L1.length();//获取顺序表长度
	print(L1,n);
}
/***********************
*function of print
*打印顺序表中元素
************************/ 
void print(AList<int>& A,int n){
	//cout<<"当前顺序表中元素为："<<endl;
	int i;
	for(i=0;i<n;i++){
		A.moveToPos(i);
		//调用getValue操作得到当前元素 
		cout<<A.getValue()<<" ";
	}
	cout<<endl<<endl; 
}

