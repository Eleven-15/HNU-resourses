#include<stdio.h>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    int x[T+1];
    for (int i=1;i<=T+1;i++)
    {
    	x[i]=0;
	}
    for (int i=1;i<=T;i++)
    {
    	int a,b,sa=0,sb=0;
    	scanf("%d %d",&a,&b);
    	bool flag=0;
		for(int j=1;1;j++)
		{
			if (flag==0) {
				sa+=j;
			}
			else sb+=j;
			if (flag==0 && sa>a) 
			{
				x[i]=0;
				break;
			}
			else if (flag==1 && sb>b) 
			{
				x[i]=1;
				break;
			}
			flag=!flag;
		}
	}
   for (int i=1;i<=T;i++)
   {
   	if (x[i]==0)  printf("Bob\n");
   	else if (x[i]==1) printf("Limak\n") ;
   }




  return 0;
}

