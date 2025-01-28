#include  <iostream>
#include  <iomanip>
#include  <cmath>    //����sqrt����
using  namespace  std;
class  Point  //���Point����������������ݳ�Ա�ͳ�Ա����
{
private:
        int  x;
        int  y;
public  :
        Point();//  ��Ա����ԭ������
        void  setPoint(int  x1,int  y1);
        int  getX();
        int  getY();
        double  myDistance(  int  x1,int  y1);
};
Point::Point(){};
void  Point::setPoint(int  x1,int  y1)  //�Ӽ�������Point������
{
    x=x1; y=y1;
}
int  Point::getX(){
        return x;
}
int  Point::getY(){    
        return y;
}
double  Point::myDistance(  int  x1,int  y1)          //����������ľ��룬�����
{
      return sqrt(x1*x1+y1*y1);
}
int  main()
{
        Point  A,B;    //��������Point����A��B;
        double  distance;
        int x,y;//�Ӽ�������A��B������
        cin>>x>>y;
        A.setPoint(x,y);
        cin>>x>>y;
        B.setPoint(x,y);
        distance  =  A.myDistance(A.getX()-B.getX(),A.getY()-B.getY());
        cout<<fixed<<setprecision(3)<<distance;  //������
        return  0;
}
