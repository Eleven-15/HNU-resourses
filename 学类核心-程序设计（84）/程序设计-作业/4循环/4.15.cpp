#include<stdio.h>
#include<algorithm>
using namespace std;
int main()
{
    int n,m,a,d,maxm,minm,sum=0,temp=0;
    int flag=0;
    scanf("%d %d %d %d",&n,&m,&a,&d);
    int t[m+1];
    for (int i=1;i<=m;i++)
    {
    	scanf("%d",&t[i]);
	}
    maxm=max(n*a,t[m]);
    minm=min(a,t[1]);
    int x[maxm-minm+1];
    for (int i=minm;i<=maxm;i++)
    {
    	x[i]=0;
	}
    for (int i=1;i<=m;i++)
    {
    	x[t[i]]=1;
	}
	for (int i=1;i<=n;i++)
	{
		x[i*a]=1;
	}
    for (int i=minm;i<=maxm;i++)
    {
    	if (flag==0 && x[i]==1) 
    	{
    		sum++;
    		flag=1;
    		temp=i+d;
		}
		else if (flag==1 && i==temp) flag=0;
	}
	printf("%d",sum);


  return 0;
}

