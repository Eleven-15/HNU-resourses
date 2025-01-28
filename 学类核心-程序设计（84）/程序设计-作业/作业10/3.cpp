//第一行 实现两个Point类对象的加法
//第二行 实现Point类对象与整数2的加法
//【样例输入】
//
//1 2 3 4
//【样例输出】
//
//4 6
//6 8
//【样例说明】
//
//加号操作符重载函数，实现两个Point类对象的加法（1+3）=4，（2+4）=6；
//加号操作符重载函数，实现Point类对象与整数 2 相加，（4+2）=6，（6+2）=8；
#include<iostream>
using  namespace  std;
class  Point
{
        private:
        int  x,y;
        public:
        Point()
        {
                x=y=0;
        }
        Point(int  x0,int  y0)
        {
                x=x0;
                y=y0;
        }
        int  GetX(){return  x;}
        int  GetY(){return  y;}
        void  Print()
        {
                cout<<x<<"  "<<y<<""<<endl;
        }  
        
friend Point  operator+(Point&  pt,int  dd);
friend Point  operator+(Point&  pt1,Point&  pt2);
               
};
Point  operator+(Point&  pt,int  dd)//加号操作符重载函数，实现Point类对象与整数加法
{
        Point temp(pt.GetX()+dd,pt.GetY()+dd);
        return temp;  
  }  
Point  operator+(Point&  pt1,Point&  pt2)//加号操作符重载函数，实现两个Point类对象的加法
{
        Point temp(pt1.GetX()+pt2.GetX(),pt1.GetY()+pt2.GetY());
        return temp;             
  }  
int  main()
{
  int  qq1,qq2,qq3,qq4;
  cin>>qq1>>qq2>>qq3>>qq4;
  Point  a(qq1,qq2);
  Point  b(qq3,qq4);
  Point  c;
  c=a+b;
  c.Print();
  c=c+2;
  c.Print();
  }
