//【样例输入】
//
//19 0.684 90 125.012
//【样例输出】
//
//c1:complex: 19+0.684i
//c2:complex: 90+125.012i
//c3:complex: 109+125.696i
#include  <iostream>
using  namespace  std;
class  Complex
{
private:
        double  real,image;
public:
        Complex(){}
        Complex(double  a,double  b)
        {
                real  =  a;
                image  =  b;
        }
        void  setRI(double  a,  double  b)
        {
                real  =  a;
                image  =  b;
        }
        double  getReal()
        {
                return  real;
        }
        double  getImage()
        {
                return  image;
        }
        void  print()
        {
        	    (image>0) ? cout<<real<<"+"<<image<<"i"<<endl : cout<<real<<"-"<<-1*image<<"i"<<endl ;

        }
        friend  Complex  add(Complex,Complex);  //声明友元函数
};
  Complex add(Complex a,Complex b)//定义友元函数
{
    Complex c3;
    c3.real=a.real+b.real;
	c3.image=a.image+b.image;   //访问Complex类中的私有成员
        return  c3;
}
int  main()
{
        double  a,b,c,d;
        cin>>a>>b>>c>>d;
        Complex  c1(a,  b),  c2,  c3;
        c2.setRI(c,d);
        c3=add(c1,c2);
        cout<<"c1:complex: ";c1.print();
        cout<<"c2:complex: ";c2.print();
        cout<<"c3:complex: ";c3.print();
        return  0;
}

