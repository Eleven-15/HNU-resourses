#include <iostream>
using namespace std;
int main( ){
    int *p1,*p2,*p,a,b;
    cin>>a>>b;            //输入两个整数
    p1=&a;                //使p1指向a
    p2=&b;                //使p2指向b
    if(a<b)               //如果a<b就使p1与p2的值交换
    {p=p1;p1=p2;p2=p;}    //将p1的指向与p2的指向交换
    cout<<"a="<<a<<" b="<<b<<endl;
    cout<<"max="<<*p1<<" min="<<*p2<<endl;//p1在前p2在后
    return 0;
}

