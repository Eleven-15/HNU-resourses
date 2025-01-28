#include<bits/stdc++.h>
using namespace std;
int main()
{
   int w,now=1;
   cin>>w;
   int x[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
   for (int i=1;i<=12;i++)
   {
      while (now<=x[i]) 
      {
      	now++;
      	w++;
      	if (w>7) w-=7;
      	if (now==13 && w==5) cout<<i<<" ";
	  };
	  now=1;
   };





  return 0;
}

