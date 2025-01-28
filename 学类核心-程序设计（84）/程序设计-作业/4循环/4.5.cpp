#include<bits/stdc++.h>
using namespace std;
int main()
{
   int n,m,temp,sum,flag,now;
   sum=0;
   cin>>n>>m;
   if (n==1) cout<<1;
   else{
   for (int i=1;i<=m;i++)
   {
   	 cin>>temp;
   	 sum+=temp;
   }
   flag=0;//ÏòÓÒ 
   now=1;
   for (int i=sum;i>=1;i--)
   {
   	if (flag==0 && ((now+1)<=n) )now++;
   	else if (flag==0 && ((now+1)>n) )
   	{
   		flag=1;
   		now--;
	   }
   	else if (flag==1 && ((now-1)>=1) )now--;
   	else if (flag==1 && ((now-1)<1) )
   	{
   		flag=0;
   		now++;
	   }
   }
   cout<<now;
}
  return 0;
}

