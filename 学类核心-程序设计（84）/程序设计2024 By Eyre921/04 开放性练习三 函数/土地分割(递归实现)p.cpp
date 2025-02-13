#include <iostream>
using namespace std;
int han(int m,int n,int k);

int han(int m,int n,int k)
{	
	
	if(m%k==0&&n%k==0)
	{
	return k;
	}
	else
	{
		k--;return han(m,n,k);
	}
}
int main()
{
	int m,n,s;
	s=1;
	cin>>m>>n;
	if(m<n)
	{
		int q=m;
		m=n;
		n=q;
	}int k=n;
	int f=han(m,n,k);
	int z=m/f;
	int x=n/f;
	cout<<z*x<<" "<<f;
}


