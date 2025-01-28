#include<iostream>
using namespace std;

int main()
{
	int n,m;
    cin>>n>>m;
    int sum[n+1];
    for (int i=1;i<=n;i++) sum[i]=0;
    for (int i=1;i<=m;i++)
    {
    	int candidate=0,maxi=0,temp;
    	for (int j=1;j<=n;j++)
    	{
    		cin>>temp;
    		if (maxi<temp)
    		{
    			maxi=temp;
    			candidate=j;
			}
		}
		sum[candidate]++;
	}
	int candidate=0,maxi=0;
	for (int i=1;i<=n;i++)
	{
		if (sum[i]>maxi)
		{
			maxi=sum[i];
			candidate=i;
		}
	}
	cout<<candidate<<endl;


    return 0;
}

