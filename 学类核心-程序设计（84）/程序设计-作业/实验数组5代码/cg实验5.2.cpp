#include<iostream>
using namespace std;
int main()
{
 int n,l,x,i,t=0;
 cin>>n>>l>>x;
 int a[n+1][3];
 for(i=1;i<=n;i++)
 {
     cin>>a[i][1]>>a[i][2];
 } 
 if(a[1][1]>=x)t+=a[1][1]/x;
 for(i=1;i<=n-1;i++)
 {
  if(a[i+1][1]-a[i][1]-a[i][2]>=x)t+=(a[i+1][1]-a[i][1]-a[i][2])/x;
 }
 if(l-a[n][1]-a[n][2]>=x)t+=(l-a[n][1]-a[n][2])/x;
 cout<<t;
 return 0;
 } 
