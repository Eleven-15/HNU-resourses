#include "RMB.h"
#include<iostream>
using namespace std;

void RMB::get()
{
	cin>>x>>y>>z;
}

RMB RMB::operator+(RMB &c)
{
	RMB temp;
	int a=(this->x*100+this->y*10+this->z);
	int b=(c.x*100+c.y*10+c.z);
	int t=a+b;
	temp.z=t%10;
	t/=10;
	temp.y=t%10;
	t/=10;
	temp.x=t;

    return temp;
}

RMB RMB::operator-(RMB &c)
{
	RMB temp;
	int a=(this->x*100+this->y*10+this->z);
	int b=(c.x*100+c.y*10+c.z);
	int t=abs(a-b);
	temp.z=t%10;
	t/=10;
	temp.y=t%10;
	t/=10;
	temp.x=t;
	return temp; 
}

int RMB::abs(int a)
{
	return (a>0) ? a : -a;
}
void RMB::show()
{
	cout<<x<<" "<<y<<" "<<z<<endl;
}
