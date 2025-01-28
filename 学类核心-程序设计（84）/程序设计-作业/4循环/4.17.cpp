#include<stdio.h>
using namespace std;
int main()
{
    int n,now,stand,sum;
    scanf("%d",&n);
    now=0; stand=1;
    for (int i=1;i<=n;i++)
    {
    	now++;		
    	sum+=stand;
    	if (now==stand) 
    	{
    		now=0;
    		stand++;
        } 
	}
	printf("%d",sum);





  return 0;
}

