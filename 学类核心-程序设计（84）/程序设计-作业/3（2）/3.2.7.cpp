#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long int n,m,sum;
	int x[20];
	cin>>n;
	m=n;
	int i=0;
	sum=0;
	while (n/10!=0)
	{
		i++;
		x[i]=n%10;
		n=n/10;
	}
	i++;
	x[i]=n;
    for (int j=1;j<=i;j++)
    {
    	sum+=x[j]*x[j]*x[j];
	}
    if (sum==m) cout<<"Yes";
    else cout<<"No";




  return 0;
}

