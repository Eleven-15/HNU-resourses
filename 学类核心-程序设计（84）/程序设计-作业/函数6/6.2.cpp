#include<iostream>
using namespace std;


int gcd(int u,int v)
{
return u%v ? gcd(v,u%v) : v;
}

int lcm(int u,int v)
{
	return u*v/gcd(u,v);
}

int main()
{
   int x,y;
   cin>>x>>y;
   cout<<gcd(x,y)<<" "<<lcm(x,y)<<endl;
   return 0;
}

