#include<bits/stdc++.h>
using namespace std;
int main()
{
   int a[10];
   int temp;
   for (int i=1;i<=4;i++)
   {
   	cin>>a[i];
   }
   for (int i=1;i<=4;i++)
   {
   	for (int j=4;j>i;j--)
   	{
   		if (a[j-1]<a[j])
   		{
   			temp=a[j-1];
   			a[j-1]=a[j];
   			a[j]=temp;
		   }
	   }
   }
    for (int i=1;i<=4;i++)
   {
   	cout<<a[i]<<" ";
   }




  return 0;
}

