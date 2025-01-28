#include<stdio.h>
#include<cmath>
using namespace std;

bool sushu(int x);
bool sushu(int x)
{
	for (int i=1;i<=sqrt(x);i++)
	{
		if (i!=1 && x%i==0) return 0;
	}
	return 1;
	
}

int main()
{
    int n,t=0;
    scanf("%d",&n);
    if (n==1) printf("null");
    else
    {
    for (int i=2;i<=n;i++)
    {
    	if (sushu(i)) 
    	{
    		printf("%d ",i);
    		t++;
		}
		if (t==10) 
		{
			printf("\n");
			t=0;
		}
    	
	}
}




  return 0;
}

