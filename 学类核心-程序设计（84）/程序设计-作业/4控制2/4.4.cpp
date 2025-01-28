#include<stdio.h>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    int x[n];
    for (int i=1;i<=n;i++)
    {
    	scanf("%d",&x[i]);
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=n;j>i;j--)
		{
			if (x[j-1]<x[j])
			{
				int temp=x[j-1];
				x[j-1]=x[j];
				x[j]=temp;
			}
		}
	}
	if (n%2==0 && x[n/2]==x[n/2+1])
	{
		int sum=0;
		for (int i=1;i<=n;i++)
		{
			if (x[i]==x[n/2]) sum++;
		}
		if (sum%2==0) printf("%d",x[n/2]);
		else printf("-1");
	}
	else if (n%2==1)
	{
		int sum=0;
		for (int i=1;i<=n;i++)
		{
			if (x[i]==x[(n+1)/2]) sum++;
		}
		if (sum%2==1) printf("%d",x[(n+1)/2]);
		else printf("-1");
	}
    else printf("-1");




  return 0;
}

