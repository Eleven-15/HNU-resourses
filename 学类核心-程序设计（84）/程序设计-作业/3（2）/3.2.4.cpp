#include<bits/stdc++.h>
using namespace std;
int main()
{
   int n;
   cin>>n;
   if (n<=1) cout<<"*";
   else
   for (int i=1;i<=n;i++)
   {
   	cout<<" ";
   	for (int j=1;j<=n-i;j++) 
   	{
   		cout<<" ";
	   }
	for (int j=1;j<=i;j++)
	{
		cout<<"*"<<" ";
	}
	cout<<endl;
   }





  return 0;
}

