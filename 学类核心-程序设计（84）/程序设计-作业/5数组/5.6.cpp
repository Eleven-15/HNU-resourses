#include<stdio.h>
using namespace std;

int max(int a,int b)
{
	if (a>b) return a;
	else return b; 
}

int main()
{
  int n,maxm=0,temp,ans=0,count=1;
  scanf("%d",&n);
  int x[10000];
  for (int i=0;i<=9999;i++)
  {
  	x[i]=0;
  }
  
  for (int i=1;i<=n;i++)
  {
  	scanf("%d",&temp);
  	x[temp]++;
  	maxm=max(temp,maxm);
  }
  temp=0;
  //printf("%d",maxm);
    //printf("\n");
  for (int i=0;i<=maxm;i++)
  {
  	//printf("%d ",x[i]);
  	if (x[i]>temp)
  	{
  		temp=x[i];   //printf("%d ",temp);
  		ans=i;       //printf("%d ",ans);
  		count=1;    
	  }
	else if (x[i]!=0 && x[i]==temp) count++;
	//printf("%d ",count);
	//printf("\n");
  }
    	//printf("\n %d %d",count,temp);
  if (count==1 && x[ans]>n/2) printf("%d",ans);
  else printf("null"); 
  



  return 0;
}

