#include<bits/stdc++.h>
using namespace std;
int main()
{
     int n,x,y;
     cin>>n>>x>>y;
     for (int i=0;i<=n;i++)
     {
     	for (int j=0;j<=(n-i);j++)
     	{
     		if ((6*i+6*j+8*(n-i-j)==x) && (i+2*j==y))
     		{
     	    	cout<<i<<" "<<j<<" "<<n-i-j; 
     	    	return 0;
			 }
		 }
	 }





  return 0;
}

