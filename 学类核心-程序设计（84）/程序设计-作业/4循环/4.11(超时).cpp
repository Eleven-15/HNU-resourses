#include<stdio.h>
#include<cmath>
using namespace std;

int mobi(int n);
int mobi(int n)
{
	int ou=0,ji=0,temp=0;
	if (n==1) return 1;
	else 
	{
		for (int i=2;;)
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
			if (flag==0)  //iÊÇËØÊý 
			{
				if (n%i==0)
				{
					n=n/i;
					if (temp==i) return 0;
					temp=i;
					if (i%2==0) ou++;
					else ji++;
				}
				else i++;
			}
			if (flag==1) i++;
		}
	}
}

int main()
{
   int n;
   scanf("%d",&n);
   printf("%d",mobi(n));





  return 0;
}

