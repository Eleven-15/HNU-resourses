#include<stdio.h>
#include<cmath>
using namespace std;

int caile(int y,int m,int d);
int runnian(int n);

int caile(int y,int m,int d)
{
   int c,D,W;
   c=y/100;
   y=y%100;
   if (m<=2) 
   {
   	if (y==0)
   	{
   		y=100;
   		c-=1;
	   }
	   	   	m+=12;
        	y-=1;
   }
   D=floor(c/4)-2*c+y+floor(y/4)+floor(13*(m+1)/5)+d-1;
   while(D<7)
   {
   	 D+=7;
   }
   W=D%7;
   if (W==0) W=7;
   printf("%d %d %d %d %d\n",W,c,y,m,d);
   return W;
   
   
}

int runnian(int n)
{
	if (n%400==0) return 1;
	else if (n%100!=0 && n%4==0) return 1;
	else return 0;
}
int main()
{
    int t,y,m,d,x;
    scanf("%d",&t);
    int ans[t+1];
    for (int i=1;i<=t;i++)
    {
    	scanf("%d-%d-%d",&y,&m,&d);
    	//printf("%d-%d-%d",y,m,d);
    	x=caile(y,m,d);
		if (m==2 && d==29)
		{
			for (int j=y+4;;j+=4)
    	{
    		
    		if (x==caile(j,m,d) && runnian(j)==1) 
    		{
    			ans[i]=j;
    			break;
			}
    		//printf("%d %d\n",j,caile(j,m,d));
		}                                        //有两个点是闰年来卡人的； 
		}
		else
    	for (int j=y+1;;j++)
    	{
    		
    		if (x==caile(j,m,d)) 
    		{
    			ans[i]=j;
    			break;
			}
    		//printf("%d %d\n",j,caile(j,m,d));
		}
	}

    for (int i=1;i<=t;i++) printf("%d\n",ans[i]);


  return 0;
}

