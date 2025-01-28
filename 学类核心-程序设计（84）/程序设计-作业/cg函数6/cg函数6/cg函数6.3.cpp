#include<iostream>
using namespace std;
int main()
{
	int N;
	cin>>N;
	while(N--)
	{
		int a,b,c,d;
		cin>>a>>b;
		d=a*b;
		while(a!=b)
		{
			if(a>b)
				a-=b;
			else
				b-=a;
		}
		c=a;
		d=d/c;
		cout<<c<<" "<<d<<endl;
 
	}
 
}
