#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long int x[101];
	int n;
   cin>>n;
   for (int i=1;i<=n;i++)
   {
   	cin>>x[i];
   }
   for (int i=1;i<=n;i++)
   {
   	for (int j=n;j>i;j--)
   	{
       if (x[j-1]>x[j])
       {
       	int temp=0;
       	temp=x[j-1];
       	x[j-1]=x[j];
       	x[j]=temp;
	   }
	   }
   }
   cout<<x[1];





  return 0;
}

