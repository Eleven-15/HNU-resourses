#include<stdio.h>
using namespace std;
int main()
{
    int l,m,a,b,ans=0;
    scanf("%d %d",&l,&m);
    int x[l+1];
    for (int i=0;i<=l;i++)
    {
    	x[i]=1;
	}
    for (int i=1;i<=m;i++)
    {
    	scanf("%d %d",&a,&b);
    	for (int j=a;j<=b;j++)
    	{
    		x[j]=0;
		}
	}
	for (int i=0;i<=l;i++)
	{
		if (x[i]==1) ans++;
	}
	printf("%d",ans);





  return 0;
}

