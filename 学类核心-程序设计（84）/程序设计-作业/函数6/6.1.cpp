#include<iostream>
using namespace std;
int getCandy(int,int);

int main()
{
	int k,r;
	cin>>k>>r;
	int result=getCandy(k,r);
	cout<<result<<endl;
	return 0;
}

int getCandy(int k,int r)
{
	for (int i=0;;i++)
	{
		if ((i*10+r)%k==0) 
		{
			return ((i*10+r)/k);
		}
		if ( ((i*10)%k==0) && (((i*10)/k)!=0) )
		{
			return ((i*10)/k);
		}
	}
}
