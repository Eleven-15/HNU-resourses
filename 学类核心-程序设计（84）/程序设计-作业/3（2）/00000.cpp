#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int x[100];
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>x[i];
	}
  for (int i=1;i<=n;i++)
  {
  	for (int j=n;j>i;j--)
  	if (x[j-1]<x[j])
  	{
  		int temp=x[j-1];
  		x[j-1]=x[j];
  		x[j]=temp;
	  }
	for (int i=1;i<=n;i++)
	{
		cout<<x[i]<<" ";
	}
	cout<<endl;
  }




  return 0;
}

