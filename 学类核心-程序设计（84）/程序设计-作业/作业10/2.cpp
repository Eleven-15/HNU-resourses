//����һ��Բ����
//�뾶 ��2.0
//��� ��12.5664
//
//����һ��Բ������
//�뾶 ��2.0
//�߶� ��3.0
//��� ��62.8319
//��� ��37.6991
//
//����һ��Բ׶����
//�뾶 ��2.0
//�߶� ��3.0
//��� ��35.2207
//��� ��12.5664
//
//����һ�������
//�뾶 ��2.0
//��� ��50.2655
//��� ��33.5103
//������˵����
//�����ֱ�׼��
#include<iostream>
#include<math.h>
using  namespace  std;

//  ������ѧ����pi
#define  pi  3.1415926

//  �����������Area
class  Area  {
public:
        virtual  double  GetArea()  =  0;
};

//  �����������Volume
class  Volume  {
public:
        virtual  double  GetVolume()  =  0;

};

//  ��������CircleԲ��
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

//  ����Բ����
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

//  ����Բ׶��
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

//  ��������

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
        cout  <<  "����һ��Բ����"  <<  endl;
        cout  <<  "�뾶  ��2.0"  <<  endl;
        cout  <<  "���  ��"  <<  circle.GetArea()  <<  endl  <<  endl;

        Cylinder  cylinder(2,  3);
        cout  <<  "����һ��Բ������"  <<  endl;
        cout  <<  "�뾶  ��2.0"  <<  endl;
        cout  <<  "�߶�  ��3.0"  <<  endl;
        cout  <<  "���  ��"  <<  cylinder.GetArea()  <<  endl;
        cout  <<  "���  ��"  <<  cylinder.GetVolume()  <<  endl  <<  endl;

        Cone  cone(2,  3);
        cout  <<  "����һ��Բ׶����"  <<  endl;
        cout  <<  "�뾶  ��2.0"  <<  endl;
        cout  <<  "�߶�  ��3.0"  <<  endl;
        cout  <<  "���  ��"  <<  cone.GetArea()  <<  endl;
        cout  <<  "���  ��"  <<  cone.GetVolume()  <<  endl  <<  endl;

        Sphere  sphere(2);
        cout  <<  "����һ�������"  <<  endl;
        cout  <<  "�뾶  ��2.0"  <<  endl;
        cout  <<  "���  ��"  <<  sphere.GetArea()  <<  endl;
        cout  <<  "���  ��"  <<  sphere.GetVolume()  <<  endl  <<  endl;
        return  0;
}
