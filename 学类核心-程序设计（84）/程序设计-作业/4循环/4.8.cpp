#include<stdio.h>
using namespace std;

int cal(int a,int b);
int cal(int a,int b)
{
	if (a<b) return ((b-a)*6+5);
	else return ((a-b)*4+5);
}

int main()
{
    int n,sum=0;
    scanf("%d",&n);
    int x[n+1];
    x[0]=0;
    for (int i=1;i<=n;i++)
    {
    	scanf("%d",&x[i]);
	}
    for (int i=1;i<=n;i++)
    {
    	sum+=cal(x[i-1],x[i]);
	}
	printf("%d",sum);




  return 0;
}

