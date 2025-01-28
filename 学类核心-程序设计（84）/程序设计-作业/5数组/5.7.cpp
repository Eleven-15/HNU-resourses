#include<stdio.h>
using namespace std;
int main()
{
     int n,temp;
     scanf("%d",&n);
     int x[n+1];
     for (int i=0;i<=n;i++)
     {
     	x[i]=0;
	 }
     for (int i=1;i<=n;i++)
     {
     	scanf("%d",&temp);
     	x[temp]=1;
	 }
	 for (int i=0;i<=n;i++)
	 {
	 	if (x[i]==0) 
	 	{
	 		printf("%d",i);
	 		break;
		 }
	 }




  return 0;
}

