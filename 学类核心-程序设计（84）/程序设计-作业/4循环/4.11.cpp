#include<stdio.h>
#include<cmath>
using namespace std;

int mobi(int n);
int mobi(int n)
{
	int temp=0,count=0,sum=0;
	int x[10000];
	if (n==1) return 1;
	else 
	{
        for (int i=2;i<=n;i++)
        {
        	int flag=0;
        	for (int j=2;j<=sqrt(i);j++)
        	{
        		if (i%j==0)
        		{
        			flag=1;
        			break;
				}
			}
			if (flag==0) 
			{
				count++;
				x[count]=i;
				if (n==i) return -1;
			}
		}//´òÓ¡ËØÊý 
		//for (int i=1;i<=count;i++) printf("%d ",x[i]);
		//printf("\n");
		
		for (int i=1;i<=count;)
		{
			//printf("%d %d   ",i,n);
				if (n%x[i]==0)
				{
					n=n/x[i];
					if (temp==x[i]) return 0;
					temp=x[i];
					//printf("%d \n",temp);
					sum++;
				}
				else i++;

		}
		if (sum%2==0) return 1;
		else return -1;
	}
}

int main()
{
   int n;
   scanf("%d",&n);
   printf("%d",mobi(n));





  return 0;
}

