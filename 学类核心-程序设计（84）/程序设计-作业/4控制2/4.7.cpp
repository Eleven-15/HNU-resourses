#include<stdio.h>
using namespace std;
int main()
{
   int n,sum=0;
   scanf("%d",&n);
   int x[n+1];
   for (int i=1;i<=n;i++) scanf("%d",&x[i]);
   for (int i=1;i<=n;i++)
   {
   	for (int j=1;j<=n;j++)
   	{
   		if (x[i]==2*x[j]) sum++;
	   }
   }
   printf("%d",sum);



  return 0;
}

