#include<stdio.h>
using namespace std;
int main()
{
   int n=0,sum=0;
   scanf("%d",&n);
   for (int i=0;i<=(n/5);i++)
   {
   	for (int j=0;j<=(n/3);j++)
   	{
   		for (int k=0;k<=n;k++)
   		{
   			if (5*i+3*j+k==n) sum++;
		   }
	   }
   }
   printf("%d",sum);




  return 0;
}

