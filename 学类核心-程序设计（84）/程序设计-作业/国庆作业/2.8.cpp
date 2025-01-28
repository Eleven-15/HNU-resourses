#include<bits/stdc++.h>
using namespace std;
int main()
{
  long long int k,w,n,s,ans;
  cin>>k>>n>>w;
  s=0;
  for (int i=1;i<=w;i++)
  {
  	s+=i*k;
  }
  if (s-n<0) { ans=0; }
  else { ans=s-n;}
  cout<<ans<<endl;




  return 0;
}

