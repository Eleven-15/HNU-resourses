#include<stdio.h>
using namespace std;
int main()
{
    int n,sum=0;
    scanf("%d",&n);
    int x[n+1],m[n+1];
    for (int i=1;i<=n;i++)
    {
    	m[i]=0;
	}
    for (int i=1;i<=n;i++)
    {
    	scanf("%d",&x[i]);
	}
    for (int i=1;i<=n;i++)
    {
    	for (int j=i+1;j<=n;j++)
    	{
    		for (int k=j+1;k<=n;k++)
    		{
    			if (x[i]==x[j]+x[k])
    			{
    				m[i]=1;
				}
				else if (x[j]==x[k]+x[i])
    			{
    				m[j]=1;
				}
				else if (x[k]==x[i]+x[j])
				{
					m[k]=1;
				}
							}
		}
	}
	for (int i=1;i<=n;i++)
    {
    	if (m[i]==1) sum++;
	}
    printf("%d",sum);



  return 0;
}

