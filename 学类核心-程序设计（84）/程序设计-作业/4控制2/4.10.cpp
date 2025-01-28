#include<stdio.h>
using namespace std;
int main()
{
   int n;
   scanf("%d",&n);
   for (int i=1;i<=n;i++)
   {
   	for (int j=1;j<=(2*n-1-(2*i-1))/2;j++)
   	{
   		printf(" ");
	   }
   	for (int j=1;j<=2*i-1;j++)
   	{
   		printf("*");
	   }
	if (i!=n) printf("\n");
   }





  return 0;
}

