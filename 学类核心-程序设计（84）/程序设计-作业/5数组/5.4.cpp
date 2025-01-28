#include<stdio.h>
using namespace std;

long long int max(int a,int b)
{
	if (a>b) return a;
	else return b;
}
int main()
{
    long long int n;
    scanf("%lld",&n);
    long long int x[n+1];
    x[0]=0;
    int sum=0;
    int maxm=0;
    for (int i=1;i<=n;i++)
    {
    	scanf("%lld",&x[i]);
    	if (x[i]>x[i-1]) sum++;
    	else 
    	{
    		maxm=max(sum,maxm);
    		sum=1;
		}
	}
	maxm=max(maxm,sum);
    printf("%d",maxm);




  return 0;
}

