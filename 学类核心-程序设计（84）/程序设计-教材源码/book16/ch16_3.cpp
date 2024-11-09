//---------------------
// ch16_3.cpp  圆类组合策略
//---------------------
#include<iostream>
using namespace std;
//---------------------
template<class T>
class Point{
protected:
  double x, y;
public:
  Point(T a=0,T b=0):x(a),y(b){}
  double xOffset()const{ return x; }
  double yOffset()const{ return y; }
  void moveTo(double a, double b){ x = a, y = b; }
  void print(){ cout<<"("<<x<<","<<y<<")\n"; }
};//-------------------
template<class T>
class Circle{   //圆-组合类
  Point point;
  double radius;
public:
  Circle(T Point& p,T r):point(p),radius(r){}
  T getRadius()const{ return radius; }
  Point getPoint()const{ return point; }
  T getArea()const{ return radius * radius * 3.14; }
  T getCircum()const{ return 2 * radius * 3.14; }
  void moveTo(T a,T b){ point.moveTo(a, b); }
  void modifyRadius(T r){ radius = r; }
};//-------------------
int main(){
  Point <double>a(2.3, 5.6);
  Circle c(a, 7);
  c.moveTo(1, 2);
  c.modifyRadius(3);
  Point q = c.getPoint();
  cout<<"radius: "<<c.getRadius()<<"\n";
  cout<<"point: ";
  q.print();
  cout<<"area: "<<c.getArea()<<"\n";
  cout<<"circum: "<<c.getCircum()<<"\n";
}//---------------------

 
