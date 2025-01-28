#include<stdio.h>
using namespace std;

int judge(int x);
int judge(int x)
{
	if (x%12==0) return 1;
	else 
	{
		int count=0;
		int m[100];
		for (;;)
		{	
		    count++;
		    m[count]=x%10;
		    x/=10;
			if (x==0) break;
		}
        for (int i=1;i<=count;i++)
        {
        	if (m[i]==2 && m[i+1]==1) return 1;
		}
	}
	return 0;
}


int main()
{
   int n;
   scanf("%d",&n);
   for (int i=1;i<=n;i++)
   {
   	if (judge(i)==1) printf("%d ",i);
   }
  return 0;
}

