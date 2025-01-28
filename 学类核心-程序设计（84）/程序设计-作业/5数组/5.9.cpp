#include<stdio.h>
using namespace std;
int main()
{
    int n,t;
    scanf("%d",&n);
    int x[n];
    for (int i=0;i<=n-1;i++)
    {
    	scanf("%d",&x[i]);
	}
    scanf("%d",&t);
    for (int i=0;i<=n-1;i++)
    {
    	for (int j=0;j<=n-1;j++)
    	{
    		if (i!=j)
    		{
    			if (x[i]+x[j]==t)
    			{
    				printf("%d %d",i,j);
    				return 0;
				}
			}
		}
	}





  return 0;
}

