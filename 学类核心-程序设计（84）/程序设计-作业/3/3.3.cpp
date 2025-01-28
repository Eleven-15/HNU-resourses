#include<bits/stdc++.h>
using namespace std;
int main()
{
  int sum,s,x;
  char c;
  cin>>s>>c>>x;
  sum=0;
  if (s>=5000) sum++;
  if (c=='y') sum++;
  if  (x<=2000) sum++;
  if (sum>=2) cout<<"Accept";
  else cout<<"Refuse";



  return 0;
}

