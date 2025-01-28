#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int main()
{
  long int sum[4],s[4],x[4];
  char c[4];
  char u[4]={'0','A','B','C'};
  for (int i=1;i<=3;i++)
  {
  	  cin>>s[i]>>c[i]>>x[i];
  	  sum[i]=0;
  	  sum[i]+=floor(s[i]/5000*100);
      if (c[i]=='y') sum[i]+=20;
      if  (x[i]<=2000) sum[i]+=100;
      else sum[i]+=max(0,100-10*int(ceil(((double(x[i])-2000.0)/200.0))));
  }
   for (int i=1;i<=3;i++)
   {
   	for (int j=3;j>i;j--)
	   {
	   	if (sum[j-1]<sum[j])
	   	{
		   int temp=0;
		   char t;
		   temp=sum[j-1];
		   sum[j-1]=sum[j];
		   sum[j]=temp;
		   t=u[j-1];
		   u[j-1]=u[j];
		   u[j]=t;
		   }
	   }
   }
   cout<<u[1];

  return 0;
}

