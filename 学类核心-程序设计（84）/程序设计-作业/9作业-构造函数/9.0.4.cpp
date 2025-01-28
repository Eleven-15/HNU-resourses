#include  <iostream>
#include  <iomanip>
#include  <cmath>    //声明sqrt函数
using  namespace  std;
class  Point  //完成Point类的声明，包含数据成员和成员函数
{
private:
        int  x;
        int  y;
public  :
        Point();//  成员函数原型声明
        void  setPoint(int  x1,int  y1);
        int  getX();
        int  getY();
        double  myDistance(  int  x1,int  y1);
};
Point::Point(){};
void  Point::setPoint(int  x1,int  y1)  //从键盘输入Point的坐标
{
    x=x1; y=y1;
}
int  Point::getX(){
        return x;
}
int  Point::getY(){    
        return y;
}
double  Point::myDistance(  int  x1,int  y1)          //计算两个点的距离，并输出
{
      return sqrt(x1*x1+y1*y1);
}
int  main()
{
        Point  A,B;    //定义两个Point对象，A和B;
        double  distance;
        int x,y;//从键盘输入A和B的坐标
        cin>>x>>y;
        A.setPoint(x,y);
        cin>>x>>y;
        B.setPoint(x,y);
        distance  =  A.myDistance(A.getX()-B.getX(),A.getY()-B.getY());
        cout<<fixed<<setprecision(3)<<distance;  //输出结果
        return  0;
}
