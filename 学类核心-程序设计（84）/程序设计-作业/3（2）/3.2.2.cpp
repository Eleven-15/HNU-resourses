#include<bits/stdc++.h>
using namespace std;
int m;
int transform(int x[9],int n);
int transform(int x[9],int n)
{
	int i=0;
    do
	{
		i++;
		x[i]=n%2;
		n=n/2;
	}
	while(n!=0);
	return i;
}

int main()
{
	int x[9];
    int n;
    cin>>n;
    m=transform(x,n);
    for (int i=m;i>=1;i--)
    {
    	cout<<x[i];
	}





  return 0;
}

