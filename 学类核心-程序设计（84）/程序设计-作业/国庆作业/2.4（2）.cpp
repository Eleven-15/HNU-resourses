#include<bits/stdc++.h>
using namespace std; 
int main()
{ 
 int a,b,c,d,e,f,g,h,i,j,k,l; 
  char ch; 
  cin>>a>>ch>>b>>ch>>c>>d>>ch>>e>>ch>>f; 
  g=a*3600+b*60+c;  
  h=d*3600+e*60+f; 
  i=h-g;         
  j=i/3600,l=i%60,k=(i-3600*j-l)/60;
  cout<<j<<":";   
  cout<<setw(2)<<setfill('0')<<k<<":";  
  cout<<setw(2)<<setfill('0')<<l;
  return 0; 
}

