#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n],num=0;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if((a[i]-a[i-1])<=0) num++;
	}
	num++;
	int b[num],l=1;
	for(int x=0;x<num-1;x++)
	{
	  for(int y=1;y<n;y++)
	  {
	  	if(y==1) y=l;
	    if((a[y]-a[y-1])<=0)
	    {
	    	b[x]=a[y-1];
	    	l=y+1;
	    	break;
		}
	  }
	}
	b[num-1]=a[n-1];
	cout<<num<<endl;
	for(int s=0;s<num;s++)
	{
		cout<<b[s]<<' ';
	}
	return 0;
}


