#include<bits/stdc++.h>
using namespace std;
int main()
{
  int n;
  int a[10];
  string b[10]={"0","mi","yd","ft","in"};
  cin>>n;
  a[1]=n/(1760*3*12);
  a[2]=(n%(1760*3*12))/(3*12);
  a[3]=((n%(1760*3*12))%(3*12))/12;
  a[4]=((n%(1760*3*12))%(3*12))%12;
  for (int i=1;i<=4;i++)
  {
  	if (a[i]!=0) {
  		cout<<a[i]<<" "<<b[i]<<" ";
	  }
  }




  return 0;
}

