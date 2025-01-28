#include<bits/stdc++.h>
using namespace std;
int main()
{
  int a,b,c,x,y,z,m,n,p;
  char ch;
  cin>>a>>ch>>b>>ch>>c>>x>>ch>>y>>ch>>z;
  if (z>=c) {p=z-c;}
  else if (y>=b) {y--;z+=60;p=z-c;}
  else{x--;y+=60;n=y-b;y--;z+=60;p=z-c;}
  if (y>=b){n=y-b;}
  else {x--;y+=60;n=y-b;};
  m=x-a;
  cout<<m<<":"<<n<<":"<<p;

  return 0;
}

