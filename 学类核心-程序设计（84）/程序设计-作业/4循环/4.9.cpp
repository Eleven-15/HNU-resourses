#include<stdio.h>
using namespace std;
int main()
{
	int T,n,k;
	scanf("%d",&T);
	int x[T+1];
	for (int i=1;i<=T;i++)
	{
		x[i]=0;
	}
	for (int i=1;i<=T;i++)
	{
		scanf("%d %d",&n,&k);
		int t[n+1];
		int d[n+1];
		for (int j=1;j<=n;j++)
		{
			t[j]=0,d[j]=0;
		}
		int sum=0;
		for (int j=1;j<=n;j++)
		{
			scanf("%d %d",&t[j],&d[j]);
			if (j>1) t[j]+=t[j-1];
		}
		
	//		for (int j=1;j<=n;j++)
	//	{
	//		printf("%d %d \n",t[j],d[j]);
	//	}
		
		int flag=0;
		for (int j=1;j<=n;j++)
		{
			if (flag==1) sum+=((t[j]-t[j-1])*d[j]);
			if (k<t[j] && flag==0) 
			{
				sum=(t[j]-k)*d[j];
				flag=1;
			}
		//	printf("%d ",sum); 
		}
		x[i]=sum;
	}
	for (int i=1;i<=T;i++)
	{
		printf("%d \n",x[i]);
	}






  return 0;
}

