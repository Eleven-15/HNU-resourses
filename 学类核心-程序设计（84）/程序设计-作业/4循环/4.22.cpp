#include<stdio.h>
using namespace std;

void empt(int x[]);
void func(long long int x,int xm[]);

void empt(int x[])
{
	for (int i=1;i<=32;i++)
	x[i]=0;
}
void func(long long int x,int xm[])
{
	int count=0;
	for (;;)
	{
		count++;
		xm[count]=x%2;
		x=x/2;
		if (x==0) break;
	}
}

int main()
{
    long long int x,y;
    int sum=0;
	int xm[35],ym[35];
	scanf("%lld %lld",&x,&y);
	//printf("%lld %lld",x,y);
	empt(xm);
	empt(ym);
    func(x,xm);
    func(y,ym);
    /* 
    for (int i=1;i<=32;i++)
    printf("%d",xm[i]);
      printf("\n");
        for (int i=1;i<=32;i++)
    printf("%d",ym[i]);
      printf("\n");
      */
    for (int i=1;i<=32;i++)
      {
      	if (xm[i]!=ym[i])
      	{
      		 sum++;
      		 //printf("%d %d\n",xm[i],ym[i]);
		  }
	  }
	  //printf("\n");
	  printf("%d",sum);
   



  return 0;
}

