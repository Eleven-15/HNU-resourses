#include<bits/stdc++.h>
using namespace std;
int main()
{
  long long int s,m,k,u;
  cin>>s>>m;
  s=s-5000-m;
  if (s<0) cout<<"0";
  else{ 
  if (s<=3000){k=3;u=0;}
  if (s>3000 && s<=12000){k=10;u=210;}
  if (s>12000 && s<=25000){k=20;u=1410;}
  if (s>25000 && s<=35000){k=25;u=2660;}
  if (s>35000 && s<=55000){k=30;u=4410;}
  if (s>55000 && s<=80000){k=35;u=7160;}
  if (s>80000){k=45;u=15160;}
  s=s*(double(k)/100.0)-u;
  cout<<s;
}



  return 0;
}

