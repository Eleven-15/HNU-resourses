#include<iostream>
#include<iomanip>
using namespace std;
long double func(int n,long double x);
long double func(int n,long double x)
{
	long double ans=1;
	for (int i=1;i<=(2*n-1);i++)
	{
		ans=ans*x/i;
	}
    return ans;
	
}
int main()
{
	long double x,temp,ans=0;
	cin>>x;
	//cout<<x<<" ";
	const long double pi=3.1415926535;
	for (;;)
	{
		if (x-2*pi>0) x-=2*pi;
		else if (x+2*pi<0) x+=2*pi;
		else break;
	} 
	//cout<<x<<" ";
	for (int i=1;;i++)
	{
		temp=func(i,x);
		//cout<<temp<<" "<<endl;
		if (i%2==0)  ans=ans-temp;
		else ans+=temp;
		if (temp>=-5E-8 && temp<=5E-8) break;
	}
	cout<<fixed<<setprecision(6)<<ans;
	
  return 0;
}

