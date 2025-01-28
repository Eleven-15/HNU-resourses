#include<iostream>
using namespace std;

int gcd(int x,int y);
int lcm(int x,int y);


int gcd(int x, int y)
{	
	int temp=y;
	while(x%y!=0)
	{
		temp=x%y;
		x=y;
		y=temp;	
	}
	return temp;
}

int lcm(int x,int y)
{
	return (x*y/gcd(x,y));
}
int main()
{
    int x,y;
    cin>>x>>y;
    cout<<gcd(x,y)<<" "<<lcm(x,y);
  return 0;
}

