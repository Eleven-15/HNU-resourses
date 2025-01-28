#include<bits/stdc++.h>
using namespace std;
int main()
{
   int x[5];
   int a,b,c;
   for (int i=1;i<=4;i++)
   {
   	cin>>x[i];
   }
   for (int i=1;i<=4;i++)
   {
   	for (int j=4;j>i;j--)
   	{
   		if (x[j-1]<x[j])
   		{
   			int temp=0;
   			temp=x[j-1];
   			x[j-1]=x[j];
   			x[j]=temp;
		   }
	   }
   }
   a=x[1]-x[2];
   b=x[1]-x[3];
   c=x[1]-x[4];
   x[2]=a;
   x[3]=b;
   x[4]=c;
    for (int i=2;i<=4;i++)
   {
   	for (int j=4;j>i;j--)
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
   for (int i=2;i<=4;i++)
   {
   	cout<<x[i]<<" ";
   }

  return 0;
}

