#include<bits/stdc++.h>
using namespace std;
int main()
{
   int n,m;
   cin>>m>>n;
   if (n>=250 && n<500) n*=(1-0.02);
   if (n>=500 && n<1000) n*=(1-0.05);
   if (n>=1000 && n<2000) n*=(1-0.08);
   if (n>=2000 && n<3000) n*=(1-0.10);
   if (n>=3000) n*=(1-0.15);
   n*=m;
   cout<<n;

  return 0;
}

