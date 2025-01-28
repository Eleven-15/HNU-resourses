#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x,y,m;
  cin>>n>>x>>y;
  if (y%x==0) 
  {
   m=n-y/x;
  }
  else {
  	m=n-y/x-1;
  }
  if (m<0) m=0;
   cout<<m;




  return 0;
}

