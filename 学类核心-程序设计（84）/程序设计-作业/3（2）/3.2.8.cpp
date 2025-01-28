#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
  cin>>n;
  for (int a=1;a<=9;a++)
    for (int b=0;b<=9;b++)
      for (int c=0;c<=9;c++)
      {
      	int m;
      	m=a*100+(b+c)*2*100+b*10+(c+a)*2*10+c+(a+b)*2;
      	if (m==n) cout<<a<<b<<c;
	  }
  





  return 0;
}

