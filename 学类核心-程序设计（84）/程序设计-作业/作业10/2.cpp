//创建一个圆对象
//半径 ：2.0
//面积 ：12.5664
//
//创建一个圆柱对象
//半径 ：2.0
//高度 ：3.0
//面积 ：62.8319
//体积 ：37.6991
//
//创建一个圆锥对象
//半径 ：2.0
//高度 ：3.0
//面积 ：35.2207
//体积 ：12.5664
//
//创建一个球对象
//半径 ：2.0
//面积 ：50.2655
//体积 ：33.5103
//【样例说明】
//【评分标准】
#include<iostream>
#include<math.h>
using  namespace  std;

//  定义数学常数pi
#define  pi  3.1415926

//  创建抽象基类Area
class  Area  {
public:
        virtual  double  GetArea()  =  0;
};

//  创建抽象基类Volume
class  Volume  {
public:
        virtual  double  GetVolume()  =  0;

};

//  创建基类Circle圆类
class  Circle:public  Area  {
private:
	double r;
public:
	Circle(){};
	Circle(double x)
	{
		r=x;
	}
	double  GetArea()
	{
		return  r*r*pi;
	}
};

//  创建圆柱类
class  Cylinder  :public  Circle,  public  Volume  {
private: double r,h;
public:
//	Cylinder(){};
	Cylinder(double a,double b)
	{
		r=a;
		h=b;
	}
	double  GetArea()
	{
		return (r*r*pi*2+2*pi*r*h);
	}
	double  GetVolume()
	{
		return (r*r*pi*h);
	}
};

//  创建圆锥类
class  Cone  :public  Circle,  public  Volume  {
private: double r,h;
public:
//Cone(){};
Cone(double a,double b)
	{
		r=a;
		h=b;
	}
	double  GetArea()
	{
		return (r*r*pi+pi*r*sqrt(h*h+r*r));
	}
	double  GetVolume()
	{
		return (r*r*pi*h/3.0);
	}
};

//  创建球类

class  Sphere  :public  Circle,  public  Volume  {
private: double r;
public:
//Sphere(){};
Sphere(double a)
	{
		r=a;
	}
	double  GetArea()
	{
		return (4*pi*r*r);
	}
	double  GetVolume()
	{
		return (pi*r*r*r*4.0/3.0);
	}
};

int  main()  {
        Circle  circle(2);
        cout  <<  "创建一个圆对象"  <<  endl;
        cout  <<  "半径  ：2.0"  <<  endl;
        cout  <<  "面积  ："  <<  circle.GetArea()  <<  endl  <<  endl;

        Cylinder  cylinder(2,  3);
        cout  <<  "创建一个圆柱对象"  <<  endl;
        cout  <<  "半径  ：2.0"  <<  endl;
        cout  <<  "高度  ：3.0"  <<  endl;
        cout  <<  "面积  ："  <<  cylinder.GetArea()  <<  endl;
        cout  <<  "体积  ："  <<  cylinder.GetVolume()  <<  endl  <<  endl;

        Cone  cone(2,  3);
        cout  <<  "创建一个圆锥对象"  <<  endl;
        cout  <<  "半径  ：2.0"  <<  endl;
        cout  <<  "高度  ：3.0"  <<  endl;
        cout  <<  "面积  ："  <<  cone.GetArea()  <<  endl;
        cout  <<  "体积  ："  <<  cone.GetVolume()  <<  endl  <<  endl;

        Sphere  sphere(2);
        cout  <<  "创建一个球对象"  <<  endl;
        cout  <<  "半径  ：2.0"  <<  endl;
        cout  <<  "面积  ："  <<  sphere.GetArea()  <<  endl;
        cout  <<  "体积  ："  <<  sphere.GetVolume()  <<  endl  <<  endl;
        return  0;
}
