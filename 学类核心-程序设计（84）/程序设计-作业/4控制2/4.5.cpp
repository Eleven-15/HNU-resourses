#include<stdio.h>
using namespace std;
int main()
{
    int n;
    long long int sum=0,now=1;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
    	now*=i;
    	sum+=now;
	}
    printf("%ld",sum);
    




  return 0;
}

