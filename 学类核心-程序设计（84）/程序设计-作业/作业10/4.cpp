#include<iostream>
#include<algorithm>
#include<string>
#include<cmath>
using  namespace  std;
class  Triangle
{
public:
        Triangle(double  s1  =  0,  double  s2  =  0,  double  s3  =  0,  double  area=0)
        {
                m_s1  =  s1;
                m_s2  =  s2;
                m_s3  =  s3;
                m_area  =  area;
        }
        double  getS1()
        {
                return  m_s1;
        }
        double  getS2()
        {
                return  m_s2;
        }
        double  getS3()
        {
                return  m_s3;
        }
        double  getArea()
        {
                return  m_area;
        }
        Triangle  operator+(Triangle  triangle);
private:
        double  m_s1;
        double  m_s2;
        double  m_s3;
        double  m_area;
};
Triangle  Triangle::operator+(Triangle  triangle)
{  double p, p1;
    p = (getS1()+getS2()+getS3())/2.0;
    p1 = (triangle.getS1()+triangle.getS2()+triangle.getS3())/2.0;
    m_area = sqrt(p*(p-getS1())*(p-getS2())*(p-getS3()));
    double area2 = sqrt(p1*(p1-triangle.getS1())*(p1-triangle.getS2())*(p1-triangle.getS3()));
Triangle t(0,0,0,m_area+area2);
    return t;

}
int  main()
{
        int  t11,t12,t13,t21,t22,t23;
        cin>>t11>>t12>>t13;
        cin>>t21>>t22>>t23;  
        Triangle  c1(t11,t12,t13),  c2(t21,t22,t23),c3;
        c3  =  c1  +  c2;
        cout<<c3.getArea()<<  endl;
        system("pause");
        return  0;
}
