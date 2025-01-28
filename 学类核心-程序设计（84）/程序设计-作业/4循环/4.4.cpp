#include<bits/stdc++.h>
using namespace std;

int fun1(int n);
int fun1(int n)
{
	int t,sum=1;
	do
	{
		t=n%10;
		n=n/10;
		if (t!=0) sum*=t;
	}while(n!=0);
	return sum;
 } 

int main()
{
	int n;
    cin>>n;
    if ((n/10)==0) cout<<n;else
    {
    do
    {
    	cout<<n<<" ";
    	n=fun1(n);
	}while((n/10)!=0);
    cout<<n;	
}



  return 0;
}

