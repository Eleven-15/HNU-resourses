#include<stdio.h>
using namespace std;
int judge(int x,int y);
int judge(int x,int y)
{
	int m,n,a,b;
	m=x%10; x=x/10; n=x%10;
	a=y%10; y=y/10; b=y%10;//printf("%d %d %d %d \n",m,n,a,b);
	if (m==7 || n==7 || a==7 || b==7) return 1;
	else return 0;
}
int main()
{
    int x,h,m,count=0;
    scanf("%d",&x);
    scanf("%d %d",&h,&m);
    for (;;)
    {
    	if (judge(h,m)==1) 
    	{
    		printf("%d",count);
    		return 0;
		}
		
		if (m-x>=0) 
		{
			m-=x;
			count++;
		}
		else if (h-1>=0)
		{
			h--;
			m+=60;
			m-=x;
			count++;
		}
		else if (h-1<0)
		{
			h=23;
			m+=60;
			m-=x;
			count++;
		}
		else 
		{
			m-=7;
			count++;
		}
	}




  return 0;
}

