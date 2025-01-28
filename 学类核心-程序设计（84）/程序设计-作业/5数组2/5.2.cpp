#include<iostream>
#include<cstring>
using namespace std;
int main()
{
   int n,L,a;
   cin>>n>>L>>a;
   int *t=new int[n];
   int *l=new int[n];
   int *x=new int[L+1];
   memset((void *)x,0,sizeof(int)*(L+1));
   for (int i=0;i<=n-1;i++)
   {
   	cin>>t[i]>>l[i];
   	for (int j=0;j<=l[i]-1;j++)
   	{
   		x[t[i]+j]=1;
	   }
   }
   int temp=0,sum=0;
   for (int now=0;now<=L-1;now++)
   {
   	 if (x[now]==0) temp++;
   	 else if (x[now]==1) temp=0;
   	 if (temp==a) 
   	 {
   	 	temp=0;
   	 	sum++;
		}
   }
   cout<<sum;
   




  return 0;
}

