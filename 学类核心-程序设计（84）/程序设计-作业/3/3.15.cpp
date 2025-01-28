#include<bits/stdc++.h>
#include<iomanip>
using namespace std;
int main()
{
   double x,y;
   cin>>x;
   if (2<x && x<=10) y=x*(x+2);
   if (-1<x && x<=2) y=2*x;
   if (x<=-1) y=x-1;
   cout<<fixed<<setprecision(6)<<y;





  return 0;
}

