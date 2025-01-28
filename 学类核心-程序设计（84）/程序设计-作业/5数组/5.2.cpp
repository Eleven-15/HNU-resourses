#include<stdio.h>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    int x[n+1];
    
    for (int i=1;i<=n;i++)
    {
    	scanf("%d",&x[i]);
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=n;j>i;j--)
		{
			if (x[j-1]>x[j]) 
			{
				int temp=x[j-1];
				x[j-1]=x[j];
				x[j]=temp;
			}
			
		}
	}
    for (int i=1;i<=n;i++)
    {
    	printf("%d ",x[i]); 
	}




  return 0;
}

