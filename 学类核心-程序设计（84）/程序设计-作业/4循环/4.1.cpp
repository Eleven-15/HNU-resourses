#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,sum=0,u=1;
   cin>>n;
   for (int i=1;i<=n;i++)
   {
   	u=(1+i)*i/2; 
   	sum+=u;
   }
    cout<<sum;



  return 0;
}

