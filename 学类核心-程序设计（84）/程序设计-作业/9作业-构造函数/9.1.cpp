#include<iostream>
#include<cmath>
using namespace std;

class rectangle
{
    public:
	double a,b;
      rectangle(){
      	cin>>a;
      	cin>>b;
	  }
	  double c(double a,double b)
	  {
	  	return (2*a+2*b);
	  }
	  double s(double a,double b)
	  {
	  	return (a*b);
	  }
	  double d(double a,double b)
	  {
	  	return (sqrt(a*a+b*b));
	  }
	  bool square(double a,double b)
	  {
	  	return (a==b) ? 1 : 0;
	  }
	  void print()
	  {
	  	cout<<"length = "<<a<<",width = "<<b<<endl;
	  	cout<<"C = "<<c(a,b)<<endl;
	  	cout<<"S = "<<s(a,b)<<endl;
        cout<<"The diagonal length = "<<d(a,b)<<endl;
        cout<<"Is square ? ";
        (square(a,b)==1) ? cout<<"Yes" : cout<<"No";
	  }
	private:
		
};
int main()
{
	rectangle m;
	m.print();
    return 0;
}

